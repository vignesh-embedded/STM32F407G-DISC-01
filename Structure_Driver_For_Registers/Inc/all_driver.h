/*
 * dreiver.h
 *
 *  Created on: Oct 11, 2025
 *      Author: vignesh
 */

#ifndef DRIVER_H_
#define DRIVER_H_

/*
 * all_drivers.h
 *
 *  Created on: Oct 11, 2025
 *      Author: vignesh
 */

#ifndef ALL_DRIVERS_H_
#define ALL_DRIVERS_H_

typedef struct
{
	uint32_t MODER0 :2;
	uint32_t MODER1 :2;
	uint32_t MODER2 :2;
	uint32_t MODER3 :2;
	uint32_t MODER4 :2;
	uint32_t MODER5 :2;
	uint32_t MODER6 :2;
	uint32_t MODER7 :2;
	uint32_t MODER8 :2;
	uint32_t MODER9 :2;
	uint32_t MODER10 :2;
	uint32_t MODER11 :2;
	uint32_t MODER12 :2;
	uint32_t MODER13 :2;
	uint32_t MODER14 :2;
	uint32_t MODER15 :2;
}GPIOx_MODER;

typedef struct
{
	uint32_t IDR0 :1;
	uint32_t IDR1 :1;
	uint32_t IDR2 :1;
	uint32_t IDR3 :1;
	uint32_t IDR4 :1;
	uint32_t IDR5 :1;
	uint32_t IDR6 :1;
	uint32_t IDR7 :1;
	uint32_t IDR8 :1;
	uint32_t IDR9 :1;
	uint32_t IDR10 :1;
	uint32_t IDR11 :1;
	uint32_t IDR12 :1;
	uint32_t IDR13 :1;
	uint32_t IDR14 :1;
	uint32_t IDR15 :1;
	uint32_t Reserved :16;
}GPIOx_IDR;

typedef struct
{
	uint32_t ODR0 :1;
	uint32_t ODR1 :1;
	uint32_t ODR2 :1;
	uint32_t ODR3 :1;
	uint32_t ODR4 :1;
	uint32_t ODR5 :1;
	uint32_t ODR6 :1;
	uint32_t ODR7 :1;
	uint32_t ODR8 :1;
	uint32_t ODR9 :1;
	uint32_t ODR10 :1;
	uint32_t ODR11 :1;
	uint32_t ODR12 :1;
	uint32_t ODR13 :1;
	uint32_t ODR14 :1;
	uint32_t ODR15 :1;
	uint32_t Reserved :16;
}GPIOx_ODR;

typedef struct
{
	GPIOx_MODER MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	GPIOx_IDR IDR;
	GPIOx_ODR ODR;
	uint32_t BSSR;
	uint32_t LCKR;
	uint32_t AFR[2];
}GPIO_TypeDef;


typedef struct
{
	uint32_t GPIOAEN :1;
	uint32_t GPIOBEN :1;
	uint32_t GPIOCEN :1;
	uint32_t GPIODEN :1;
	uint32_t GPIOEEN :1;
	uint32_t GPIOFEN :1;
	uint32_t GPIOGEN :1;
	uint32_t GPIOHEN :1;
	uint32_t GPIOIEN :1;
	uint32_t Reserved_01 :3;
	uint32_t CRCEN :1;
	uint32_t Reserved_02 :5;
	uint32_t BKPSRAMEN :1;
	uint32_t Reserved_03 :1;
	uint32_t CCMDATARAMEN :1;
	uint32_t DMA1EN :1;
	uint32_t DMA2EN :1;
	uint32_t Reserved_04 :2;
	uint32_t ETHMACEN :1;
	uint32_t ETHMACTXEN :1;
	uint32_t ETHMACRXEN :1;
	uint32_t ETHMACPTPEN :1;
	uint32_t OTGHSEN :1;
	uint32_t OTGHSULPIEN :1;
	uint32_t Reserved_05 :1;
}RCC_AHB1ENR;


#endif /* ALL_DRIVERS_H_ */

#endif /* DRIVER_H_ */
