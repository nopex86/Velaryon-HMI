#include "ToolsMenuFactory.h"
#include "src/mvvm/viewmodels/AppViewModels.h"
#include "src/features/parameters_window/ParametersWindowFactory.h"

ToolsMenu* makeToolsMenu(AppViewModel* appVM, QWidget* parent){
    ToolsMenuDeps deps = {
                          .makeParametersWindow = [appVM](){
            return makeParametersWindow(appVM, nullptr);
        }
};
    return new ToolsMenu(deps, parent);
}
