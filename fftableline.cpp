#include "fftabledata.h"
#include <QJsonDocument>
#include <QRegExp>
#include <QStringList>

const QRegExp regex0("\\S"); // Not White Space
const QRegExp regex1("\\s"); // White space

FFTableLine::FFTableLine()
{
    setFlags("");
    setGraph("");
    setValue("");
    setDescription("");
}

void FFTableLine::setFlags(const QString &flags)
{
    json["flags"] = flags;
}

void FFTableLine::setGraph(const QString &graph)
{
    json["graph"] = graph;
}

void FFTableLine::setValue(const QString &value)
{
    json["value"] = value;
}

void FFTableLine::setDescription(const QString &desc)
{
    json["description"] = desc;
}

QString FFTableLine::flags() const
{
    return json["flags"].toString();
}

QString FFTableLine::graph() const
{
    return json["graph"].toString();
}

QString FFTableLine::value() const
{
    return json["value"].toString();
}

QString FFTableLine::description() const
{
    return json["description"].toString();
}

QString FFTableLine::toString() const
{
    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Indented);
}

QJsonObject FFTableLine::toJson() const
{
    return json;
}

FFTableLine FFTableLine::fromBuildConf(const QString &line)
{
    FFTableLine data;
    data.setValue(line.trimmed());
    return data;
}

FFTableLine FFTableLine::fromFormat(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = 1;
    c2 = 3;
    data.setFlags(line.mid(c1,c2-c1));

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    data.setDescription(line.mid(c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromDevice(const QString &line)
{
    return fromFormat(line);
}

FFTableLine FFTableLine::fromCodec(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setFlags(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    data.setDescription(line.mid(c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromBsf(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromProtocol(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setFlags(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    data.setValue(line.mid(c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromFilter(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setFlags(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setGraph(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    data.setDescription(line.mid(c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromPixFmt(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setFlags(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromLayout(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setFlags(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    if(data.flags().contains("I"))
    {
        data.setDescription(line.mid(c1).trimmed());
    }
    else
    {
        data.setGraph(line.mid(c1).trimmed());
    }

    return data;
}

FFTableLine FFTableLine::fromSampleFmt(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    auto name = line.mid(c1,c2-c1).trimmed();

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    auto bits = line.mid(c1,c2-c1).trimmed();

    QStringList desc;

    if(name.startsWith('u'))
    {
        desc << "Unsigned";
    }
    else if(name.startsWith('s'))
    {
        desc << "Signed";
    }

    desc << QString("%1-bit").arg(bits);

    if(name.startsWith('f') || name.startsWith('d'))
    {
        desc << "floating-point";
    }

    if(name.endsWith('p'))
    {
        desc << "(Planar)";
    }

    data.setValue(name);
    data.setDescription(desc.join(' '));

    return data;
}

FFTableLine FFTableLine::fromColor(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setDescription(line.mid(c1,c2-c1).trimmed());

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    return data;
}

FFTableLine FFTableLine::fromHwAccel(const QString &line)
{
    FFTableLine data;

    int c1,c2=0;

    c1 = line.indexOf(regex0,c2);
    c2 = line.indexOf(regex1,c1);
    data.setValue(line.mid(c1,c2-c1).trimmed());

    return data;
}
