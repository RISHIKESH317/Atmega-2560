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

#define PORT_A   0
#define PORT_B   1
#define PORT_C   2
#define PORT_D   3
#define PORT_E   4
#define PORT_F   5
#define PORT_G   6
#define PORT_H   7
#define PORT_J   8
#define PORT_K   9
#define PORT_L   10

/* ================= GPIO LOGIC VALUES ================= */

#define HIGH     1
#define LOW      0

/* ================= GPIO DIRECTION VALUES ================= */

#define GPIO_INPUT    0
#define GPIO_OUTPUT   1

#define PORT_INPUT   0x00
#define PORT_OUTPUT  0xFF

/* ===== REGISTER POINTER ARRAYS ==== */

extern volatile uint8_t *gpio_ddr_reg[11];
extern volatile uint8_t *gpio_port_reg[11];
extern volatile uint8_t *gpio_pin_reg[11];

/* ==== GPIO PORT FUNCTIONS ==== */

void gpio_port_config(uint8_t port, uint8_t direction);  // to set as output and input (full port/ custom )
void gpio_port_write(uint8_t port, uint8_t value); // to write the value to configured port (macros / custom)
uint8_t gpio_port_read(uint8_t port); // to read the value 

/* ==== GPIO PIN FUNCTIONS ==== */

void gpio_pin_config(uint8_t port, uint8_t pin, uint8_t direction); // to set as output and input (specific pin)
void gpio_pin_write(uint8_t port, uint8_t pin, uint8_t value); // to write the value to configured pin
uint8_t gpio_pin_read(uint8_t port, uint8_t pin);

/* ==== GPIO TOGGLE FUNCTION ==== */
void gpio_port_toggle (uint8_t port); //to toggle full port
void gpio_port_toggle_value (uint8_t port, uint16_t value); // to toggle port with few pins
void gpio_pin_toggle(uint8_t port, uint8_t pin); //to toggle specific pin only 

/* ==== GPIO PULL-UP FUNCTIONS ==== */

void gpio_pullup_enable(uint8_t port, uint8_t pin);
void gpio_pullup_disable(uint8_t port, uint8_t pin);

#endif
