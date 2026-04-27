#include "UdpChannelParametersWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include "UdpChannelParametersViewModel.h"

UdpChannelParametersWidget::UdpChannelParametersWidget(
    UdpChannelParametersViewModel* udpChannelParametersVM,
    QWidget* parent) :
    QWidget(parent),
    m_udpChannelParametersVM(udpChannelParametersVM)
{
    m_form = new QFormLayout(this);
    field("Endpoint adress", m_udpChannelParametersVM->EndpointAdress());
    field("Endpoint port", m_udpChannelParametersVM->EndpointPort());
    field("Target adress", m_udpChannelParametersVM->TargetAdress());
    field("Target port", m_udpChannelParametersVM->TargetPort());

}

void UdpChannelParametersWidget::field(const QString& name, QString value)
{
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setText(value);
    lineEdit->setPlaceholderText(value);
    m_form->addRow(name + " :", lineEdit);
    m_formValues[name] = lineEdit;
}
void UdpChannelParametersWidget::applyParameters(){
    m_udpChannelParametersVM->setEndpointAdress(m_formValues["Endpoint adress"]->text());
    m_udpChannelParametersVM->setEndpointPort(m_formValues["Endpoint port"]->text().toShort());
    m_udpChannelParametersVM->setTargetAdress(m_formValues["Target adress"]->text());
    m_udpChannelParametersVM->setTargetPort(m_formValues["Target port"]->text().toShort());
    m_udpChannelParametersVM->restartEndpoint();
}


