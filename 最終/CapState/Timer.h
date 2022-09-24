#include <Arduino.h>

void GetTime(long& valTime);//時間取得（起動後の経過時間）
bool CheckElapsedTime(long startTime, long targetTime);//時間タイムアウトチェック