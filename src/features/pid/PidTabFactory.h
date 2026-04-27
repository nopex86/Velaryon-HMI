#pragma once
#include "PidTab.h"

class AppViewModel;

PidTab* makePidTab(AppViewModel* appVM, const PidTabConfig& config, QWidget* parent);
