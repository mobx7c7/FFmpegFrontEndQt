#include "ffbuildprobe.h"
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include <QRegularExpression>
#include <qjsondocument.h>
#include <qjsonarray.h>

const QRegExp regexWhiteSpaces("^\\s+|\\s+$");

FFBuildProbe::FFBuildProbe()
{
    m_Options << OptionEntry{"buildconf",  2,  FFTableLine::fromBuildConf};
    m_Options << OptionEntry{"formats",    4,  FFTableLine::fromFormat};
    m_Options << OptionEntry{"devices",    4,  FFTableLine::fromDevice};
    m_Options << OptionEntry{"codecs",     10, FFTableLine::fromCodec};
    m_Options << OptionEntry{"bsfs",       1,  FFTableLine::fromBsf};
    m_Options << OptionEntry{"protocols",  0,  FFTableLine::fromProtocol};
    m_Options << OptionEntry{"filters",    8,  FFTableLine::fromFilter};
    m_Options << OptionEntry{"pix_fmts",   8,  FFTableLine::fromPixFmt};
    m_Options << OptionEntry{"layouts",    0,  FFTableLine::fromLayout};
    m_Options << OptionEntry{"sample_fmts",1,  FFTableLine::fromSampleFmt};
    m_Options << OptionEntry{"colors",     1,  FFTableLine::fromColor};
    m_Options << OptionEntry{"hwaccels",   1,  FFTableLine::fromHwAccel};
}

QMap<QString, QString> FFBuildProbe::buildProtoFlagsMap(const QString &dataFromStdOut)
{
    QMap<QString, QString> flagsMap;

    auto c1 = dataFromStdOut.indexOf(QRegExp("Input.*"));
    auto c2 = dataFromStdOut.indexOf(QRegExp("Output.*"));

    auto mark = [&](char c, int i, int off, int siz)
    {
        auto lines = dataFromStdOut.mid(off,siz).split('\n');
        lines.removeFirst(); // Header
        lines.replaceInStrings(regexWhiteSpaces, QString());

        for(auto it = lines.cbegin(); it != lines.cend(); it++)
        {
            if(it->isEmpty())
                continue;

            auto &flags = flagsMap[*it];

            if(flags.isEmpty())
                flags.resize(2,'.');

            flags[i] = c;
        }
    };

    mark('I',0,c1,c2-c1);
    mark('O',1,c2,-1);

    return flagsMap;
}

QStringList FFBuildProbe::rebuildProtoLines(const QString &textFromStdOut)
{
    QStringList lines;

    auto flagsMap = buildProtoFlagsMap(textFromStdOut);

    auto keys = flagsMap.keys();
    for(auto it = keys.cbegin(); it != keys.cend(); it++)
    {
        const auto &key = *it;
        const auto &val = flagsMap[key];
        lines += QString("%1 %2").arg(val,key);
    }

    return lines;
}

QMap<QString, QString> FFBuildProbe::buildLayoutMap(const QString &dataFromStdOut)
{
    QMap<QString, QString> flagsMap;

    auto c1 = dataFromStdOut.indexOf(QRegExp("NAME.*"));
    auto c2 = dataFromStdOut.lastIndexOf(QRegExp("NAME.*"));

    auto mark = [&](char c, int i, int off, int siz)
    {
        auto lines = dataFromStdOut.mid(off,siz).split('\n');
        lines.removeFirst(); // Column names
        lines.replaceInStrings(regexWhiteSpaces, QString());

        for(auto it = lines.cbegin(); it != lines.cend(); it++)
        {
            if(it->isEmpty())
                continue;

            auto &flags = flagsMap[*it];

            if(flags.isEmpty())
                flags.resize(1,'.');

            flags[i] = c;
        }
    };

    mark('I',0,c1,c2-c1); // (I)ndividual
    mark('S',0,c2,-1); // (S)tandard

    return flagsMap;
}

QStringList FFBuildProbe::rebuildLayoutLines(const QString &textFromStdOut)
{
    QStringList lines;

    auto flagsMap = buildLayoutMap(textFromStdOut);

    auto keys = flagsMap.keys();
    for(auto it = keys.cbegin(); it != keys.cend(); it++)
    {
        const auto &key = *it;
        const auto &val = flagsMap[key];
        lines += QString("%1 %2").arg(val,key);
    }

    return lines;
}

void FFBuildProbe::refresh()
{
    FFOptionDataMap dataMap;

    QProcess process;
    process.setProgram("ffmpeg");

    for(auto opt = m_Options.cbegin(); opt != m_Options.cend(); opt++)
    {
        process.setArguments(QStringList() << "-hide_banner" << QString("-%1").arg(opt->name));
        process.start();
        process.waitForFinished();

        if(process.exitCode() != 0) continue;

        QString textFromStdOut = process.readAllStandardOutput();

        QStringList lines;

        if(opt->name.contains("protocols"))
        {
            lines = rebuildProtoLines(textFromStdOut);
        }
        else if(opt->name.contains("layouts"))
        {
            lines = rebuildLayoutLines(textFromStdOut);
        }
        else
        {
            lines = textFromStdOut.split('\n');
        }

        auto &dataList = dataMap[opt->name];

        for(auto line = lines.cbegin() + opt->lineOffset; line != lines.cend(); line++)
        {
            if(line->isEmpty()) continue;
            auto data = opt->builder(*line);
            dataList << data;
        }
    }

    m_DataMap.swap(dataMap);
}

const FFOptionDataList &FFBuildProbe::getBuildConf()
{
    return m_DataMap["buildconf"];
}

const FFOptionDataList &FFBuildProbe::getFormats()
{
    return m_DataMap["formats"];
}

const FFOptionDataList &FFBuildProbe::getDevices()
{
    return m_DataMap["devices"];
}

const FFOptionDataList &FFBuildProbe::getCodecs()
{
    return m_DataMap["codecs"];
}

const FFOptionDataList &FFBuildProbe::getBsfs()
{
    return m_DataMap["bsfs"];
}

const FFOptionDataList &FFBuildProbe::getProtocols()
{
    return m_DataMap["protocols"];
}

const FFOptionDataList &FFBuildProbe::getFilters()
{
    return m_DataMap["filters"];
}

const FFOptionDataList& FFBuildProbe::getPixFmts()
{
    return m_DataMap["pix_fmts"];
}

const FFOptionDataList& FFBuildProbe::getLayouts()
{
    return m_DataMap["layouts"];
}

const FFOptionDataList& FFBuildProbe::getSampleFmts()
{
    return m_DataMap["sample_fmts"];
}

const FFOptionDataList& FFBuildProbe::getColors()
{
    return m_DataMap["colors"];
}

const FFOptionDataList& FFBuildProbe::getHwAccels()
{
    return m_DataMap["hwaccels"];
}

QString FFBuildProbe::toString()
{
    QJsonObject json;
    auto keys = m_DataMap.keys();
    for(auto it1 = keys.cbegin(); it1 != keys.cend(); it1++)
    {
        const auto &key = *it1;
        const auto &lst = m_DataMap[key];

        QJsonArray arr;
        for(auto it2 = lst.cbegin(); it2 != lst.cend(); it2++)
        {
            arr.push_back(it2->toJson());
        }
        json[key] = arr;
    }

    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Indented);
}
