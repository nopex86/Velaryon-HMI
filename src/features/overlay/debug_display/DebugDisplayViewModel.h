#ifndef DEBUGDISPLAYVIEWMODEL_H
#define DEBUGDISPLAYVIEWMODEL_H

#include <QString>
#include <QObject>
class Timer;

using Variable =  std::variant<QString, double, int> ;
using Fonction = std::function<Variable ()>;

struct DisplayBinding{
    QString name;
    Fonction fonction;
};

class DebugDisplayViewModel : public QObject {
    Q_OBJECT
public :
    static constexpr size_t MAX_NUMBER_OF_BINDINGS = 10;
    DebugDisplayViewModel(Timer* timer, QObject* parent = nullptr);
    bool displayVariable(const QString& name, Fonction fonction);
    size_t numberOfBindings() const;
    size_t maxNumberOfBidings() const;
    bool getBinding(const size_t& pos, DisplayBinding& binding);
    void initialise();
private :
    Timer* m_timer = nullptr;
    std::array<DisplayBinding, MAX_NUMBER_OF_BINDINGS> m_bindings;
    size_t m_bindingCount = 0;
signals :
    void numberOfBindingsChanged();
    void refreshDisplay();
};

#endif // DEBUGDISPLAYVIEWMODEL_H
