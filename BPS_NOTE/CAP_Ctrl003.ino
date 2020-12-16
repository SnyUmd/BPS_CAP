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

#define PORT_SENSOR_PASS_2 6
#define PORT_SENSOR_PASS_3 7

#define INT_NUM_AREA2 0
#define INT_NUM_AREA3 1

#define PORT_AIR_2 10
#define PORT_AIR_3 11

bool blPE = false;
bool blW = false;


#include "Timer.h"

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void setup() {
    InitPort();//ポートのイニシャライズ

    FlashLED(10, 50, LED_OFF);

    attachInterrupt(INT_NUM_AREA2, FlgSetAir2, FALLING);
    attachInterrupt(INT_NUM_AREA3, FlgSetAir3, FALLING);

    Serial.begin(115200);
    Serial.println("-----Start-----");
}

//*********************************************************************************
void loop() {
    if (blPE && PORT_SENSOR_PE == HIGH)
    {
        
    }
    

    if (blW && PORT_SENSOR_W == HIGH)
    {

    }
}

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void InitPort()
{

    pinMode(PORT_SENSOR_PE, INPUT_PULLUP);
    pinMode(PORT_SENSOR_W, INPUT_PULLUP);

    pinMode(PORT_SENSOR_PASS_2, INPUT_PULLUP);
    pinMode(PORT_SENSOR_PASS_3, INPUT_PULLUP);

    pinMode(PORT_AIR_2, OUTPUT);
    pinMode(PORT_AIR_3, OUTPUT);
    pinMode(PORT_LED, OUTPUT);

    digitalWrite(PORT_AIR_2, AIR_OFF);
    digitalWrite(PORT_AIR_3, AIR_OFF);
    digitalWrite(PORT_LED, LED_OFF);

    Serial.println("-----START-----");
}

//*********************************************************************************
void FlashLED(int loopNum, int delayTime, bool blEnd)
{
    for (int i = 0; i < loopNum; i++)
    {
        digitalWrite(PORT_LED, LED_ON);
        delay(delayTime);
        digitalWrite(PORT_LED, LED_OFF);
        delay(delayTime);
    }
    digitalWrite(PORT_LED, blEnd);

}

//*********************************************************************************
void FlgSetAir2()
{
    blPE = true;
    digitalWrite(PORT_LED, !digitalRead(PORT_LED));
    Serial.println("Air2 Flg Set");
}


//*********************************************************************************
void FlgSetAir3()
{
    blW = true;
    digitalWrite(PORT_LED, !digitalRead(PORT_LED));
    Serial.println("Air3 Flg Set");
}


//*********************************************************************************
void ExeAir(int portNum)
{
    digitalWrite(portNum, LOW);

    if (portNum == PORT_AIR_2);
    if (portNum == PORT_AIR_3);
}

