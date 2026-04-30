#ifndef LOGGER_H
#define LOGGER_H

/**
 * @file Logger.h
 * @ingroup Logging
 * @brief Tool that provide the ability to display and log
 * errors and debug messages.
 */

#include <QWidget>
#include "src/core/Protocols/Messages.h"

/**
 * @brief Tool that provide the ability to display and log
 * errors and debug messages.
 * @details This service is given to the components of the
 * app to give them the ability to display errors and help
 * debugging. Requirements :
 *  - Thread safe (not currently done)
 *  - Lock free (not currently done)
 *  - Provide differents importance levels of logs
 *  - Write the logs in a file (not currently done)
 */
class Logger : public QObject {

    Q_OBJECT
public :
    explicit Logger(QObject* parent);

    /**
     * @brief Log the messages and send signal to display
     * it.
     * @param level Level of importance of the message.
     * @param text Text of the message.
     * @note this methode is depreciated
     */
    void log(TextMessage::Level level,
             const QString& text);

    /**
     * @brief Log the messages as a debug and send
     * a signal to display it.
     * @param text Text of the message.
     */
    void debug(const std::string& text);

    /**
     * @brief Log the messages as an error and send
     * a signal to display it.
     * @param text Text of the message.
     */
    void error(const std::string& text);

    /**
     * @brief Log the messages as a warning and send
     * a signal to display it.
     * @param text Text of the message.
     */
    void warning(const std::string& text);
signals :

    /**
     * @brief Signal that send the message to the rest
     * of the app.
     * @param message Struct that contain the text of the
     * message and is level of importance.
     */
    void messageLogged(const TextMessage& message);

};

#endif // LOGGER_H
