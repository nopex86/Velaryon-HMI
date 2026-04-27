#include "GraphicTabFactory.h"
#include "plot/PlotViewModel.h"

GraphicTab* makeGraphicTab(AppViewModel* appVM, QWidget* parent){
    GraphicTabConfig config = {{
        {
            "Pressure section", {
                { "PS11", "#0000FF" },
                { "PS12", "#388AFF" },
                { "PS21", "#FF0000" },
                { "PS22", "#FF6363" },
                { "PS31", "#08CC0A" },
                { "PS41", "#B26701" },
                { "PS42", "#DB7F01" },
                { "PS51", "#B700FF" },
                { "PS61", "#FF9C00" },
                { "PS62", "#F08B08" },
                { "PS63", "#FFDD00" },
                { "PS64", "#FFBB2A" }
            }
        },
        {
            "Temperature section", {
             { "TS11", "#0000FF" },
             { "TS12", "#60A917" },
             { "TS41", "#B26701" },
             { "TS42", "#DB7F01" },
             { "TS61", "#FF9C00" },
             { "TS62", "#F08B08" },
             }
        },
        {
            "Flowrate section", {
             { "FM11", "#0000FF" },
             { "FM21", "#FF0000" },
             { "FM61", "#FF9C00" },
             }
        },
        {
            "Force section", {
                { "FS01", "#B26701" }
            }
        }
    }};

    GraphicTapDeps deps = {
        .makePlotViewModel = [appVM](QObject * parent){
            return appVM->create<PlotViewModel>(parent);}
    };

    return new GraphicTab(deps, config, parent);
}
