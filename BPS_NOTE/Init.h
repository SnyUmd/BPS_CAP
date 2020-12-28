#include <Arduino.h>
#include "Def.h"

extern bool FlgPE;
extern bool FlgW;
extern int DebugCntAAA;

extern long AryStsPE[9];
extern long AryStsW[9];
enum _EnmArySts
{
    cntAir = 0,
    cntFlg,
    cntWaitPass,
    timeStart,
    timeSpeed,
    timeSpeedMin,
    timeAirSignalEnd,
    timeAirInterval,
    timeIntervalMin
};

void InitPort();