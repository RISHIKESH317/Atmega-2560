#ifndef HEAD_H
#define HEAD_H

#include <avr/interrupt.h>
#include <stdint.h>

#include "gpio_configure.h"
#include "timer_configure.h"

/* ADC registers */
#define ADMUX_REG  (*(volatile uint8_t *)0x7C)
#define ADCSRA_REG (*(volatile uint8_t *)0x7A)
#define ADCL_REG   (*(volatile uint8_t *)0x78)
#define ADCH_REG   (*(volatile uint8_t *)0x79)

extern volatile uint16_t adc_value;

void adc_init(void);
void app_init(void);

/* new function */
void display_adc_and_voltage(uint16_t adc);

#endif
