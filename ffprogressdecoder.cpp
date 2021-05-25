#include "ffprogressdecoder.h"

void FFProgressDecoder::process(const QString& input)
{
    m_Fields.clear();
    auto lines = input.split('\n');
    auto it = lines.cbegin();
    while(it != lines.cend())
    {
        auto keyValuePair = it->split('=', QString::SplitBehavior::SkipEmptyParts);
        m_Fields[keyValuePair.front()] = keyValuePair.back();
        it++;
    }
}
QString FFProgressDecoder::getBitrate()
{
    return m_Fields["bitrate"];
}
QString FFProgressDecoder::getTotalSize()
{
    return m_Fields["total_size"];
}
QString FFProgressDecoder::getOutTimeUS()
{
    return m_Fields["out_time_us"];
}
QString FFProgressDecoder::getOutTimeMS()
{
    return m_Fields["out_time_ms"];
}
QString FFProgressDecoder::getOutTime()
{
    return m_Fields["out_time"];
}
QString FFProgressDecoder::getDupFrames()
{
    return m_Fields["dup_frames"];
}
QString FFProgressDecoder::getDropFrames()
{
    return m_Fields["drop_frames"];
}
QString FFProgressDecoder::getSpeed()
{
    return m_Fields["speed"];
}
QString FFProgressDecoder::getProgress()
{
    return m_Fields["progress"];
}
QString FFProgressDecoder::toString()
{
    return QString();
}
