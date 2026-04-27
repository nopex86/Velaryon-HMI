#include "CsvExporter.h"
#include <QFileInfo>
#include <QDir>
#include <fstream>
#include "src/features/communication/udp/codecs/UdpCodec.h"
#include "src/features/communication/udp/UdpChannel.h"
#include <QByteArray>

struct BdfHeader {
    char magic[4];        // "BDF\0"
    std::int32_t frameSize;
    std::uint32_t frameQty;

};

CSVLogger::CSVLogger(UdpChannel* udpChannel, QObject* parent) :
    QObject(parent), m_udpChannel(udpChannel)
{
    m_topics = {"ID","time","PS11","PS12","PS21","PS22","PS31","PS41","PS42","PS51","PS61","PS62","PS63","PS64",
                "TS11","TS12","TS41","TS42","TS61","TS62","FM11","FM21","FM61","LC","ref5V", "gpTension","SV11","SV12","SV13"
                ,"SV21","SV22","SV24","SV25","SV31","SV32","SV33","SV34","SV35","SV36","SV51","SV52","SV53"
                ,"SV61","SV62","SV63","SV71","GlowPlug","actLPos","actRPos","actLOK","actROK","state","test_step"};
}

static bool readExact(std::istream& in, void* dst, std::size_t n) {
    in.read(reinterpret_cast<char*>(dst), static_cast<std::streamsize>(n));
    return in.good();
}

bool CSVLogger::logFile(const std::string& outputPath,
                        const std::string& inputPath){
    m_udpChannel->stopEndpoint();
    std::ifstream in(inputPath, std::ios::binary);
    if (!in) {
        qDebug() << "Erreur: impossible d'ouvrir " << inputPath;
        return false;
    }

    BdfHeader h{};
    if (!readExact(in, &h, sizeof(BdfHeader))) {
        qDebug() << "Erreur: lecture header impossible";
        return false;
    }

    // Vérif "BDF"
    if (!(h.magic[0] == 'B' && h.magic[1] == 'D' && h.magic[2] == 'F')) {
        qDebug() << "Erreur: magic invalide (pas un .bdf attendu)";
        return false;
    }
    if (h.frameSize <= 0) {
        qDebug() << "Erreur: frameSize invalide";
        return false;
    }

    std::ofstream out(outputPath);
    if (!out) {
        qDebug() << "Erreur: impossible d'ouvrir " << outputPath;
        return false;
    }

    // En-tête CSV
    for (size_t i = 0; i < m_topics.size(); ++i) {
        if (i != 0){out << ",";}
        out << m_topics[i];
    }
    out << "\n";

    std::vector<std::uint8_t> frame(static_cast<std::size_t>(h.frameSize));

    for (std::uint32_t idx = 0; idx < h.frameQty; ++idx) {
        if (m_udpChannel->running()){
            m_udpChannel->stopEndpoint();
        }

        if (!readExact(in, frame.data(), frame.size())) {
            qDebug() << "Erreur: fichier tronque (frame " << idx << ")";
            return false;
        }

        QByteArray ba(reinterpret_cast<const char*>(frame.data()),
                      static_cast<int>(frame.size()));

        auto decoded = ProtocolCodec::decode(ba);
        if (!decoded)
            return false;

        auto res = std::visit([](const auto& msg) -> std::optional<TestBenchStatesList>{
            using T = std::decay_t<decltype(msg)>;

            if constexpr (std::is_same_v<T, TestBenchStatesList>) {
                return msg; // copie dans l'optional
            } else {
                qDebug() << "Erreur : message inattendu";
                return std::nullopt;
            }
        }, *decoded);

        if (!res) {
            return false;
        }

        for (size_t i = 0; i < m_topics.size(); ++i) {
            if (i != 0){out << ",";}

            double v;
            if (res->getValue<double>(m_topics[i], &v)){
                out << v;
            }
            else {
                out << "no data";
            }
        }
        out << "\n";
    }
    m_udpChannel->startEndpoint();
    return true;
}

// void CSVLogger::logFile(const std::string& path) {
//     QString filepath = QString::fromStdString(path);

//     // Look for filepath
//     QFileInfo fileInfo{};
//     QDir dir = fileInfo.absoluteDir();

//     // Create a file
//     QFile file(filepath);
//     bool writeHeader = !file.exists();

//     // Open file in append mode and write only
//     if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
//         QTextStream out(&file);

//     // Writte header if the file is empty
//     if (writeHeader) {
//         out << "ID,time,PS11,PS12,PS21,PS22,PS31,PS41,PS42,PS51,PS61,PS62,PS63,PS64,"
//                 "TS11,TS12,TS41,TS42,TS61,TS62,FM11,FM21,FM61,LC,ref5V,valvesState,"
//                 "actLPos,actRPos,actLOK,actROK,state,test_step\n";
//      }

//     // Write data in csv
//     for (const QString &line : buffer) {
//         out << line << "\n";
//     }

//      // Clear buffer and close file
//     buffer.clear();
//     file.close();
//     } else {
//         qDebug() << "Failed to open CSV file for flushing.";
//     }
// }

// // Add a line of data to a CSV
// void UdpReceiver::logVectorToCSV(const QVector<QVariant> &dataVector, QStringList &buffer, QMutex &mutex) {
//     QString line;
//     QTextStream out(&line);

//     // Transform array to one single string
//     for (int i = 0; i < dataVector.size(); ++i) {
//         out << dataVector[i].toString();
//         if (i < dataVector.size() - 1) out << ",";
//     }

//     // Send the string to the mutex
//     QMutexLocker locker(&mutex);
//     buffer.append(line);
// }

// #include <cstdint>
// #include <fstream>
// #include <iostream>
// #include <string>
// #include <vector>

// struct BdfHeader {
//     char magic[4];        // "BDF\0"
//     std::int32_t frameSize;
//     std::uint32_t frameQty;
// };

// static bool readExact(std::istream& in, void* dst, std::size_t n) {
//     in.read(reinterpret_cast<char*>(dst), static_cast<std::streamsize>(n));
//     return in.good();
// }

// int main(int argc, char** argv) {
//     if (argc < 3) {
//         qDebug() << "Usage: " << argv[0]
//                   << " input.bdf output.csv [--hex]\n";
//         return 2;
//     }

//     const std::string inputPath = argv[1];
//     const std::string outputPath = argv[2];
//     const bool hexOutput = (argc >= 4 && std::string(argv[3]) == "--hex");

//     std::ifstream in(inputPath, std::ios::binary);
//     if (!in) {
//         qDebug() << "Erreur: impossible d'ouvrir " << inputPath << "\n";
//         return false;
//     }

//     BdfHeader h{};
//     if (!readExact(in, &h, sizeof(BdfHeader))) {
//         qDebug() << "Erreur: lecture header impossible.\n";
//         return false;
//     }

//     // Vérif "BDF"
//     if (!(h.magic[0] == 'B' && h.magic[1] == 'D' && h.magic[2] == 'F')) {
//         qDebug() << "Erreur: magic invalide (pas un .bdf attendu).\n";
//         return false;
//     }
//     if (h.frameSize <= 0) {
//         qDebug() << "Erreur: frameSize invalide.\n";
//         return false;
//     }

//     std::ofstream out(outputPath);
//     if (!out) {
//         qDebug() << "Erreur: impossible d'ouvrir " << outputPath << "\n";
//         return false;
//     }

//     // En-tête CSV
//     out << "frame_index";
//     for (int i = 0; i < h.frameSize; ++i) {
//         out << ",b" << i;
//     }
//     out << "\n";

//     std::vector<std::uint8_t> frame(static_cast<std::size_t>(h.frameSize));

//     for (std::uint32_t idx = 0; idx < h.frameQty; ++idx) {
//         if (!readExact(in, frame.data(), frame.size())) {
//             qDebug() << "Erreur: fichier tronque (frame " << idx << ").\n";
//             return false;
//         }

//         out << idx;
//         for (int i = 0; i < h.frameSize; ++i) {
//             const auto v = static_cast<unsigned int>(frame[static_cast<size_t>(i)]);
//             if (hexOutput) {
//                 // format 0x00..0xFF
//                 static const char* hex = "0123456789ABCDEF";
//                 out << ",0x" << hex[(v >> 4) & 0xF] << hex[v & 0xF];
//             } else {
//                 out << "," << v; // 0..255
//             }
//         }
//         out << "\n";
//     }

//     return 0;
// }

// // Global log file paths with timestamp
// QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
// QString filepath_log = QString("output_data/test_%1/log%1.txt").arg(timestamp);
// QString filepath_csv = QString("output_data/test_%1/data_%1.csv").arg(timestamp);
// QString filepath_csv_HF = QString("output_data/test_%1/data_HF_%1.csv").arg(timestamp);

// // Lock mutex & log data in "main" csv
// QMutexLocker locker1(&queueMutex);
// latestData = data;
// // logVectorToCSV(latestData, csvBuffer, csvMutex);

// // Log in HF csv if time difference between two packets exceeds threshold
// quint32 timeDiff = timing - previousTiming;
// if (timeDiff < 20) {    // Threshold for HF logging (f>50Hz)
//     // logVectorToCSV(latestData, csvBuffer2, csvMutex2);
// }

// // Timer to flush buffered CSV data to file
// flushTimer = new QTimer(this);
// connect(flushTimer, &QTimer::timeout, this, &UdpReceiver::flushAllCsvBuffers);
// flushTimer->start(50);  // Flush every 50 ms

// // Timer to process latest sensor data
// processTimer = new QTimer(this);
// connect(processTimer, &QTimer::timeout, this, &UdpReceiver::processQueuedData);
// processTimer->start(50); // Process every 50ms
