#include "filefieldwidget.h"
#include "ui_filefieldwidget.h"

FileFieldWidget::FileFieldWidget(QWidget *parent, QFileDialog::AcceptMode acceptMode) :
    FieldWidget(parent),
    ui(new Ui::FileFieldWidget),
    m_FileDialog(this)
{
    ui->setupUi(this);

    connect(ui->pushButton,
            SIGNAL(clicked()), this,
            SLOT(handleFileDialog()));
    connect(ui->lineEdit,
            SIGNAL(textEdited(const QString&)), this,
            SLOT(handleTextEdited(const QString&)));

    //m_FileDialog.setDirectory("C:\\");
    m_FileDialog.setFileMode(QFileDialog::AnyFile);
    m_FileDialog.setAcceptMode(acceptMode);
    m_FileDialog.setAcceptDrops(false);

    QString label;

    if(acceptMode == QFileDialog::AcceptOpen)
    {
        label = "Input file";
    }
    else
    {
        label = "Output file";
    }

    Q_ASSERT(!label.isEmpty());

    setLabel(label);
    m_FileDialog.setWindowTitle(label);
}

FileFieldWidget::~FileFieldWidget()
{
    delete ui;
}

QString FileFieldWidget::toString()
{
    QString ret;

    QString lineText = ui->lineEdit->text();

    if(!lineText.isEmpty())
    {
        if(m_FileDialog.acceptMode() == QFileDialog::AcceptOpen)
        {
            ret = "-i ";
        }

        ret += "\"" + ui->lineEdit->text() + "\"";
    }

    return ret;
}

void FileFieldWidget::handleTextEdited(const QString& text)
{
    emit changed();
}

void FileFieldWidget::handleFileDialog()
{
    if(m_FileDialog.exec())
    {
        QStringList fileNames = m_FileDialog.selectedFiles();
        QLineEdit *lineEdit = sender()->parent()->findChild<QLineEdit*>();
        lineEdit->setText(fileNames.front());
        emit changed();
    }
}
