#include "FilesMenu.h"
#include "src/features/file_export/ui/ExportMenuViewModel.h"
#include "src/features/file_export/ui/ExportMenu.h"

FilesMenu::FilesMenu(
    const FilesMenuDeps& deps,
    QWidget* parent) :
        QMenu("&Files", parent)
{
    ExportMenuViewModel* exportMenuVM = deps.makeExportMenuVM(this);
    addMenu(new ExportMenu(exportMenuVM, this));
}
