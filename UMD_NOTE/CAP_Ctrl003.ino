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
    CtrlPE(FlgPE);
    CtrlW(FlgW);
}
//*********************************************************************************
//*********************************************************************************
void CtrlPE(bool& flg)
{
    if(flg)
    {
        //通過信号よりもセンサ信号が早い時の為のWait
        //St_Cnt.WaitPassPE++;
        //CAP通過が終わったらPE命令発信
        if(CheckCnt(St_Cnt.WaitPassPE, CNT_WAIT) && digitalRead(PORT_SENSOR_PASS_2) == HIGH)
        {
            digitalWrite(PORT_LED_PE, LED_OFF);

            digitalWrite(PORT_AIR_PE, AIR_ON);
            digitalWrite(PORT_LED_AIR, LED_ON);
            St_Time.T_SpeedPE = TimeElapsed(St_Time.T_StartPE);
            Serial.print("PE,");
            Serial.println(St_Time.T_SpeedPE);
            flg *= false;
            
            ResetCnt(true, false);
        }
        else
        {
            if(CheckCnt(St_Cnt.FlgPE, CNT_FLG_CANCEL))
            {
                flg *= false;
                ResetCnt(true, false);
            }
        }

        if(St_Cnt.WaitPassPE >= CNT_WAIT)
            digitalWrite(PORT_DEBUG_PE, LOW);
    }
    //エア命令信号を出している時の命令出す時間の為のカウント
    else
    {
        if(digitalRead(PORT_AIR_PE) == AIR_ON)
        {
            if(CheckCnt(St_Cnt.AirPE, CNT_END_NUM))
            {
                //digitalWrite(PORT_LED, LED_OFF);
                digitalWrite(PORT_AIR_PE, AIR_OFF);
                digitalWrite(PORT_LED_AIR, LED_OFF);
                //St_Cnt.AirPE = 0;
                ResetCnt(true, false);
            }
        }
    }
}

//*********************************************************************************
void CtrlW(bool& flg)
{
    if(flg)
    {
        //通過信号よりもセンサ信号が早い時の為のWait
        //St_Cnt.WaitPassW++;
        //CAP通過が終わったらPE命令発信
        if(CheckCnt(St_Cnt.WaitPassW, CNT_WAIT) && digitalRead(PORT_SENSOR_PASS_3) == HIGH)
        {
            digitalWrite(PORT_LED_W, LED_OFF);

            digitalWrite(PORT_AIR_W, AIR_ON);
            digitalWrite(PORT_LED_AIR, LED_ON);
            St_Time.T_SpeedW = TimeElapsed(St_Time.T_StartW);
            Serial.print("W,");
            Serial.println(St_Time.T_SpeedW);
            flg *= false;
            
            ResetCnt(false, true);
        }
        else
        {
            if(CheckCnt(St_Cnt.FlgW, CNT_FLG_CANCEL))
            {
                flg *= false;
                ResetCnt(false, true);
            }
        }

        if(St_Cnt.WaitPassW >= CNT_WAIT)
            digitalWrite(PORT_DEBUG_W, LOW);
    }
    //エア命令信号を出している時の命令出す時間の為のカウント
    else
    {
        if(digitalRead(PORT_AIR_W) == AIR_ON)
        {
            if(CheckCnt(St_Cnt.AirW, CNT_END_NUM))
            {
                digitalWrite(PORT_AIR_W, AIR_OFF);
                digitalWrite(PORT_LED_AIR, LED_OFF);
                //St_Cnt.AirW = 0;
                ResetCnt(false, true);
            }
        }
    }
}

//*********************************************************************************
void FlgSetAir2()
{
    FlgPE = true;
    //センサ反応時間をセット
    St_Time.T_StartPE = millis();
    //PEデバッグポートをセット
    digitalWrite(PORT_DEBUG_PE, HIGH);
    digitalWrite(PORT_LED_PE, LED_ON);
    //PEのカウンタをリセット
    ResetCnt(true, false);
    Serial.println("Air2 Flg Set");
}


//*********************************************************************************
void FlgSetAir3()
{
    FlgW = true;
    //センサ反応時間をセット
    St_Time.T_StartW = millis();
    //Wデバッグポートをセット
    digitalWrite(PORT_DEBUG_W, HIGH);
    digitalWrite(PORT_LED_W, LED_ON);
    //Wのカウンタをリセット
    ResetCnt(false, true);
    Serial.println("Air3 Flg Set");
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
void ResetCnt(bool cntPE, bool cntW)
{
    if(cntPE)
    {
        St_Cnt.AirPE = 0;
        St_Cnt.FlgPE = 0;
        St_Cnt.WaitPassPE = 0;
    }
    if(cntW)
    {
        St_Cnt.AirW = 0;
        St_Cnt.FlgW = 0;
        St_Cnt.WaitPassW = 0;
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

