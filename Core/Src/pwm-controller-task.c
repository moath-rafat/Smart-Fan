#include "pwm-controller-task.h"

extern volatile uint16_t temp;

void pwm_controller_handler(void * const pvParameters) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;) {
		uint16_t t = temp; // temp might change if an interrupt fires
		TIM2->CCR2 = ((t - 25) * TIM2->ARR) / (40 - 25);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
	}
}
