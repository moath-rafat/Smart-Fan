#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

void SystemClock_Config(void);
void seven_seg_gpio_init(void);

volatile uint8_t temp;

TaskHandle_t seven_seg_pointer;
TaskHandle_t temp_sensor_pointer;
TaskHandle_t pwm_contoller_pointer;

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    seven_seg_gpio_init();

    BaseType_t status;

    status = xTaskCreate(seven_seg_handler, "Seven Segment Multiplexer", 200, NULL, 1, &seven_seg_pointer);
    configASSERT(status == pdPASS);
    status = xTaskCreate(temp_sensor_handler, "Temp Sensor", 200, NULL, 2, &temp_sensor_pointer);
	configASSERT(status == pdPASS);
	status = xTaskCreate(pwm_controller_handler, "PWM Controller", 200, NULL, 3, &pwm_contoller_pointer);
	configASSERT(status == pdPASS);

	vTaskStartScheduler();

    while (1)
    {

    }
}

void seven_seg_gpio_init(void) {
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef init = {0};

	// GPIOD[0:6] connected to the two seven segments
	init.Mode = GPIO_MODE_OUTPUT_PP;
	init.Speed = GPIO_SPEED_HIGH;
	init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;

	HAL_GPIO_Init(GPIOD, &init);

	// GPIOA for controlling
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
	Error_Handler();
	}
}

void Error_Handler(void)
{
	__disable_irq();
	while (1)
	{
	}

}
