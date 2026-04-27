#include "InitialiseValveButtonWidget.h"
#include "InitialiseValveButtonViewModel.h"

InitialiseValveButton::InitialiseValveButton(
    InitialiseValveButtonViewModel* vm,
    QWidget* parent) :
    QPushButton(parent){
    m_vm = vm;

    setText("Initialise valves");
    setGeometry(0, 0, m_size.width(), m_size.height());
    setFont(QFont("Arial", 8, QFont::Bold));
    setStyleSheet(R"(
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

    connect(
        this, &QPushButton::clicked,
        vm, &InitialiseValveButtonViewModel::initialiseValve);
}

QSize InitialiseValveButton::sizeHint() const {
    return m_size;
}

