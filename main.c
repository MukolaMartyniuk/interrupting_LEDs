#include "stm32f4xx_hal.h"

#define LED_GREEN GPIO_PIN_12
#define LED_RED GPIO_PIN_14
#define LED_BLUE GPIO_PIN_15
#define LED_YELLO GPIO_PIN_13
#define BTN_USER GPIO_PIN_0
#define JITTER_TIME_MS 5

int led_on = 1;

static int led_state = 0;

EXTI_HandleTypeDef exti_Handle = {0};

void LED_Init(void)
{

	GPIO_InitTypeDef gpio_InitStruct = {0};

	__HAL_RCC_GPIOD_CLK_ENABLE();

	gpio_InitStruct.Pin = LED_GREEN | LED_YELLO | LED_RED | LED_BLUE;
	gpio_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &gpio_InitStruct);
}

void Button_Init(void)
{

	GPIO_InitTypeDef gpio_InitStruct = {0};
	EXTI_ConfigTypeDef exti_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	gpio_InitStruct.Pin = BTN_USER;
	gpio_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &gpio_InitStruct);

	exti_InitStruct.Line = EXTI_LINE_0;
	exti_InitStruct.Mode = EXTI_MODE_INTERRUPT;
	exti_InitStruct.Trigger = EXTI_TRIGGER_RISING;
	exti_InitStruct.GPIOSel = EXTI_GPIOA;
	HAL_EXTI_SetConfigLine(&exti_Handle, &exti_InitStruct);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}

void EXTI0_IRQHandler(void)
{

	static int last_interrupt_start_tick = 0;

	for (volatile int i = 0; i < 1000000; ++i)
		;

	if (HAL_EXTI_GetPending(&exti_Handle, EXTI_TRIGGER_RISING_FALLING))
	{
		if (led_on == 1)
		{
			led_on = 0;
		}
		else
		{
			led_on = 1;
		}
		HAL_EXTI_ClearPending(&exti_Handle, EXTI_TRIGGER_RISING_FALLING);
	}
}

int main(void)
{

	HAL_Init();

	Button_Init();

	LED_Init();

	while (1)
	{
		if (led_on)
		{
			HAL_GPIO_WritePin(GPIOD, LED_BLUE, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED_YELLO, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED_GREEN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, LED_RED, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOD, LED_GREEN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED_RED, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOD, LED_BLUE, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, LED_YELLO, GPIO_PIN_SET);
		}
	}
}
