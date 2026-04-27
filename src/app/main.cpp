/*******************************************************************************
**                                                                            **
**   Velaryon is a modern and intuitive Human-Machine Interface (HMI)         **
**   designed to facilitate control and monitoring for the Arrax student      **
**   rocket engine project.                                                   **
**                                                                            **
**   This software provides a user-friendly interface for engineers and       **
**   students working on the development and testing of the Arrax rocket      **
**   engine at the Innovative Propulsion Laboratory (IPL).                    **
**                                                                            **
**   This software is the intellectual property of Innovative Propulsion      **
**   Laboratory and is intended for educational and research purposes only.   **
**                                                                            **
********************************************************************************
**           Author: Mehdi Delouane                                           **
**           Contact: mehdi.delouane@ipsa.fr                                  **
**             Date: 19.02.2025                                               **
**             Version: 2.2.0                                                 **
********************************************************************************
**  This version was designed specifically for the Arrax project.             **
**  You may use this version as a reference but do not modify it directly.    **
*******************************************************************************/

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
// #include "src/ui/common/LoadingScreen.h"
#include "src/app/MainWindow.h"
#include "src/mvvm/viewmodels/AppViewModels.h"
#include "src/services/AppServices.h"
#include "src/mvvm/models/AppModels.h"
#include "src/features/communication/udp/UdpChannel.h"
int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    AppServices services = AppServices();
    AppModels models = AppModels(&services);
    AppViewModel appVM = AppViewModel(&services, &models);

    // Create the main window with tabs
    MainWindow mainWindow(&appVM);
    auto* udpChannel=  services.create<UdpChannel>();
    udpChannel->startEndpoint();
    // mainWindow->hide();  // Initially hide the main window

    // // Create and show the loading screen
    // QWidget* loadingScreen = createLoadingScreen(mainWindow);
    // loadingScreen->show();
    return app.exec();
}

// #include "mainwindow.h"

// #include <QApplication>
// #include <QLocale>
// #include <QTranslator>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);

//     QTranslator translator;
//     const QStringList uiLanguages = QLocale::system().uiLanguages();
//     for (const QString &locale : uiLanguages) {
//         const QString baseName = "VelaryonV3_" + QLocale(locale).name();
//         if (translator.load(":/i18n/" + baseName)) {
//             a.installTranslator(&translator);
//             break;
//         }
//     }
//     MainWindow w;
//     w.show();
//     return a.exec();
// }
