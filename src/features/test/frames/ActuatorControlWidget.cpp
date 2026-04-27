#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QSlider>
#include <QLabel>
#include <QPainter>

#include "ActuatorControlWidget.h"

actuatorControlFrame::actuatorControlFrame(QWidget* parent, const QFont& font) :QWidget(parent){
    m_font = font;
    m_frame = new QFrame(this);
    m_frame->setFrameShape(QFrame::StyledPanel);
    m_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* frame_layout = new QVBoxLayout(m_frame);
    frame_layout->setAlignment(Qt::AlignCenter);

    // Title label for actuator control section
    QLabel* actuator_title = new QLabel("Actuator control",m_frame);
    actuator_title->setFont(m_font);
    actuator_title->setAlignment(Qt::AlignCenter);
    frame_layout->addWidget(actuator_title);

    // Radiobuttons to switch input types (angle or length)
    QHBoxLayout* layout_radio_button = new QHBoxLayout();
    QRadioButton* radio_button1 = new QRadioButton("Length", m_frame);
    QRadioButton* radio_button2 = new QRadioButton("Angle", m_frame);
    radio_button1->setChecked(true);        // Default length
    layout_radio_button->addWidget(radio_button1);
    layout_radio_button->addWidget(radio_button2);
    frame_layout->addLayout(layout_radio_button);

    // Separate left-right control
    QFrame* separator = new QFrame(m_frame);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    frame_layout->addWidget(separator);

    // Spinbox for command inputs
    QHBoxLayout* layout_actuator_spinbox = new QHBoxLayout();
    QDoubleSpinBox* spinbox_left = new QDoubleSpinBox(m_frame);
    QDoubleSpinBox* spinbox_right = new QDoubleSpinBox(m_frame);

    spinbox_left->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    spinbox_right->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    spinbox_left->setStyleSheet(
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

    spinbox_right->setStyleSheet(
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

    // Set range and size
    spinbox_left->setRange(0.0, 100.0);
    spinbox_right->setRange(0.0, 100.0);
    spinbox_left->setFixedSize(90, 30);
    spinbox_right->setFixedSize(90, 30);
    spinbox_left->setDecimals(1);
    spinbox_right->setDecimals(1);

    layout_actuator_spinbox->addWidget(spinbox_left);
    layout_actuator_spinbox->addWidget(spinbox_right);

    // Slider control (redundacy with spinbox)
    frame_layout->addLayout(layout_actuator_spinbox);
    QHBoxLayout* layout_actuator_slider = new QHBoxLayout();

    QSlider* slider_left = new QSlider(Qt::Vertical, m_frame);
    QSlider* slider_right = new QSlider(Qt::Vertical, m_frame);
    slider_left->setStyleSheet(
        R"(
        QSlider::groove:vertical {
            border: 1px solid #555555;
            background: #999999;
            width: 8px;
            margin: 4px 0;
            border-radius: 4px;
        }
        QSlider::handle:vertical {
            background: #5c5c5c;
            border: 1px solid #1a1a1a;
            width: 16px;
            height: 30px;
            margin: -5px -4px;
            border-radius: 3px; /* Rectangular with slightly rounded corners */
        }
        QSlider::add-page:vertical, QSlider::sub-page:vertical {
            background: #999999;
            border-radius: 4px;
        }
        )"
        );

    slider_right->setStyleSheet(
        R"(
        QSlider::groove:vertical {
            border: 1px solid #555555;
            background: #999999;
            width: 8px;
            margin: 4px 0;
            border-radius: 4px;
        }
        QSlider::handle:vertical {
            background: #5c5c5c;
            border: 1px solid #1a1a1a;
            width: 16px;
            height: 30px;
            margin: -5px -4px;
            border-radius: 3px; /* Rectangular with slightly rounded corners */
        }
        QSlider::add-page:vertical, QSlider::sub-page:vertical {
            background: #999999;
            border-radius: 4px;
        }
        )"
        );

    // Set range (x10 because decimal precision)
    slider_left->setRange(0, 1000);
    slider_right->setRange(0, 1000);

    layout_actuator_slider->addWidget(slider_left);
    layout_actuator_slider->addWidget(slider_right);
    frame_layout->addLayout(layout_actuator_slider);

    // Link spinbox with slider

    QObject::connect(spinbox_left, QOverload<double>::of(&QDoubleSpinBox::valueChanged), slider_left, [=](double value){
        slider_left->setValue(static_cast<int>(value * 10));
    });

    QObject::connect(slider_left, &QSlider::valueChanged, spinbox_left, [=](int value){
        spinbox_left->setValue(value / 10.0);
    });

    QObject::connect(spinbox_right, QOverload<double>::of(&QDoubleSpinBox::valueChanged), slider_right, [=](double value){
        slider_right->setValue(static_cast<int>(value * 10));
    });

    QObject::connect(slider_right, &QSlider::valueChanged, spinbox_right, [=](int value){
        spinbox_right->setValue(value / 10.0);
    });

    //////////////////////////////////////////////////////////////////////////////
    /// Determine 3D equation for central angle computation
    /// Make the switch between angle and length (range of slider-spinbox)
    /// Define limits for warnings
    //////////////////////////////////////////////////////////////////////////////

    //radio_button1.toggled.connect(update_ranges)
    //radio_button2.toggled.connect(update_ranges)

    // This label should be used to display the central angle value and warn user if interfering angles
    // See python version l1429 at https://github.com/Innovative-Propulsion-Laboratory/Velaryon-IHM-Python/blob/main/main.py
    QLabel* angle_central_label = new QLabel("Control Panel", m_frame);

    angle_central_label->setFont(font);
    angle_central_label->setAlignment(Qt::AlignCenter);

    frame_layout->addWidget(angle_central_label);

    frame_layout->setSpacing(10);

    // This button should be linked to the UdpSender to send values types (length/angles) and content
    QPushButton* send_actuator_button = new QPushButton("Send Data",m_frame);
    send_actuator_button->setStyleSheet(R"(
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

    frame_layout->addWidget(send_actuator_button);

    // Unavailable display (should be remove in future updates)
    m_actuator_disabled = new QLabel(this);
    m_actuator_disabled->setStyleSheet("background-color: rgba(128, 128, 128, 100);;");

    // Le mettre au-dessus de tout
    m_actuator_disabled->raise();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_frame);
};

// Si le widget est redimensionné, adapter l’overlay :
void actuatorControlFrame::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (m_actuator_disabled)
        m_actuator_disabled->setGeometry(rect());

    // Create a pixmap to draw on
    QPixmap pixmap(m_frame->size());
    pixmap.fill(Qt::transparent);  // Transparent background


    // Draw the rotated text
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(pixmap.width() / 2, pixmap.height() / 2);
    painter.rotate(-45);  // Rotate counterclockwise

    m_font.setBold(true);
    m_font.setPointSize(20);  // Adjust size as needed
    painter.setFont(m_font);
    painter.setPen(Qt::black);  // Text color

    painter.drawText(QRect(-pixmap.width()/2, -pixmap.height()/2, pixmap.width(), pixmap.height()),
                     Qt::AlignCenter, "UNAVAILABLE");


    // Apply the pixmap to the label
    m_actuator_disabled->setPixmap(pixmap);
    // End of the unavailability display (do not remove further lines)
}
