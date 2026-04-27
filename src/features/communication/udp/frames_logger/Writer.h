#ifndef WRITER_H
#define WRITER_H

#include <cstdint>
#include <fstream>
#include <string>
#include "src/services/Logger/Logger.h"

template<int MAX_FRAME_SIZE, int BUFFER_SIZE>
class Writer{
private:
    using frame = uint8_t[MAX_FRAME_SIZE];
    frame m_writeBuffer[BUFFER_SIZE];

    std::string m_filePath{""};
    int m_framesBufferised{0};

    struct Header{
        char magic[4] = "BDF";
        int frameSize;
        uint32_t frameQty;
    };
    Header m_LogFileHeader;
    Logger* m_logger;
public:
    Writer(Logger* logger) : m_logger(logger){}
    bool initialise(const std::string& path){
        std::ofstream file(path, std::ios::binary);
        if (!file){
            m_logger->error("Frame writer : log file cannot be created\n"
                            "path : " + path);
            return false;
        }

        m_filePath = path;
        m_LogFileHeader.frameSize = MAX_FRAME_SIZE;
        m_LogFileHeader.frameQty = 0;
        m_framesBufferised = 0;
        file.seekp(0);
        file.write(reinterpret_cast<const char*>(&m_LogFileHeader), sizeof(m_LogFileHeader));
        m_logger->debug("Frame writer : successfully initialised.");
        return true;
    };
    bool logFrame(uint8_t data[], int size){
        if (size != MAX_FRAME_SIZE){
            m_logger->error("Frame writer : wrong size of frame pushed ("
                            + std::to_string(size)
                            + " instead of "
                            + std::to_string(MAX_FRAME_SIZE) + ").");
            return false;
        }
        memcpy(m_writeBuffer[m_framesBufferised], data, size);
        m_framesBufferised++;
        if (m_framesBufferised == BUFFER_SIZE){
            if (!flushFrames()){
                m_framesBufferised--;
                return false;
            }
        }
        return true;
    };
    bool flushFrames(){
        qDebug() << "flushFrames executed";
        if (m_filePath ==""){
            qDebug() << "Udp log writer path has not been initialised";
            return false;
        }

        std::fstream file(m_filePath, std::ios::binary | std::ios::in | std::ios::out);
        if (!file){
            m_logger->error("Frame writer : log file is invalid, flush aborted.");
            return false;
        }

        int oldFrameQty = m_LogFileHeader.frameQty;
        m_LogFileHeader.frameQty += m_framesBufferised;
        file.seekp(0);
        file.write(reinterpret_cast<const char*>(&m_LogFileHeader), sizeof(m_LogFileHeader));


        file.seekp(sizeof(m_LogFileHeader) + oldFrameQty*MAX_FRAME_SIZE);
        file.write(reinterpret_cast<const char*>(m_writeBuffer), m_framesBufferised * MAX_FRAME_SIZE);
        m_framesBufferised = 0;
        return true;
    };
};


#endif // WRITER_H
