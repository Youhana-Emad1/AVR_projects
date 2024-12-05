# README

## Student Information
- **Name:** Youhana Emad Youhana  
- **Section:** 7  
- **Department:** Communication  
- **Code:** 4230497  

---

## Projects Overview

### 1st Project: Simple Calculator
In this project, I developed a simple calculator using the Atmega 32 microcontroller (AVR). The calculator can perform various arithmetic operations, including addition, subtraction, multiplication, and division. 

**Project Highlights:**
- **Microcontroller:** Atmega 32 (AVR)
- **Display:** 2x16 Liquid Crystal Display (LCD)
- **Input:** 4x4 Keypad
- **Development Environment:** Eclipse

### 2nd Project: Weather Station System
I designed and developed a weather station utilizing several components, which includes a temperature sensor for monitoring environmental conditions.

**Project Highlights:**
- **Microcontroller:** Atmega 32 (AVR)
- **Temperature Sensor:** LM35
- **Fan Control:** DC Fan
- **Display:** 2x16 LCD
- **Development Environment:** Eclipse

**Functionality:**
1. If the temperature is less than 20°C, the fan is off.
2. If the temperature is between 20°C and 22°C, the fan operates at 50% duty cycle.
3. If the temperature is between 22°C and 25°C, the fan operates at 75% duty cycle.
4. If the temperature is between 25°C and 30°C, the fan operates at 90% duty cycle.
5. If the temperature exceeds 30°C, the fan operates at 100% duty cycle.

### 3rd Project: Smart Home System
In this project, I developed a Smart Home System employing a master-slave configuration with two Atmega 32 microcontrollers.

**Project Highlights:**
- **Microcontrollers:** 2 Atmega 32 (AVR) (master and slave)
- **Display:** 2x16 LCD
- **Input:** 4x4 Keypad
- **Additional Components:** 3.3mm LEDs and switches
- **Development Environment:** Eclipse

### 4th Project: Traffic Light System Based on RTOS
I designed and developed a traffic light system implemented with a real-time operating system (RTOS).

**Project Highlights:**
- **Microcontroller:** Atmega 32 (AVR)
- **LEDs:** 3x3.3mm LEDs
- **Development Environment:** Eclipse

**Functionality:**
- The red LED is illuminated for 60 seconds.
- The yellow LED (waiting) is illuminated next for 5 seconds.
- The green LED is illuminated for 30 seconds.
- The system then cycles back to the yellow LED for 5 seconds before returning to the red LED.

### 5th Project: Traffic Light System Based on FreeRTOS
This project involves a traffic light system designed using FreeRTOS to simulate a traffic control system.

**Project Highlights:**
- **Microcontroller:** Atmega 32 (AVR)
- **LEDs:** 3x3.3mm LEDs
- **Development Environment:** Eclipse

**Functionality:**
- Similar to the previous traffic light project, the red LED remains on for 60 seconds, followed by a 5-second illumination of the yellow LED (waiting).
- The green LED is then illuminated for 30 seconds, followed by another 5 seconds of the yellow LED before reverting back to the red LED.

