#include "gpio_configure.h"

/* =========================================================
   GPIO REGISTER ADDRESS TABLES
   ========================================================= */

/*
 * DDR registers are used to select input/output direction.
 *
 * DDRx bit = 1 -> Output
 * DDRx bit = 0 -> Input
 */
volatile uint8_t *gpio_ddr_reg[11] =
{
    (volatile uint8_t *)0x21,   // DDRA
    (volatile uint8_t *)0x24,   // DDRB
    (volatile uint8_t *)0x27,   // DDRC
    (volatile uint8_t *)0x2A,   // DDRD
    (volatile uint8_t *)0x2D,   // DDRE
    (volatile uint8_t *)0x30,   // DDRF
    (volatile uint8_t *)0x33,   // DDRG
    (volatile uint8_t *)0x101,  // DDRH
    (volatile uint8_t *)0x104,  // DDRJ
    (volatile uint8_t *)0x107,  // DDRK
    (volatile uint8_t *)0x10A   // DDRL
};

/*
 * PORT registers are used to write output value.
 *
 * If pin is output:
 * PORTx bit = 1 -> HIGH
 * PORTx bit = 0 -> LOW
 *
 * If pin is input:
 * PORTx bit = 1 -> Pull-up enabled
 * PORTx bit = 0 -> Pull-up disabled
 */
volatile uint8_t *gpio_port_reg[11] =
{
    (volatile uint8_t *)0x22,   // PORTA
    (volatile uint8_t *)0x25,   // PORTB
    (volatile uint8_t *)0x28,   // PORTC
    (volatile uint8_t *)0x2B,   // PORTD
    (volatile uint8_t *)0x2E,   // PORTE
    (volatile uint8_t *)0x31,   // PORTF
    (volatile uint8_t *)0x34,   // PORTG
    (volatile uint8_t *)0x102,  // PORTH
    (volatile uint8_t *)0x105,  // PORTJ
    (volatile uint8_t *)0x108,  // PORTK
    (volatile uint8_t *)0x10B   // PORTL
};

/*
 * PIN registers are used to read input value.
 */
volatile uint8_t *gpio_pin_reg[11] =
{
    (volatile uint8_t *)0x20,   // PINA
    (volatile uint8_t *)0x23,   // PINB
    (volatile uint8_t *)0x26,   // PINC
    (volatile uint8_t *)0x29,   // PIND
    (volatile uint8_t *)0x2C,   // PINE
    (volatile uint8_t *)0x2F,   // PINF
    (volatile uint8_t *)0x32,   // PING
    (volatile uint8_t *)0x100,  // PINH
    (volatile uint8_t *)0x103,  // PINJ
    (volatile uint8_t *)0x106,  // PINK
    (volatile uint8_t *)0x109   // PINL
};

/* =========================================================
   GPIO PORT FUNCTIONS
   ========================================================= */

/*
 * Configure complete port direction.
 *
 * Example:
 * gpio_port_config(PORT_B, PORT_OUTPUT);
 * gpio_port_config(PORT_D, PORT_INPUT);
 *
 * Custom direction is also allowed:
 * gpio_port_config(PORT_L, 0xF0);
 */
void gpio_port_config(uint8_t port, uint8_t direction)
{
    *gpio_ddr_reg[port] = direction;
}

/*
 * Write 8-bit value to full PORT register.
 * Example :
 * void gpio_port_write(PORT_B, 0x0f);
 */
void gpio_port_write(uint8_t port, uint8_t value)
{
    *gpio_port_reg[port] = value;
}

/*
 * Read 8-bit value from full PIN register.
 */
uint8_t gpio_port_read(uint8_t port)
{
    return *gpio_pin_reg[port];
}

/* =========================================================
   GPIO PIN FUNCTIONS
   ========================================================= */

/*
 * Configure single pin direction.
 *
 * direction:
 * OUTPUT -> work as output
 * INPUT  -> work as input
 */
void gpio_pin_config(uint8_t port, uint8_t pin, uint8_t direction)
{
    if(direction == OUTPUT)
    {
        *gpio_ddr_reg[port] |= (1 << pin);
    }
    else
    {
        *gpio_ddr_reg[port] &= ~(1 << pin);
    }
}

/*
 * Write HIGH or LOW to one output pin.
 */
void gpio_pin_write(uint8_t port, uint8_t pin, uint8_t value)
{
    if(value == HIGH)
    {
        *gpio_port_reg[port] |= (1 << pin);
    }
    else
    {
        *gpio_port_reg[port] &= ~(1 << pin);
    }
}

/*
 * Read one input pin.
 *
 * Returns:
 * GPIO_HIGH if pin is high
 * GPIO_LOW  if pin is low
 */
uint8_t gpio_pin_read(uint8_t port, uint8_t pin)
{
    if((*gpio_pin_reg[port]) & (1 << pin))
    {
        return HIGH;
    }
    else
    {
        return LOW;
    }
}
/* =========================================================
   GPIO TOGGLE FUNCTIONS
   ========================================================= */


/* to toggle specific pin */
void gpio_pin_toggle(uint8_t port, uint8_t pin)
{
    *gpio_port_reg[port] ^= (1 << pin);
}

/*to toggle entire port */
void gpio_port_toggle(uint8_t port)
{
    *gpio_port_reg[port] ^= 0xFF;
}

/* To toggle few pins in port */
void gpio_port_toggle_value(uint8_t port, uint8_t value)
{
    *gpio_port_reg[port] ^= value;
}
/* =========================================================
   GPIO PULL-UP FUNCTIONS
   ========================================================= */

/*
 * Enable internal pull-up resistor.
 *
 * Important:
 * Pin must be configured as input before enabling pull-up.
 */
void gpio_pullup_enable(uint8_t port, uint8_t pin)
{
    *gpio_port_reg[port] |= (1 << pin);
}

/*
 * Disable internal pull-up resistor.
 */
void gpio_pullup_disable(uint8_t port, uint8_t pin)
{
    *gpio_port_reg[port] &= ~(1 << pin);
}
