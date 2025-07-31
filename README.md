# 🌡️ STM32F4 ADC UART Sensor Read Project

This project demonstrates how to interface an **analog sensor** with an **STM32F4** microcontroller, read sensor values via the **ADC (Analog-to-Digital Converter)**, and transmit those values over **UART** to a PC. This enables real-time monitoring of sensor data through a **serial terminal** or a **debugger's Live Expressions** view.

---

## 📦 Project Structure

| File        | Description                                      |
|-------------|--------------------------------------------------|
| `main.c`    | Core application logic: UART + ADC initialization and loop |
| `uart.c/h`  | UART driver for serial communication             |
| `ADC.c/h`   | ADC driver for analog sensor data acquisition    |

---

## 🧰 Requirements

### 🖥️ Hardware
- STM32F4 Development Board (e.g., STM32F401RE, STM32F407VG)
- Analog sensor (e.g., temperature, potentiometer)
- USB-to-UART converter *(if your board lacks native USB-UART)*
- Breadboard + jumper wires (optional, for prototyping)

### 💻 Software
- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) *(or compatible IDE/toolchain)*
- ARM GCC toolchain (if using CLI-based development)
- Serial terminal: PuTTY, Tera Term, Minicom, etc.
- STM32F4 standard peripheral libraries (`stm32f4xx.h`, etc.)

---

## ⚙️ Configuration Details

### ✅ UART Setup
| Parameter    | Value     |
|--------------|-----------|
| Peripheral   | UART2     |
| TX Pin       | PA2       |
| RX Pin       | PA3       |
| Baud Rate    | 115200    |
| Data Bits    | 8         |
| Stop Bits    | 1         |
| Parity       | None      |
| Flow Control | None      |

UART is configured for transmitting sensor data to the PC via USB-to-Serial.

### ✅ ADC Setup
| Setting       | Value         |
|---------------|---------------|
| Analog Input  | PA1           |
| Resolution    | 12-bit        |
| Input Voltage | 0–3.3V        |

PA1 is set to **Analog Mode** to receive sensor input. ADC readings are started manually and read in polling mode.

---

## 🚀 How It Works

1. **Initialization**  
   - `UART2_RXTX_INIT()` configures UART2 for serial output.
   - `pa1_adc_init()` sets up PA1 as an analog input for the ADC.

2. **Main Loop Execution**
   ```c
   while (1) {
       start_conversion();                     // Begin ADC conversion
       sensor_value = adc_read();              // Read sensor value
       printf("sensor value: %d\n\r", sensor_value); // Send via UART
   }
Continuously reads the sensor value.

Transmits the data over UART to be viewed in a terminal or debugger.

🧪 How to Use
Hardware Setup

-Connect your analog sensor to PA1.

-Connect your board to the PC using USB-UART (PA2 to RX, PA3 to TX).

-Build & Flash

-Import or create the project in STM32CubeIDE.

-Add the provided uart.c, uart.h, ADC.c, and ADC.h files.

-Flash the firmware to your STM32F4 board.

-View Output

-Open your serial terminal (realterm, Tera Term).

-Connect to the appropriate COM port with 115200 baud.

-Observe live sensor values being printed every loop.

🧠 Example Snippet
c
Copy
Edit
// Initialize UART and ADC
UART2_RXTX_INIT();     // UART2 for serial output
pa1_adc_init();        // Set up PA1 for ADC input

while (1) {
    start_conversion();                  // Begin ADC conversion
    sensor_value = adc_read();           // Read digital value
    printf("sensor value: %d\n\r", sensor_value); // Output to terminal
}
📝 Notes
Make sure printf() is properly retargeted to UART in your toolchain.

If using STM32CubeIDE, enable semihosting or use ITM_SendChar() alternatives if UART retargeting fails.

Check your board’s clock configuration—ADC timing depends on it.

If no output is seen:

Verify COM port and UART wiring

Ensure baud rate and parity settings match in your terminal

Confirm sensor is properly connected to PA1 and powered

👨‍💻 Author
Desai
🗓️ Created on: July 31, 2025

Example Experiment: (I have used capacitive soil moisture sensor u can use any of the analog sensor or just for testing purpose u can directly connect the adc pin with +3.3v or gnd (only for implementation purpose only) u can see the values for gnd and 3.3v in live expression tab i.e gnd=0,1... and 3.3v=4095)
Soil Moisture Sensor Experiment

--I have learned about different types of soil sensors such as capacitive and resistive sensors, and how they work by detecting changes in the conductivity or dielectric constant of the soil. These sensors are widely used in precision agriculture, automated irrigation, and environmental monitoring, providing real-time insights into soil conditions.

✅ Practical Example Used
As part of my learning, I used a capacitive soil moisture sensor to observe its behavior and verify the output signal. This type of sensor is more durable in moist conditions compared to resistive types.
📹 A video demonstration is also provided as a reference for how the sensor performs in real-world conditions.
