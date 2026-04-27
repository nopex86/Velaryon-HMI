#include "AppServices.h"
#include "src/features/communication/udp/UdpChannel.h"
#include "./Logger/Logger.h"
#include "./TXTManager/TxtParser.h"
#include "src/features/file_export/csv/CsvExporter.h"
#include "./FileSystem/FileSystem.h"
#include "./Timer/Timer.h"

AppServices::AppServices(QObject* parent) : QObject(parent){
    FileSystem* fileSystem = new FileSystem(this);
    registerFactory<FileSystem>([fileSystem](QObject*){
        return fileSystem;
    });

    Logger* logger = new Logger(this);
    registerFactory<Logger>([logger](QObject*){
        return logger;
    });

    Timer* timer = new Timer(this);
    registerFactory<Timer>([timer](QObject*){
        return timer;
    });

    UdpChannel* udpChannel = new UdpChannel(fileSystem, logger,this);
    registerFactory<UdpChannel>([udpChannel](QObject*){
        return udpChannel;
    });

    TxtParser * txtParser = new TxtParser(this);
    registerFactory<TxtParser>([txtParser](QObject*){
        return txtParser;
    });

    CSVLogger* csvLogger = new CSVLogger(udpChannel, this);
    registerFactory<CSVLogger>([csvLogger](QObject*){
        return csvLogger;
    });
}
