#include "formatfieldwidget.h"
#include "ui_formatfieldwidget.h"

FormatFieldWidget::FormatFieldWidget(QWidget *parent) :
    FieldWidget(parent),
    ui(new Ui::FormatFieldWidget)
{
    ui->setupUi(this);

    connect(ui->lineEdit,
            SIGNAL(textEdited(const QString&)), this,
            SLOT(handleTextEdited(const QString&)));

    setLabel("Custom format");
}

void FormatFieldWidget::handleTextEdited(const QString& text)
{
    emit changed();
}

FormatFieldWidget::~FormatFieldWidget()
{
    delete ui;
}

QString FormatFieldWidget::toString()
{
    QString ret;

    QString lineText = ui->lineEdit->text();

    if(!lineText.isEmpty())
    {
        ret += "-f " + lineText;
    }

    return ret;
}
