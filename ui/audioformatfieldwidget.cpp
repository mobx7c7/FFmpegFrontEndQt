#include "audioformatfieldwidget.h"
#include "ui_audioformatfieldwidget.h"

AudioFormatFieldWidget::AudioFormatFieldWidget(QWidget *parent) :
    FieldWidget(parent),
    ui(new Ui::AudioFormatFieldWidget)
{
    ui->setupUi(this);

    setLabel("Audio format");
}

AudioFormatFieldWidget::~AudioFormatFieldWidget()
{
    delete ui;
}

QString AudioFormatFieldWidget::toString()
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
            args << QString("-c:a %1").arg(strCodec);
        }

        auto numBitRate = ui->spinBox_3->value();
        if(numBitRate > 0)
        {
            args << QString("-b:a %1").arg(numBitRate);
        }

        auto strSampleFormat = ui->comboBox->currentData().toString();
        if(!strSampleFormat.isEmpty())
        {
            args << QString("-sample_fmt %1").arg(strSampleFormat);
        }

        auto numSampleRate = ui->spinBox->value();
        if(numSampleRate > 0)
        {
            args << QString("-ar %1").arg(numSampleRate);
        }

        auto strChannelFormat = ui->comboBox_2->currentData().toString();
        if(!strChannelFormat.isEmpty())
        {
            args << QString("-channel_format").arg(strChannelFormat);
        }

        auto numChannelCount = ui->spinBox_2->value();
        if(numChannelCount > 0)
        {
            args << QString("-ac").arg(numChannelCount);
        }
    }

    return args.join(' ');
}

void AudioFormatFieldWidget::handleChanged()
{
    emit changed();
}
