#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

class AppViewModel;
class FileSystem;
class Logger;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(AppViewModel* appVM,
                        FileSystem* fileSystem,
                        Logger* logger,
                        QWidget* = nullptr);
};

#endif // MAINWINDOW_H
