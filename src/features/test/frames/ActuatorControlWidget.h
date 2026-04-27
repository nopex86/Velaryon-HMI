#ifndef ARCTUATORCONTROLFRAME_H
#define ARCTUATORCONTROLFRAME_H

#include <QPushButton>
#include <QLabel>

class actuatorControlFrame : public QWidget {
    Q_OBJECT
public :
    explicit actuatorControlFrame(QWidget* parent, const QFont& font);
protected:
    void resizeEvent(QResizeEvent* event) override;
private :
    QFont m_font;
    QFrame* m_frame;
    QLabel* m_label;
    QPushButton* sendData_button;
    QLabel* m_actuator_disabled;
};

#endif // ARCTUATORCONTROLFRAME_H
