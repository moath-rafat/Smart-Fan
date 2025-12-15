#include "pwm-controller-task.h"

extern volatile uint8_t temp;

void pwm_controller_handler(void * const pvParameters) {
	uint8_t t = temp; // temp might change if an interrupt fires

	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;) {
		if(t > 40) {
			// 100%
			TIM2->CCR2 = TIM2->ARR;
		}
		else if(t >= 20 && t <= 40) {
			// 75%
			TIM2->CCR2 = (TIM2->ARR * 3) / 4;
		} else {
			TIM2->CCR2 = 0;
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
	}
}
