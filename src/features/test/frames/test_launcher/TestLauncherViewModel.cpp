#include "TestLauncherViewModel.h"
#include "src/services/TXTManager/TxtParser.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "../../TestBenchModel.h"
#include "src/core/Protocols/Messages.h"
#include <QDir>

TestLauncherViewModel::TestLauncherViewModel(
    UdpChannel* udpChannel,
    TxtParser* txtParser,
    TestBenchModel* testBenchM,
    QObject* parent) :
    QObject(parent){
    m_txtParser = txtParser;
    m_udpChannel = udpChannel;
    m_testBenchM = testBenchM;
    connect(m_txtParser, &TxtParser::FileParsed,
            this, &TestLauncherViewModel::onFileParsed);
    connect(m_udpChannel, &UdpChannel::controlEventReceived,
            this, &TestLauncherViewModel::onLaunchConfirmed);
}

QString TestLauncherViewModel::selectedFile(){
    return m_selectedFile;
}
QStringList TestLauncherViewModel::fileList(){
    return m_fileList;
}
QString TestLauncherViewModel::fileDirPath(){
    return m_fileDirPath;
}
SequenceParameters TestLauncherViewModel::sequenceParameters(){
    return m_sequenceParameters;
}

void TestLauncherViewModel::selectFile(const QString& file){
    m_selectedFile = file;
    emit selectedFileChanged();
    if (!file.isEmpty()){
        m_txtParser->parseFile(m_fileDirPath, file);
    }
}
void TestLauncherViewModel::changeDirPath(const QString& path){
    m_fileDirPath = path;
    emit fileDirPathChanged();
    acquireFileList();
}
void TestLauncherViewModel::requestBrowse(){
    m_isBrowsingRequested = true;
    emit browsingRequested();
}
void TestLauncherViewModel::initialise(){
    acquireFileList();
}

void TestLauncherViewModel::acquireFileList(){
    const QStringList files = QDir(m_fileDirPath).entryList(
        QStringList() << "*.txt"
                      << "*.json",
        QDir::Files | QDir::NoSymLinks,
        QDir::Name);

    m_fileList = files;
    emit fileListChanged();
    selectFile(m_fileList[0]);
}

void TestLauncherViewModel::onFileParsed(
    const SequenceParameters& parameters)
{
    m_sequenceParameters = parameters;
    emit sequenceParametersChanged();
}

void TestLauncherViewModel::launchTest(){
    SequenceCommand command;
    for (
        auto it = m_sequenceParameters.cbegin();
        it != m_sequenceParameters.cend();
        it++){
        command.values.append(std::get<1>(*it));
    }
    m_udpChannel->sendData(command);
    m_isConfirmationRequested = true;
    emit confirmationRequested();
}


void TestLauncherViewModel::confirmLaunch(){
    m_isConfirmationRequested = false;
    TestLauchConfirmation command;
    m_udpChannel->sendData(command);
}

void TestLauncherViewModel::onLaunchConfirmed(const ControlEvent& event){
    if (event.type == ControlEventType::LaunchConfirm){
        m_testBenchM->setTestStatus(TestBenchModel::TESTSTATUS::ONGOING);
    }
}
