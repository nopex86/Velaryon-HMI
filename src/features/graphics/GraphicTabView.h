#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
class AppViewModel;

struct PlotConfig;
struct GraphicTabConfig{
    std::vector<PlotConfig> plots;
};

class PlotViewModel;

struct GraphicTapDeps {
    std::function<PlotViewModel* (QObject* parent)> makePlotViewModel;
};

class GraphicTab : public QWidget {
    Q_OBJECT
public :
    explicit GraphicTab(
        const GraphicTapDeps& deps,
        const GraphicTabConfig& config,
        QWidget* parent = nullptr);
};

#endif // GRAPHIC_H
