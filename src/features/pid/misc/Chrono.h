#ifndef CHRONO_H
#define CHRONO_H


#include <QWidget>

class Chrono : public QWidget{
    Q_OBJECT
public :
    explicit Chrono(QWidget* parent = nullptr);
    QSize sizeHint() const override;
private :
    QSize m_size = {250, 60};
};

#endif // CHRONO_H
