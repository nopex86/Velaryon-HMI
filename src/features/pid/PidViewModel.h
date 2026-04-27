#ifndef PidVIEWMODEL_H
#define PidVIEWMODEL_H

#include <QObject>

class TestBenchModel;

class PidViewModel : public QObject{
    Q_OBJECT
public :
    explicit PidViewModel(
        TestBenchModel* testBenchM,
        QObject* parent = nullptr);
    bool pidIsLocked();
private :
    TestBenchModel* m_testBenchM = nullptr;
    bool m_pidIsLocked = false;
public slots :
    void onTestStateChanged();
signals :
    void PidStateChanged();
};

#endif // PidVIEWMODEL_H
