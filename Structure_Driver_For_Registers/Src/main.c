#include <stdint.h>
#include "all_driver.h"
//uint32_t *RCC_AHB1ENR   = (uint32_t*)0x40023830;  // RCC Base Address + AHB1 Add.Offset
//uint32_t *GPIOD_MODER   = (uint32_t*)0x40020C00;  // GPIOD Base Address + Mode Register Add.Offset
//uint32_t *GPIOD_ODR     = (uint32_t*)0x40020C14;  // GPIOD Base Address + 0x14
//uint32_t *GPIOA_MODER   = (uint32_t*)0x40020000;  // GPIOA Base Address + Mode Register Add.Offset
//uint32_t *GPIOA_IDR     = (uint32_t*)0x40020010;  // GPIOA Base Address + 0x10
uint32_t value = 0;

GPIO_TypeDef *GPIOD = (GPIO_TypeDef*)0x40020C00;
GPIO_TypeDef *GPIOA = (GPIO_TypeDef*)0x40020000;
RCC_AHB1ENR *RCC_AHB1 = (RCC_AHB1ENR*)0x40023830;

int main()
{
    // Enable RCC for GPIOD and GPIOA
    RCC_AHB1->GPIOAEN = 1;     // GPIOD enable
    RCC_AHB1->GPIODEN = 1;     // GPIOA enable

    // GPIOD 12th Pin Output
    //*GPIOD_MODER &= (~(1<<25));
    //*GPIOD_MODER |= (1<<24);
    GPIOD->MODER.MODER12 = 1;
    // Enable GPIOA Pin as I/P
    //*GPIOA_MODER &= (~(3<<0));
    GPIOA->MODER.MODER0 = 0;

    while(1)
    {
    	value = GPIOA->IDR.IDR0;
        if(value==1)
        	{
        		//*GPIOD_ODR |= (1<<12);   // Set LED 12 ON
        		GPIOD->ODR.ODR12 = 1;
        	}
        else
        	{
        		GPIOD->ODR.ODR12 = 0;	// Clear LED 12 OFF
        	}
    }
}
