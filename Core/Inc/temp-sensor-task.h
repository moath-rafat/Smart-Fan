#ifndef INC_TEMP_SENSOR_TASK_H_
#define INC_TEMP_SENSOR_TASK_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

void temp_sensor_handler(void * const pvParameters);

#endif
