#ifndef PIDBACKGROUND_H
#define PIDBACKGROUND_H

#include <QLabel>

class PidBackground : public QLabel {
    Q_OBJECT
public :
    explicit PidBackground(const QString& path, int width, int height, QWidget* parent = nullptr);
    QSize sizeHint() const override;
private :
    QSize m_originalSize;
};


#endif // PIDBACKGROUND_H
