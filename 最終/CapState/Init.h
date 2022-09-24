#include <Arduino.h>
#include "Def.h"

extern bool FlgPE;
extern bool FlgW;
extern int DebugCntAAA;

//=============================
extern long AryInfoPE[7];
extern long AryInfoW[7];
//ステータス配列アドレス用　列挙
enum _EnmAryInfo
{
    areaState = 0,      //状態番号
    portNumPass,        //通過センサ入力ポート番号
    portNumDetection,   //検知信号入力ポート番号
    portNumAir,         //エア命令出力ポート番号
    portNumLED,         //LEDポート番号
    flgAirOrderWaitStart//Air命令準備状態フラグ(未使用)
    //flgDetectFirstTime//機器起動後から初回検知フラグ(未使用)
};

//=============================
extern long AryTimeBuf_PE[7];
extern long AryTimeBuf_W[7];

//時間管理アドレス要　列挙
enum _TimeBuf
{
    timeWaitStart = 0,  //通過センサON待ち時間
    timeTargetBuf,      //未使用
    timePassOn,         //通過開始時間
    timePassEnd,        //通過終了時間
    timeWaitPassStart,  //通過センサON待ち時間
    timeGetDetect,      //検知信号取得時間
    timeCancelNextDetect//未使用
};

//=============================
//ステータス番号用　列挙
enum _StateTransition
{
    enm_Sts0_WaitDetection = 0,
    enm_Sts1_CheckPassOn,
    enm_Sts2_WaitPassOff,
    enm_Sts3_AirSignal
};


void InitPort();//ポートイニシャライズ