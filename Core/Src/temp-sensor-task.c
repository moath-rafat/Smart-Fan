#include "temp-sensor-task.h"

extern volatile uint16_t temp;
extern volatile uint16_t adc_raw_temp;

void ADC_init(void);

void temp_sensor_handler(void * const pvParameters) {
	ADC_init();

	for(;;) {
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		uint16_t raw = adc_raw_temp;
		temp = ((((raw * 3300) / 4096 - 760) * 1000) / 25 + 25000) / 1000;
	}
}

void ADC_init(void) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM3->PSC = 1599;   // 16 MHz / 1600 = 10 kHz
	TIM3->ARR = 99;     // 10 kHz / 100 = 100 Hz (10 ms)

	// TRGO on update event
	TIM3->CR2 &= ~TIM_CR2_MMS;
	TIM3->CR2 |=  TIM_CR2_MMS_1;

	TIM3->CR1 |= TIM_CR1_CEN;


	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	// Enable temp sensor
	ADC->CCR |= ADC_CCR_TSVREFE;

	ADC->CCR |= ADC_CCR_ADCPRE_0;

	ADC1->CR1 |= ADC_CR1_EOCIE;    // Enable EOC interrupt

	ADC1->CR2 |= ADC_CR2_EXTEN_0;  // Trigger on rising edge
	ADC1->CR2 |= (0x4 << 24);      // EXTSEL = TIM3 TRGO
	ADC1->CR2 |= ADC_CR2_EOCS;

	// Long sampling time for temp sensor
	ADC1->SMPR1 |= (7 << 18);      // SMP16 = 480 cycles

	// One conversion: channel 16
	ADC1->SQR1 = 0;
	ADC1->SQR3 = 16;

	// Enable ADC
	ADC1->CR2 |= ADC_CR2_ADON;

	// Enable ADC interrupt in NVIC
	NVIC_SetPriority(ADC_IRQn, 5);
	NVIC_EnableIRQ(ADC_IRQn);

}
