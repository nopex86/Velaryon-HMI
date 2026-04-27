#include <QVBoxLayout>

#include <QMessageBox>
#include <QTimer>
#include <QFileDialog>
#include <QDebug>

#include "TestLaunchWidget.h"
#include "TestLauncherViewModel.h"

TestLauncher::TestLauncher(
    TestLauncherViewModel* vm,
    QWidget* parent) :
    QWidget(parent){
    m_vm = vm;

    QFrame* mainFrame = new QFrame(this);
    mainFrame->setFrameShape(QFrame::StyledPanel);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* mainFrameLayout = new QVBoxLayout(mainFrame);
    mainFrameLayout->setContentsMargins(10, 10, 10, 10);
    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->setAlignment(Qt::AlignCenter);

    QLabel* title = new QLabel("Launch test :", mainFrame);
    title->setStyleSheet("font-weight: bold; font-size: 16px;");

    QFrame* filePickerFrame = new QFrame(mainFrame);
    filePickerFrame->setFixedHeight(30);
    filePickerFrame->setObjectName("filePickerFrame");
    filePickerFrame->setStyleSheet(R"(
        QFrame#filePickerFrame {
            background-color: white;
            border: 2px solid #696969;
            border-radius: 5px;
        }
    )");

    QHBoxLayout* filePickerLayout = new QHBoxLayout(filePickerFrame);
    filePickerLayout->setContentsMargins(0, 0, 0, 0);
    filePickerLayout->setSpacing(0);
    filePickerLayout->setAlignment(Qt::AlignVCenter);

    // ComboBox (sans bordure, intégré au cadre)
    m_comboBox = new QComboBox(filePickerFrame);
    m_comboBox->setObjectName("sequenceCombo");
    m_comboBox->setFixedHeight(26);
    m_comboBox->setMinimumWidth(140);
    m_comboBox->setStyleSheet(R"(
        QComboBox#sequenceCombo {
            background: transparent;
            color: black;
            border: none;
            padding-left: 10px;
            font-size: 14px;
        }
        QComboBox::drop-down {
            width: 30px;
            height: 30px;
            background-color: lightgray;
            border: none;
            border-radius: 2px;
        }
        QComboBox::drop-down:hover {
            background-color: #696969;
        }
        QComboBox::down-arrow {
            width: 16px;
            height: 16px;
            image: url(./Pictures/arrow_down.png);
        }
        QComboBox QAbstractItemView {
            background-color: #f0f0f0;
            border: 1px solid #777777;
            selection-background-color: #e0e0e0;
            selection-color: black;
            outline: 0px;
            padding: 5px;
        }
    )");


    // Bouton browse collé, même hauteur, séparateur léger
    QPushButton* browseButton = new QPushButton("Browse...", filePickerFrame);
    browseButton->setFlat(true);
    browseButton->setObjectName("browseButton");
    browseButton->setFixedHeight(26);
    browseButton->setFixedWidth(90);
    browseButton->setStyleSheet(R"(
        QPushButton#browseButton {
            background-color: lightgray;
            color: black;
            border: none;
            border-left: 1px solid #696969; /* séparation entre les 2 zones */
            padding: 0px 10px;
            font-size: 14px;
            border-top-left-radius: 0px;
            border-bottom-left-radius: 0px;
            border-top-right-radius: 2px;
            border-bottom-right-radius: 2px;
        }
        QPushButton#browseButton:hover {
            background-color: #696969;
        }
        QPushButton#browseButton:pressed {
            background-color: #d0d0d0;
        }
    )");
    filePickerLayout->addWidget(m_comboBox);
    filePickerLayout->addWidget(browseButton);

    headerLayout->addWidget(title);
    headerLayout->addWidget(filePickerFrame);

    m_sequenceParametersGrid = new QGridLayout;
    m_sequenceParametersGrid->setSpacing(10);
    m_sequenceParametersGrid->setAlignment(Qt::AlignCenter);

    mainFrameLayout->addLayout(headerLayout);
    mainFrameLayout->addLayout(m_sequenceParametersGrid, 1);
    mainFrame->setLayout(mainFrameLayout);

    // Button to send the sequence to the uC
    QPushButton* launchButton = new QPushButton("Start test");
    launchButton->setFixedSize(150, 30);
    launchButton->setStyleSheet(R"(
            QPushButton {
                border: 1px solid black;
                background-color: white;
                border-radius: 5px;
                font-size: 12px;
                font-weight: bold;
            }
            QPushButton:hover {
                background-color: #ADADAD;
                border: 2px solid rgb(0, 0, 0);
            }
        )");


    // QHBoxLayout* footerLayout = new QHBoxLayout;
    headerLayout->addWidget(launchButton);
    // mainFrameLayout->addLayout(footerLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(mainFrame);


    connect(
        m_comboBox, &QComboBox::currentTextChanged,
        m_vm, &TestLauncherViewModel::selectFile);
    connect(
        browseButton, &QPushButton::clicked,
        m_vm, &TestLauncherViewModel::requestBrowse);
    connect(
        launchButton, &QPushButton::clicked,
        m_vm, &TestLauncherViewModel::launchTest);

    connect(
        vm, &TestLauncherViewModel::fileListChanged,
        this, &TestLauncher::renderFileList);
    connect(
        vm, &TestLauncherViewModel::sequenceParametersChanged,
        this, &TestLauncher::renderFileContent);
    connect(
        vm, &TestLauncherViewModel::browsingRequested,
        this, &TestLauncher::showFileDialogWindow);
    connect(
        vm, &TestLauncherViewModel::confirmationRequested,
        this, &TestLauncher::showConfirmationWindow);
    vm->initialise();
};

void TestLauncher::renderFileContent(){
    const SequenceParameters& parameters = m_vm->sequenceParameters();
    QLayoutItem* item;
    while ((item = m_sequenceParametersGrid->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    if (!parameters.empty()){
        int row = 0, col = 0;
        for (auto it = parameters.cbegin(); it != parameters.cend(); ++it) {
            m_sequenceParametersGrid->setColumnStretch(col, 1);
            m_sequenceParametersGrid->setRowStretch(row, 1);
            QString parameter = QString::fromStdString(std::get<0>(*it));
            double value = std::get<1>(*it);
            QString unit = QString::fromStdString(std::get<2>(*it));
            QString text = " - " + parameter + " : " + QString::number(value, 'f', 0) + " " + unit;
            QLabel* label = new QLabel(text);
            label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            label->setContentsMargins(30, 0, 0, 0);
            m_sequenceParametersGrid->addWidget(label, row, col);
            if (++row == 6) {
                row = 0;
                if (++col == 5) break; // Stop if the grid is full
            }
        }
    } else{
        // Create a 5x6 grid but leave it empty initially
        int row = 0, col = 0;
        for (int i = 0; i <= 30; i++) {
            m_sequenceParametersGrid->setColumnStretch(col, 1);
            m_sequenceParametersGrid->setRowStretch(row, 1);
            QLabel* empty_label = new QLabel(" - ");  // Empty label initially
            empty_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            empty_label->setContentsMargins(0, 0, 0, 0);
            m_sequenceParametersGrid->addWidget(empty_label, row, col);
            if (++row == 6) {
                row = 0;
                if (++col == 5) break; // Stop if the grid is full
            }
        }
    }
}

void TestLauncher::renderFileList(){
    m_comboBox->clear();
    m_comboBox->addItems(m_vm->fileList());
}

void TestLauncher::showFileDialogWindow(){
    const QString dirPath = QFileDialog::getExistingDirectory(
        this,
        "Chose folder",
        m_vm->fileDirPath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dirPath.isEmpty()) return;
    m_vm->changeDirPath(dirPath);
}

void TestLauncher::showConfirmationWindow(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(
        nullptr, "Warning: Test Launch",
        "This is your final warning!\n\n"
        "By clicking 'Yes', you are about to launch the test.\n"
        "Are you sure you want to proceed?",
        QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        m_vm->confirmLaunch();
    }
}
