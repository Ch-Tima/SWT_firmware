[![status: experimental](https://img.shields.io/badge/status-experimental-orange)]()
[![limited](https://img.shields.io/badge/version-test--build-red)]()

# SWT 🚧 (v0.2b)

**SWT** is a desktop smart clock based on the **STM32F103** microcontroller,  
featuring an **LX-12864-B5** graphic LCD.  
It displays **time, date, temperature**, and includes a **settings menu**.


## Important Notice — Development Status
> **Warning:**  
> The project is currently under **development**.  
> Errors and incorrect behavior **may occur** in both hardware and firmware.  
> A new **schematic and PCB design** are being created.  
>
> However, the repository **[`SWT_hardware_docs`](https://github.com/Ch-Tima/SWT_hardware_docs)**  
> already contains:
> - Full component datasheets  
> - Preliminary circuit drawings  
> - Hardware design references  
>
> At this stage, **the risk of design or schematic errors is high**.  
> A fully verified circuit and board layout will be published in future updates.

## Features
| Component | Description |
|------------|--------------|
| **MCU** | STM32F103C8T6 (Cortex-M3, 72 MHz) |
| **Display** | LX-12864-B5 (SPI interface) |
| **RTC** | Built-in real-time clock (LSE 32.768 kHz) |
| **Power** | 3.3V 300mAh, Li-ion battery supported |
| **Battery charging** | LTH7R-based Li-ion charging module (usb) |
| **Temperature sensor** | Analog thermistor (ADC input) |
| **Control** | Two buttons (UP / DOWN) |
| **LCD Backlight** | Controlled via GPIO |


### Requirements
- **STM32CubeIDE ≥ 1.18**
- **STM32CubeMX** (included with CubeIDE)
- **ST-Link v2** or **OpenOCD**

## Developer

- **Name**: Tymofii
- **GitHub**: [Ch-Tima](https://github.com/Ch-Tima)

## License
This project is licensed under the GNU Affero General Public License v3.0 (AGPL-3.0)  
See the [LICENSE](LICENSE) file for details.