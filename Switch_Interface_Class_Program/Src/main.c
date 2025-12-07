#include <stdint.h>

uint32_t *RCC_AHB1ENR   = (uint32_t*)0x40023830;  // RCC Base Address + AHB1 Add.Offset
uint32_t *GPIOD_MODER   = (uint32_t*)0x40020C00;  // GPIOD Base Address + Mode Register Add.Offset
uint32_t *GPIOD_ODR     = (uint32_t*)0x40020C14;  // GPIOD Base Address + 0x14
uint32_t *GPIOC_MODER   = (uint32_t*)0x40020800;  // GPIOC Base Address + Mode Register Add.Offset
uint32_t *GPIOC_PUPDR   = (uint32_t*)0x4002080C;  // GPIOC Base Address + 0x0C
uint32_t *GPIOC_IDR     = (uint32_t*)0x40020810;  // GPIOC Base Address + 0x10

int main()
{
    // Enable clock for GPIOC bit2 and GPIOD bit3
    *RCC_AHB1ENR |= (1<<2);      // GPIOC enable, 0001 << 2 => 0100 and do OR
    *RCC_AHB1ENR |= (1<<3);      // GPIOD enable  0001 << 3 => 1000 and do OR

    // Make PD12, PD13 as output for LED
    *GPIOD_MODER = 0x05000000;   // 0000 0101 0000 0000 0000 0000 0000 0000
    *GPIOC_MODER = 0x00000000;

    // Enable pull-down for PC5, PC6, PC7
    *GPIOC_PUPDR = 0x00002A00;   // 0000 0000 0000 0000 0010 1010 0000 0000

    while(1)
    {
        uint32_t switch1 = (*GPIOC_IDR >> 5) & 1;  // PC5
        uint32_t switch2 = (*GPIOC_IDR >> 6) & 1;  // PC6
        uint32_t switch3 = (*GPIOC_IDR >> 7) & 1;  // PC7

        if(switch1)
        {
            *GPIOD_ODR |=  (1<<12);   // LED PD12 ON
            *GPIOD_ODR &= ~(1<<13);   // LED PD13 OFF
        }
        else if(switch2)
        {
            *GPIOD_ODR |=  (1<<13);   // LED PD13 ON
            *GPIOD_ODR &= ~(1<<12);   // LED PD12 OFF
        }
        else if(switch3)
        {
            *GPIOD_ODR |=  (1<<12) | (1<<13);  // Both ON
        }
    }
}
