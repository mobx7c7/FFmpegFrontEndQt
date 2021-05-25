#include "cliprocess.h"
#include <QDebug>

CLIProcess::CLIProcess(QObject* parent)
    : QObject(parent)
{
    connect(&m_Process,
            SIGNAL(started()), this,
            SLOT(handleStarted()));
    connect(&m_Process,
            SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(handleFinished(int, QProcess::ExitStatus)));
    connect(&m_Process,
            SIGNAL(readyRead()), this,
            SLOT(handleReadStdOut()));

    m_Process.setReadChannel(QProcess::StandardOutput);
    m_Process.setProcessChannelMode(QProcess::MergedChannels);
}

void CLIProcess::start(const QString &cmd)
{
    m_Process.start(cmd, QProcess::Unbuffered | QProcess::ReadWrite);
}

void CLIProcess::handleStarted()
{
    m_ProcessHasFinished = false;
    m_OutputHasFinished = false;
    emit consoleStarted();
}

void CLIProcess::handleFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "ProcessFinished" << m_ProcessHasFinished;

    /*
    if(!m_ProcessHasFinished)
    {
        if(m_OutputHasFinished)
        {
            qDebug() << "ProcessFinished" << "consoleFinished";
            emit consoleFinished();
            m_ProcessHasFinished = true;
        }
    }
    */

    emit consoleFinished();
}

void CLIProcess::handleReadStdOut()
{
    qDebug() << "ProcessReadStdOut" << m_OutputHasFinished << m_Process.bytesAvailable();
    static QByteArray buf(128, Qt::Initialization::Uninitialized);

    //if(!m_OutputHasFinished)
    {

        QTextStream textStream(m_Process.readAll());
        QString line;
        while (!textStream.atEnd())
        {
            line = textStream.readLine();
            //line.remove("\r\n");
            emit consoleLine(line);
        }


//        auto textLines = QString(m_Process.readAllStandardOutput()).split("\n");
//        auto textIter = textLines.cbegin();
//        while(textIter != textLines.cend()){
//            auto line = *textIter;
//            emit consoleLine(line);
//            textIter++;
//        }


//        auto text = QString(m_Process.readAllStandardOutput());
//        emit consoleLine(text);

//        // Não atualiza durante trabalho de codificação
//        QString line;
//        while(m_Process.canReadLine()){
//            line = m_Process.readLine();
//            line.remove("\r\n");
//            emit consoleLine(line);
//        }

//        if()
//        {
//            qDebug() << "ProcessReadStdOut" << "consoleFinished" << m_Process.bytesAvailable();
//            emit consoleFinished();
//            m_OutputHasFinished = true;
//        }

    }
}
