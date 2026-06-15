# ATmega2560 GPIO Library

## Overview

This folder contains a register-level GPIO library for the ATmega2560 microcontroller.
The library provides simple functions to configure and control digital input/output pins without using Arduino built-in functions such as `pinMode()`, `digitalWrite()`, or `digitalRead()`.

The main aim of this library is to understand direct register programming using `DDR`, `PORT`, and `PIN` registers.

---

## GPIO Concept

In ATmega2560, each GPIO port is controlled mainly by three registers:

| Register | Purpose                                                          |
| -------- | ---------------------------------------------------------------- |
| `DDRx`   | Configures pin direction as input or output                      |
| `PORTx`  | Writes HIGH/LOW to output pins or enables pull-up for input pins |
| `PINx`   | Reads the current logic value of input pins                      |

Example for PORTB:

| Register | Description                  |
| -------- | ---------------------------- |
| `DDRB`   | Direction register for PORTB |
| `PORTB`  | Output register for PORTB    |
| `PINB`   | Input register for PORTB     |

---

## Features

* Full port direction configuration
* Single pin direction configuration
* Full port write operation
* Single pin HIGH/LOW write operation
* Full port read operation
* Single pin read operation
* Single pin toggle operation
* Internal pull-up enable and disable support
* Supports PORTA to PORTL except PORTI
* Written using direct register addresses

---

## Folder Structure

```text
GPIO/
│
├── LIBRARY/
│   ├── gpio_configure.h
│   └── gpio_configure.cpp
│
├── EXAMPLES/
│   ├── GPIO_PORT_OUTPUT/
│   ├── GPIO_PIN_OUTPUT/
│   ├── GPIO_PIN_TOGGLE/
│   └── GPIO_INPUT_PULLUP/
│
└── README.md
```

---

## Supported Ports

| Macro         | ATmega2560 Port |
| ------------- | --------------- |
| `GPIO_PORT_A` | PORTA           |
| `GPIO_PORT_B` | PORTB           |
| `GPIO_PORT_C` | PORTC           |
| `GPIO_PORT_D` | PORTD           |
| `GPIO_PORT_E` | PORTE           |
| `GPIO_PORT_F` | PORTF           |
| `GPIO_PORT_G` | PORTG           |
| `GPIO_PORT_H` | PORTH           |
| `GPIO_PORT_J` | PORTJ           |
| `GPIO_PORT_K` | PORTK           |
| `GPIO_PORT_L` | PORTL           |

---

## Important Macros

```c
#define GPIO_HIGH       1
#define GPIO_LOW        0

#define GPIO_INPUT      0
#define GPIO_OUTPUT     1

#define GPIO_PORT_INPUT   0x00
#define GPIO_PORT_OUTPUT  0xFF
```

---

## Library Functions

### Port Configuration

```c
void gpio_port_config(uint8_t port, uint8_t direction);
```

Configures the complete port as input, output, or custom direction.

Example:

```c
gpio_port_config(GPIO_PORT_B, GPIO_PORT_OUTPUT);
```

Equivalent register operation:

```c
DDRB = 0xFF;
```

---

### Pin Configuration

```c
void gpio_pin_config(uint8_t port, uint8_t pin, uint8_t direction);
```

Configures a selected pin as input or output.

Example:

```c
gpio_pin_config(GPIO_PORT_B, 5, GPIO_OUTPUT);
```

Equivalent register operation:

```c
DDRB |= (1 << 5);
```

---

### Port Write

```c
void gpio_port_write(uint8_t port, uint8_t value);
```

Writes an 8-bit value to a complete port.

Example:

```c
gpio_port_write(GPIO_PORT_B, 0xFF);
```

Equivalent register operation:

```c
PORTB = 0xFF;
```

---

### Pin Write

```c
void gpio_pin_write(uint8_t port, uint8_t pin, uint8_t value);
```

Writes HIGH or LOW to a selected pin.

Example:

```c
gpio_pin_write(GPIO_PORT_B, 5, GPIO_HIGH);
```

Equivalent register operation:

```c
PORTB |= (1 << 5);
```

---

### Port Read

```c
uint8_t gpio_port_read(uint8_t port);
```

Reads the complete input value from a port.

Example:

```c
uint8_t value = gpio_port_read(GPIO_PORT_D);
```

Equivalent register operation:

```c
value = PIND;
```

---

### Pin Read

```c
uint8_t gpio_pin_read(uint8_t port, uint8_t pin);
```

Reads the logic level of a selected pin.

Example:

```c
uint8_t value = gpio_pin_read(GPIO_PORT_D, 2);
```

Returns:

```text
GPIO_HIGH if pin is HIGH
GPIO_LOW  if pin is LOW
```

---

### Pin Toggle

```c
void gpio_pin_toggle(uint8_t port, uint8_t pin);
```

Toggles the selected output pin.

Example:

```c
gpio_pin_toggle(GPIO_PORT_B, 5);
```

Equivalent register operation:

```c
PORTB ^= (1 << 5);
```

---

### Internal Pull-up Enable

```c
void gpio_pullup_enable(uint8_t port, uint8_t pin);
```

Enables the internal pull-up resistor for an input pin.

Example:

```c
gpio_pin_config(GPIO_PORT_D, 2, GPIO_INPUT);
gpio_pullup_enable(GPIO_PORT_D, 2);
```

Equivalent register operation:

```c
DDRD &= ~(1 << 2);
PORTD |= (1 << 2);
```

When pull-up is enabled:

```text
Button not pressed → input reads HIGH
Button pressed     → input reads LOW
```

---



## Example Programs

| Example Folder      | Description                                                 |
| ------------------- | ----------------------------------------------------------- |
| `GPIO_PORT_OUTPUT`  | Configures a full port as output and writes HIGH/LOW values |
| `GPIO_PIN_OUTPUT`   | Configures a single GPIO pin as output                      |
| `GPIO_PIN_TOGGLE`   | Toggles a selected GPIO pin                                 |
| `GPIO_INPUT_PULLUP` | Reads button input using internal pull-up resistor          |

---

## Notes

* This library is written for ATmega2560.
* It uses direct register addresses instead of Arduino functions.
* PORTI is not included because ATmega2560 does not provide a normal GPIO PORTI.
* Internal pull-up is useful for switches, push buttons, and keypad row inputs.
* The library is mainly created for learning low-level embedded programming.

---

## Learning Outcomes

By using this GPIO library, the user can understand:

* How GPIO pins are configured using DDR registers
* How output pins are controlled using PORT registers
* How input pins are read using PIN registers
* How bit manipulation is used in embedded C
* How to create reusable driver-style code for microcontrollers

---

## Author

Developed by Rishikesh S
B.E. Electronics and Communication Engineering
Bannari Amman Institute of Technology
