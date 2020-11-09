#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QLayoutItem>
#include <QScrollArea>
#include <QPushButton>
#include <QList>

#include <QDebug>

#include <ui/filefieldwidget.h>
#include <ui/formatfieldwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_CmdProcess(this)
{
    ui->setupUi(this);

    // Command line

    ui->textEdit_2->setText("ffmpeg.exe -hide_banner -version");
    m_CmdProcess.setProcessChannelMode(QProcess::MergedChannels);

    connect(ui->pushButton_3,
            SIGNAL(clicked()), this,
            SLOT(handleRunProcess()));
    connect(&m_CmdProcess,
            SIGNAL(started()), this,
            SLOT(handleProcessStarted()));
    connect(&m_CmdProcess,
            SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(handleProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_CmdProcess,
            SIGNAL(readyReadStandardOutput()), this,
            SLOT(handleProcessReadStdOut()));

    // Options insert buttons

    connect(ui->pushButton_5, // File input
            SIGNAL(clicked()), this,
            SLOT(handleInsertFileInputField()));
    connect(ui->pushButton_6, // File output
            SIGNAL(clicked()), this,
            SLOT(handleInsertFileOutputField()));
    connect(ui->pushButton_8, // Format
            SIGNAL(clicked()), this,
            SLOT(handleInsertFormatField()));

    // Timer

    connect(&m_CmdLineRebuildTimer,
            SIGNAL(timeout()), this,
            SLOT(handleRebuildCmdLine()));

    m_CmdLineRebuildTimer.setSingleShot(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableInputs(bool enabled)
{
    ui->groupBox->setEnabled(enabled);
    ui->frame->setEnabled(enabled);
}

void MainWindow::addFieldWidget(FieldWidget* widget)
{
    auto layout0 = new QVBoxLayout();
    layout0->addWidget(widget);

    auto groupBox0 = new QGroupBox();
    groupBox0->setTitle(widget->objectName());
    groupBox0->setLayout(layout0);

    auto scrollArea = ui->groupBox->findChild<QScrollArea*>();
    auto scrollLayout = scrollArea->findChild<QVBoxLayout*>();
    scrollLayout->addWidget(groupBox0);

    connect(widget, SIGNAL(changed()), this, SLOT(handleFieldChanged()));
    {
        QTreeWidgetItem *newTreeItem = new QTreeWidgetItem();
        newTreeItem->setText(0, widget->objectName());
        newTreeItem->setData(0, Qt::UserRole, QVariant::fromValue<QGroupBox*>(groupBox0));

        QTreeWidget *tree = ui->treeWidget;
        QTreeWidgetItem *rootTreeItem = tree->topLevelItem(0);
        rootTreeItem->addChild(newTreeItem);
        rootTreeItem->setExpanded(true);
    }
    notifyFieldChanged();
}

void MainWindow::notifyFieldChanged()
{
    m_CmdLineRebuildTimer.start(1000);
}

void MainWindow::handleRunProcess()
{
    QString cmd = ui->textEdit_2->toPlainText();

    if(!cmd.isEmpty())
    {
        //QStringList args = ui->textEdit_2->toPlainText().split(" ");
        //QString program = args.first();
        //args.removeFirst();
        //m_CmdProcess.start(program, args);

        m_CmdProcess.start(ui->textEdit_2->toPlainText());
    }
}

void MainWindow::handleProcessStarted()
{
    enableInputs(false);
    ui->textEdit->clear();
}

void MainWindow::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    enableInputs(true);
}

void MainWindow::handleProcessReadStdOut()
{
    QProcess *p = qobject_cast<QProcess*>(sender());
    QByteArray data = p->readAllStandardOutput();
    ui->textEdit->append(data);
}

void MainWindow::handleRebuildCmdLine()
{
    qDebug() << "rebuildCmdLine";

    QStringList opts;
    opts.push_back("ffmpeg.exe");
    opts.push_back("-hide_banner");
    opts.push_back("-loglevel error");
    opts.push_back("-stats");
    opts.push_back("-y");

    auto rootTreeItem = ui->treeWidget->topLevelItem(0);

    for(int i=0; i<rootTreeItem->childCount(); i++)
    {
        auto childTreeItem = rootTreeItem->child(i);
        auto treeItemData = childTreeItem->data(0, Qt::UserRole);
        auto groupBox = treeItemData.value<QGroupBox*>();
        auto field = groupBox->findChild<FieldWidget*>();
        opts.push_back(field->toString());
    }

    auto cmdLine = ui->textEdit_2;
    cmdLine->setText(opts.join(' '));
}

void MainWindow::handleFieldChanged()
{
    qDebug() << "FieldChanged";
    qDebug() << sender() << sender()->objectName();
    notifyFieldChanged();
}

void MainWindow::handleInsertFileInputField()
{
    auto widget = new FileFieldWidget(nullptr, QFileDialog::AcceptOpen);
    addFieldWidget(widget);
}

void MainWindow::handleInsertFileOutputField()
{
    auto widget = new FileFieldWidget(nullptr, QFileDialog::AcceptSave);
    addFieldWidget(widget);
}

void MainWindow::handleInsertFormatField()
{
    auto widget = new FormatFieldWidget();
    addFieldWidget(widget);
}