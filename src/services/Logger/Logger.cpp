#include "Logger.h"

Logger::Logger(QObject* parent) : QObject(parent){}

void Logger::log(TextMessage::Level level,
                 const QString& text){
    TextMessage message;
    message.level = level;
    message.text = text;
    qDebug() << text;
    emit messageLogged(message);
}

void Logger::debug(const std::string& text){
    TextMessage message;
    message.level = TextMessage::Level::Debug;
    message.text = QString::fromStdString(text);
    qDebug() << text.c_str();
    emit messageLogged(message);
}

void Logger::error(const std::string& text){
    TextMessage message;
    message.level = TextMessage::Level::Error;
    message.text = QString::fromStdString(text);
    qDebug() << text.c_str();
    emit messageLogged(message);
}

void Logger::warning(const std::string& text){
    TextMessage message;
    message.level = TextMessage::Level::Warning;
    message.text = QString::fromStdString(text);
    qDebug() << text.c_str();
    emit messageLogged(message);
}
