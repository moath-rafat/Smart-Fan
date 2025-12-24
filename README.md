# STM32F407 Board Cooler Fan Controller (FreeRTOS)

This project implements a **board temperature–based cooling fan controller** using an **STM32F407** microcontroller and **FreeRTOS**.

The system periodically samples the **internal temperature sensor**, displays the temperature on **dual 7-segment displays**, and controls a **DC fan** using **PWM** with smooth linear speed control.

---

## ✨ Features

- STM32F407 internal temperature sensor
- ADC triggered every **10 ms** using **TIM3 TRGO**
- FreeRTOS task-based architecture
- Interrupt-driven ADC with task notification
- Linear PWM fan speed control
- Dual 7-segment temperature display
- Fully register-level peripheral configuration (no HAL drivers)

---

## 🧠 System Overview

### Temperature Sampling
- ADC1 samples **channel 16** (internal temperature sensor)
- Triggered by **TIM3 update event** every **10 ms**
- ADC End-Of-Conversion interrupt wakes the temperature task

### Fan Control (PWM)
- PWM generated using **TIM2 Channel 2**
- PWM frequency ≈ **10 kHz**
- Fan speed is controlled using a **linear temperature-to-duty mapping**

### Display
- Two multiplexed **7-segment displays**
- Displays temperature in **°C**
- Refresh rate ≈ **250 Hz**

---

## 🧩 Task Architecture

| Task Name            | Priority | Function |
|---------------------|----------|----------|
| `seven_seg_handler` | 1        | Display temperature |
| `temp_sensor_handler` | 2      | ADC conversion & temperature calculation |
| `pwm_controller_handler` | 3   | Fan speed control |

---

## 🔁 Fan Control Logic

The fan speed is controlled linearly based on temperature:

| Temperature | Fan Duty |
|-------------|----------|
| < 25 °C     | 0% (OFF) |
| 25–40 °C   | (0 → 100%) |
| > 40 °C    | 100% (MAX) |

### PWM Formula
```c
duty = ((temp - 25) * ARR) / (40 - 25);
