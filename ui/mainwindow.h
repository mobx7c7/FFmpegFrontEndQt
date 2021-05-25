#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <ui/fieldwidget.h>

#include <QMutexLocker>

#include <cliprocess.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addFieldWidget(FieldWidget*);

private:
    Ui::MainWindow *ui;
    CLIProcess m_CliProcess;
    QTimer m_CmdLineRebuildTimer;
    QTimer m_ConsoleRepaintTimer;
    QMutex m_ConsoleMutex;

    void enableInputs(bool);
    void notifyFieldChanged();

private slots:
    void handleRunProcess();
    void handleConsoleLine(const QString&);
    void handleConsoleStarted();
    void handleConsoleFinished();
    void handleConsoleRepaint();
    void handleRebuildCmdLine();
    void handleFieldChanged();
    void handleFieldAlloc(FieldWidget*);
};
#endif // MAINWINDOW_H
