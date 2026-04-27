#include "ParametersWindow.h"
#include <QTabWidget>
#include <QPushButton>
#include <QFrame>
#include "src/features/communication/udp/ui/UdpChannelParametersViewModel.h"
#include "src/features/communication/udp/ui/UdpChannelParametersWidget.h"

ParametersWindow::ParametersWindow(const ParametersWindowDeps& deps){
    setWindowTitle("Parameters");
    resize(400, 300);
    setAttribute(Qt::WA_DeleteOnClose);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    auto* headerWidget = new QFrame(this);
    headerWidget->setFixedHeight(30);
    // headerWidget->setStyleSheet("background-color: white;");
    QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    headerLayout->setContentsMargins(0,0,0,0);
    headerLayout->setSpacing(0);

    QHBoxLayout* saveButtonsLayout = new QHBoxLayout();
    saveButtonsLayout->setContentsMargins(0,0,0,0);
    saveButtonsLayout->setSpacing(0);

    QPushButton* applyButton = new QPushButton("apply", this);
    saveButtonsLayout->addWidget(applyButton);
    QPushButton* saveButton = new QPushButton("save", this);
    saveButtonsLayout->addWidget(saveButton);
    saveButtonsLayout->setAlignment(Qt::AlignVCenter);

    headerLayout->addLayout(saveButtonsLayout);
    mainLayout->addWidget(headerWidget);

    QTabWidget* tabs = new QTabWidget(this);
    tabs->setContentsMargins(0,0,0,0);
    tabs->setTabPosition(QTabWidget::West);
    mainLayout->addWidget(tabs);

    auto* udpChannelParametersViewModel = deps.makeUdpChannelParametersVM(this);
    auto* udpTab = new UdpChannelParametersWidget(udpChannelParametersViewModel, this);
    tabs->addTab(udpTab, "UDP");

    std::function applyParameters = [udpTab]{
        udpTab->applyParameters();
    };

    connect(applyButton, &QPushButton::clicked,
            this, [applyParameters]{
        applyParameters();
    });
    connect(saveButton, &QPushButton::clicked, this, [this, applyParameters](){
        applyParameters();
        close();
    });

    show();
}
