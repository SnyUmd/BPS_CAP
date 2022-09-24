#include "Def.h"
#include "Init.h"
#include "Timer.h"
#include "Interrupt.h"

//*********************************************************************************
//セットアップ
//*********************************************************************************
void setup() {
    Serial.begin(115200);
    InitPort();//ポートのイニシャライズ
#ifdef DEBUG_TIME_SEND
    digitalWrite(PORT_LED, LED_ON);
    digitalWrite(PORT_LED_PE, LED_ON);
    digitalWrite(PORT_LED_W, LED_ON);
    digitalWrite(PORT_LED_AIR, LED_ON);
    delay(500);
    digitalWrite(PORT_LED, LED_OFF);
    digitalWrite(PORT_LED_PE, LED_OFF);
    digitalWrite(PORT_LED_W, LED_OFF);
    digitalWrite(PORT_LED_AIR, LED_OFF);
#else //DEBUG_TIME_SEND
    FlashLED(PORT_LED, 3, 50, LED_OFF);
#endif //DEBUG_TIME_SEND

    //割り込み設定
    attachInterrupt(INT_NUM_AREA2, Int_DetIn_PE, FALLING);//PE検知信号割込みポート
    attachInterrupt(INT_NUM_AREA3, Int_DetIn_W, FALLING);//白検知信号割込みポート
    Serial.println("-----Start-----");
}

//*********************************************************************************
//メインループ
//*********************************************************************************
void loop() 
{
    CtrlSignal(AryInfoPE, AryTimeBuf_PE);
    CtrlSignal(AryInfoW, AryTimeBuf_W);
}



//*********************************************************************************
//状態遷移処理
//aryInfo：ステータス配列
//aryTimeBuf：時間管理配列
//*********************************************************************************
void CtrlSignal(long *aryInfo, long *aryTimeBuf)
{
    long TimeBuf = 0;//未使用

    switch(aryInfo[areaState])
    {
        //--------------------------------------------------------------------------------------------------------------------------
        //■アイドル状態　
        //検知信号からの割込み待ち
        case enm_Sts0_WaitDetection:
            break;
        
        //--------------------------------------------------------------------------------------------------------------------------
        //■通過センサがONになっているかチェック
        case enm_Sts1_CheckPassOn:
                //通過センサがONになっているかチェック
                //ONになっている事で通過OFF待ち状態へ移動
                if(digitalRead(aryInfo[portNumPass]) == PASS_ON)
                {
                    GetTime(aryTimeBuf[timeWaitPassStart]);//エア命令準備開始時間をセット
                    ChangeState(aryInfo, enm_Sts2_WaitPassOff);//通過完了待ち状態へ移行
                }
                //※通過センサノイズによる連続PE検知の対策
                //PE検知ON時に通過OFFの場合は無視してアイドル状態に戻す
                //(PE検知信号は必ず通過ON中に発信される)
                else if(aryInfo[portNumPass] == PORT_SENSOR_PASS_PE)
                    ChangeState(aryInfo, enm_Sts0_WaitDetection);//アイドル状態へ移行

                //検知後、待ち時間以上経過しても通過センサがONにならない場合はアイドル状態に戻す
                else if(CheckElapsedTime(aryTimeBuf[timeGetDetect], TIME_CANCEL_PASS_ON))
                    ChangeState(aryInfo, enm_Sts0_WaitDetection);//アイドル状態へ移行
            break;

        //--------------------------------------------------------------------------------------------------------------------------
        //■"通過完了割込み待ち"　割込みが来たら "エア命令発信遅延" へ
        //※■※指定時間経っても割込が無い時は通常状態に戻す
        case enm_Sts2_WaitPassOff:
#pragma region 通過完了待ち---------------------------
            if(digitalRead(aryInfo[portNumPass]) == PASS_OFF)
            {
                //エア命令ON時間状態へ移行
                digitalWrite(aryInfo[portNumLED], LED_OFF);
                digitalWrite(aryInfo[portNumAir], AIR_ON);
                GetTime(aryTimeBuf[timePassEnd]);//エア出力命令出力準備の終了時間をセット(未使用)
                ChangeState(aryInfo, enm_Sts3_AirSignal);//エア命令ON時間状態へ移行
            }
            //検知信号受信後、通過センサがOFFしない場合はタイムアウト[TIME_CANCEL]
            else if(CheckElapsedTime(aryTimeBuf[timeWaitPassStart], TIME_CANCEL) && 
                        aryInfo[areaState] == enm_Sts2_WaitPassOff)
            {
                digitalWrite(aryInfo[portNumLED], LED_OFF);
                ChangeState(aryInfo, enm_Sts0_WaitDetection);//アイドル状態へ移行
            }
            break;
#pragma endregion


        //--------------------------------------------------------------------------------------------------------------------------
        //■エア命令ON時間
        //エア出力命令の時間を
        case enm_Sts3_AirSignal:
#pragma region エア命令信号発信-------------------------------
            //特定時間経過後、エア命令OFFしてアイドル状態へ移行[TIME_AIR_SIGNAL_ON]
            if(CheckElapsedTime(aryTimeBuf[timePassEnd], TIME_AIR_SIGNAL_ON))
            {
                digitalWrite(aryInfo[portNumAir], AIR_OFF);
                ChangeState(aryInfo, enm_Sts0_WaitDetection);//アイドル状態へ
            }
            break;
#pragma endregion

    }
}

//*********************************************************************************
//移行する状態をセット
//aryInfo：ステータス配列
//stateNum：状態番号
//*********************************************************************************
void ChangeState(long *aryInfo, int stateNum)
{
    aryInfo[areaState] = stateNum;
}


//*********************************************************************************
//LED点滅処理
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
