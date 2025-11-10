# LIS3DSH Tilt Detection (Register-Level SPI)

This project demonstrates **SPI communication between STM32F407 Discovery Board and the onboard LIS3DSH accelerometer** to detect board tilt and light corresponding LEDs on **PORTD**.

---

## 🔧 Hardware Setup

| Signal | STM32 Pin | Description |
|---------|------------|-------------|
| SCK     | PA5        | SPI Clock |
| MISO    | PA6        | Master In Slave Out |
| MOSI    | PA7        | Master Out Slave In |
| CS      | PE3        | Chip Select (Active LOW) |
| LEDs    | PD12–PD15  | Green, Orange, Red, Blue LEDs |

---

## ⚙️ Features
- Register-level SPI (no HAL)
- Reads acceleration from LIS3DSH
- Detects tilt (X and Y axes)
- Controls LEDs based on tilt direction

---

## 🧩 Files
- `main.c` → Complete code for SPI initialization and tilt detection
- `README.md` → Project documentation

---

## 🧑‍💻 Author
**Vignesh Vasudevan** 
