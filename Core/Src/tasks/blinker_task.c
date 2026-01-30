/*
 * blinker_task.c
 *
 *  Created on: 30 Jan 2026
 *      Author: Csaba
 */
#include "tasks/blinker_task.h"
#include "tasks/logger_task.h"
#include "string.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

/* Private objects */
static osThreadId_t blinkerTaskHandle;
static TickType_t lastWake;
/* Task attributes */
const osThreadAttr_t blinkerTask_attributes = {
  .name = "blinkerTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Task function */
static void BlinkerTask(void *argument)
{
	lastWake = xTaskGetTickCount();
    for (;;)
    {
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		vTaskDelayUntil(&lastWake, pdMS_TO_TICKS(500));
		LoggerTask_Log("LED toggled\r\n");
    }
}

/* Task interface functions */
void BlinkerTask_Init(void)
{
    blinkerTaskHandle = osThreadNew(BlinkerTask, NULL, &blinkerTask_attributes);
}



