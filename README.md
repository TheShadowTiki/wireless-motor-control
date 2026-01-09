# Wireless Motor Control

## Overview

This project implements a wireless motor speed control system using two microcontrollers. A user controls the motor speed from a browser-based interface over WiFi. An ESP32 handles the wireless communication and forwards commands to an MSP430FR2355, which performs PWM-based motor control and updates an LCD display.

Motor speed is controlled as a percentage from 0% to 100%, with the current value displayed in real time on the LCD.

## Video Demo

A short video demonstration of the working system is available here:

https://github.com/user-attachments/assets/c6f56627-b7d6-451f-9f7c-10c3a04ff481

The video shows wireless motor speed adjustment from a phone browser, with real-time response from the motor and LCD.

## Wiring Diagram

Below is the hardware setup used for the project, including the ESP32, MSP430FR2355, motor driver, motor, and LCD.

<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/2e8d3667-c0a4-4e76-914f-42d2770effad" />

## User Interface

The user interface is a simple web application served over WiFi. It provides a slider and input field for selecting the desired motor speed percentage. When a value is submitted, it is sent to the ESP32 as an HTTP request.

<img width="250" height="542" alt="image" src="https://github.com/user-attachments/assets/752d0378-50ab-4036-ba0b-72e3ff56f2fc" />
<img width="250" height="542" alt="image" src="https://github.com/user-attachments/assets/a70d7106-6d49-460a-b096-2617dd252eaf" />
<img width="250" height="542" alt="image" src="https://github.com/user-attachments/assets/d735faa6-037c-4a21-88bf-7093d7a18ec1" />

The ESP32 parses the request and sends the motor speed value to the MSP430 over UART.

## Hardware Used

The main components used in this project are listed below:

- ESP32 development board
    
- MSP430FR2355 launchpad
    
- DC motor
    
- Motor driver module
    
- I2C LCD display
    
- External power supply

## Repository Structure

- `esp32/` – ESP32 WiFi server and UART communication code
    
- `msp430/` – MSP430 PWM motor control and LCD display code
    
- `ui/` – Python-based web interface for motor control
    
- `README.md` – Project overview
