#pragma once

#include "TankPressureControlFrameWidget.h"
#include "src/mvvm/viewmodels/AppViewModels.h"

TankPressureControlFrame* makeTankPressureControlFrame(
    AppViewModel* appVM, TpcFrameConfig config, QWidget* parent);
