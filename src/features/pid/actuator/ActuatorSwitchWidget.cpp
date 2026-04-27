#include "ActuatorSwitchWidget.h"
#include "ActuatorSwitchViewModel.h"
#include <QVBoxLayout>

ActuatorSwitchWidget::ActuatorSwitchWidget(
    ActuatorSwitchViewModel* vm,
    QWidget* parent) :
    QFrame(parent)
{
    QFrame::setFixedSize(m_size);
    m_vm = vm;
}

void ActuatorSwitchWidget::display(){
    setObjectName("valveFrame");
    setStyleSheet(R"(
        QFrame#valveFrame {
            background-color: rgb(230, 230, 230);
            border: 3px solid grey;
            border-radius: 10px;
            padding: 2px;
        }
    )");

    QFont font = QFont("Arial", 8, QFont::Bold);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(2, 5, 2, 5);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignHCenter);


    m_title = new QLabel(this);
    m_title->setText(m_vm->name());
    m_title->setAlignment(Qt::AlignHCenter);
    m_title->setFont(font);
    m_title->setStyleSheet("QLabel { color: black; }");
    mainLayout->addWidget(m_title);

    m_statusIndicator = new QLabel("no status", this);
    m_statusIndicator->setFont(font);
    m_statusIndicator->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(m_statusIndicator);

    QFont font2 = font;
    font2.setPointSize(font.pointSize()-1);

    m_defaultStatusIndicator = new QLabel();
    m_defaultStatusIndicator->setAlignment(Qt::AlignHCenter);
    m_statusIndicator->setFont(font2);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setContentsMargins(0, 0, 0, 0);
    buttonsLayout->setSpacing(2);
    buttonsLayout->setAlignment(Qt::AlignHCenter);

    m_enableButton = new QPushButton("Enable", this);
    m_enableButton->setFixedHeight(25);
    m_enableButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_enableButton->setFont(font);
    m_enableButton->setStyleSheet(R"(
        QPushButton {
            border: 1px solid black;
            background-color: white;
            border-radius: 3px;
            height: 30px;
        }
        QPushButton:hover {
            background-color: #ADADAD;
            border: 2px rgb(255,200,200);
        }
    )");
    buttonsLayout->addWidget(m_enableButton);

    m_disableButton = new QPushButton("Disable", this);
    m_disableButton->setFixedHeight(25);
    m_disableButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_disableButton->setFont(font);
    m_disableButton->setStyleSheet(R"(
        QPushButton {
            border: 1px solid black;
            background-color: white;
            border-radius: 3px;
            height: 30px;
        }
        QPushButton:hover {
            background-color: #ADADAD;
            border: 2px rgb(255,200,200);
        }
    )");
    buttonsLayout->addWidget(m_disableButton);

    mainLayout->addLayout(buttonsLayout);

    connect(m_enableButton, &QPushButton::clicked,
            m_vm, &ActuatorSwitchViewModel::enable);
    connect(m_disableButton, &QPushButton::clicked,
            m_vm, &ActuatorSwitchViewModel::disable);
    connect(m_vm, &ActuatorSwitchViewModel::statusChanged,
            this, &ActuatorSwitchWidget::onActuatorStatusChanged);

    m_vm->initialise();
}

ActuatorSwitchViewModel* ActuatorSwitchWidget::viewModel(){return m_vm;}
QSize ActuatorSwitchWidget::sizeHint() const {return m_size;}

void ActuatorSwitchWidget::setFixedSize(int w, int h){
    m_size = {w,h};
    QFrame::setFixedSize(m_size);
}

void ActuatorSwitchWidget::setFont(const QFont& font){
    m_title->setFont(font);
    m_statusIndicator->setFont(font);
    QFont font2 = font;
    font2.setPointSize(font.pointSize()-1);
    m_defaultStatusIndicator->setFont(font2);
    m_enableButton->setFont(font);
    m_disableButton->setFont(font);
}

void ActuatorSwitchWidget::onActuatorStatusChanged(){
    if (isVisible()){
        m_statusIndicator->setText(m_vm->status());
        QString arg  = (m_vm->statusColor() == "green" ? "lightgreen" : m_vm->statusColor());
        QString style = QString(
                            R"(QFrame#valveFrame {
                background-color: rgb(230, 230, 230);
                border: 3px solid %1;
                border-radius: 10px;
                padding: 2px;
            })").arg(arg);
        setStyleSheet(style);
    }
}
