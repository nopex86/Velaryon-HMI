#pragma once
#include <QObject>
#include <QDir>
#include "src/features/file_export/csv/CsvExporter.h"
#include "src/services/FileSystem/FileSystem.h"

enum class ExportFormat{CSV};
class ExportMenuViewModel : public QObject{
    Q_OBJECT
private:
    FileSystem* m_fileSystem;
    ExportFormat m_action;
    CSVLogger* m_csvLogger;
    QStringList m_fileList;
    QString m_selectedFile;
public :
    ExportMenuViewModel(
        FileSystem* fileSystem,
        CSVLogger* csvLogger,
        QObject* parent = nullptr):
        QObject(parent), m_fileSystem(fileSystem),
        m_csvLogger(csvLogger){}
    QString getSelectedFile(){return m_selectedFile;}
    void selectAction(ExportFormat action){
        m_action = action;
        QString fileName = m_selectedFile;
        if (m_action == ExportFormat::CSV){
            fileName.replace(".bdf", ".csv");
            emit requestFileDialogWindow(fileName);
        }
    }
    void selectFile(const QString& file){
        m_selectedFile = file;
    }
    void selectPath(QString path){
        std::string logfilePath;
        m_fileSystem->getDirectory("statesDatas", &logfilePath);
        if (m_action == ExportFormat::CSV){
            m_csvLogger->logFile(path.toStdString(),
                                 logfilePath + "/" + m_selectedFile.toStdString());
        }
    }
    QStringList getFileList(){
        std::string path;
        m_fileSystem->getDirectory("statesDatas", &path);
        const QStringList files = QDir(QString::fromStdString(path)).entryList(
            QStringList() << "*.bdf",
            QDir::Files | QDir::NoSymLinks,
            QDir::Name);
        m_fileList = files;
        return m_fileList;
    }

signals :
    void requestFileDialogWindow(const QString& fileName);
};
