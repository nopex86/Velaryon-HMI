#include "UdpLogger.h"
#include "RingBuffer.h"
#include "Writer.h"
#include "src/services/Logger/Logger.h"
#include <chrono>
#include <format>
#include <chrono>

void UdpLogger::writerLoop(){
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

UdpLogger::UdpLogger(const std::string& logDirPath, Logger* logger)
    : m_logDirPath(logDirPath), m_logger(logger)
{
    m_writer = std::make_unique<Writer>(m_logger);
    m_ringBuffer = std::make_unique<RingBuffer>(m_logger);
}

UdpLogger::~UdpLogger(){
    if (m_running.load(std::memory_order_acquire)){
        stop();
    }
}

bool UdpLogger::log(uint8_t data[], int size){
    return m_ringBuffer->push(data, size);
}

int UdpLogger::cyclesCount(){
    return m_ringBuffer->cyclesCount();
}

int UdpLogger::droppedFramesCount(){
    return m_ringBuffer->droppedFramesCount();
}

bool UdpLogger::start(){
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

bool UdpLogger::stop(){
    m_running.store(false, std::memory_order_release);
    if (m_writerThread.joinable())
        m_writerThread.join();
    m_logger->debug("UDP logger : successfully stopped.");
    return true;
}
