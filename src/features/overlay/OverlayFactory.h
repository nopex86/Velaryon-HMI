#pragma once

#include "Overlay.h"
class AppViewModel;

Overlay* makeOverlay(AppViewModel* appVM, QWidget* parent = nullptr);
