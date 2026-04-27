#ifndef TESTLAUNCHWIDGET_H
#define TESTLAUNCHWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QDir>
#include <QGridLayout>
#include <QMap>
#include <QComboBox>

class TestLauncherViewModel;

class TestLauncher : public QWidget {
    Q_OBJECT
public :
    explicit TestLauncher(TestLauncherViewModel* vm, QWidget* parent=nullptr);
public slots :
    void renderFileList();
    void renderFileContent();
    void showFileDialogWindow();
    void showConfirmationWindow();
private :
    QGridLayout* m_sequenceParametersGrid = nullptr;
    QComboBox* m_comboBox = nullptr;
    TestLauncherViewModel* m_vm= nullptr;
};

#endif // TESTLAUNCHWIDGET_H
