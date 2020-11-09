#ifndef FILEFIELDWIDGET_H
#define FILEFIELDWIDGET_H

#include <QFileDialog>
#include <ui/fieldwidget.h>

namespace Ui {
class FileFieldWidget;
}

class FileFieldWidget : public FieldWidget
{
    Q_OBJECT

public:
    explicit FileFieldWidget(QWidget *parent = nullptr, QFileDialog::AcceptMode acceptMode = QFileDialog::AcceptOpen);
    ~FileFieldWidget();
    QString toString() override;

private:
    Ui::FileFieldWidget *ui;
    QFileDialog m_FileDialog;

private slots:
    void handleTextEdited(const QString&);
    void handleFileDialog();
};

#endif // FILEFIELDWIDGET_H
