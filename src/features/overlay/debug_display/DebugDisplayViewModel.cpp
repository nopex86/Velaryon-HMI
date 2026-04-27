#include "DebugDisplayViewModel.h"
#include "src/services/Timer/Timer.h"


DebugDisplayViewModel::DebugDisplayViewModel(Timer* timer, QObject* parent) :
    QObject(parent), m_timer(timer)
{
    connect(m_timer, &Timer::timeout,
            this, [this]{
        emit refreshDisplay();
    });

    displayVariable("refresh rate", [this]{
        return m_timer->frequencyHz();
    });
}

size_t DebugDisplayViewModel::numberOfBindings()const {return m_bindingCount;}
size_t DebugDisplayViewModel::maxNumberOfBidings() const {return MAX_NUMBER_OF_BINDINGS;};

bool DebugDisplayViewModel::displayVariable(const QString& name, Fonction fonction){
    if (m_bindingCount >= MAX_NUMBER_OF_BINDINGS){
        return false;
    }
    DisplayBinding binding = {
        .name = name,
        .fonction = fonction
    };
    m_bindings[m_bindingCount] = binding;
    m_bindingCount++;
    emit numberOfBindingsChanged();
    return true;
}

bool DebugDisplayViewModel::getBinding(const size_t& pos, DisplayBinding& binding){
    if (pos >= m_bindingCount){
        return false;
    }
    binding = m_bindings[pos];
    return true;
}

void DebugDisplayViewModel::initialise(){
    emit numberOfBindingsChanged();
}
