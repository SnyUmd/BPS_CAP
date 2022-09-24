#include "Def.h"
#include "Interrupt.h"
#include "Init.h"
#include "Timer.h"


//*********************************************************************************
void Int_DetIn_PE()
{
    OrderAir(AryInfoPE, AryTimeBuf_PE);
}

//*********************************************************************************
void Int_DetIn_W()
{
    OrderAir(AryInfoW, AryTimeBuf_W);
}

//*********************************************************************************
void OrderAir(long *aryInfo, long *aryTimeBuf)
{
    //アイドル状態では無い時は検知信号を無視
    if (aryInfo[areaState] != enm_Sts0_WaitDetection) return;
    //前回の検知信号受信後、特定時間内の場合は検知信号を無視（白のみ）
    else if(!CheckElapsedTime(aryTimeBuf[timeGetDetect], aryTimeBuf[timeCancelNextDetect])) return;
    
    aryInfo[areaState] = enm_Sts1_CheckPassOn;//通過センサON待ち状態へ移行
    digitalWrite(aryInfo[portNumLED], LED_ON);
    GetTime(aryTimeBuf[timeWaitStart]);
    GetTime(aryTimeBuf[timeGetDetect]);
    // }

}
