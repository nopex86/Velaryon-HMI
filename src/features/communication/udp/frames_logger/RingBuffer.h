#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QDebug>
#include <cstdint>
#include <fstream>
#include <atomic>
#include <algorithm>
#include "src/services/Logger/Logger.h"

template<int MAX_FRAME_SIZE>
class RingBuffer{
private:
    static constexpr int BUFFER_SIZE{1024*1024/82}; //1024

    using frame = uint8_t[MAX_FRAME_SIZE];
    frame m_ring[BUFFER_SIZE];

    std::atomic<unsigned int> m_cyclesCount{0};
    std::atomic<unsigned int> m_droppedFramesCount{0};
    std::atomic<unsigned int> m_head{0};
    std::atomic<unsigned int> m_tail{0};

    Logger* m_logger;
public:
    RingBuffer(Logger* logger) : m_logger(logger){
        qDebug() << " taille buffer : " << BUFFER_SIZE;
        qDebug() << " taille frame : " << MAX_FRAME_SIZE;
    }
    bool isEmpty(){
        int tail = m_tail.load(std::memory_order_acquire);
        int head = m_head.load(std::memory_order_relaxed);
        return (tail - head) == 0;
    };
    bool push(const uint8_t data[], int size){
        if (size != MAX_FRAME_SIZE){
            m_droppedFramesCount.fetch_add(1, std::memory_order_release);
            qDebug() << "mauvaise taille de frame";
            m_logger->error("Frame buffer : wrong size of frame pushed ("
                            + std::to_string(size)
                            + " instead of "
                            + std::to_string(MAX_FRAME_SIZE) + ").");
            return false;
        }
        int tail = m_tail.load(std::memory_order_relaxed);
        int head = m_head.load(std::memory_order_acquire);
        if (tail - head >= BUFFER_SIZE){
            m_droppedFramesCount.fetch_add(1, std::memory_order_relaxed);
            m_logger->error("Buffer Full");
            return false;
        }
        std::memcpy(m_ring[tail%BUFFER_SIZE], data, MAX_FRAME_SIZE);
        m_tail.store(tail+ 1, std::memory_order_release);
        m_cyclesCount.fetch_add(1, std::memory_order_release);
        return true;
    }
    bool pull(uint8_t data[], int size){
        if (size != MAX_FRAME_SIZE){
            m_logger->error("Frame buffer : wrong size of frame pulled ("
                            + std::to_string(size)
                            + " instead of "
                            + std::to_string(MAX_FRAME_SIZE) + ").");
            return false;
        }
        int tail = m_tail.load(std::memory_order_acquire);
        int head = m_head.load(std::memory_order_relaxed);
        if (tail - head == 0) return false;
        std::memcpy(data, m_ring[head%BUFFER_SIZE], MAX_FRAME_SIZE);
        m_head.store(head + 1, std::memory_order_release);
        return true;
    }
    int cyclesCount(){
        return m_cyclesCount.exchange(0,std::memory_order_acq_rel);
    }
    int droppedFramesCount(){
        return m_droppedFramesCount.exchange(0,std::memory_order_acq_rel);
    }
};



#endif // RINGBUFFER_H
