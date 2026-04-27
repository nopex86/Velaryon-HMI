#ifndef LOGTERMINALWIDGET_H
#define LOGTERMINALWIDGET_H

#include <QPlainTextEdit>
#include "src/core/Protocols/Messages.h"

class LogTerminalViewModel;

class logTerminalFrame : public QWidget  {
    Q_OBJECT
public :
    explicit logTerminalFrame(
        LogTerminalViewModel* vm,
        QWidget* parent=nullptr);
    QPlainTextEdit* getTerminal();
public slots :
    void receiveLog(TextMessage message);
private :
    QPlainTextEdit* m_logTerminal;
};

#endif // LOGTERMINALWIDGET_H
