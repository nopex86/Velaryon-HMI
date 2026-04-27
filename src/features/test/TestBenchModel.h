#ifndef TESTBENCHMODEL_H
#define TESTBENCHMODEL_H

#include <QObject>
#include <string>
#include "src/core/Protocols/Messages.h"

class UdpChannel;


class TestBenchModel : public QObject{
    Q_OBJECT
public :
    enum TESTSTATUS{ONGOING, STOPPED};
    explicit TestBenchModel(UdpChannel* udpChannel, QObject* parent = nullptr);
    void setTestStatus(const TESTSTATUS& testState);
    TESTSTATUS getTestStatus();
    bool getStatus(const std::string& name, double* value);
    bool getStatus(const size_t& ID, double* value);
    bool getStatusID(const std::string& name, size_t* ID);
private :
    TestBenchStatesList m_states;
    UdpChannel* m_udpChannel;
    TESTSTATUS m_testStatus = STOPPED;
    bool m_testStatusInitialised = false;
public slots :
    void onStatesListRecieved(const TestBenchStatesList& list);
signals :
    void statesListChanged();
    void testStatusChanged();
};

#endif // TESTBENCHMODEL_H
