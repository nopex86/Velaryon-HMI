#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QWidget>

class AppViewModel;
class UdpChannelParametersViewModel;

struct ParametersWindowDeps{
    std::function<UdpChannelParametersViewModel* (QObject* parent)>
        makeUdpChannelParametersVM;
};

class ParametersWindow : public QWidget {
    Q_OBJECT
public :
    explicit ParametersWindow(
        const ParametersWindowDeps& deps);
};

#endif // PARAMETERSWINDOW_H
