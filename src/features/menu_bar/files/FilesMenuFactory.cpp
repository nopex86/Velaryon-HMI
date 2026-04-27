#include "src/mvvm/viewmodels/AppViewModels.h"
#include "FilesMenuFactory.h"
#include "src/features/file_export/ui/ExportMenuViewModel.h"

FilesMenu* makeFileMenu(AppViewModel* appVM, QWidget* parent){
    FilesMenuDeps deps = {
        .makeExportMenuVM = [appVM](QObject* parent){
            return appVM->create<ExportMenuViewModel>(parent);
        }
    };
    return new FilesMenu(deps, parent);
}
