#include <QVBoxLayout>

#include "TankPressureControlFrameWidget.h"
#include "TankPressureControlWidget.h"
#include "TankPressureControlerViewModel.h"

TankPressureControlFrame::TankPressureControlFrame(
    const TpcDeps& deps,
    const TpcFrameConfig& config,
    QWidget* parent) :
    QWidget(parent){
    m_font = new QFont("Arial",10,QFont::Bold);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignCenter);

    m_frame = new QFrame(this);
    m_frame->setFrameShape(QFrame::StyledPanel);
    m_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_frame);

    QVBoxLayout* frameLayout = new QVBoxLayout(m_frame);
    frameLayout->setAlignment(Qt::AlignCenter);

    // Title label for the pressure control section
    QLabel* title = new QLabel("Tank pressure control\n", m_frame);
    title->setFont(*m_font);
    title->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(title);

    // Layout for holding the individual tank controls3
    m_tank_layout = new QHBoxLayout();
    m_tank_layout->setAlignment(Qt::AlignCenter);
    frameLayout->addLayout(m_tank_layout);

    for (const auto& c : config.controlers){
        TankPressureControlerViewModel* controlerVM = deps.makeTankPressureControlerVM(this);
        controlerVM->setTankName(c.tankName);
        controlerVM->setSensor(c.sensorName, c.sensorUnit);
        controlerVM->setPressureRange(c.pressureRange);
        controlerVM->setPressureDefaultValue(c.defaultPressureValue);
        TankPressureControler* controler = new TankPressureControler(
            controlerVM,
            this);
        controler->set_color(c.tankColor);
        m_tank_layout->addWidget(controler);
    }
};
