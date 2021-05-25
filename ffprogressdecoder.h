#ifndef FFPROGRESSREADER_H
#define FFPROGRESSREADER_H

#include <QString>
#include <QMap>

class FFProgressDecoder
{
    QMap<QString, QString> m_Fields;

public:
    void process(const QString&);
    QString getBitrate();
    QString getTotalSize();
    QString getOutTimeUS();
    QString getOutTimeMS();
    QString getOutTime();
    QString getDupFrames();
    QString getDropFrames();
    QString getSpeed();
    QString getProgress();
    QString toString();
};

#endif // FFPROGRESSREADER_H
