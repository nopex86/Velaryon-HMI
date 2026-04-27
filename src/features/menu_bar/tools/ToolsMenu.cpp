 #include "ToolsMenu.h"
#include <QAction>

ToolsMenu::ToolsMenu(const ToolsMenuDeps& deps, QWidget* parent) :
    QMenu("&Tools", parent)
{
    QAction* parametersAction = addAction("&Parameters");
    connect(parametersAction, &QAction::triggered,
            this, [deps]{
        deps.makeParametersWindow();
    });
}
