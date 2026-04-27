#pragma once

#include "ParametersWindow.h"
class AppViewModel;
class QWidget;

ParametersWindow* makeParametersWindow(AppViewModel* appVM, QWidget* parent);
