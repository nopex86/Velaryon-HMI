#include "PlotWidget.h"
#include "PlotViewModel.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QCheckBox>

Plot::Plot(
    PlotViewModel* vm,
    QWidget* parent) :
    QWidget(parent), m_vm(vm){
    m_font = QFont("Arial", 10, QFont::Bold);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignCenter);

    QFrame* mainFrame = new QFrame(this);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainFrame->setFrameShape(QFrame::StyledPanel);
    mainLayout->addWidget(mainFrame);

    QHBoxLayout* mainFrameLayout = new QHBoxLayout(mainFrame);
    mainFrameLayout->setContentsMargins(0, 0, 0, 0);
    mainFrameLayout->setSpacing(0);
    mainFrameLayout->setAlignment(Qt::AlignCenter);

//          Definition of the plot section
//-----------------------------------------------------------------------------
    m_plot = new QCustomPlot(mainFrame);
    m_plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainFrameLayout->addWidget(m_plot, 9);

    // X-axis displayed in hour format
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    m_plot->xAxis->setTicker(timeTicker);

    // Ensure correct display of the axis
    m_plot->axisRect()->setupFullAxesBox();

    // Initial Y-axis
    m_plot->yAxis->setRange(-100, 100);

//          Definition of the plot control section
// -----------------------------------------------------------------------------
    QVBoxLayout* controlLayout = new QVBoxLayout();
    controlLayout->setContentsMargins(10, 10, 10, 10);
    controlLayout->setSpacing(15);
    mainFrameLayout->addLayout(controlLayout, 1);

    QLabel* title = new QLabel(m_vm->title(), mainFrame);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(m_font);
    controlLayout->addWidget(title);

    QVBoxLayout* buttonLayout = new QVBoxLayout();
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(0);
    controlLayout->addLayout(buttonLayout);

    QGridLayout* timeRangeGrid = new QGridLayout();
    buttonLayout ->addLayout(timeRangeGrid,30);



    m_TRBtnUnselectedStyle = R"(
        QPushButton {
            border: 1px solid black;
            background-color: white;
            border-radius: 3px;
            height: 20px;
        }
        QPushButton:hover {
            background-color: darkgray;
            border-color: darkgray;
        }
    )";
    m_TRBtnSelectedStyle =R"(
        QPushButton {
            border: 1px solid black;
            background-color: lightgray;
            border-radius: 3px;
            height: 20px;
        }
        QPushButton:hover {
            background-color: darkgray;
            border-color: darkgray;
        }
    )";

    int maxRow = 2;
    int maxColumn = 2;
    int row = 0, col = 0;
    for (const auto& b : m_vm->timeRangeButtons()){
        QPushButton* btn = new QPushButton(b.name, mainFrame);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setStyleSheet(m_TRBtnUnselectedStyle);
        timeRangeGrid->addWidget(btn, row, col);

        m_timeRangeButtons.insert(b.name, btn);

        connect(
            btn, &QPushButton::clicked,
            this, [this, b]{emit selectTimeRange(b.name);});

        if (++col == maxColumn) {
            col = 0;
            if (++row == maxRow) break;
        }
    }



    m_curveSelectionGrid = new QGridLayout();
    m_curveSelectionGrid->setContentsMargins(10, 10, 10, 10);
    m_curveSelectionGrid->setSpacing(3);
    buttonLayout ->addLayout(m_curveSelectionGrid,70);

    m_checkboxUncheckedStyle = "QCheckBox::indicator {"
                               "width: 14px;"
                               "height: 14px;"
                               "border: 1px solid lightgray;"
                               "border-radius: 3px;"
                               "}";
    m_checkboxCheckedStyle = [](const QString& color){
        return QString(
                   "QCheckBox::indicator {"
                   "width: 14px;"  // Set a fixed width
                   "height: 14px;" // Set a fixed height
                   "background-color: %1;"
                   "border: 1px solid %1;"
                   "border-radius: 3px;"
                   "}"
                   ).arg(color);
    };


    connect(m_vm, &PlotViewModel::SelectedTimeRangeChanged,
            this, &Plot::onSelectedTimeRangeChanged);
    connect(m_vm, &PlotViewModel::curvesParametersChanged,
            this, &Plot::onCurvesParametersChanged);
    connect(this, &Plot::selectTimeRange,
            m_vm, &PlotViewModel::selectTimeRange);
    connect(m_vm, &PlotViewModel::visibleCurvesChanged,
            this, &Plot::onVisibleCurvesChanged);
    connect(m_vm, &PlotViewModel::curvesValuesChanged,
            this, &Plot::onCurvesValuesChanged);
    connect(m_vm, &PlotViewModel::replot,
            this, &Plot::onReplot);
    connect(this, &Plot::isVisible,
            m_vm, &PlotViewModel::isVisible);
    m_vm->initialise();
}

void Plot::onSelectedTimeRangeChanged(){
    QString selected = m_vm->timeRangeSelected();
    const auto& buttons = m_vm->timeRangeButtons();
    for (auto it = buttons.begin();
         it != buttons.end() ;
         ++it){
        if (it->name == selected){
            double t = m_vm->currentTime();
            double timeRange = m_vm->selectedTimeRange();
            m_plot->xAxis->setRange(t, timeRange, Qt::AlignRight);
            m_plot->replot();
            break;
        }
    }

    for (auto it = m_timeRangeButtons.begin();
         it != m_timeRangeButtons.end();
         ++it){
        it.value()->setStyleSheet(it.key()==selected ?
        m_TRBtnSelectedStyle : m_TRBtnUnselectedStyle);
    }
}

void Plot::onCurvesValuesChanged(){
    if (m_bindings.size() == 0){
        initialiseBindings();
    }
    double t = m_vm->currentTime();
    for (const auto& b : m_bindings){
        double value;
        if (!m_vm->getValue(b.valueID, &value)) continue;
        b.graph->addData(t, value);
    }

    bool foundRange = false;
    for (int i = 0; i < m_plot->graphCount(); ++i) {
        if (m_plot->graph(i)->visible()) {
            m_plot->graph(i)->rescaleValueAxis(foundRange, true);
            foundRange = true;
        }
    }
}
void Plot::onReplot(){
    if (m_plot->isVisible()){
        double t = m_vm->currentTime();
        double timeRange = m_vm->selectedTimeRange();
        m_plot->xAxis->setRange(t, timeRange, Qt::AlignRight);
        m_plot->replot(QCustomPlot::rpQueuedReplot);
    }
}

void Plot::initialiseBindings(){
    m_plot->clearGraphs();

    for (auto& c : m_vm->curveParameters()){
        size_t valueID;
        if (!m_vm->getValueID(c.name, &valueID)) continue;

        QCPGraph* graph = m_plot->addGraph();
        graph->setName(c.name);
        graph->setPen(QPen(QColor(c.color)));
        graph->setVisible(false);
        m_bindings.push_back({c.name, valueID, graph});
    }
}

void Plot::onCurvesParametersChanged(){
    QLayoutItem* item;
    while ((item = m_curveSelectionGrid->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    int maxRow = 4;
    int maxColumn = 5;
    int row = 0, col = 0;
    for (const auto& c : m_vm->curveParameters()){
        QCheckBox* checkbox = new QCheckBox(c.name);
        connect(
            checkbox, &QCheckBox::checkStateChanged,
            this, [this, c, checkbox]
            {
                checkbox->setStyleSheet(checkbox->isChecked() ?
                                            m_checkboxCheckedStyle(c.color) :
                                            m_checkboxUncheckedStyle);
                emit isVisible(c.name, checkbox->isChecked());
            });
        m_curveSelectionGrid->addWidget(checkbox, row, col);
        checkbox->setStyleSheet(m_checkboxUncheckedStyle);
        if (++row == maxRow) {
            row = 0;
            if (++col == maxColumn) break;
        }
    }
    m_plot->replot();
    m_curveSelectionGrid->setRowStretch(maxRow+1, 1);
    m_curveSelectionGrid->setColumnStretch(maxColumn+1, 1);
}

void Plot::onVisibleCurvesChanged(){
    for (const auto& b : m_bindings){
        bool isVisible = false;
        for (const QString& visibleCurve : m_vm->visibleCurves()){
            if (b.name == visibleCurve){
                isVisible = true;
                break;
            }
        }
        if (m_plot->graphCount() != 0){
            b.graph->setVisible(isVisible);
        }
    }
    m_plot->replot();
}
