#include "toolboxwidget.h"
#include "ui_toolboxwidget.h"

#include <ui/filefieldwidget.h>
#include <ui/formatfieldwidget.h>
#include <ui/audioformatfieldwidget.h>
#include <ui/videoformatfieldwidget.h>

#include <QPushButton>

#include <QDebug>

ToolboxWidget::ToolboxWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolboxWidget)
{
    ui->setupUi(this);

    addInputButton("File", [](){
        return new FileFieldWidget(nullptr, QFileDialog::AcceptOpen);
    });

    addOutputButton("File", [](){
        return new FileFieldWidget(nullptr, QFileDialog::AcceptSave);
    });

    addFormatClassButton("Audio", [](){
        return new AudioFormatFieldWidget();
    });
    addFormatClassButton("Video", [](){
        return new VideoFormatFieldWidget();
    });
    addFormatClassButton("Custom", [](){
        return new FormatFieldWidget();
    });
}

ToolboxWidget::~ToolboxWidget()
{
    delete ui;
}

void ToolboxWidget::addButton(QLayout *layout, const QString &name, ToolboxFieldAllocator alloc)
{
    auto button = new QPushButton(name);

    if(alloc){
        connect(button, &QPushButton::clicked, [this, alloc](){
            auto field = alloc();
            Q_ASSERT(field != nullptr);
            emit this->fieldAlloc(field);
        });
    }else{
        button->setEnabled(false);
    }

    layout->addWidget(button);
}

void ToolboxWidget::addInputButton(QString name, ToolboxFieldAllocator allocator)
{
    addButton(ui->frame->layout(), name, allocator);
}

void ToolboxWidget::addOutputButton(QString name, ToolboxFieldAllocator allocator)
{
    addButton(ui->frame_2->layout(), name, allocator);
}

void ToolboxWidget::addFormatClassButton(QString name, ToolboxFieldAllocator allocator)
{
    addButton(ui->frame_3->layout(), name, allocator);
}

void ToolboxWidget::addFormatAudioButton(QString name, ToolboxFieldAllocator allocator)
{
    addButton(ui->frame_4->layout(), name, allocator);
}

void ToolboxWidget::addFormatVideoButton(QString name, ToolboxFieldAllocator allocator)
{
    addButton(ui->frame_5->layout(), name, allocator);
}
