#include "Timer.h"

long TimeElapsed(long timeStart)
{
    long TimeResult = 0;
    long TimeNow = millis();

    //millilの値がリセットされたときの対処
    if(TimeNow < timeStart)
        TimeResult = TimeNow + (4320000000 - timeStart);
    else
        TimeResult = TimeNow - timeStart;

    return TimeResult;
}
