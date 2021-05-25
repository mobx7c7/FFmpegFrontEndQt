#include "fftableinfo.h"

FFTableInfo::FFTableInfo(const FFTableLine &data)
    : m_Data(data)
{}

const FFTableLine& FFTableInfo::data()
{
    return m_Data;
}

QString FFTableInfo::flags()
{
    return m_Data.flags();
}

QString FFTableInfo::value()
{
    return m_Data.value();
}

QString FFTableInfo::description()
{
    return m_Data.description();
}

bool _FFFormatTableInfo::isDemuxingSupported()
{
    return flags().at(0) == 'D';
}

bool _FFFormatTableInfo::isMuxingSupported()
{
    return flags().at(1) == 'E';
}

_FFCodecTableInfo::_FFCodecTableInfo(const FFTableLine& data)
    : FFTableInfo(data)
{}

bool _FFCodecTableInfo::isDecodingSupported()
{
    return flags().at(0) == 'D';
}

bool _FFCodecTableInfo::isEncodingSupported()
{
    return flags().at(1) == 'E';
}

bool _FFCodecTableInfo::isAudioType()
{
    return flags().at(2) == 'A';
}

bool _FFCodecTableInfo::isVideoType()
{
    return flags().at(2) == 'V';
}

bool _FFCodecTableInfo::isSubtitleType()
{
    return flags().at(2) == 'S';
}

bool _FFCodecTableInfo::isIntraFrameOnly()
{
    return flags().at(3) == 'I';
}

bool _FFCodecTableInfo::isLossy()
{
    return flags().at(4) == 'L';
}

bool _FFCodecTableInfo::isLossless()
{
    return flags().at(5) == 'S';
}
