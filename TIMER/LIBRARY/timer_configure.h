#ifndef TIMER_CONFIGURE_H
#define TIMER_CONFIGURE_H

#include <stdint.h>

/*
 * ATmega2560 Timer Library
 * Supports:
 * - Timer0 and Timer1
 * - Normal Mode
 * - CTC Mode
 * - Fast PWM Mode
 * - Phase Correct PWM Mode
 * - Polling and Interrupt-based usage
 */

/* ================= TIMER0 REGISTERS ================= */

#define TCCR0A_REG (*(volatile uint8_t *)0x44)   // Timer0 Control Register A
#define TCCR0B_REG (*(volatile uint8_t *)0x45)   // Timer0 Control Register B
#define TCNT0_REG  (*(volatile uint8_t *)0x46)   // Timer0 Counter Register
#define OCR0A_REG  (*(volatile uint8_t *)0x47)   // Timer0 Output Compare Register A
#define OCR0B_REG  (*(volatile uint8_t *)0x48)   // Timer0 Output Compare Register B
#define TIFR0_REG  (*(volatile uint8_t *)0x35)   // Timer0 Interrupt Flag Register
#define TIMSK0_REG (*(volatile uint8_t *)0x6E)   // Timer0 Interrupt Mask Register

/* ================= TIMER1 REGISTERS ================= */

#define TCCR1A_REG (*(volatile uint8_t *)0x80)    // Timer1 Control Register A
#define TCCR1B_REG (*(volatile uint8_t *)0x81)    // Timer1 Control Register B
#define TCCR1C_REG (*(volatile uint8_t *)0x82)    // Timer1 Control Register C

#define TCNT1_REG  (*(volatile uint16_t *)0x84)   // Timer1 Counter Register
#define ICR1_REG   (*(volatile uint16_t *)0x86)   // Timer1 Input Capture Register

#define OCR1A_REG  (*(volatile uint16_t *)0x88)   // Timer1 Output Compare Register A
#define OCR1B_REG  (*(volatile uint16_t *)0x8A)   // Timer1 Output Compare Register B
#define OCR1C_REG  (*(volatile uint16_t *)0x8C)   // Timer1 Output Compare Register C

#define TIFR1_REG  (*(volatile uint8_t *)0x36)    // Timer1 Interrupt Flag Register
#define TIMSK1_REG (*(volatile uint8_t *)0x6F)    // Timer1 Interrupt Mask Register

/* ================= COMMON REGISTER ================= */

#define SREG_REG (*(volatile uint8_t *)0x5F)      // Status Register, bit 7 = Global Interrupt Enable

/* ================= TIMER MODES ================= */

/*
 * These mode numbers are software labels only.
 * They are used inside timer0_setmode() and timer1_setmode().
 */

#define TIMER0_NORMAL_MODE          100
#define TIMER0_CTC_MODE             101
#define TIMER0_FAST_PWM_MODE        102
#define TIMER0_PHASE_CORRECT_MODE   103

#define TIMER1_NORMAL_MODE          200
#define TIMER1_CTC_MODE             201
#define TIMER1_FAST_PWM_MODE        202
#define TIMER1_PHASE_CORRECT_MODE   203

/* ================= PRESCALER VALUES ================= */

/*
 * These values are directly written into CS bits.
 * CS bits select the timer clock source/prescaler.
 */

#define TIMER_STOP                  0x00
#define TIMER_PRESCALER_1           0x01
#define TIMER_PRESCALER_8           0x02
#define TIMER_PRESCALER_64          0x03
#define TIMER_PRESCALER_256         0x04
#define TIMER_PRESCALER_1024        0x05

/* ================= GLOBAL INTERRUPT FUNCTIONS ================= */

void global_interrupt_enable(void);
void global_interrupt_disable(void);

/* ================= TIMER0 FUNCTIONS ================= */

void timer0_setmode(uint16_t mode);
void timer0_start(uint8_t prescaler);
void timer0_stop(void);

void timer0_setcounter(uint8_t value);
void timer0_setcompareA(uint8_t value);
void timer0_setcompareB(uint8_t value);

void timer0_overflow_interrupt_enable(void);
void timer0_overflow_interrupt_disable(void);

void timer0_compareA_interrupt_enable(void);
void timer0_compareA_interrupt_disable(void);

void timer0_clear_overflow_flag(void);
void timer0_clear_compareA_flag(void);

/* ================= TIMER1 FUNCTIONS ================= */

void timer1_setmode(uint16_t mode);
void timer1_start(uint8_t prescaler);
void timer1_stop(void);

void timer1_setcounter(uint16_t value);
void timer1_setcompareA(uint16_t value);
void timer1_setcompareB(uint16_t value);
void timer1_setcompareC(uint16_t value);

void timer1_overflow_interrupt_enable(void);
void timer1_overflow_interrupt_disable(void);

void timer1_compareA_interrupt_enable(void);
void timer1_compareA_interrupt_disable(void);

void timer1_clear_overflow_flag(void);
void timer1_clear_compareA_flag(void);

/* ================= PWM FUNCTIONS ================= */

/* Timer0 PWM Output Mode */
void timer0_pwmA_non_inverting(void);
void timer0_pwmA_inverting(void);
void timer0_pwmB_non_inverting(void);
void timer0_pwmB_inverting(void);

/* Timer1 PWM Output Mode */
void timer1_pwmA_non_inverting(void);
void timer1_pwmA_inverting(void);
void timer1_pwmB_non_inverting(void);
void timer1_pwmB_inverting(void);
void timer1_pwmC_non_inverting(void);
void timer1_pwmC_inverting(void);

void timer1_set_top(uint16_t top);

/* Duty Cycle */
void timer0_set_duty_A(uint8_t duty);
void timer0_set_duty_B(uint8_t duty);

void timer1_set_duty_A(uint16_t duty);
void timer1_set_duty_B(uint16_t duty);
void timer1_set_duty_C(uint16_t duty);

#endif
