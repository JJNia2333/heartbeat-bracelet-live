#ifndef __PRINTTOPC_H
#define __PRINTTOPC_H
#include "main.h"

extern QueueHandle_t print_msg_queue;
typedef enum
{
    PRINT_ENABLE = 1,
    PRINT_DISABLE = 0
} print_stus_type_t;
typedef struct
{
    print_stus_type_t enable_print;
    int heart_rate;
} print_msg_t;


void SerialPort_Init();
void PrintToPC_task(void *pvParameters);
#endif // !__PRINTTOPC_H