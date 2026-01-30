/*
 * default_task.c
 *
 *  Created on: 30 Jan 2026
 *      Author: Csaba
 */
#include "tasks/default_task.h"
#include "cmsis_os.h"

/* Private objects */
static osThreadId_t defaultTaskHandle;

const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Task function */
static void DefaultTask(void *argument)
{
    for(;;)
    {
      osDelay(1);
    }
}

/* Task interface functions */
void DefaultTask_Init(void)
{
	defaultTaskHandle = osThreadNew(DefaultTask, NULL, &defaultTask_attributes);
}



