#include <stdint.h>

/*RCC Register Address (Base Address => 0x4002 3800) */
uint32_t *RCC_AHB1ENR = (uint32_t*)0x40023830;  // RCC Base Address + AHB1 Offset (0x30)
uint32_t *RCC_APB2ENR = (uint32_t*)0x40023844;  // RCC Base Address + APB2 Offset (0x44)

/* GPIOD For LED's (Base Address => 0x40020C00) */
uint32_t *GPIOD_MODER = (uint32_t*)0x40020C00;  // GPIOD Base Address + Mode Reg (0x00)
uint32_t *GPIOD_ODR   = (uint32_t*)0x40020C14;  // GPIOD Base Address + Output Data Reg (0x14)

/* GPIOE (Base Address => 0x40021000) SPI Chip Select Pin (CS) */
uint32_t *GPIOE_MODER = (uint32_t*)0x40021000;  // GPIOE Base Address + Mode Reg (0x00)
uint32_t *GPIOE_ODR   = (uint32_t*)0x40021014;  // GPIOE Base Address + Output Data Reg (0x14)

/* GPIOA (Base Address => 0x40020000) Set GPIO to Alternate function mode for SPI */
uint32_t *GPIOA_MODER = (uint32_t*)0x40020000;  // GPIOA Base + Mode Reg (0x00)
uint32_t *GPIOA_AFRL  = (uint32_t*)0x40020020;  // GPIOA Base + Alt. Func. Low Reg (0x20)

/*SPI1 (Base Address => 0x40013000) */
uint32_t *SPI1_CR1 = (uint32_t*)0x40013000;  // SPI1 Base + Control Reg 1 (0x00)
uint32_t *SPI1_SR  = (uint32_t*)0x40013008;  // SPI1 Base + Status Reg (0x08)
uint32_t *SPI1_DR  = (uint32_t*)0x4001300C;  // SPI1 Base + Data Reg (0x0C)

// Function Prototypes
void delay(uint32_t count);
uint8_t spi_transmit_receive(uint8_t data);
void lis_write(uint8_t reg_addr, uint8_t data);

int16_t accel_x = 0;
int16_t accel_y = 0;

int main()
{
    //Enable Clock For GPIO & SPI
    *RCC_AHB1ENR |= (1<<0);  // GPIOA clock enable
    *RCC_AHB1ENR |= (1<<3);  // GPIOD clock enable
    *RCC_AHB1ENR |= (1<<4);  // GPIOE clock enable
    *RCC_APB2ENR |= (1<<12); // SPI1  clock enable

    // Set PD12, PD13, PD14, PD15 as Output (LEDs)
    *GPIOD_MODER &= ~(0xFF000000);  // 1111 1111 << 24
    *GPIOD_MODER |=  (0x55000000);  // 0101 0101 << 24 (01 = For General Purpose Output)

    // Set PE3 as Output (SPI CS)
    *GPIOE_MODER &= ~(0x03 << (3*2)); // Clear bits 6-7
    *GPIOE_MODER |=  (0x01 << (3*2)); // Set to 01 (Output)
    *GPIOE_ODR   |=  (1<<3);          // Set PE3 HIGH

    // Set PA5(SCK), PA6(MISO), PA7(MOSI) as Alternate Function (10)
    *GPIOA_MODER &= ~((0x3 << (5*2)) | (0x3 << (6*2)) | (0x3 << (7*2)));
    *GPIOA_MODER |=  ((0x2 << (5*2)) | (0x2 << (6*2)) | (0x2 << (7*2)));

    // Set Alternate Function to AF5 (0101) for SPI1
    *GPIOA_AFRL &= ~((0xF << (5*4)) | (0xF << (6*4)) | (0xF << (7*4)));
    *GPIOA_AFRL |=  ((0x5 << (5*4)) | (0x5 << (6*4)) | (0x5 << (7*4)));

    // SPI1 Configurations
    *SPI1_CR1 = 0; 		 // Clear
    *SPI1_CR1 |= (1<<1); // CPOL=1
    *SPI1_CR1 |= (1<<0); // CPHA=1
    *SPI1_CR1 |= (1<<2); // MSTR: Master mode (STM32 as Master, LIS3DSH sensor as Slave)

    /* Bard Rate Bits [2:0] = 011 (Baud rate = f_PCLK/16)
    SPI1 Connected in APB2 Bus, APB2 Clock => 84MHz, So SPI speed => 84/16 = 5.25Mhz
    */

    *SPI1_CR1 |= (0x3 << 3);
    *SPI1_CR1 |= (1<<9); // SSM: Software slave management enabled
    *SPI1_CR1 |= (1<<8); // SSI: Internal slave select
    *SPI1_CR1 |= (1<<6); // SPE: SPI Enable

    // Write 0x67 to CTRL_REG4 (0x20) to wake up LIS3DSH sensor
    lis_write(0x20, 0x67);

    while(1)
    {
        uint8_t rx_data[6];				// To store acceleration data read from sensor
        int16_t threshold = 2000;		// Tilt threshold value to activate LED's

        *GPIOE_ODR &= ~(1<<3); 			// Pull CS (PE3) LOW

        spi_transmit_receive(0xA8);		// Send Read Command

        // Read 6 bytes of data
        /* Send a dummy byte (0x00) to generate 8 clock cycles,
         * simultaneously receiving the data from the sensor's OUT_X_L,OUT_X_H register and so the other.
        */
        rx_data[0] = spi_transmit_receive(0x00); // X_LowByte
        rx_data[1] = spi_transmit_receive(0x00); // X_HighByte
        rx_data[2] = spi_transmit_receive(0x00); // Y_LowByte
        rx_data[3] = spi_transmit_receive(0x00); // Y_HighByte
        rx_data[4] = spi_transmit_receive(0x00); // Z_LowByte
        rx_data[5] = spi_transmit_receive(0x00); // Z_HighByte

        *GPIOE_ODR |= (1<<3); 			// Pull CS (PE3) HIGH

        // Shift High Byte (rx_data[1]) Left, then OR with Low Byte (rx_data[0]).
        accel_x = (int16_t)((rx_data[1] << 8) | rx_data[0]);
        accel_y = (int16_t)((rx_data[3] << 8) | rx_data[2]);

        // Turn all 4 LEDs Of PORTD OFF first
        *GPIOD_ODR &= ~((1<<12) | (1<<13) | (1<<14) | (1<<15));

        // Check X-axis => Left/Right Tilt
        if (accel_x > threshold)   		// Board is tilting in the positive X direction (Right)
        {
            *GPIOD_ODR |= (1<<14); 		// Tilted Right -> Red LED (PD14)
        }
        else if (accel_x < -threshold) 	// Board is tilting in the positive X direction (Left)
        {
            *GPIOD_ODR |= (1<<12); 		// Tilted Left -> Greem LED (PD15)
        }

        // Check Y-axis => Forward/Back Tilt
        if (accel_y > threshold)
        {
            *GPIOD_ODR |= (1<<13); 		// Tilted Forward -> Orange LED (PD13)
        }
        else if (accel_y < -threshold)
        {
            *GPIOD_ODR |= (1<<15); 		// Tilted Back -> Blue LED (PD12)
        }
        delay(50000);
    }
}

uint8_t spi_transmit_receive(uint8_t data)
{
    while (!(*SPI1_SR & (1<<1)));	// Wait until Transmit buffer is empty (TXE flag set)
    *SPI1_DR = data; 				// Write data
    while (!(*SPI1_SR & (1<<0)));	// Wait until Receive buffer is not empty (RXNE flag set)
    return (uint8_t)(*SPI1_DR);     // Return Data
}


//Function to write single byte to register in the LIS3DSH
void lis_write(uint8_t reg_addr, uint8_t data)
{
    *GPIOE_ODR &= ~(1<<3); 			// Pull CS LOW to Select to Slave (On Board LIS3DSH Sensor)
    spi_transmit_receive(reg_addr); // Send address
    spi_transmit_receive(data);		// Send data
    *GPIOE_ODR |= (1<<3); 			// Pull CS to HIGH
}

// Software delay function
void delay(uint32_t count)
{
    volatile uint32_t i = count;
    while(i--);
}
