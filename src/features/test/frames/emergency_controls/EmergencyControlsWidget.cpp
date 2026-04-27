#include <QVBoxLayout>
#include "EmergencyControlsWidget.h"
#include "EmergencyControlsViewModel.h"

EmergencyControls::EmergencyControls(
    EmergencyControlsViewModel* vm,
    QWidget* parent) :
    QWidget(parent){

    QFrame* mainFrame = new QFrame(this);
    mainFrame->setFrameShape(QFrame::StyledPanel);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* frameLayout = new QVBoxLayout(mainFrame);


    // Title label for emergency section
    QLabel* title = new QLabel("Test abortion");
    title->setStyleSheet("font-weight: bold; font-size: 16px;");
    title->setAlignment(Qt::AlignCenter);
    frameLayout->addWidget(title);

    QPushButton* abortButton = new QPushButton("Abort test");
    abortButton->setFixedSize(150, 100);
    abortButton->setStyleSheet(
        "QPushButton {"
        "    border: 1px solid rgb(255, 0, 0);"
        "    background-color: rgb(220, 0, 0);"
        "    border-radius: 20px;"
        "    height: 30px;"
        "    font-size: 12px;"
        "    font-weight: bold;"
        "    margin-bottom: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgb(250, 0, 0);"
        "    border: 2px solid rgb(255, 0, 0);"
        "}"
        );

    frameLayout->addWidget(abortButton, 0, Qt::AlignCenter);
    mainFrame->setLayout(frameLayout);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(mainFrame);

    connect(
        abortButton, &QPushButton::clicked,
        vm, &EmergencyControlsViewModel::onTestAbortion);

};
