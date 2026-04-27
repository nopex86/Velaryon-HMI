#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include "src/core/Protocols/Messages.h"

class Logger : public QObject {
    Q_OBJECT
public :
    explicit Logger(QObject* parent);
    void log(TextMessage::Level level,
             const QString& text);
    void debug(const std::string& text);
    void error(const std::string& text);
    void warning(const std::string& text);
signals :
    void messageLogged(const TextMessage& message);

};

#endif // LOGGER_H
