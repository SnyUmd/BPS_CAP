/*
 Name:    CAP_Ctrl.ino
 Created: 2020/12/15 15:35:40
 Author:  BPS-Umeda
*/

#include "Def.h"
#include "Init.h"
#include "Timer.h"

// extern bool FlgPE;
// extern bool FlgW;

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void setup() {
    InitPort();//ポートのイニシャライズ

    FlashLED(PORT_LED, 3, 50, LED_OFF);
    FlashLED(PORT_LED_PE, 3, 50, LED_OFF);
    FlashLED(PORT_LED_W, 3, 50, LED_OFF);
    FlashLED(PORT_LED_AIR, 3, 50, LED_OFF);

    //割り込み設定
    attachInterrupt(INT_NUM_AREA2, FlgSetAir2, FALLING);
    attachInterrupt(INT_NUM_AREA3, FlgSetAir3, FALLING);

    Serial.begin(115200);
}

//*********************************************************************************
//extern bool FlgPE;
//extern bool FlgW;


//*********************************************************************************
void loop() 
{
    CtrlCAP(AryStsPE, FlgPE, AREA_NUM_PE);
    CtrlCAP(AryStsW, FlgW, AREA_NUM_W);
}
//*********************************************************************************
//*********************************************************************************
void CtrlCAP(long *aryCnt, bool& flg, int areaNum)
{
    if(flg)
    {
        //CAP通過が終わったらPE命令発信
        if(CheckCnt(aryCnt[cntWaitPass] , CNT_WAIT) && digitalRead(PORT_SENSOR_PASS_2) == HIGH)
        {
            digitalWrite(PORT_LED_PE, LED_OFF);

            digitalWrite(PORT_AIR_PE, AIR_ON);
            digitalWrite(PORT_LED_AIR, LED_ON);
            aryCnt[timeSpeed] = TimeElapsed(aryCnt[timeStart]);
            Serial.print("PE,");
            Serial.println(aryCnt[timeSpeed]);
            flg *= false;
            
            ResetCnt(areaNum);
        }
        else
        {
            if(CheckCnt(aryCnt[cntFlg], CNT_FLG_CANCEL))
            {
                flg *= false;
                ResetCnt(areaNum);
            }
        }

        if(aryCnt[cntWaitPass] >= CNT_WAIT)
            digitalWrite(PORT_DEBUG_PE, LOW);
    }
    //エア命令信号を出している時の命令出す時間の為のカウント
    else
    {
        if(digitalRead(PORT_AIR_PE) == AIR_ON)
        {
            if(CheckCnt(aryCnt[cntAir], CNT_END_NUM))
            {
                //digitalWrite(PORT_LED, LED_OFF);
                digitalWrite(PORT_AIR_PE, AIR_OFF);
                digitalWrite(PORT_LED_AIR, LED_OFF);
                ResetCnt(areaNum);
            }
        }
    }
}

//*********************************************************************************
void FlgSetAir2()
{
    FlgPE = true;
    //センサ反応時間をセット
    AryStsPE[timeStart] = millis();
    //PEデバッグポートをセット
    digitalWrite(PORT_DEBUG_PE, HIGH);
    digitalWrite(PORT_LED_PE, LED_ON);
    //PEのカウンタをリセット
    ResetCnt(AREA_NUM_PE);
}


//*********************************************************************************
void FlgSetAir3()
{
    FlgW = true;
    //センサ反応時間をセット
    AryStsW[timeStart] = millis();
    //Wデバッグポートをセット
    digitalWrite(PORT_DEBUG_W, HIGH);
    digitalWrite(PORT_LED_W, LED_ON);
    //Wのカウンタをリセット
    ResetCnt(AREA_NUM_W);
}


//*********************************************************************************
bool CheckCnt(long& cnt, long endNum)
{
    if(cnt >= endNum)
        return true;
    else
    {
        cnt++;
        return false;
    }
}

//*********************************************************************************
void ResetCnt(int areaNum)
{
    if(areaNum == AREA_NUM_PE)
    {
        AryStsPE[cntAir] = 0;
        AryStsPE[cntFlg] = 0;
        AryStsPE[cntWaitPass]= 0;
    }
    if(areaNum == AREA_NUM_W)
    {
        AryStsW[cntAir] = 0;
        AryStsW[cntFlg] = 0;
        AryStsW[cntWaitPass]= 0;
    }

}


//*********************************************************************************
void FlashLED(int portNum, int loopNum, int delayTime, bool blEnd)
{
    for (int i = 0; i < loopNum; i++)
    {
        digitalWrite(portNum, LED_ON);
        delay(delayTime/20);
        digitalWrite(portNum, LED_OFF);
        delay(delayTime*10);
    }
    digitalWrite(portNum, blEnd);
}

