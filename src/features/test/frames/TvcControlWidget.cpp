#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QPainter>

#include "TvcControlWidget.h"
#include "dependencies/QCustomPlot/qcustomplot.h"

tvcControlFrame::tvcControlFrame(QWidget* parent, const QFont& font) :QWidget(parent){
    m_font = font;
    m_frame = new QFrame(this);
    m_frame->setFrameShape(QFrame::StyledPanel);
    m_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* frame_layout = new QVBoxLayout(m_frame);
    frame_layout->setAlignment(Qt::AlignCenter);

    // Title label for TVC control
    QLabel* TVC_label = new QLabel("TVC control", m_frame);
    TVC_label->setAlignment(Qt::AlignCenter);
    TVC_label->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; margin-bottom: 10px; }");
    frame_layout->addWidget(TVC_label);

    // Combobox to choose the desired pattern
    QHBoxLayout* layout_combobox_TVC = new QHBoxLayout();
    layout_combobox_TVC->setAlignment(Qt::AlignCenter);

    QComboBox* combobox_TVC = new QComboBox(m_frame);
    combobox_TVC->setFixedSize(120, 30);
    combobox_TVC->addItems({"None", "Cross", "Circle", "Square", "Up-Down", "Left-Right"});
    combobox_TVC->setStyleSheet(R"(
        QComboBox {
            background-color: white;
            color: black;
            border: 2px solid #696969;
            border-radius: 5px;
            padding: 5px;
            font-size: 14px;
            padding-left: 10px;
        }
        QComboBox::drop-down {
            width: 25px;
            height: 26px;
            background-color: lightgray;
            border: none;
            border-radius: 2px;
        }
        QComboBox::down-arrow {
            width: 16px;
            height: 16px;
            image: url(./Pictures/arrow_down.png);
        }
        QComboBox QAbstractItemView {
            background-color: #f0f0f0;
            border: 1px solid #777777;
            selection-background-color: black;
            selection-color: black;
            outline: 0px;
            padding: 5px;
        }
        QComboBox QAbstractItemView::item:selected {
            background-color: #f0f0f0;
            padding: 5px;
            border-left: none;
        }
        QComboBox QAbstractItemView::item:focus {
            outline: none;
            padding: 5px;
        }
        QComboBox QAbstractItemView::item:hover {
            background-color: #e0e0e0;
            padding: 5px;
        })");
    layout_combobox_TVC->addWidget(combobox_TVC);
    layout_combobox_TVC->addStretch();

    // Layout originally use for two buttons - might be useless depending on future choices
    QVBoxLayout* buttonLayout = new QVBoxLayout();

    // Send a TVC command to test a pattern ( a second might be required for sending pattern to uC)
    QPushButton* patterntest = new QPushButton("Test pattern", m_frame);
    patterntest->setFixedSize(100, 30);
    patterntest->setStyleSheet(R"(
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
    buttonLayout->addWidget(patterntest);

    layout_combobox_TVC->addLayout(buttonLayout);

    frame_layout->addLayout(layout_combobox_TVC);

    // Display a visual of the pattern
    QCustomPlot* customPlot = new QCustomPlot(m_frame);
    customPlot->setFixedSize(100, 100);
    customPlot->xAxis->setVisible(false);
    customPlot->yAxis->setVisible(false);

    frame_layout->addWidget(customPlot, 0, Qt::AlignCenter);

    customPlot->setBackground(QColor("#F3F3F3"));
    // QObject::connect(combobox_TVC, &QComboBox::currentTextChanged, [=]() {
    //     customPlot->clearPlottables();
    //     QString selectedShape = combobox_TVC->currentText();

    //     UdpSender* sender = new UdpSender();

    //     // Clear previous items and graphs
    //     customPlot->clearGraphs();
    //     customPlot->clearItems();

    //     // Drawing
    //     if (selectedShape == "Cross") {
    //         QVector<double> x, y;

    //         // Define the two lines that make up the cross
    //         x << -1 << 1;
    //         y << 0 << 0; // Horizontal line

    //         customPlot->addGraph();
    //         customPlot->graph(0)->setData(x, y);
    //         customPlot->graph(0)->setPen(QPen(Qt::black, 2));

    //         QVector<double> x2, y2;
    //         x2 << 0 << 0;
    //         y2 << -1 << 1; // Vertical line

    //         // Add grap and provide points
    //         customPlot->addGraph();
    //         customPlot->graph(1)->setData(x2, y2);
    //         customPlot->graph(1)->setPen(QPen(Qt::black, 2));
    //         sender->sendTVCtest(1);     // Sends TVC pattern to uC
    //     }
    //     else if (selectedShape == "Circle") {
    //         // Draw a curve/spline instead of lines
    //         QCPCurve *circle = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
    //         QVector<QCPCurveData> dataCircle;
    //         for (int i = 0; i < 101; ++i) {
    //             double theta = 2 * M_PI * i / 100;
    //             dataCircle.push_back(QCPCurveData(i, 1 * cos(theta), 1 * sin(theta)));
    //         }
    //         circle->data()->set(dataCircle, true);
    //         circle->setPen(QPen(Qt::black, 2));
    //         sender->sendTVCtest(2);
    //     }
    //     else if (selectedShape == "Square") {
    //         // Draw a rectangle using two points instead of 4
    //         QCPItemRect *rect = new QCPItemRect(customPlot);
    //         rect->topLeft->setCoords(-1, 1);
    //         rect->bottomRight->setCoords(1, -1);
    //         rect->setPen(QPen(Qt::black, 2));  // Outline color
    //         sender->sendTVCtest(3);
    //     }
    //     else if (selectedShape == "Up-Down") {
    //         QVector<double> x, y;
    //         x << 0 << 0;
    //         y << -1 << 1;
    //         customPlot->addGraph();
    //         customPlot->graph(0)->setData(x, y);
    //         customPlot->graph(0)->setPen(QPen(Qt::black, 2));
    //         sender->sendTVCtest(4);
    //     }
    //     else if (selectedShape == "Left-Right") {
    //         QVector<double> x, y;
    //         x << -1 << 1;
    //         y << 0 << 0;
    //         customPlot->addGraph();
    //         customPlot->graph(0)->setData(x, y);
    //         customPlot->graph(0)->setPen(QPen(Qt::black, 2));
    //         sender->sendTVCtest(5);
    //     }
    //     else {
    //         // Handle the case where no valid shape is selected
    //     }

    //     // Rescale axes to fit the shapes
    //     customPlot->xAxis->setRange(-1.05, 1.05);
    //     customPlot->yAxis->setRange(-1.05, 1.05);
    //     customPlot->replot();
    // });

    // Similarlw to above, the next section creates an unavailability display (remove for future updates
    m_tvc_disabled = new QLabel(this);
    m_tvc_disabled->setStyleSheet("background-color: rgba(128, 128, 128, 100);;");
    m_tvc_disabled->raise();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(m_frame);
};

// Si le widget est redimensionné, adapter l’overlay :
void tvcControlFrame::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    if (m_tvc_disabled)
        m_tvc_disabled->setGeometry(rect());

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
    m_tvc_disabled->setPixmap(pixmap);
    // End of the unavailability display (do not remove further lines)
}
