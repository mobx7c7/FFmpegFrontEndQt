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

#include <ffprogressreader.h>
#include <ffprogressdecoder.h>
#include <ffbuildprobe.h>

#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_CliProcess(this)
{
    ui->setupUi(this);

    // Command line

    connect(ui->pushButton_3,
            SIGNAL(clicked()), this,
            SLOT(handleRunProcess()));
    connect(&m_CliProcess,
            SIGNAL(consoleLine(const QString&)), this,
            SLOT(handleConsoleLine(const QString&)));
    connect(&m_CliProcess,
            SIGNAL(consoleStarted()), this,
            SLOT(handleConsoleStarted()));
    connect(&m_CliProcess,
            SIGNAL(consoleFinished()), this,
            SLOT(handleConsoleFinished()));

    // Timer

    connect(&m_CmdLineRebuildTimer,
            SIGNAL(timeout()), this,
            SLOT(handleRebuildCmdLine()));
    connect(&m_ConsoleRepaintTimer,
            SIGNAL(timeout()), this,
            SLOT(handleConsoleRepaint()));

    m_CmdLineRebuildTimer.setInterval(1000);
    m_CmdLineRebuildTimer.setSingleShot(true);
    m_ConsoleRepaintTimer.setInterval(20);
    m_ConsoleRepaintTimer.setSingleShot(true);

    // Test

    connect(ui->pushButton_4, &QPushButton::clicked, [&](){
        ui->textEdit_2->setText("ffmpeg.exe -h full");
        handleRunProcess();
    });

    /*
    QString input, result;
    input =
            "oausdhahdhaousduhausdhasd\r\n"
            "oausdhahdhaousduhausdhasd\r\n"
            "bitrate= 123.5kbits/s\r\n"
            "total_size=3628085\r\n"
            "out_time_us=235013500\r\n"
            "out_time_ms=235013500\r\n"
            "out_time=00:03:55.013500\r\n"
            "dup_frames=0\r\n"
            "drop_frames=0\r\n"
            "speed=38.8x\r\n"
            "progress=end\r\n"
            "zuchxuhzuxuhzxhzuhchzucuh\r\n"
            "ootioyirtoyvmdmmvmdvmmvmm\r\n";

    FFProgressReader reader;
    int end = reader.process(input, result);

    FFProgressDecoder decoder;
    decoder.process(result);

    QPlainTextEdit *consoleText = ui->plainTextEdit;
    //consoleText->appendPlainText(result);
    consoleText->appendPlainText(input.mid(end+1));
    qDebug() << end;
    */

    std::default_random_engine re;
    std::uniform_int_distribution<int> dis;

    auto consolePrint = [&](const QList<FFTableLine> &data){
        static const QString format("<font color=%1>%2</font>");
        auto fontColorHex = QColor::fromHsv(dis(re)%359, 127, 255).name(QColor::NameFormat::HexRgb);
        auto consoleText = ui->plainTextEdit;
        for(auto it = data.begin(); it != data.end(); it++)
        {
            auto json = it->toString().trimmed();

            QStringList html;
            html << format.arg(fontColorHex, json);
            auto text = html.join(' ').replace("\n","<br>").replace("    ","&nbsp;&nbsp;&nbsp;&nbsp;");
            qDebug() << text;
            consoleText->appendHtml(text);
        }
    };

    FFBuildProbe probe;
    probe.refresh();
    ui->plainTextEdit->setPlainText(probe.toString());
//    consolePrint(probe.getBuildConf());
//    consolePrint(probe.getFormats());
//    consolePrint(probe.getDevices());
//    consolePrint(probe.getCodecs());
//    consolePrint(probe.getBsfs());
//    consolePrint(probe.getProtocols());
//    consolePrint(probe.getFilters());
//    consolePrint(probe.getPixFmts());
//    consolePrint(probe.getLayouts());
//    consolePrint(probe.getSampleFmts());
//    consolePrint(probe.getColors());
//    consolePrint(probe.getHwAccels());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableInputs(bool enabled)
{
    ui->groupBox->setEnabled(enabled);
    ui->widget->setEnabled(enabled);
    ui->pushButton_3->setEnabled(enabled);
    ui->pushButton_4->setEnabled(enabled);
}

void MainWindow::addFieldWidget(FieldWidget* widget)
{
    auto layout0 = new QVBoxLayout();
    layout0->addWidget(widget);

    auto groupBox0 = new QGroupBox();
    groupBox0->setTitle(widget->label());
    groupBox0->setLayout(layout0);

    auto scrollArea = ui->groupBox->findChild<QScrollArea*>();
    auto scrollLayout = scrollArea->findChild<QVBoxLayout*>();
    scrollLayout->addWidget(groupBox0);

    connect(widget, SIGNAL(changed()), this, SLOT(handleFieldChanged()));
    {
        QTreeWidgetItem *newTreeItem = new QTreeWidgetItem();
        newTreeItem->setText(0, groupBox0->title());
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
    m_CmdLineRebuildTimer.start();
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

        qDebug() << QString("cmd: %1").arg(ui->textEdit_2->toPlainText());
        m_CliProcess.start(ui->textEdit_2->toPlainText());
    }
}

void MainWindow::handleConsoleLine(const QString& line)
{
    QPlainTextEdit *consoleText = ui->plainTextEdit;
    consoleText->appendPlainText(line);
    //consoleText->repaint(); // fica irresponsivo
    //consoleText->viewport()->repaint(); // fica irresponsivo
    QCoreApplication::processEvents(); // ok
}

void MainWindow::handleConsoleStarted()
{
    enableInputs(false);
    ui->plainTextEdit->clear();
    //m_ConsoleRepaintTimer.start();
}

void MainWindow::handleConsoleFinished()
{
    enableInputs(true);
    //m_ConsoleRepaintTimer.stop();
}

void MainWindow::handleConsoleRepaint()
{
    QPlainTextEdit *consoleText = ui->plainTextEdit;
    consoleText->repaint();
}

void MainWindow::handleRebuildCmdLine()
{
    qDebug() << "RebuildCmdLine";

    QStringList opts;
    opts += "ffmpeg.exe";
    opts += "-hide_banner";
    //opts += "-loglevel error";
    opts += "-progress pipe:2";
    opts += "-nostats";
    opts += "-y";

    auto rootTreeItem = ui->treeWidget->topLevelItem(0);

    for(int i=0; i<rootTreeItem->childCount(); i++)
    {
        auto childTreeItem = rootTreeItem->child(i);
        auto treeItemData = childTreeItem->data(0, Qt::UserRole);
        auto groupBox = treeItemData.value<QGroupBox*>();
        auto field = groupBox->findChild<FieldWidget*>();

        auto fontColor = QColor::fromHsv(qrand()%359, 127, 255).name(QColor::NameFormat::HexRgb);
        opts.push_back(QString("<font color=%1>%2</font>").arg(fontColor).arg(field->toString()));
    }

    auto cmdLine = ui->textEdit_2;
    qDebug() << opts;
    cmdLine->setHtml(opts.join(' '));
}

void MainWindow::handleFieldChanged()
{
    qDebug() << "FieldChanged";
    qDebug() << sender() << sender()->objectName();
    notifyFieldChanged();
}

void MainWindow::handleFieldAlloc(FieldWidget *widget)
{
    qDebug() << "FieldAlloc";
    qDebug() << sender() << sender()->objectName();
    addFieldWidget(widget);
}
