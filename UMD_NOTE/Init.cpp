#include "Init.h"

long AryStsPE[5] = {0,0,0,0,0};
long AryStsW[5] = {0,0,0,0,0};

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
    pinMode(PORT_LED_PE, OUTPUT);
    pinMode(PORT_LED_W, OUTPUT);
    pinMode(PORT_LED_AIR, OUTPUT);
    
    digitalWrite(PORT_AIR_PE, AIR_OFF);
    digitalWrite(PORT_AIR_W, AIR_OFF);
    digitalWrite(PORT_LED, LED_OFF);
    digitalWrite(PORT_LED_PE, LED_OFF);
    digitalWrite(PORT_LED_W, LED_OFF);
    digitalWrite(PORT_LED_AIR, LED_OFF);
}