#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include "StatusTableWidget.h"
#include "ActuatorSwitchViewModel.h"
#include "ActuatorSwitchWidget.h"

StatusTableWidget::StatusTableWidget(
    QPoint position,
    QWidget* parent) :
    QTableWidget(0, 2, parent){
    setGeometry(position.x(), position.y(), m_size.width(),m_size.height());
    setHorizontalHeaderLabels({"Actuator Name", "Status"});  // Set header labels

    QFont font = horizontalHeader()->font();
    font.setBold(true);  // Make the header font bold
    horizontalHeader()->setFont(font);

    verticalHeader()->setVisible(false);   // Hide vertical header
    setColumnWidth(0, 120);  // Set column widths
    verticalHeader()->setDefaultSectionSize(10);   // Set row height
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // Disable vertical scrollbar
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  // Disable horizontal scrollbar

    /*table_engine->setEditTriggers(QAbstractItemView::NoEditTriggers); // Make table non-editable
        table_engine->setSelectionMode(QAbstractItemView::NoSelection); // Disable selection
        table_engine->setFocusPolicy(Qt::NoFocus);  // Remove focus rectangle*/
    setEnabled(false);

    setStyleSheet(R"(
                QTableWidget {
                    border: 2px solid black;
                    background-color: #ededed;
                }
                QHeaderView::section {
                    background-color: #dbdbdb;
                }
        )");  // Apply styling to the table
}


void StatusTableWidget::addActuator(ActuatorSwitchWidget *actuator){
    ActuatorSwitchViewModel* actuatorVM = actuator->viewModel();

    int row = rowCount();
    insertRow(row);

    // Add name of the valve in first column
    QTableWidgetItem* nameItem = new QTableWidgetItem(actuatorVM->name());
    nameItem->setTextAlignment(Qt::AlignCenter);
    nameItem->setFont(font);
    nameItem->setForeground(QColor("black"));
    setItem(row, 0, nameItem);

    QLabel* statusLabel = new QLabel(this);
    statusLabel->setText(actuatorVM->status());
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setFont(font);
    QString style = QString("QLabel { color: %1; }").arg(actuatorVM->statusColor());
    statusLabel->setStyleSheet(style);

    setCellWidget(row, 1, statusLabel);

    connect(actuatorVM, &ActuatorSwitchViewModel::statusChanged,
            this, [statusLabel, actuatorVM]{
        statusLabel->setText(actuatorVM->status());
        QString style = QString("QLabel { color: %1; }").arg(actuatorVM->statusColor());
        statusLabel->setStyleSheet(style);
    });

    //Get the dimesions of one cell
    int w = verticalHeader()->width();
    int h = horizontalHeader()->height();

    //Calculate the correct size for the table depending of the number of cells
    for (int c = 0; c < columnCount(); ++c)
        w += columnWidth(c);

    for (int r = 0; r < rowCount(); ++r)
        h += rowHeight(r);

    //Parameters that can be ajusted to add margins
    w += 2;
    h += 2;
    m_size = {w, h};
    setGeometry(x(), y(), w, h); //Adujust the size and the position of the table
}

QSize StatusTableWidget::sizeHint()const{
    return m_size;
}
