#include <stdint.h>

uint32_t *RCC_AHB1ENR = (uint32_t*)0x40023830;
// RCC (Base Address => 0x40023800)
// RCC_AHB1ENR (Address Offset => 0x30)
// RCC_AHB1ENR Address => 0x40023830
uint32_t *GPIOB_MODER = (uint32_t*)0x40020400;
// GPIOB (Base Address => 0x40020400)
// GPIO_MODER (Address Offset => 0x00)
// GPIOB_MODER Address => 0x40020400
uint32_t *GPIO_ODR = (uint32_t*)0x40020414;
// GPIOB (Base Address => 0x40020400)
// GPIO_ODR (Address Offset => 0x14)
// GPIO_ODR Address => 0x40020414

int main(void)
{
	// Enable Clock for PORTB (Bit 1 = 1 enable clock)
	*RCC_AHB1ENR = 0X00000002;  // 0000 0000 0000 0000 0000 0000 0000 0010
	*GPIOB_MODER = 0X00010040;  // 0000 0000 0000 0001 0000 0000 0100 0000
	// 01: output mode
	// Bit 7-> 0, Bit 6-> 1 => To make Pin 3 Output Mode
	// Bit 17-> 0, Bit 16-> 1 => To make Pin 8 Output Mode

	while(1)
	{
		*GPIO_ODR = 0x00000008;	// Pin 3 ON,  Pin 8 OFF
		*GPIO_ODR = 0x00000108; // Pin 3 ON,  Pin 8 ON
		*GPIO_ODR = 0x00000100;	// Pin 3 OFF, Pin 8 ON
		*GPIO_ODR = 0x00000000; // Pin 3 OFF, Pin 8 OFF
	}
}
