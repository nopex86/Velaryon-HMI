#include "PidBackground.h"

PidBackground::PidBackground(
    const QString& path,
    int width, int height,
    QWidget* parent) :
    QLabel(parent){
    m_originalSize = QSize(width, height);
    QPixmap arrax_engine(path);
    setPixmap(arrax_engine);
    setScaledContents(true);
    setGeometry(0, 0, width, height);  // Set position and size
}

QSize PidBackground::sizeHint() const{
    return m_originalSize;
}
