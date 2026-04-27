#ifndef STATUS_TABLE_H
#define STATUS_TABLE_H

#include <QObject>
#include <QTableWidget>

/*Declaration of the class that provide the status table
 *The main objective of this table is to give a summary of the valve status*/

class ActuatorSwitchWidget;
class StatusTableViewModel;

class StatusTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    //Class constructor
    explicit StatusTableWidget(
        QPoint position,
        QWidget* parent = nullptr);
    void addActuator(ActuatorSwitchWidget *valve);   //Allow to sync a new valve with the table
    QSize sizeHint() const override;
private:
    QSize m_size = {220,316};
    QFont font = QFont("Arial", 8, QFont::Bold);    //Font that is used in the table
};

#endif // STATUS_TABLE_H
