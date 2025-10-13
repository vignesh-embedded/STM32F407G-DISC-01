#include <stdint.h>

uint32_t *RCC_AHB1ENR = (uint32_t*)0x40023830;
uint32_t *GPIOD_MODER = (uint32_t*)0x40020C00;
uint32_t *GPIOD_ODR = (uint32_t*)0x40020C14;

void delay(void)
{
    for (volatile int i = 0; i < 1000000; i++);
}

int main(void)
{
	*RCC_AHB1ENR |= (1 << 3);
	*GPIOD_MODER &= (~(1 << 25));
	*GPIOD_MODER |=  (1 << 24);

	*GPIOD_MODER &= (~(1 << 27));
	*GPIOD_MODER |=  (1 << 26);

	*GPIOD_MODER &= (~(1 << 29));
	*GPIOD_MODER |=  (1 << 28);

	*GPIOD_MODER &= (~(1 << 31));
	*GPIOD_MODER |=  (1 << 30);

	while(1)
	{
		*GPIOD_ODR |=  (1 << 12);
		delay();
		*GPIOD_ODR &= ~(1 << 12);
		delay();
		*GPIOD_ODR |=  (1 << 13);
		delay();
		*GPIOD_ODR &= ~(1 << 13);
		delay();
		*GPIOD_ODR |=  (1 << 14);
		delay();
		*GPIOD_ODR &= ~(1 << 14);
		delay();
		*GPIOD_ODR |=  (1 << 15);
		delay();
		*GPIOD_ODR &= ~(1 << 15);
		delay();
	}
}
