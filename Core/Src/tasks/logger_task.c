/*
 * logger_task.c
 *
 *  Created on: 30 Jan 2026
 *      Author: Csaba
 */
#include "tasks/logger_task.h"
#include "string.h"
#include "cmsis_os.h"
#include "queue.h"
#include "peripherals/usart.h"
#include "stm32f4xx_hal.h"

/* Private objects */
static osThreadId_t loggerTaskHandle;
static QueueHandle_t logQueue;

/* Task attributes */
static const osThreadAttr_t loggerTask_attributes = {
		.name = "loggerTask",
		.stack_size = 128 * 4,
		.priority = (osPriority_t) osPriorityNormal1,
};

/* Task function */
static void LoggerTask(void *argument)
{
    char msg[64];

    for (;;)
    {
        if (xQueueReceive(logQueue, msg, portMAX_DELAY) == pdPASS)
        {
            HAL_UART_Transmit(&huart2,
                              (uint8_t *)msg,
                              strlen(msg),
                              HAL_MAX_DELAY);
        }
    }
}

/* Task interface functions */
void LoggerTask_Init(void)
{
    logQueue = xQueueCreate(8, sizeof(char[64]));
    loggerTaskHandle = osThreadNew(LoggerTask, NULL, &loggerTask_attributes);
}

void LoggerTask_Log(const char *msg)
{
    /* Non-blocking, drop if full */
    xQueueSend(logQueue, msg, 0);
}


