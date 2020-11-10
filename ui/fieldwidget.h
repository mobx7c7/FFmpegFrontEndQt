#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>

class FieldWidget : public QWidget
{
    Q_OBJECT
protected:
    FieldWidget(QWidget* parent);

public:
    QString label(){return m_Label;}
    void setLabel(const QString& label){m_Label = label;}
    virtual QString toString() { return QString(); }

private:
    QString m_Label;

signals:
    void changed();
};

#endif // FIELDWIDGET_H
