#include <stdint.h>

uint32_t *RCC_AHB1ENR = (uint32_t*)0x40023830;
uint32_t *GPIOD_MODER = (uint32_t*)0x40020C00;
uint32_t *GPIO_ODR = (uint32_t*)0x40020C14;

int main(void)
{
	*RCC_AHB1ENR = 0X00000008;
	*GPIOD_MODER = 0X01000000;

	while(1)
	{
		*GPIO_ODR = 0x00001000;
		*GPIO_ODR = 0x00000000;
	}
}
