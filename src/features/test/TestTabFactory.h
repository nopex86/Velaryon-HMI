#pragma once

#include "src/mvvm/viewmodels/AppViewModels.h"
#include "TestTabView.h"

TestTab* makeTestTab(
    AppViewModel* appVM,
    QWidget* parent);
