#include "CloseButtonWidget.h"

// Close button to remove window control buttons
CloseButton::CloseButton(QWidget* parent) : QWidget(parent){
    setGeometry(1410 - 120/2, 710 -40/2, 120, 40);
    QPushButton* button = new QPushButton("End Program", this);
    button->setGeometry(0, 0, 120, 40);
    button->setStyleSheet(R"(
        QPushButton {
            border: 2px solid #B20000;
            background-color: #FF1400;
            border-radius: 3px;
        }
        QPushButton:hover {
            background-color: rgb(255,100,100);
            border: 2px solid rgb(255,200,200);
        }
    )");
    button->setFont(QFont("Arial", 10, QFont::Bold));

    connect(button, &QPushButton::clicked, this, [this]() {
        // Create a warning message box
        QWidget* w = this->window();
        QMessageBox::StandardButton reply = QMessageBox::warning(
            w, "Confirm Exit", "Are you sure you want to exit?",
            QMessageBox::Yes | QMessageBox::No, QMessageBox::No
            );

        // If Yes is clicked, exit the application
        if (reply == QMessageBox::Yes) {
            QCoreApplication::quit();
        }
    });
}
