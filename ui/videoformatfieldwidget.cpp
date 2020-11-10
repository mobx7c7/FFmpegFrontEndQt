#include "videoformatfieldwidget.h"
#include "ui_videoformatfieldwidget.h"

VideoFormatFieldWidget::VideoFormatFieldWidget(QWidget *parent) :
    FieldWidget(parent),
    ui(new Ui::VideoFormatFieldWidget)
{
    ui->setupUi(this);

    setLabel("Video format");
}

VideoFormatFieldWidget::~VideoFormatFieldWidget()
{
    delete ui;
}

QString VideoFormatFieldWidget::toString()
{
    QStringList args;

    auto strFormat = ui->lineEdit->text();

    if(!strFormat.isEmpty())
    {
        auto strOtherOpts = ui->lineEdit_3->text();

        args << QString("-f %1").arg(strFormat) << strOtherOpts;

        auto strCodec = ui->lineEdit_2->text();
        if(!strCodec.isEmpty())
        {
            args << QString("-c:v %1").arg(strCodec);
        }

        auto numBitRate = ui->spinBox_3->value();
        if(numBitRate > 0)
        {
            args << QString("-b:v %1").arg(numBitRate);
        }

        auto strPixelFormat = ui->comboBox->currentData().toString();
        if(!strPixelFormat.isEmpty())
        {
            args << QString("-pixel_fmt %1").arg(strPixelFormat);
        }

        auto numFPS = ui->doubleSpinBox->value();
        if(numFPS > 0.0)
        {
            args << QString("-fps %1").arg(numFPS);
        }

        auto numSizeW = ui->spinBox->value();
        auto numSizeH = ui->spinBox_2->value();
        if(numSizeW > 0 && numSizeH > 0)
        {
            args << QString("-size %1x%2").arg(numSizeW).arg(numSizeH);
        }
    }

    return args.join(' ');
}

void VideoFormatFieldWidget::handleChanged()
{
    emit changed();
}
