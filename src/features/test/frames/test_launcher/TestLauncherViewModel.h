#ifndef TESTLAUNCHERVIEWMODEL_H
#define TESTLAUNCHERVIEWMODEL_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QObject>
#include "src/core/Protocols/Messages.h"

class TxtParser;
class UdpChannel;
class TestBenchModel;


class TestLauncherViewModel: public QObject{
    Q_OBJECT
public :
    explicit TestLauncherViewModel(
        UdpChannel* udpChannel,
        TxtParser* txtParser,
        TestBenchModel* testBenchM,
        QObject* parent);

    QString selectedFile();
    QStringList fileList();
    QString fileDirPath();
    SequenceParameters sequenceParameters();

    void initialise();
    void acquireFileList();

    void confirmLaunch();
private :
    UdpChannel* m_udpChannel = nullptr;
    TxtParser* m_txtParser = nullptr;
    TestBenchModel* m_testBenchM = nullptr;

    QString m_selectedFile;
    QStringList m_fileList;
    QString m_fileDirPath = "./sequences";
    SequenceParameters m_sequenceParameters;

    bool m_isBrowsingRequested = false;

    bool m_isConfirmationRequested = false;
public slots :
    void selectFile(const QString& file);
    void changeDirPath(const QString& path);
    void requestBrowse();
    void onFileParsed(
        const SequenceParameters& parameters);

    void launchTest();
    void onLaunchConfirmed(const ControlEvent& event);
signals:
    void selectedFileChanged();
    void fileListChanged();
    void fileDirPathChanged();
    void sequenceParametersChanged();
    void browsingRequested();

    void confirmationRequested();
};


#endif // TESTLAUNCHERVIEWMODEL_H
