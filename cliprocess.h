#ifndef CLIPROCESS_H
#define CLIPROCESS_H

#include <QObject>
#include <QProcess>

class CLIProcess : public QObject
{
    Q_OBJECT
public:
    CLIProcess(QObject* parent);
    void start(const QString& cmd);

private:
    QProcess m_Process;
    bool m_OutputHasFinished;
    bool m_ProcessHasFinished;

private slots:
    void handleStarted();
    void handleFinished(int, QProcess::ExitStatus);
    void handleReadStdOut();

signals:
    void consoleLine(const QString&);
    void consoleStarted();
    void consoleFinished();
};

#endif // CLIPROCESS_H
