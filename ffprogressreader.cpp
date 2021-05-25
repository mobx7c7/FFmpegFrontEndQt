#include "ffprogressreader.h"
#include <QString>

int FFProgressReader::process(const QString &input, QString& output)
{
    int beg, end;

    beg = input.indexOf("bitrate");
    if(beg != -1)
    {
        end = input.indexOf("progress", beg);
        if(end != -1)
        {
            end = input.indexOf('\n', end);
            if(end != -1)
            {
                output = input.mid(beg, end - beg);
                return end;
            }
        }
    }
    return 0;
}

