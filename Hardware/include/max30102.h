#ifndef __MAX30102_H
#define __MAX30102_H
#include "main.h"
#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

void MAX30102_Init();
void getHeartRate_task(void *pvParameters);
#endif // !__MAX30102_H