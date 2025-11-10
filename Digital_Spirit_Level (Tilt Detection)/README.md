🚀 STM32F4-Discovery: Bare-Metal SPI Driver for LIS3DSH Accelerometer

This project implements a complete, bare-metal SPI master driver to interface with the on-board LIS3DSH 3-Axis Accelerometer on the STM32F407G-DISC1 Discovery Kit.

The application reads the X and Y-axis acceleration data and utilizes it to implement a simple Tilt-Sensing LED application, turning on one of the four on-board LEDs (PD12, PD13, PD14, PD15) corresponding to the tilt direction.

This entire implementation is done by directly manipulating the memory-mapped peripheral registers (RCC, GPIO, SPI) without using the STM32 HAL, LL libraries, or CubeMX. This demonstrates a deep, fundamental understanding of the STM32 architecture.

✨ Technical Highlights

This project serves as a strong portfolio entry, showcasing proficiency in core embedded systems development:

Bare-Metal Register Access: Direct configuration and control of the RCC, GPIO, and SPI peripherals using their base addresses and offsets, demonstrating a comprehensive understanding of the STM32 microcontroller datasheet.

SPI Master Implementation: Full configuration of the SPI1 peripheral in Master Mode, including:

Setting CPOL=1 and CPHA=1 (SPI Mode 3) for LIS3DSH communication.

Configuring Baud Rate (fPCLK/16 for ~5.25 MHz).

Implementing Software Slave Management (SSM).

Synchronous Communication: The spi_transmit_receive() function correctly handles the SPI handshake using register polling:

Polling the TXE (Transmit Buffer Empty) flag before writing to SPI1_DR.

Polling the RXNE (Receive Buffer Not Empty) flag before reading from SPI1_DR.

External Device Interface (LIS3DSH):

Implemented device-specific write function (lis_write) to configure the sensor's CTRL_REG4 for data rate and axis enablement.

Managed the Chip Select (CS) pin (PE3) manually by pulling it LOW before a transaction and HIGH afterward.

Data Handling: Correctly concatenating the two 8-bit registers (Low Byte and High Byte) into a single 16-bit signed integer (int16_t) to reconstruct the acceleration value.


$$\text{accel\_x} = (\text{int}16\_\text{t})((\text{rx\_data}[1] \ll 8) \mid \text{rx\_data}[0])$$

📌 Hardware & Peripheral Configuration

Component

Function

Configuration

Microcontroller

STM32F407VGT6



Board

STM32F407G-DISC1 (Discovery Kit)



Sensor

LIS3DSH (3-Axis Accelerometer)



SPI Pins (GPIOA)

PA5 (SCK), PA6 (MISO), PA7 (MOSI)

Configured to Alternate Function (AF5).

Chip Select (GPIOE)

PE3 (CS)

Configured as General Purpose Output.

Status LEDs (GPIOD)

PD12 (Green), PD13 (Orange), PD14 (Red), PD15 (Blue)

Configured as General Purpose Output.

🛠️ Toolchain and Environment

Development Environment: STM32CubeIDE (or equivalent GCC toolchain)

Operating System: Zorin OS (Linux)

Programming Language: C

Compiler: GNU C Compiler (GCC)

📁 Code Structure

The main file (main.c - containing the provided code) consists of three key functions:

main():

Initializes clocks (RCC) for all necessary peripherals.

Configures GPIO pins for Output, Alternate Function, and initial CS state.

Configures the SPI1 peripheral control register (SPI1_CR1).

Initializes the LIS3DSH sensor using lis_write().

Enters the main while(1) loop for continuous data acquisition and LED control.

spi_transmit_receive(uint8_t data):

The core driver function responsible for polling the status register and exchanging 8 bits of data over the SPI bus.

lis_write(uint8_t reg_addr, uint8_t data):

Handles the CS pin toggling and sequential transmission of register address (write mode implied) followed by data.

delay(uint32_t count):

Simple software blocking delay loop.

⚙️ How to Compile and Run

Clone this repository.

Import the project into STM32CubeIDE (or compile using an ARM-Cortex cross-compiler).

Flash the resulting binary file (.elf or .bin) onto the STM32F407G Discovery Board.

Observe the on-board LEDs (PD12-PD15) light up based on the physical tilt direction of the board.
