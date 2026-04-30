#ifndef TIMER_H
#define TIMER_H

/**
 * @file Timer.h
 * @ingroup Core
 * @brief Timer that emit a signal at a certain frequency
 * to synchronise the refresh of the app widgets.
 */

#include <QTimer>

/**
 * @brief Timer that emit a signal at a certain frequency
 * to synchronise the refresh of the app widgets.
 * @details Requirements :
 *  - Frequency should be variable with a method.
 *  - Effective frequency should be watchable.
 */
class Timer : public QObject{
    Q_OBJECT
public :
    explicit Timer(QObject* parent = nullptr);

    /**
     * @brief Set the frequency of the timer.
     * @param freq Frequency to be set in Hertz.
     * @return @c true if the opertation is successfull.
     * @c false if the operation failed.
     */
    bool setFrequecy(int freq);

    /**
     * @brief Set the period of the timer.
     * @param period Period to be set in miliseconds.
     * @return @c true if the opertation is successfull.
     * @c false if the operation failed.
     */
    bool setPeriod(int period);

    /**
     * @brief Allow to get the effective frequency of the
     * timer.
     * @return Effective frequency in Hertz.
     */
    int frequencyHz();
private :

    /** @brief time of the last pulse of the timer */
    int m_lastRefresh;

    /** @brief Period betwen two pulse of the timer */
    int m_periodOfRefresh;
    QTimer m_timer;
signals:

    /** @brief Signal that send the pulse of the timer */
    void timeout();
};

#endif // TIMER_H
