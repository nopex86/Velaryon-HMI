#ifndef APPMODELS_H
#define APPMODELS_H

#include <QObject>
#include <typeindex>

class AppServices;
class AppModels : public QObject{
    Q_OBJECT
public :
    explicit AppModels(AppServices* appM, QObject* parent = nullptr);
    template <typename T>
    T* create(QObject* parent = nullptr){
        auto it = m_factories.find(std::type_index(typeid(T)));
        if (it != m_factories.end()){
            return static_cast<T*>(it->second(parent));
        }
        return nullptr;
    }

private:
    template <typename T>
    void registerFactory(
        std::function<T*(QObject*)> factory){
        m_factories[std::type_index(typeid(T))] = [factory](QObject* p){
            return factory(p);
        };
    }

    std::unordered_map<
        std::type_index,
        std::function<QObject*(QObject*)>
    > m_factories;
};

#endif // APPMODELS_H
