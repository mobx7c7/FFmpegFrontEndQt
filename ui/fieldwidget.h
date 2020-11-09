#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>

class FieldWidget : public QWidget
{
    Q_OBJECT
protected:
    FieldWidget(QWidget* parent);

public:
    virtual QString toString() { return QString(); }

signals:
    void changed();
};

#endif // FIELDWIDGET_H
