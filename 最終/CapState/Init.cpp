#include "Init.h"

bool FlgPE = false;
bool FlgW = false;
int DebugCntAAA = 0;

//PEエリアのステータス配列
long AryInfoPE[7] = {0,                         //状態番号
                     PORT_SENSOR_PASS_PE,       //通過センサ入力ポート番号
                     PORT_DETECTION_PE,         //検知信号入力ポート番号
                     PORT_AIR_PE,               //エア命令出力ポート番号
                     PORT_LED_PE,               //LEDポート番号
                     0,                         //Air命令準備状態フラグ(未使用)
                     1};                        //機器起動後から初回検知フラグ(未使用)

long AryInfoW[7] = {0,                         //状態番号
                    PORT_SENSOR_PASS_W,       //通過センサ入力ポート番号
                    PORT_DETECTION_W,         //検知信号入力ポート番号
                    PORT_AIR_W,               //エア命令出力ポート番号
                    PORT_LED_W,               //LEDポート番号
                    0,                        //Air命令準備状態(未使用)
                    1};                       //機器起動後から初回検知フラグ(未使用)
//-----------------------------------
//配列アドレス指定時に使用する列挙(Init.h)
// enum _EnmAryInfo
// {
//     areaState = 0,      //状態番号
//     portNumPass,        //通過センサ入力ポート番号
//     portNumDetection,   //検知信号入力ポート番号
//     portNumAir,         //エア命令出力ポート番号
//     portNumLED,         //LEDポート番号
//     flgAirOrderWaitStart//Air命令準備状態フラグ(未使用)
//     //flgDetectFirstTime//機器起動後から初回検知フラグ(未使用)
// };
//-----------------------------------

long AryTimeBuf_PE[7] = {0,0,0,0,0,0,TIME_CANCEL_NEXT_DETECT_PE};
long AryTimeBuf_W[7] = {0,0,0,0,0,0,TIME_CANCEL_NEXT_DETECT_W};
//-----------------------------------
// enum _TimeBuf
//配列アドレス指定時に使用する列挙
// {
//     timeWaitStart = 0,
//     timeTargetBuf,
//     timePassOn,
//     timePassEnd,
//     timeWaitPassStart,
//     timeGetDetect,
//     timeCancelNextDetect
// };
//-----------------------------------

//*********************************************************************************
//ポートイニシャライズ
//*********************************************************************************
void InitPort()
{
    //----------------------------
    pinMode(PORT_DEBUG_PE, OUTPUT);
    pinMode(PORT_DEBUG_W, OUTPUT);
    digitalWrite(PORT_DEBUG_PE, LOW);
    digitalWrite(PORT_DEBUG_W, LOW);
    //----------------------------

    //ポート設定----------------------
    pinMode(PORT_DETECTION_PE, INPUT_PULLUP);
    pinMode(PORT_DETECTION_W, INPUT_PULLUP);

    pinMode(PORT_SENSOR_PASS_PE, INPUT_PULLUP);
    pinMode(PORT_SENSOR_PASS_W, INPUT_PULLUP);

    pinMode(PORT_AIR_PE, OUTPUT);
    pinMode(PORT_AIR_W, OUTPUT);

    pinMode(PORT_LED, OUTPUT);
    pinMode(PORT_LED_PE, OUTPUT);
    pinMode(PORT_LED_W, OUTPUT);
    pinMode(PORT_LED_AIR, OUTPUT);
    
    //ポート状態------------------------
    digitalWrite(PORT_AIR_PE, AIR_OFF);
    digitalWrite(PORT_AIR_W, AIR_OFF);
    
    digitalWrite(PORT_LED, HIGH);
    digitalWrite(PORT_LED_PE, LED_OFF);
    digitalWrite(PORT_LED_W, LED_OFF);
    digitalWrite(PORT_LED_AIR, LED_OFF);
}