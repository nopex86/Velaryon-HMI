#include "GraphicTabView.h"
#include "plot/PlotWidget.h"
#include <QHBoxLayout>

GraphicTab::GraphicTab(
    const GraphicTapDeps& deps,
    const GraphicTabConfig& config,
    QWidget* parent) :
    QWidget(parent){
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignCenter);


    for (const auto& c : config.plots){
        PlotViewModel* PlotVM = deps.makePlotViewModel(this);
        PlotVM->set(c);
        Plot* plot = new Plot(PlotVM, this);
        mainLayout->addWidget(plot, 1);
    }
}
