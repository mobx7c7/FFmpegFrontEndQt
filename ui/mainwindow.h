#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <ui/fieldwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QProcess m_CmdProcess;
    QTimer m_CmdLineRebuildTimer;

    void enableInputs(bool);
    void addFieldWidget(FieldWidget*);
    void notifyFieldChanged();

private slots:
    void handleRunProcess();
    void handleProcessStarted();
    void handleProcessFinished(int, QProcess::ExitStatus);
    void handleProcessReadStdOut();
    void handleRebuildCmdLine();
    void handleFieldChanged();
    void handleInsertFileInputField();
    void handleInsertFileOutputField();
    void handleInsertFormatField();
};
#endif // MAINWINDOW_H
