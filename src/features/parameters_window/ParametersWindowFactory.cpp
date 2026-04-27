#include "ParametersWindowFactory.h"
#include "src/features/communication/udp/ui/UdpChannelParametersViewModel.h"
#include "src/mvvm/viewmodels/AppViewModels.h"

ParametersWindow* makeParametersWindow(AppViewModel* appVM, QWidget* parent){
    ParametersWindowDeps deps = {
        .makeUdpChannelParametersVM = [appVM](QObject* parent){
            return appVM->create<UdpChannelParametersViewModel>(parent);}
    };
    return new ParametersWindow(deps);
}
