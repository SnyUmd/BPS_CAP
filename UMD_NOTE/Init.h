#include <Arduino.h>
#include "Def.h"

static bool FlgPE = false;
static bool FlgW = false;
static int DebugCntAAA = 0;

struct _structCNT
{
    long AirPE = 0;
    long AirW = 0;

    long FlgPE = 0;
    long FlgW = 0;

    long WaitPassPE = 0;
    long WaitPassW = 0;

    long testAAA = 0;
};
static struct _structCNT St_Cnt;

//通過時間カウント用
struct _Time
{
    long T_StartPE = 0;
    long T_StartW = 0;
    long T_SpeedPE = 0;
    long T_SpeedW = 0;
};
static struct _Time St_Time;

void InitPort();