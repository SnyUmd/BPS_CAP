#define DEBUG_TIME_SEND

//Port番号-----------------------
#define PORT_SENSOR_PE 2
#define PORT_SENSOR_W 3

#define PORT_SENSOR_PASS_2 4
#define PORT_SENSOR_PASS_3 5

#define PORT_AIR_PE 6
#define PORT_AIR_W 7

#define PORT_LED 13
#define PORT_LED_PE 14
#define PORT_LED_W 15
#define PORT_LED_AIR 16

//割込み番号------------------------
#define INT_NUM_AREA2 0
#define INT_NUM_AREA3 1

//カウント閾------------------------
#define CNT_END_NUM 1000
#define CNT_FLG_CANCEL 62000
#define CNT_WAIT 5000

//信号論理--------------------------
#define AREA_NUM_PE 2
#define AREA_NUM_W 3

#define LED_OFF 0
#define LED_ON 1

#define AIR_ON 0
#define AIR_OFF 1

//デバッグ用--------------------------
#define CNT_DEBUG 100000
#define PORT_DEBUG_PE 11
#define PORT_DEBUG_W 12