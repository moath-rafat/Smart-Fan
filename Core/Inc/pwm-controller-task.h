#ifndef INC_PWM_CONTROLLER_TASK_H_
#define INC_PWM_CONTROLLER_TASK_H_

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

void pwm_controller_handler(void * const pvParameters);

#endif
