#include "OverlayFactory.h"
#include "src/mvvm/viewmodels/AppViewModels.h"
#include "src/features/overlay/debug_display/DebugDisplayViewModel.h"

Overlay* makeOverlay(AppViewModel* appVM, QWidget* parent){
    OverlayDeps deps = {
        .makeDebugDisplayVM = [appVM](QObject* parent){
            return appVM->create<DebugDisplayViewModel>();
        }
    };
    return new Overlay(deps, parent);
}

