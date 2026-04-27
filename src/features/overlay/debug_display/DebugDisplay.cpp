#include "DebugDisplay.h"

Data::Data(DisplayBinding binding, QWidget* parent) :
    QLabel(parent), m_binding(binding){}

void Data::onRefresh(){
    std::visit([this](auto v){
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, double>){
            setText(m_binding.name + " : " + QString::number(v));
        }
        if constexpr (std::is_same_v<T, int>){
            setText(m_binding.name + " : " + QString::number(v));
        }
        if constexpr (std::is_same_v<T, QString>){
            setText(m_binding.name + " : " + v);
        }
    }, m_binding.fonction());
}

DebugDisplay::DebugDisplay(DebugDisplayViewModel* vm, QWidget* parent) :
    QFrame(parent), m_vm(vm)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_mainLayout->setContentsMargins(10,0,0,0);
    m_mainLayout->setSpacing(3);

    m_datas.fill(nullptr);
    connect(m_vm, &DebugDisplayViewModel::numberOfBindingsChanged,
            this, &DebugDisplay::onNumberOfBindingsChanged);

    m_vm->initialise();
}

void DebugDisplay::onNumberOfBindingsChanged(){
    for (size_t i = 0 ; i < m_vm->numberOfBindings(); i++){
        if (m_datas[i] != nullptr) continue;
        DisplayBinding binding;
        if (!m_vm->getBinding(i, binding)) continue;
        Data* data = new Data(binding, this);
        m_mainLayout->addWidget(data);
        m_datas[i] = data;

        connect(m_vm, &DebugDisplayViewModel::refreshDisplay,
                m_datas[i], &Data::onRefresh);
    }
}
