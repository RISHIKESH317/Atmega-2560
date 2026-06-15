#ifndef GPIO_CONFIGURE_H
#define GPIO_CONFIGURE_H

#include <stdint.h>

/*
 * ATmega2560 GPIO Library
 *
 * Supports:
 * - PORTA to PORTL except PORTI
 * - Full port input/output configuration
 * - Single pin input/output configuration
 * - Port write/read
 * - Pin write/read
 * - Pin toggle
 * - Internal pull-up enable/disable
 */

/* ================= PORT SELECTION ================= */

#define GPIO_PORT_A   0
#define GPIO_PORT_B   1
#define GPIO_PORT_C   2
#define GPIO_PORT_D   3
#define GPIO_PORT_E   4
#define GPIO_PORT_F   5
#define GPIO_PORT_G   6
#define GPIO_PORT_H   7
#define GPIO_PORT_J   8
#define GPIO_PORT_K   9
#define GPIO_PORT_L   10

/* ================= GPIO LOGIC VALUES ================= */

#define GPIO_HIGH     1
#define GPIO_LOW      0

/* ================= GPIO DIRECTION VALUES ================= */

#define GPIO_INPUT    0
#define GPIO_OUTPUT   1

#define GPIO_PORT_INPUT   0x00
#define GPIO_PORT_OUTPUT  0xFF

/* ================= REGISTER POINTER ARRAYS ================= */

extern volatile uint8_t *gpio_ddr_reg[11];
extern volatile uint8_t *gpio_port_reg[11];
extern volatile uint8_t *gpio_pin_reg[11];

/* ================= GPIO PORT FUNCTIONS ================= */

void gpio_port_config(uint8_t port, uint8_t direction);
void gpio_port_write(uint8_t port, uint8_t value);
uint8_t gpio_port_read(uint8_t port);

/* ================= GPIO PIN FUNCTIONS ================= */

void gpio_pin_config(uint8_t port, uint8_t pin, uint8_t direction);
void gpio_pin_write(uint8_t port, uint8_t pin, uint8_t value);
uint8_t gpio_pin_read(uint8_t port, uint8_t pin);
void gpio_pin_toggle(uint8_t port, uint8_t pin);

/* ================= GPIO PULL-UP FUNCTIONS ================= */

void gpio_pullup_enable(uint8_t port, uint8_t pin);
void gpio_pullup_disable(uint8_t port, uint8_t pin);

#endif