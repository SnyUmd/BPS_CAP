//信号のHigh/Low-----------------------
#define LED_ON 0
#define LED_OFF 1

#define AIR_ON 0
#define AIR_OFF 1

#define PASS_ON 0
#define PASS_OFF 1

//Port番号----------------------- 
#define PORT_SENSOR_PASS_PE 4//通過センサ入力ポート PE
#define PORT_SENSOR_PASS_W 5//通過センサ入力ポート 白

#define PORT_DETECTION_PE 2//検知信号割込みポート　PE
#define PORT_DETECTION_W 3//検知信号割込みポート　白

#define PORT_AIR_PE 6//エア命令出力ポート PE
#define PORT_AIR_W 7//エア命令出力ポート 白

#define PORT_LED 13//Arduino搭載LEDポート
#define PORT_LED_AIR 14//未使用
#define PORT_LED_PE 15//検知～通過終了まで点灯(エア命令準備中)　PE
#define PORT_LED_W 16//検知～通過終了まで点灯(エア命令準備中)　白

//割込み番号------------------------
#define INT_NUM_AREA2 0//検知割込み番号　PE
#define INT_NUM_AREA3 1//検知割込み番号　白

//時間（ms）
//#define TIME_WAIT 50//未使用
#define TIME_AIR_SIGNAL_ON 20//エア命令信号時間
#define TIME_CANCEL 500//検知受信後から通過センサがOFFにならない場合のタイムアウト時間
#define TIME_CANCEL_PASS_ON 50//検知受信後に通過センサがONにならない場合のタイムアウト時間（白のみ）

//通過センサのバタつきが起こっている為、
//カメラ制御BOXからPE検出信号が、1つのCAPに対して複数送信される。
//1つのPE信号を受けた後、一定時間のPE信号を無視するようにする。
#define TIME_CANCEL_NEXT_DETECT_PE 50 //★PE検知時に通過OFFで無視する処理を入れた為250→50へ変更
#define TIME_CANCEL_NEXT_DETECT_W 50


//その他-----------------------
//#define AREA_NUM_PE 2//未使用
//#define AREA_NUM_W 3//未使用

#define TIME_MAX_VALUE 4294967295//PGM開始からの時間カウント最大値
//#define TIME_DEVIDE 0//未使用

//デバッグ用--------------------------
////#define CNT_DEBUG 100000
#define PORT_DEBUG_PE 11
#define PORT_DEBUG_W 12
