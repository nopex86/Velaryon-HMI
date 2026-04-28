#include "Logo.h"

Logo::Logo(const QString& picturePath, QWidget* parent) : QLabel(parent){
    QPixmap pixmap(picturePath);
    setPixmap(pixmap);
    setScaledContents(true);
}

QSize Logo::sizeHint() const{
    return m_size;
}
