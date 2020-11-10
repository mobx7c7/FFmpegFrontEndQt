#ifndef AUDIOFORMATFIELDWIDGET_H
#define AUDIOFORMATFIELDWIDGET_H

#include <ui/fieldwidget.h>

namespace Ui {
class AudioFormatFieldWidget;
}

class AudioFormatFieldWidget : public FieldWidget
{
    Q_OBJECT

public:
    explicit AudioFormatFieldWidget(QWidget *parent = nullptr);
    ~AudioFormatFieldWidget();
    QString toString() override;

private:
    Ui::AudioFormatFieldWidget *ui;

private slots:
    void handleChanged();
};

#endif // AUDIOFORMATFIELDWIDGET_H
