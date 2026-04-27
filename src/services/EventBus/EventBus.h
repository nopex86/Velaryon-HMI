#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <any>
#include <functional>
#include <iostream>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

class DataBus {
public:
    template <typename T>
    void subscribe(const std::string& topic, std::function<void(const T&)> cb) {
        auto& subs = subscribers_[topic];
        subs.push_back(Subscriber{
            std::type_index(typeid(T)),
            [cb = std::move(cb)](const std::any& payload) {
                cb(std::any_cast<const T&>(payload));
            },
        });
    }

    template <typename T>
    void publish(const std::string& topic, const T& payload) const {
        auto it = subscribers_.find(topic);
        if (it == subscribers_.end()) {
            return;
        }

        const std::any boxed = payload;

        for (const auto& sub : it->second) {
            if (sub.type != std::type_index(typeid(T))) {
                continue;  // Ignore les abonnés d'un autre type sur ce topic
            }
            sub.invoke(boxed);
        }
    }

private:
    struct Subscriber {
        std::type_index type;
        std::function<void(const std::any&)> invoke;
    };

    std::unordered_map<std::string, std::vector<Subscriber>> subscribers_;
};

struct SensorData {
    int id;
    double value;
};

int main() {
    DataBus bus;

    bus.subscribe<SensorData>(
        "sensor/update", [](const SensorData& d) {
            std::cout << "Sensor " << d.id << " value=" << d.value << "\n";
        });

    bus.subscribe<int>("app/tick", [](int t) {
        std::cout << "Tick: " << t << "\n";
    });

    bus.publish("app/tick", 1);
    bus.publish("sensor/update", SensorData{42, 3.14});
    bus.publish("app/tick", 2);

    return 0;
}

#endif // EVENTBUS_H
