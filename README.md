# Interfacing ATmega328P with PC using RS485 Protocol

-------------------------------------------------------------------------------------------------------------------------------------------
## Introduction

Tutorial on interfacing your Windows 10 PC with an ATmega328P microcontroller using RS485 Protocol for Bidirectional Communication.

- **In the first case**,
  - ATmega328P will send a text string "Hello from ATmega328P" to PC where a C# application will read and display it on the console Window.

- **In the second case**,
  - PC will send ASCII charcters to the ATmega328P microcontroller through the RS485 link and the LED's connected to the Microcontroller will light up depending upon the command


## Toolchain /IDE

- The Code for ATmega328P is written in **AVR C** using **ATMEL Studio 7**.
- C# code is written using **Microsoft Visual Studio Community Edition 2019**.

## Tools used 

- ATmega328P Microcontroller
- MAX485 RS485 chip
