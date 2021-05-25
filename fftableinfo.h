#ifndef FFOPTIONINFO_H
#define FFOPTIONINFO_H

#include <fftableline.h>

class FFTableInfo
{
    FFTableLine m_Data;

protected:
    FFTableInfo(const FFTableLine&);
    const FFTableLine& data();

public:
    virtual ~FFTableInfo() = default;
    QString flags();
    QString value();
    QString description();
};

class _FFFormatTableInfo : public FFTableInfo
{
public:
    _FFFormatTableInfo(const FFTableLine&);
    bool isDemuxingSupported();
    bool isMuxingSupported();
};

class _FFCodecTableInfo : public FFTableInfo
{
public:
    _FFCodecTableInfo(const FFTableLine&);
    bool isDecodingSupported();
    bool isEncodingSupported();
    bool isAudioType();
    bool isVideoType();
    bool isSubtitleType();
    bool isIntraFrameOnly();
    bool isLossy();
    bool isLossless();
};

typedef _FFFormatTableInfo  FFFormatTableInfo;
typedef _FFFormatTableInfo  FFDeviceTableInfo; // same format
typedef _FFCodecTableInfo   FFCodecTableInfo;
#endif // FFOPTIONINFO_H
