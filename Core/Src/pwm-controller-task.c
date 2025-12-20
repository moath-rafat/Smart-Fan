#include "pwm-controller-task.h"

extern volatile uint16_t temp;

void pwm_controller_handler(void * const pvParameters) {
	TickType_t xLastWakeTime = xTaskGetTickCount();
	for(;;) {
		uint16_t t = temp; // temp might change if an interrupt fires

		if (t < 25) {
			// Fan off
			TIM2->CCR2 = 0;
		} else if (t > 40) {
			// Full speed
			TIM2->CCR2 = TIM2->ARR;
		} else {
			// 25°C → 0%, 40°C → 100%
			TIM2->CCR2 = ((t - 25) * TIM2->ARR) / (40 - 25);
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(100));
	}
}
