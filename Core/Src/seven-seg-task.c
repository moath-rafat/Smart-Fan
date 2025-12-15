#include "seven-seg-task.h"

extern volatile uint8_t temp;

// Using common anode segments
uint8_t seg_vals[10] = {0B11000000, 0B11111001, 0B10100100, 0B10110000, 0B10011001,
				0B10010010, 0B10000010, 0B11111000, 0B10000000, 0B10011000};

void seven_seg_handler(void * const pvParameters) {
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for(;;) {
		GPIOA->ODR &= ~((1 << 1) | (1 << 0));
		GPIOD->ODR = (GPIOD->ODR & ~0xff) | seg_vals[temp % 10];
		GPIOA->ODR |= (1 << 0);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2));

		GPIOA->ODR &= ~((1 << 1) | (1 << 0));
		GPIOD->ODR = (GPIOD->ODR & ~0xff) | seg_vals[temp / 10];
		GPIOA->ODR |= (1 << 1);
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2));
	}
}


