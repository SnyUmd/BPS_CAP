/*
 Name:    CAP_Ctrl.ino
 Created: 2020/12/15 15:35:40
 Author:  BPS-Umeda
*/
#define LED_ON 1
#define LED_OFF 0

#define AIR_ON 0
#define AIR_OFF 1

#define PORT_LED 13

#define PORT_SENSOR_PE 2
#define PORT_SENSOR_W 3

#define PORT_SENSOR_PASS_2 4
#define PORT_SENSOR_PASS_3 5

#define INT_NUM_AREA2 0
#define INT_NUM_AREA3 1

#define PORT_AIR_PE 6
#define PORT_AIR_W 7

#define CNT_END_NUM 5000
#define CNT_FLG_CANCEL 62000

#define PORT_DEBUG 12

#include "Timer.h"

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void setup() {
    InitPort();//ポートのイニシャライズ

    FlashLED(3, 50, LED_OFF);

    attachInterrupt(INT_NUM_AREA2, FlgSetAir2, FALLING);
    attachInterrupt(INT_NUM_AREA3, FlgSetAir3, FALLING);

    Serial.begin(115200);
    Serial.println("-----Start-----");
}

//*********************************************************************************
long CntAirPE = 0;
long CntAirW = 0;

long CntFlgPE = 0;
long CntFlgW = 0;

//bool BlCntRunPE = false;
//bool BlCntRunW = false;

bool FlgPE = false;
bool FlgW = false;

void loop() 
{
    CtrlPE(FlgPE);
    CtrlW(FlgW);

    if(FlgPE || FlgW)
    {
        digitalWrite(PORT_DEBUG, LOW);
        digitalWrite(PORT_LED, LED_ON);
    }
    else
    {
        digitalWrite(PORT_DEBUG, HIGH);
        digitalWrite(PORT_LED, LED_OFF);
    }
}
//*********************************************************************************
//*********************************************************************************
void CtrlPE(bool& flg)
{
    if(flg)
    {
        //CAP通過が終わったらPE命令発信
        if(digitalRead(PORT_SENSOR_PASS_2) == HIGH)
        {
            digitalWrite(PORT_AIR_PE, AIR_ON);
            flg *= false;
            Serial.println("-AirPE Start-");
            CntFlgPE = 0;
        }
        else
        {
            CntFlgPE++;
            if(CntFlgPE > CNT_FLG_CANCEL)
            {
                flg *= false;
                CntFlgPE = 0;
            }
        }
    }
    else
    {
        if(digitalRead(PORT_AIR_PE) == AIR_ON)
        {
            CntAirPE++;
            if(CntAirPE >= CNT_END_NUM)
            {
                //digitalWrite(PORT_LED, LED_OFF);
                digitalWrite(PORT_AIR_PE, AIR_OFF);
                CntAirPE = 0;
                Serial.println("-AirPE Stop-");
            }
        }
    }
}

//*********************************************************************************
void CtrlW(bool& flg)
{
    if(flg)
    {
        //CAP通過が終わったらPE命令発信
        if(digitalRead(PORT_SENSOR_PASS_3) == HIGH)
        {
            digitalWrite(PORT_AIR_W, AIR_ON);
            flg *= false;
            Serial.println("-AirW Start-");
            CntFlgW = 0;
        }
        else
        {
            CntFlgW++;
            if(CntFlgW > CNT_FLG_CANCEL)
            {
                flg *= false;
                CntFlgW = 0;
            }
        }
    }
    else
    {
        if(digitalRead(PORT_AIR_W) == AIR_ON)
        {
            CntAirW++;
            if(CntAirW >= CNT_END_NUM)
            {
                //digitalWrite(PORT_LED, LED_OFF);
                digitalWrite(PORT_AIR_W, AIR_OFF);
                CntAirW = 0;
                Serial.println("-AirW Stop-");
            }
        }
    }
}
//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void InitPort()
{
    //----------------------------
    pinMode(PORT_DEBUG, OUTPUT);
    digitalWrite(PORT_DEBUG, HIGH);
    //----------------------------


    pinMode(PORT_SENSOR_PE, INPUT_PULLUP);
    pinMode(PORT_SENSOR_W, INPUT_PULLUP);

    pinMode(PORT_SENSOR_PASS_2, INPUT_PULLUP);
    pinMode(PORT_SENSOR_PASS_3, INPUT_PULLUP);

    pinMode(PORT_AIR_PE, OUTPUT);
    pinMode(PORT_AIR_W, OUTPUT);
    pinMode(PORT_LED, OUTPUT);

    digitalWrite(PORT_AIR_PE, AIR_OFF);
    digitalWrite(PORT_AIR_W, AIR_OFF);
    digitalWrite(PORT_LED, LED_OFF);

    Serial.println("-----START-----");
}

//*********************************************************************************
void FlashLED(int loopNum, int delayTime, bool blEnd)
{
    for (int i = 0; i < loopNum; i++)
    {
        digitalWrite(PORT_LED, LED_ON);
        delay(delayTime/10);
        digitalWrite(PORT_LED, LED_OFF);
        delay(delayTime*10);
    }
    digitalWrite(PORT_LED, blEnd);

}

//*********************************************************************************
void FlgSetAir2()
{
    FlgPE = true;
    digitalWrite(PORT_DEBUG, LOW);
    digitalWrite(PORT_LED, LED_ON);
    Serial.println("Air2 Flg Set");
}


//*********************************************************************************
void FlgSetAir3()
{
    FlgW = true;
    digitalWrite(PORT_LED, !digitalRead(PORT_LED));
    digitalWrite(PORT_DEBUG, LOW);
    digitalWrite(PORT_LED, LED_ON);
    Serial.println("Air3 Flg Set");
}


