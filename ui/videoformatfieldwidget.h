#ifndef VIDEOFORMATFIELDWIDGET_H
#define VIDEOFORMATFIELDWIDGET_H

#include <ui/fieldwidget.h>

namespace Ui {
class VideoFormatFieldWidget;
}

class VideoFormatFieldWidget : public FieldWidget
{
    Q_OBJECT

public:
    explicit VideoFormatFieldWidget(QWidget *parent = nullptr);
    ~VideoFormatFieldWidget();
    QString toString() override;

private:
    Ui::VideoFormatFieldWidget *ui;

private slots:
    void handleChanged();
};

#endif // VIDEOFORMATFIELDWIDGET_H
