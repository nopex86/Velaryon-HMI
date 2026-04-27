#include "Overlay.h"
#include "src/features/pid/PidLayout.h"
#include "src/features/overlay/debug_display/DebugDisplay.h"
#include "src/features/overlay/debug_display/DebugDisplayViewModel.h"

Overlay::Overlay(const OverlayDeps& deps, QWidget* parent){
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    PidLayout* overlayLayout = new PidLayout(this);
    DebugDisplayViewModel* debugDisplayVM = deps.makeDebugDisplayVM(this);
    DebugDisplay* debugDisplay = new DebugDisplay(debugDisplayVM, this);
    debugDisplay->setGeometry(0, 200, 500, 500);
    overlayLayout->addWidget(debugDisplay, PidLayout::alignCenter | PidLayout::alignLeft);

}
