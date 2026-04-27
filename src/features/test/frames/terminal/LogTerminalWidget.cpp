#include <QVBoxLayout>
#include <QDateTime>

#include "LogTerminalWidget.h"
#include "LogTerminalViewModel.h"

logTerminalFrame::logTerminalFrame(LogTerminalViewModel* vm, QWidget* parent) :QWidget(parent){
    m_logTerminal = new QPlainTextEdit(this);
    m_logTerminal->setMaximumBlockCount(500);     // Set a limit to the number of lines
    m_logTerminal->setReadOnly(true);             // Makes the terminal read-only
    m_logTerminal->setStyleSheet("background-color: black; color: white;");

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_logTerminal);

    connect(
        vm, &LogTerminalViewModel::displayLog,
        this, &logTerminalFrame::receiveLog
    );
}

QPlainTextEdit* logTerminalFrame::getTerminal(){
    return m_logTerminal;
}

void logTerminalFrame::receiveLog(TextMessage message){
    QString text = message.text;
    TextMessage::Level level = message.level;

    // Default format
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    format.setForeground(QBrush(Qt::white));
    QString messageType = "";

    // If warning, color is orange, if error, color's red
    if (level == TextMessage::Level::Warning) {
        format.setFontWeight(QFont::Bold);
        format.setForeground(QBrush(QColor("orange")));
        messageType = "[WARNING] ";
    } else if (level == TextMessage::Level::Error) {
        format.setFontWeight(QFont::Bold);
        format.setForeground(QBrush(Qt::red));
        messageType = "[ERROR] ";
    } else if (level == TextMessage::Level::Debug) {
        messageType = "[DEBUG] ";
    }

    // Add time
    QString date = QDateTime::currentDateTime().toString("hh:mm:ss");
    QTextCursor cursor = m_logTerminal->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("[" + date + "] " + messageType + text + "\n", format);
    m_logTerminal->setTextCursor(cursor);
}


