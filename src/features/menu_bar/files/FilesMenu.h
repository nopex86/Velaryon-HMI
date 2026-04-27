#pragma once

#include <QMenu>
#include <QAction>

class ExportMenuViewModel;

struct FilesMenuDeps {
    std::function<ExportMenuViewModel* (QObject* parent)> makeExportMenuVM;
};

class FilesMenu : public QMenu{
    Q_OBJECT
public :
    explicit FilesMenu(
        const FilesMenuDeps& deps,
        QWidget* parent = nullptr);
};

