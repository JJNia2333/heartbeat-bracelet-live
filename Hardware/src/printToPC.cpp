#include "printToPC.h"

QueueHandle_t print_msg_queue;

void SerialPort_Init()
{
    Serial.begin(115200);
    print_msg_queue = xQueueCreate(10, sizeof(print_msg_t));

    printf("\n ********Serial Port Initialized*********\n");
}

void PrintToPC_task(void *pvParameters)
{
    print_msg_t print_msg;
    while (1)
    {
        if (xQueueReceive(print_msg_queue, &print_msg, portMAX_DELAY) == PRINT_ENABLE)
        {
            printf("$%d\r\n", print_msg.heart_rate);
        }
    }
}