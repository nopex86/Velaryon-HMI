#ifndef EXPORTMENU_H
#define EXPORTMENU_H

#include <QAction>
#include <QMenu>
#include <QFileDialog>
#include "ExportMenuViewModel.h"

class ExportMenu : public QMenu{
    Q_OBJECT
private :
    ExportMenuViewModel* m_exportMenuVM;
public :
    explicit ExportMenu(
        ExportMenuViewModel* exportMenuVM,
        QWidget* parent = nullptr) :
        QMenu("&Export", parent), m_exportMenuVM(exportMenuVM)
    {
        connect(m_exportMenuVM, &ExportMenuViewModel::requestFileDialogWindow,
                this, &ExportMenu::onFileDialogWindowRequested);
        connect(this, &QMenu::aboutToShow, this, &ExportMenu::onMenuAboutToShow);
    }
    void onMenuAboutToShow() {
        clear();
        QStringList files = m_exportMenuVM->getFileList();
        for (QString file : files){
            addFile(file);
        }
    }
    void addFile(const QString& name){
        QMenu* menu = new QMenu("&" + name, this);
        addMenu(menu);
        QAction* action = menu->addAction("&CSV");
        connect(action, &QAction::triggered, this, [this, name]{
            m_exportMenuVM->selectFile(name);
            m_exportMenuVM->selectAction(ExportFormat::CSV);
        });
    }
public slots :
    void onFileDialogWindowRequested(const QString& fileName){
        const QString dirPath = QFileDialog::getSaveFileName(
            this,
            "Chose folder",
            QDir::homePath() + "/" + fileName);
        m_exportMenuVM->selectPath(dirPath);
    }
};

#endif // EXPORTMENU_H
