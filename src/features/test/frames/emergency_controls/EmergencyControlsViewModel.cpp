#include "EmergencyControlsViewModel.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "../../TestBenchModel.h"

EmergencyControlsViewModel::EmergencyControlsViewModel(
    UdpChannel* udpChannel,
    TestBenchModel* testBenchM,
    QObject* parent) :
    QObject(parent){
    m_udpChannel = udpChannel;
    m_testBenchM = testBenchM;
}
void EmergencyControlsViewModel::onTestAbortion(){
    TestAbortionCommand command;
    m_udpChannel->sendData(command);
    m_testBenchM->setTestStatus(TestBenchModel::TESTSTATUS::STOPPED);
}
