#ifndef PIDLAYOUT_H
#define PIDLAYOUT_H

#include <QLayout>
#include <QList>




class PidLayout : public QLayout {
    Q_OBJECT
public:
    enum Constraints {
        noConstraints = 1,
        resize = 2,
        alignLeft = 4,
        alignRight = 8,
        alignTop = 16,
        alignBottom = 32,
        alignCenter = 64
    };

    explicit PidLayout(QWidget *parent = nullptr);
    ~PidLayout();

    // Ajout avec position relative
    void addWidget(QWidget* widget, int contstraints = noConstraints);

    void addItem(QLayoutItem *item) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    int count() const override;
    QSize sizeHint() const override;
    void setGeometry(const QRect &rect) override;

private:
    struct LayoutItem {
        QLayoutItem* item;
        float relX; // position X relative (0.0 à 1.0)
        float relY; // position Y relative (0.0 à 1.0)
        int constraints;
    };
    QList<LayoutItem> m_items;
};

// PidLayout.h

#endif // PIDLAYOUT_H
