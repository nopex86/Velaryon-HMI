#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>

class AppViewModel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(AppViewModel* appVM, QWidget* = nullptr);
};

#endif // MAINWINDOW_H
