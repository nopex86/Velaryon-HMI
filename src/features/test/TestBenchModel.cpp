#include "TestBenchModel.h"
#include "src/features/communication/udp/UdpChannel.h"

TestBenchModel::TestBenchModel(UdpChannel* udpChannel, QObject* parent) :
    QObject(parent), m_udpChannel(udpChannel)
{
    connect(m_udpChannel, &UdpChannel::StatesListReceived,
            this , &TestBenchModel::onStatesListRecieved);
}
void TestBenchModel::setTestStatus(const TESTSTATUS& status){
    m_testStatus = status;
    emit testStatusChanged();
}
TestBenchModel::TESTSTATUS TestBenchModel::getTestStatus(){
    return m_testStatus;
}
void TestBenchModel::onStatesListRecieved(const TestBenchStatesList& list){
    if (!m_testStatusInitialised) m_testStatusInitialised = true;
    m_states = list;
    emit statesListChanged();
}

bool TestBenchModel::getStatus(const std::string& name, double* value){
    if (!m_testStatusInitialised) return false;
    if (!m_states.getValue<double>(name, value)) {
        qWarning() << "No data for" << name;
        return false;
    }
    return true;
}
bool TestBenchModel::getStatus(const size_t& ID, double* value){
    if (!m_testStatusInitialised) return false;
    if (!m_states.getValue<double>(ID, value)) {
        qWarning() << "ID is incorrect : " << ID;
        return false;
    }
    return true;
}
bool TestBenchModel::getStatusID(const std::string& name, size_t* ID){
    if (!m_testStatusInitialised) return false;
    if (!m_states.getID(name, ID)) {
        qWarning() << "No ID for" << name;
        return false;
    }
    return true;
}
