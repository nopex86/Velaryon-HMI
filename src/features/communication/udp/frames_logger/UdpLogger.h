#ifndef UDPLOGGER_H
#define UDPLOGGER_H


#include <atomic>
#include <cstdint>
#include <thread>
#include "RingBuffer.h"
#include "Writer.h"

/**
 * @file UdpLogger.h
 * @brief High-frequency binary logger for UDP telemetry frames.
 * @ingroup Logging
 */

class Logger;

/**
 * @brief High-frequency binary logger for UDP telemetry frames.
 * @ingroup Logging
 *
 * @details UdpLogger allows the UDP channel to persist incoming telemetry
 * and state frames at a sustained rate of at least 2 kHz. Responsibilities:
 *  - Accept variable-length binary frames from the UDP worker thread.
 *  - Buffer frames in a lock-free SPSC ring buffer.
 *  - Drain the ring buffer on a dedicated writer thread and flush to a
 *    binary @c .bdf file via Writer.
 *
 * @par Threading model
 * @c log() is called from the UDP worker thread. The ring buffer is the
 * only shared resource and is accessed lock-free. The writer loop runs
 * on a dedicated @c std::thread and is the only consumer of the buffer.
 *
 * @par Backpressure policy
 * If the ring buffer is full, incoming frames are silently dropped and
 * counted. Use droppedFramesCount() to monitor frame loss.
 *
 * @note This class is non-copyable and non-movable.
 */
class UdpLogger{
private :
    static constexpr int MAX_FRAME_SIZE = 83;

    Logger* m_logger = nullptr;

    /**
     * @brief Buffered binary file writer.
     *
     * @details Template parameters are resolved at compile time.
     * The write buffer size (2 MiB / MAX_FRAME_SIZE frames) is tuned to
     * amortize the latency of the underlying storage device.
     */
    using Writer = Writer<MAX_FRAME_SIZE, (1024*1024*2)/MAX_FRAME_SIZE>;
    std::unique_ptr<Writer> m_writer = nullptr;

    /**
     * @brief Lock-free SPSC ring buffer bridging the UDP thread and the
     *        writer thread.
     *
     * @details The ring buffer allows the writer to flush to disk
     * periodically without stalling the incoming frame flow. Frames that
     * cannot be enqueued when the buffer is full are silently dropped.
     */
    using RingBuffer = RingBuffer<MAX_FRAME_SIZE>;
    std::unique_ptr<RingBuffer> m_ringBuffer = nullptr;

    std::atomic<bool> m_running{false};

    /** @brief Dedicated thread running writerLoop(). */
    std::thread m_writerThread;

    /** @brief Path to the directory where the binary log file is written. */
    std::string m_logDirPath;

    /**
     * @brief Writer loop executed on @c m_writerThread.
     *
     * @details Drains the ring buffer and flushes frames to the binary
     * output file. This loop is designed to be the throughput bottleneck
     * of the pipeline: every upstream stage (UDP receive → ring buffer
     * enqueue) must sustain at least 2 kHz to avoid frame loss.
     */
    void writerLoop();
public :
    UdpLogger(const std::string& logDirPath, Logger* logger);
    ~UdpLogger();
    UdpLogger(const UdpLogger&) = delete;
    UdpLogger& operator=(const UdpLogger&) = delete;
    UdpLogger(UdpLogger&&) = delete;
    UdpLogger& operator=(UdpLogger&&) = delete;

    /**
     * @brief Push a binary frame into the ring buffer.
     *
     * @details Thread-safe. Called from the UDP worker thread.
     * If the ring buffer is full, the frame is dropped and the internal
     * drop counter is incremented.
     *
     * @param data Pointer to the raw frame bytes.
     * @param size Length of the frame in bytes. Must be ≤ MAX_FRAME_SIZE.
     * @return @c true if the frame was successfully enqueued,
     *         @c false if the buffer was full and the frame was dropped.
     */
    bool log(uint8_t data[], int size);

    /**
     * @brief Return the number of frames successfully logged since the
     *        last call to this function, then reset the counter to zero.
     * @return Number of frames logged.
     */
    int cyclesCount();

    /**
     * @brief Return the number of frames dropped since the last call to
     *        this function, then reset the counter to zero.
     * @return Number of frames dropped.
     */
    int droppedFramesCount();

    /**
     * @brief Initialize the writer and start the writer thread.
     * @return @c true on success, @c false if initialization failed.
     */
    bool start();

    /**
     * @brief Signal the writer loop to stop and join the writer thread.
     * @return @c true on success, @c false if the thread could not be joined.
     */
    bool stop();
};

#endif //UDPLOGGER_H
