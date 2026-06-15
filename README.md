# ATmega2560 Timer Library

## Overview

This repository contains a reusable Timer0 and Timer1 library developed for the **ATmega2560 microcontroller** using **direct register programming**.

The library provides support for timer configuration, polling-based timing operations, interrupt-driven timing operations, and PWM mode configuration without relying on Arduino built-in timer functions.

---

## Objectives

* Understand ATmega2560 timer architecture.
* Implement Timer0 and Timer1 using direct register access.
* Develop reusable timer driver functions.
* Demonstrate polling and interrupt-based timer applications.
* Build a foundation for PWM generation and ADC-triggered applications.

---

## Supported Timers

| Timer  | Resolution | Modes Supported                          |
| ------ | ---------- | ---------------------------------------- |
| Timer0 | 8-bit      | Normal, CTC, Fast PWM, Phase Correct PWM |
| Timer1 | 16-bit     | Normal, CTC, Fast PWM, Phase Correct PWM |

---

## Features

| Feature                        | Timer0 | Timer1 |
| ------------------------------ | ------ | ------ |
| Normal Mode                    | ✓      | ✓      |
| CTC Mode                       | ✓      | ✓      |
| Fast PWM Mode                  | ✓      | ✓      |
| Phase Correct PWM Mode         | ✓      | ✓      |
| Polling Method                 | ✓      | ✓      |
| Interrupt Method               | ✓      | ✓      |
| Prescaler Configuration        | ✓      | ✓      |
| Compare Register Configuration | ✓      | ✓      |
| PWM Output Configuration       | ✓      | ✓      |
| Duty Cycle Configuration       | ✓      | ✓      |
| Custom TOP using ICR1          | -      | ✓      |

---

## Repository Structure

```text
TIMER
│
├── LIBRARY
│   ├── timer_configure.h
│   └── timer_configure.cpp
│
├── EXAMPLES
│   ├── TIMER0_NORMAL_POLLING
│   ├── TIMER0_CTC_POLLING
│   ├── TIMER0_NORMAL_INTERRUPT
│   ├── TIMER0_CTC_INTERRUPT
│   ├── TIMER1_NORMAL_POLLING
│   ├── TIMER1_CTC_POLLING
│   ├── TIMER1_NORMAL_INTERRUPT
│   └── TIMER1_CTC_INTERRUPT
│
└── IMAGES
```

---

## Library Capabilities

### Timer Configuration

* Select Normal Mode
* Select CTC Mode
* Select Fast PWM Mode
* Select Phase Correct PWM Mode

### Timer Control

* Start Timer
* Stop Timer
* Configure Prescaler
* Load Counter Register
* Load Output Compare Register

### Interrupt Control

* Enable Overflow Interrupt
* Disable Overflow Interrupt
* Enable Compare Match Interrupt
* Disable Compare Match Interrupt
* Enable Global Interrupt
* Disable Global Interrupt

### Flag Handling

* Clear Overflow Flag
* Clear Compare Match Flag

### PWM Control

* Configure non-inverting PWM output
* Configure inverting PWM output
* Set PWM duty cycle using OCR registers
* Configure Timer1 Fast PWM Mode 14 using ICR1 as TOP
---

## Example Applications

### Timer0

* Normal Mode Polling
* CTC Mode Polling
* Normal Mode Interrupt
* CTC Mode Interrupt

### Timer1

* Normal Mode Polling
* CTC Mode Polling
* Normal Mode Interrupt
* CTC Mode Interrupt

---

## Development Environment

| Tool                 | Usage                              |
| -------------------- | ---------------------------------- |
| Arduino IDE          | Code development and uploading     |
| Wokwi                | Online simulation and testing      |
| Proteus              | Circuit simulation and verification |
| ATmega2560 Datasheet | Register reference                 |
| GitHub               | Version control and documentation  |
---

## Learning Outcomes

Through this project:

* Gained understanding of AVR timer architecture.
* Learned timer register configuration.
* Implemented delay generation using polling.
* Implemented interrupt-driven timing applications.
* Developed reusable embedded software components.
* Understood prescaler, compare match, overflow, and PWM concepts.

---

## Future Enhancements

* Timer2 Driver Support
* Input Capture Unit (ICU)
* PWM Motor Control Examples
* Timer Triggered ADC Acquisition
* Multi-Timer Applications

---

## Author

**Rishikesh**

B.E Electronics and Communication Engineering

Bannari Amman Institute of Technology

ATmega2560 Embedded Systems Learning Repository
