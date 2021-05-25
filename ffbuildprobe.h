#ifndef FFRESOURCESPARSER_H
#define FFRESOURCESPARSER_H

#include <QMap>
#include <fftableline.h>

class FFBuildProbe
{
    typedef std::function<FFTableLine(const QString&)> OptionBuilder;
    typedef QMap<QString, FFOptionDataList> FFOptionDataMap;

    struct OptionEntry
    {
        QString name;
        int lineOffset;
        OptionBuilder builder;
    };

    QList<OptionEntry> m_Options;
    FFOptionDataMap m_DataMap;

    QMap<QString, QString> buildProtoFlagsMap(const QString&);
    QStringList rebuildProtoLines(const QString&);

    QMap<QString, QString> buildLayoutMap(const QString&);
    QStringList rebuildLayoutLines(const QString&);

public:
    FFBuildProbe();
    void refresh();
    const FFOptionDataList& getBuildConf();
    const FFOptionDataList& getFormats();
    //const QStringList& getMuxers();
    //const QStringList& getDemuxers();
    const FFOptionDataList& getDevices();
    const FFOptionDataList& getCodecs();
    //const QStringList& getDecoders();
    //const QStringList& getEncoders();
    const FFOptionDataList& getBsfs();
    const FFOptionDataList& getProtocols();
    const FFOptionDataList& getFilters();
    const FFOptionDataList& getPixFmts();
    const FFOptionDataList& getLayouts();
    const FFOptionDataList& getSampleFmts();
    const FFOptionDataList& getColors();
    const FFOptionDataList& getHwAccels();
    QString toString();
};

#endif // FFRESOURCESPARSER_H
