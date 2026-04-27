#ifndef SENSORVALUEINDICATOR_H
#define SENSORVALUEINDICATOR_H

#include <QObject>
#include <QLabel>

class SensorValueIndicatorViewModel;


class SensorValueIndicator : public QLabel
{
    Q_OBJECT

public:
    explicit SensorValueIndicator(
        SensorValueIndicatorViewModel* vm,
        const QPoint& position,
        QWidget* parent = nullptr);
    QSize sizeHint() const override;
public slots:
    void onValueChanged();
private:
    SensorValueIndicatorViewModel* m_vm;
    QFont m_font = QFont("Arial", 10, QFont::Bold);
    QSize m_size = {60,22};
};

#endif // SENSORVALUEINDICATOR_H
