#include "flacformatfieldwidget.h"
#include "ui_flacformatfieldwidget.h"

FlacFormatFieldWidget::FlacFormatFieldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlacFormatFieldWidget)
{
    ui->setupUi(this);
}

FlacFormatFieldWidget::~FlacFormatFieldWidget()
{
    delete ui;
}
