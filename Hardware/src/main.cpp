#include "main.h"
#include "printToPC.h"
#include "max30102.h"

void setup() {
  // put your setup code here, to run once:
  SerialPort_Init();
  MAX30102_Init();
  xTaskCreate(PrintToPC_task, "PrintToPC_task", 4096, NULL, 1, NULL);
  xTaskCreate(getHeartRate_task, "getHeartRate_task", 4096, NULL, 1, NULL);
}

void loop() {
}