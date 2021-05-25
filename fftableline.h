#ifndef FFOPTIONDATA_H
#define FFOPTIONDATA_H

#include <QString>
#include <QJsonObject>

class FFTableLine
{
    QJsonObject json;
   // QJsonValueRef m_Flags, m_Value, m_Description;

    FFTableLine();
    void setFlags(const QString&);
    void setGraph(const QString&);
    void setValue(const QString&);
    void setDescription(const QString&);

public:
    virtual ~FFTableLine() = default;
    QString flags() const;
    QString graph() const;
    QString value() const;
    QString description() const;
    QString toString() const;
    QJsonObject toJson() const;
    static FFTableLine fromBuildConf(const QString&);
    static FFTableLine fromFormat(const QString&);
    static FFTableLine fromDevice(const QString&);
    static FFTableLine fromCodec(const QString&);
    static FFTableLine fromBsf(const QString&);
    static FFTableLine fromProtocol(const QString&);
    static FFTableLine fromFilter(const QString&);
    static FFTableLine fromPixFmt(const QString&);
    static FFTableLine fromLayout(const QString&);
    static FFTableLine fromSampleFmt(const QString&);
    static FFTableLine fromColor(const QString&);
    static FFTableLine fromHwAccel(const QString&);
};

typedef QList<FFTableLine> FFOptionDataList;

#endif // FFOPTIONDATA_H
