#pragma once

#include "ToolsMenu.h"
class AppViewModel;
class QWidget;

ToolsMenu* makeToolsMenu(AppViewModel* appVM, QWidget* parent);
