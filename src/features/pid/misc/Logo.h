#ifndef LOGO_H
#define LOGO_H

#include <QLabel>
#include <QWidget>
#include <QPixmap>

class Logo : public QLabel{
    Q_OBJECT
public :
    explicit Logo(QWidget* parent = nullptr);
    QSize sizeHint()const override;
private :
    QSize m_size = {200, 80};
};

#endif // LOGO_H
