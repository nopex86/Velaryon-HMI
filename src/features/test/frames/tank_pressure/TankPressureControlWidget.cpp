#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QStackedLayout>
#include "TankPressureControlWidget.h"
#include "TankPressureControlerViewModel.h"


TankPressureControler::TankPressureControler(
    TankPressureControlerViewModel* vm,
    QWidget* parent) :
    QWidget(parent), m_vm(vm){

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignCenter);

    QLabel* title = new QLabel(
        QString(R"(%1 pressure)").arg(vm->tankName()), this);
    title->setFont(m_font);
    mainLayout->addWidget(title, 0, Qt::AlignCenter);

    m_pressureSelector = new QDoubleSpinBox(this);
    m_pressureSelector->setFixedSize(100, 30);
    m_pressureSelector->setLocale(
        QLocale(QLocale::English, QLocale::UnitedStates));
    m_pressureSelector->setStyleSheet(
        R"(QDoubleSpinBox {
            background-color: white;  /* Dark gray background */
            color: black;             /* Light text for contrast */
            border: 2px solid #696969;  /* Subtle blue border */
            border-radius: 5px;
            padding: 5px;
            font-size: 14px;
            }

            QDoubleSpinBox::up-button {
                width: 30px;
                height: 15px;
                background-color: lightgray;
                border: none;
                border-radius: 2px;
                image: url(./Pictures/arrow_up.png); /* Custom up arrow icon */
            }

            QDoubleSpinBox::down-button {
                width: 30px;
                height: 15px;
                background-color: lightgray;
                border: none;
                border-radius: 2px;
                image: url(./Pictures/arrow_down.png); /* Custom down arrow icon */
            }
            )");
    m_pressureSelector->setRange(
        vm->pressureRange()[0], vm->pressureRange()[1]);
    m_pressureSelector->setValue(
        vm->pressureSetting());
    mainLayout->addWidget(m_pressureSelector);

    QWidget* tankLayoutContainer = new QWidget(this);
    tankLayoutContainer->setSizePolicy(
        QSizePolicy::Fixed, QSizePolicy::Fixed);

    QStackedLayout* tankLayout = new QStackedLayout(
        tankLayoutContainer);
    tankLayout->setStackingMode(QStackedLayout::StackAll);
    tankLayout->setContentsMargins(0, 0, 0, 0);

    m_tankLogo = new QLabel(tankLayoutContainer);
    m_tankLogo->setFixedSize(50, 115);
    m_tankLogo->setAlignment(Qt::AlignCenter);

    m_pressureIndicator = new QLabel(
        "no\ndata", tankLayoutContainer);
    m_pressureIndicator->setAlignment(Qt::AlignCenter);
    m_pressureIndicator->setStyleSheet("background: transparent;");
    m_pressureIndicator->setFont(m_font);
    m_pressureIndicator->setAttribute(
        Qt::WA_TransparentForMouseEvents, true);

    tankLayout->addWidget(m_pressureIndicator);
    tankLayout->addWidget(m_tankLogo);
    mainLayout->addWidget(tankLayoutContainer, 0, Qt::AlignCenter);


    QPushButton* pressurisation_button = new QPushButton(
        "Set pressure", this);
    pressurisation_button->setFont(m_font);
    pressurisation_button->setFixedSize(95, 30);
    pressurisation_button->setStyleSheet(R"(
            QPushButton {
                border: 1px solid black;
                background-color: white;
                border-radius: 4px;
                height: 30px;
            }
            QPushButton:hover {
                background-color: #ADADAD;
                border: 2px rgb(255,200,200);
            }
            )");
    mainLayout->addWidget(pressurisation_button, 0, Qt::AlignCenter);



    m_BB_button = new QPushButton(this);
    m_BB_button->setText(m_vm->BBControlStatus() == BBSTATUS::ON ?
                             "BB enabled" : "BB disabled");
    m_BB_button->setFont(m_font);
    m_BB_button->setFixedSize(95, 25);
    m_BB_button->setStyleSheet(R"(
            QPushButton {
                border: 1px solid black;
                background-color: white;
                border-radius: 4px;
                height: 30px;
            }
            QPushButton:hover {
                background-color: #ADADAD;
                border: 2px rgb(255,200,200);
            }
            )");
    mainLayout->addWidget(m_BB_button, 0, Qt::AlignCenter);

    connect(
        m_pressureSelector, &QDoubleSpinBox::valueChanged,
        m_vm, &TankPressureControlerViewModel::onPressureSettingSelected);
    connect(
        pressurisation_button, &QPushButton::clicked,
        m_vm, &TankPressureControlerViewModel::onPressurSettingSent);

    connect(
        m_BB_button, &QPushButton::clicked,
        m_vm, &TankPressureControlerViewModel::onBBCommandSent);

    connect(
        m_vm, &TankPressureControlerViewModel::BBControlStatusChanged,
        this, &TankPressureControler::onBBControlStatusChanged);

    connect(
        m_vm, &TankPressureControlerViewModel::sensorDataChanged,
        this, &TankPressureControler::onsensorDataChanged);
}

//Setting handlers :
void TankPressureControler::set_color(QColor backgroundColor)
{
    QColor hsvColor = backgroundColor.toHsv();
    qreal luminosity = hsvColor.valueF()*0.7;
    QColor borderColor = QColor::fromHsvF(
        hsvColor.hueF(), hsvColor.saturationF(), luminosity);

    QString styleSheet = QString(
            R"( QLabel {
                background-color: %1;
                padding: 10px;
                border: 1px solid %2;
                border-radius: 25px;
            })"
        ).arg(backgroundColor.name(),borderColor.name());

    m_tankLogo->setStyleSheet(styleSheet);
}

void TankPressureControler::onBBControlStatusChanged(){
    m_BB_button->setText(m_vm->BBControlStatus() == BBSTATUS::ON ?
        "BB enabled" : "BB disabled");
}

void TankPressureControler::onsensorDataChanged(){
    m_pressureIndicator->setText(
        QString::number(m_vm->sensorValue()) + "\n" + m_vm->sensorUnit());
}







