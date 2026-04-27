#include "PidViewModel.h"
#include "src/features/test/TestBenchModel.h"

PidViewModel::PidViewModel(
    TestBenchModel* testBenchM,
    QObject* parent) :
    QObject(parent){
    m_testBenchM = testBenchM;
}

bool PidViewModel::pidIsLocked(){
    return m_pidIsLocked;
}

void PidViewModel::onTestStateChanged(){
    if (m_testBenchM->getTestStatus() == TestBenchModel::TESTSTATUS::ONGOING){
        emit PidStateChanged();
    }
    else {
        emit PidStateChanged();
    }
}
