#ifndef TANKPRESSURECONTROLFRAMEWIDGET_H
#define TANKPRESSURECONTROLFRAMEWIDGET_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

class AppViewModel;

struct TpcFrameConfig{
    struct TpcConfig{
        QString tankName = "";
        QColor tankColor;
        QString sensorName = "";
        QString sensorUnit = "";
        double defaultPressureValue = NULL;
        std::array<double, 2> pressureRange = {};
    };
    QVector<TpcConfig> controlers;
};

class TankPressureControlerViewModel;

struct TpcDeps{
    std::function<TankPressureControlerViewModel* (QObject* parent)>
        makeTankPressureControlerVM;
};

class TankPressureControlFrame : public QWidget {
    Q_OBJECT
public :
    explicit TankPressureControlFrame(
        const TpcDeps& deps,
        const TpcFrameConfig& config,
        QWidget* parent);
private :
    QFont* m_font;
    QFrame* m_frame;
    QHBoxLayout* m_tank_layout;
};

#endif // TANKPRESSURECONTROLFRAMEWIDGET_H
