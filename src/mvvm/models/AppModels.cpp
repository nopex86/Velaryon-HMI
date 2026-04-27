#include "AppModels.h"
#include "src/features/test/TestBenchModel.h"
#include "src/features/test/frames/tank_pressure/PressureTanksModel.h"
#include "src/services/AppServices.h"
#include "src/features/communication/udp/UdpChannel.h"

AppModels::AppModels(AppServices* appM, QObject* parent) : QObject(parent) {
    UdpChannel* udpChannel = appM->create<UdpChannel>();
    TestBenchModel* testBenchM = new TestBenchModel(udpChannel, this);
    registerFactory<TestBenchModel>([testBenchM](QObject*){
        return testBenchM;
    });

    PressureTanksModel* pressureTankM = new PressureTanksModel(this);
    registerFactory<PressureTanksModel>([pressureTankM](QObject*){
        return pressureTankM;
    });
}



