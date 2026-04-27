#include "Logo.h"

Logo::Logo(QWidget* parent) : QLabel(parent){
    QPixmap pixmap("./pictures/Logo_IPL.png");
    setPixmap(pixmap);
    setScaledContents(true);
}

QSize Logo::sizeHint() const{
    return m_size;
}
