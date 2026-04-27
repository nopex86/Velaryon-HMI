#include "PidLayout.h"
#include <QWidget>

PidLayout::PidLayout(QWidget *parent) : QLayout(parent) {}

PidLayout::~PidLayout() {
    for (auto& pidItem : m_items)
        delete pidItem.item;
    m_items.clear();
}

void PidLayout::addItem(QLayoutItem *item) {
    // addItem de base, sans position relative (0.0, 0.0 par défaut)
    m_items.append({item, 0.0f, 0.0f, noConstraints});
}

QLayoutItem *PidLayout::itemAt(int index) const {
    if (index < 0 || index >= m_items.size())
        return nullptr;
    return m_items[index].item;
}

QLayoutItem *PidLayout::takeAt(int index) {
    if (index < 0 || index >= m_items.size())
        return nullptr;
    LayoutItem pidItem = m_items.takeAt(index);
    return pidItem.item;
}

void PidLayout::addWidget(QWidget* widget, int contstraints) {
    float relX =  widget->x();
    float relY = widget->y();
    QWidgetItem* item = new QWidgetItem(widget);
    m_items.append({item, relX, relY, contstraints});
}

int PidLayout::count() const {
    return m_items.size();
}

QSize PidLayout::sizeHint() const {
   return QSize(200, 200); // taille suggérée
}

void PidLayout::setGeometry(const QRect &rect) {
    QLayout::setGeometry(rect);

    if (m_items.isEmpty())
        return;

    const int refWidth  = 1533;
    const int refHeight = 767;

    const double scaleFactorX = static_cast<double>(rect.width()) / refWidth;
    const double scaleFactorY = static_cast<double>(rect.height()) / refHeight;

    for (auto& pidItem : m_items) {
        QSize initialSize = pidItem.item->widget()->sizeHint();
        const int initialX = pidItem.relX;
        const int initialY = pidItem.relY;
        const int initialWidth = initialSize.width();
        const int initialHeight = initialSize.height();

        int newX = initialX;
        int newY = initialY;
        int newWidth = initialWidth;
        int newHeight = initialHeight;

        if (pidItem.constraints & noConstraints){
            pidItem.item->setGeometry(
                QRect(initialX, initialY, initialWidth, initialHeight));
            return;
        }
        if (pidItem.constraints & resize){
            newWidth = initialWidth * scaleFactorX;
            newHeight = initialHeight * scaleFactorY;
        }
        if (pidItem.constraints & alignCenter){
            newX = (initialX + initialWidth/2) * scaleFactorX - newWidth/2;
            newY = (initialY + initialHeight/2) * scaleFactorY - newHeight/2;
        }
        if (pidItem.constraints & alignLeft){
            newX = initialX*scaleFactorX;
        }
        if (pidItem.constraints & alignRight){
            newX = (initialX + initialWidth) * scaleFactorX - newWidth;
        }
        if (pidItem.constraints & alignBottom){
            newY = (initialY + initialHeight) * scaleFactorY - newHeight;
        }
        if (pidItem.constraints & alignTop){
            newY = initialY*scaleFactorY;
        }
        pidItem.item->setGeometry(
            QRect(newX, newY, newWidth, newHeight));
    }
}

