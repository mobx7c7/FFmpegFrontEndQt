#ifndef FLACFORMATFIELDWIDGET_H
#define FLACFORMATFIELDWIDGET_H

#include <QWidget>

namespace Ui {
class FlacFormatFieldWidget;
}

class FlacFormatFieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FlacFormatFieldWidget(QWidget *parent = nullptr);
    ~FlacFormatFieldWidget();

private:
    Ui::FlacFormatFieldWidget *ui;
};

#endif // FLACFORMATFIELDWIDGET_H
