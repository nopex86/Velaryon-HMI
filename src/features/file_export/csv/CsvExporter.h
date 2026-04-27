#pragma once

#include <string>
#include <vector>
#include <QObject>

class UdpChannel;

class CSVLogger : public QObject{
    Q_OBJECT
public :
    CSVLogger(UdpChannel* udpChannel, QObject* parent = nullptr);
    bool logFile(const std::string& outputPath,
                 const std::string& inputPath);
    std::vector<std::string> m_topics;
private :
    UdpChannel* m_udpChannel;
};
