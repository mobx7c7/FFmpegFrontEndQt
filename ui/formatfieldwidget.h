#ifndef FORMATFIELDWIDGET_H
#define FORMATFIELDWIDGET_H

#include <ui/fieldwidget.h>

namespace Ui {
class FormatFieldWidget;
}

class FormatFieldWidget : public FieldWidget
{
    Q_OBJECT

public:
    explicit FormatFieldWidget(QWidget *parent = nullptr);
    ~FormatFieldWidget();
    QString toString() override;

private:
    Ui::FormatFieldWidget *ui;

private slots:
    void handleTextEdited(const QString&);
};

#endif // FORMATFIELDWIDGET_H
