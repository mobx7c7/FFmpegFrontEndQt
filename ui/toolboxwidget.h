#ifndef TOOLBOXWIDGET_H
#define TOOLBOXWIDGET_H

#include <QWidget>
#include <functional>
#include <ui/fieldwidget.h>

typedef std::function<FieldWidget*()> ToolboxFieldAllocator;

namespace Ui {
class ToolboxWidget;
}

class ToolboxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolboxWidget(QWidget *parent = nullptr);
    ~ToolboxWidget();

signals:
    void fieldAlloc(FieldWidget*);

private:
    Ui::ToolboxWidget *ui;
    void addButton(QLayout*, const QString&, ToolboxFieldAllocator);
    void addInputButton(QString, ToolboxFieldAllocator = nullptr);
    void addOutputButton(QString, ToolboxFieldAllocator = nullptr);
    void addFormatClassButton(QString, ToolboxFieldAllocator = nullptr);
    void addFormatAudioButton(QString, ToolboxFieldAllocator = nullptr);
    void addFormatVideoButton(QString, ToolboxFieldAllocator = nullptr);
};

#endif // TOOLBOXWIDGET_H
