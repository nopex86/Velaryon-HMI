#ifndef CLOSEBUTTONWIDGET_H
#define CLOSEBUTTONWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QCoreApplication>
#include <QMessageBox>

class CloseButton : public QWidget{
    Q_OBJECT
public :
    explicit CloseButton(QWidget* parent);
    QSize sizeHint() const override { return QSize(120, 40); }
};





#endif // CLOSEBUTTONWIDGET_H
