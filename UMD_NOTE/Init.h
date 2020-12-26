#include <Arduino.h>
#include "Def.h"

static bool FlgPE = false;
static bool FlgW = false;
static int DebugCntAAA = 0;

extern long AryStsPE[5];
extern long AryStsW[5];
enum _EnmArySts
{
    cntAir = 0,
    cntFlg,
    cntWaitPass,
    timeStart,
    timeSpeed
};

void InitPort();