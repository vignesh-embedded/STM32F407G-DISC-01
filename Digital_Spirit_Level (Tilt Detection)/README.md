# 🚀 STM32F4-Discovery: Bare-Metal SPI Driver for LIS3DSH Accelerometer

This project implements a **bare-metal SPI master driver** to interface with the **on-board LIS3DSH 3-Axis Accelerometer** on the **STM32F407G-DISC1 Discovery Kit**.

The application reads the **X and Y-axis acceleration data** and uses it to implement a **Tilt-Sensing LED application**, turning on one of the four on-board LEDs (PD12, PD13, PD14, PD15) corresponding to the tilt direction.

This project is implemented **entirely using register-level programming**, manipulating the **RCC**, **GPIO**, and **SPI** peripheral registers directly — without relying on HAL, LL libraries, or CubeMX.  
It demonstrates strong fundamental knowledge of STM32 architecture and embedded firmware design.

---

## ✨ Technical Highlights

### 🔹 Bare-Metal Register Access
- Direct control of RCC, GPIO, and SPI peripherals using base addresses and register offsets.
- Full peripheral setup from scratch without HAL or CubeMX.

### 🔹 SPI1 Master Implementation
- Configured **SPI1** in **Master Mode**.
- **SPI Mode 3** communication (`CPOL=1`, `CPHA=1`).
- Baud rate configured to **fPCLK/16 ≈ 5.25 MHz**.
- Software Slave Management (SSM) enabled.
- Controlled data flow using polling on **TXE** (Transmit Empty) and **RXNE** (Receive Not Empty) flags.

### 🔹 External Device Interface (LIS3DSH)
- `lis_write()` function writes to device registers (e.g., CTRL_REG4 = 0x67 to wake up the sensor).
- Chip Select (CS) manually controlled via PE3 (LOW → transaction start, HIGH → transaction end).

### 🔹 Data Handling
The 16-bit signed acceleration data is reconstructed from two 8-bit registers:

```c
accel_x = (int16_t)((rx_data[1] << 8) | rx_data[0]);
