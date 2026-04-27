#ifndef TOOLSMENU_H
#define TOOLSMENU_H

#include <QMenu>
class ParametersWindow;

struct ToolsMenuDeps{
    std::function<ParametersWindow* ()>
        makeParametersWindow;
};

class ToolsMenu : public QMenu{
    Q_OBJECT
public :
    explicit ToolsMenu(
        const ToolsMenuDeps& deps, QWidget* parent = nullptr);
};


#endif // TOOLSMENU_H
