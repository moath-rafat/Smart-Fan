# STM32F407 Board Cooler Fan Controller (FreeRTOS)

This project implements a **board temperature–based cooling fan controller** using an **STM32F407** microcontroller and **FreeRTOS**.

The system periodically samples the **internal temperature sensor**, displays the temperature on **dual 7-segment displays**, and controls a **DC fan** using **PWM** with smooth linear speed control.

---

## Features

- STM32F407 internal temperature sensor
- FreeRTOS task-based architecture
- PWM fan speed control
- Dual 7-segment temperature display

---

## System Overview

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

## Fan Control Logic

The fan speed is controlled linearly based on temperature:

25C -> 0%, 40C -> 100%  
duty = ((temp - 25) * ARR) / (40 - 25);
