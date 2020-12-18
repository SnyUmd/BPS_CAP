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

#define CNT_END_NUM 1000
#define CNT_FLG_CANCEL 62000
#define CNT_WAIT 5000

#define CNT_DEBUG 100000
#define PORT_DEBUG_PE 11
#define PORT_DEBUG_W 12

//*********************************************************************************
//*********************************************************************************
//*********************************************************************************
void setup() {
    InitPort();//ポートのイニシャライズ

    FlashLED(6, 50, LED_OFF);

    attachInterrupt(INT_NUM_AREA2, FlgSetAir2, FALLING);
    attachInterrupt(INT_NUM_AREA3, FlgSetAir3, FALLING);

    Serial.begin(115200);
    Serial.println("-----Start-----");
}

//*********************************************************************************
// long AirPE = 0;
// long AirW = 0;

// long FlgPE = 0;
// long FlgW = 0;

// long WaitPassPE = 0;
// long WaitPassW = 0;

//bool BlCntRunPE = false;
//bool BlCntRunW = false;

bool FlgPE = false;
bool FlgW = false;

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
struct _structCNT St_Cnt;

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
            digitalWrite(PORT_AIR_PE, AIR_ON);
            flg *= false;
            
            //St_Cnt.FlgPE = 0;
            //St_Cnt.WaitPassPE = 0;
            ResetCnt(true, false);
            
        }
        else
        {
            if(CheckCnt(St_Cnt.FlgPE, CNT_FLG_CANCEL))
            {
                flg *= false;
                //St_Cnt.FlgPE = 0;
                //St_Cnt.WaitPassPE = 0;
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
            digitalWrite(PORT_AIR_W, AIR_ON);
            flg *= false;
            
            //St_Cnt.FlgW = 0;
            //St_Cnt.WaitPassW = 0;
            ResetCnt(false, true);
        }
        else
        {
            if(CheckCnt(St_Cnt.FlgW, CNT_FLG_CANCEL))
            {
                flg *= false;
                //St_Cnt.FlgW = 0;
                //St_Cnt.WaitPassW = 0;
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
                //digitalWrite(PORT_LED, LED_OFF);
                digitalWrite(PORT_AIR_W, AIR_OFF);
                //St_Cnt.AirW = 0;
                ResetCnt(false, true);
            }
        }
    }
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
//*********************************************************************************
//*********************************************************************************
void InitPort()
{
    //----------------------------
    pinMode(PORT_DEBUG_PE, OUTPUT);
    pinMode(PORT_DEBUG_W, OUTPUT);
    digitalWrite(PORT_DEBUG_PE, LOW);
    digitalWrite(PORT_DEBUG_W, LOW);
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
        delay(delayTime/20);
        digitalWrite(PORT_LED, LED_OFF);
        delay(delayTime*10);
    }
    digitalWrite(PORT_LED, blEnd);

}

//*********************************************************************************
void FlgSetAir2()
{
    // if(digitalRead(PORT_SENSOR_PASS_2) == LOW)
    // {
    FlgPE = true;
    digitalWrite(PORT_DEBUG_PE, HIGH);
    ResetCnt(true, false);
    Serial.println("Air2 Flg Set");
    // }
}


//*********************************************************************************
void FlgSetAir3()
{
    // if(digitalRead(PORT_SENSOR_PASS_3) == LOW)
    // {
    FlgW = true;
    digitalWrite(PORT_DEBUG_W, HIGH);
    ResetCnt(false, true);
    Serial.println("Air3 Flg Set");
    // }
}


