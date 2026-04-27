#ifndef UDPLOGGER_H
#define UDPLOGGER_H

#include "RingBuffer.h"
#include "Writer.h"
#include <atomic>
#include <cstdint>
#include <thread>
#include <chrono>
#include <format>
#include <chrono>
#include "src/services/Logger/Logger.h"

class UdpLogger{
private :
    static constexpr int MAX_FRAME_SIZE = 83;
    //
    Logger* m_logger = nullptr;
    using Writer = Writer<MAX_FRAME_SIZE, (1024*1024*2)/MAX_FRAME_SIZE>;
    std::unique_ptr<Writer> m_writer = nullptr;
    using RingBuffer = RingBuffer<MAX_FRAME_SIZE>;
    std::unique_ptr<RingBuffer> m_ringBuffer = nullptr;
    std::atomic<bool> m_running{false};
    std::thread m_writerThread;
    std::string m_logDirPath;

    void writerLoop(){
        while (true){
            if (!m_ringBuffer->isEmpty()){
                uint8_t data[MAX_FRAME_SIZE];
                m_ringBuffer->pull(data, MAX_FRAME_SIZE);
                m_writer->logFrame(data, MAX_FRAME_SIZE);
            }
            else {
                std::this_thread::sleep_for(std::chrono::microseconds(200));
            }
            if (!m_running.load(std::memory_order_acquire)){
                while (!m_ringBuffer->isEmpty()){
                    uint8_t data[MAX_FRAME_SIZE];
                    m_ringBuffer->pull(data, MAX_FRAME_SIZE);
                    m_writer->logFrame(data, MAX_FRAME_SIZE);
                }
                if (!m_writer->flushFrames()){
                    m_logger->error("UDP logger : frames could not be flushed.");
                }
                m_logger->debug("UDP logger : frames sucessfully flushed.");
                break;
            }
        }
        m_logger->debug("UDP logger : writer loop successfully stopped.");
    }

public :
    UdpLogger(const std::string& logDirPath, Logger* logger) :
        m_logDirPath(logDirPath), m_logger(logger)
    {
        m_writer = std::make_unique<Writer>(m_logger);
        m_ringBuffer = std::make_unique<RingBuffer>(m_logger);
    }
    ~UdpLogger(){
        if (m_running.load(std::memory_order_acquire)){
            stop();
        }
    }
    UdpLogger(const UdpLogger&) = delete;
    UdpLogger& operator=(const UdpLogger&) = delete;
    UdpLogger(UdpLogger&&) = delete;
    UdpLogger& operator=(UdpLogger&&) = delete;
    bool log(uint8_t data[], int size){
        return m_ringBuffer->push(data, size);
    }
    int cyclesCount(){
        return m_ringBuffer->cyclesCount();
    }
    int droppedFramesCount(){
        return m_ringBuffer->droppedFramesCount();
    }
    bool start(){
        std::ostringstream fileName;
        auto now = std::chrono::system_clock::now();

        bool writerInitialised =  m_writer->initialise(
            std::format("{}/Test_{:%Y-%m-%d_%H-%M-%S}.bdf", m_logDirPath, now));
        if (!writerInitialised){
            m_logger->error("UDP logger : writer has not been initialised.");
            return false;
        }
        m_running.store(true, std::memory_order_release);
        m_writerThread = std::thread([this]{ writerLoop(); });
        m_logger->debug("UDP logger : successfully initialised.");
        return true;
    }
    bool stop(){
        m_running.store(false, std::memory_order_release);
        if (m_writerThread.joinable())
            m_writerThread.join();
        m_logger->debug("UDP logger : successfully stopped.");
        return true;
    }
};

#endif //UDPLOGGER_H
