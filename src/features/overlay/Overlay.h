#pragma once

#include <QWidget>

class DebugDisplayViewModel;
struct OverlayDeps{
    std::function<DebugDisplayViewModel* (QObject* parent)>
        makeDebugDisplayVM;
};

class Overlay : public QWidget{
    Q_OBJECT
public :
    explicit Overlay(const OverlayDeps& deps, QWidget* parent = nullptr);
};
