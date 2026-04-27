#ifndef TVCCONTROLWIDGET_H
#define TVCCONTROLWIDGET_H

#include <QLabel>

class tvcControlFrame : public QWidget {
    Q_OBJECT
public :
    explicit tvcControlFrame(QWidget* parent, const QFont& font);
protected:
    void resizeEvent(QResizeEvent* event) override;
private :
    QFont m_font;
    QFrame* m_frame;
    QLabel* m_label;
    QLabel* m_tvc_disabled;
};


#endif // TVCCONTROLWIDGET_H
