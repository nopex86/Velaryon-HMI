#ifndef UDPCHANNELPARAMETERSWIDGET_H
#define UDPCHANNELPARAMETERSWIDGET_H
#include <QFormLayout>
#include <QWidget>
#include <QLineEdit>

class UdpChannelParametersViewModel;
class UdpChannelParametersWidget : public QWidget{
    Q_OBJECT
public :
    explicit UdpChannelParametersWidget(
        UdpChannelParametersViewModel* udpChannelParametersVM,
        QWidget* parent = nullptr);
private :
    UdpChannelParametersViewModel* m_udpChannelParametersVM;
    QFormLayout* m_form;
    QMap<QString, QLineEdit*> m_formValues;
    void field(const QString& name, QString value = "");
public slots :
    void applyParameters();
};

#endif // UDPCHANNELPARAMETERSWIDGET_H
