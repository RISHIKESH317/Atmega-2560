#include "timer_configure.h"

/*  (bit manupulation hints ) 

&= ~  -> Clear bit to 0
^=    -> Toggle bit
|=    -> to set bit 

*/

/*
 * Enable global interrupts by setting I-bit in SREG.
 */
void global_interrupt_enable(void)
{
    SREG |= (1 << 7);
}

/*
 * Disable global interrupts by clearing I-bit in SREG.
 */
void global_interrupt_disable(void)
{
    SREG &= ~(1 << 7);
}

/* =========================================================
   TIMER0 FUNCTIONS
   ========================================================= */

/*
 * Select Timer0 operating mode.
 * Supported modes:
 * - Normal Mode
 * - CTC Mode
 * - Fast PWM Mode
 * - Phase Correct PWM Mode
 */
void timer0_setmode(uint16_t mode)
{
    if(mode == TIMER0_NORMAL_MODE)
    {
        // WGM02:0 = 000
        TCCR0A &= ~((1 << 0) | (1 << 1));  // Clear WGM00, WGM01
        TCCR0B &= ~(1 << 3);               // Clear WGM02
    }
    else if(mode == TIMER0_CTC_MODE)
    {
        // WGM02:0 = 010
        TCCR0A &= ~(1 << 0);               // Clear WGM00
        TCCR0A |=  (1 << 1);               // Set WGM01
        TCCR0B &= ~(1 << 3);               // Clear WGM02
    }
    else if(mode == TIMER0_FAST_PWM_MODE)
    {
        // WGM02:0 = 011
        TCCR0A |=  (1 << 0) | (1 << 1);    // Set WGM00, WGM01
        TCCR0B &= ~(1 << 3);               // Clear WGM02
    }
    else if(mode == TIMER0_PHASE_CORRECT_MODE)
    {
        // WGM02:0 = 001
        TCCR0A |=  (1 << 0);               // Set WGM00
        TCCR0A &= ~(1 << 1);               // Clear WGM01
        TCCR0B &= ~(1 << 3);               // Clear WGM02
    }
}

/*
 * Start Timer0 with selected prescaler.
 * Prescaler value is written into CS02:CS00 bits.
 */
void timer0_start(uint8_t prescaler)
{
    TCCR0B &= ~0x07;               // Clear old CS02:CS00 bits
    TCCR0B |= (prescaler & 0x07);  // Load new prescaler value
}

/*
 * Stop Timer0 by clearing CS02:CS00 bits.
 */
void timer0_stop(void)
{
    TCCR0B &= ~0x07;
}

/*
 * Load value into Timer0 counter register.
 */
void timer0_setcounter(uint8_t value)
{
    TCNT0 = value;
}

/*
 * Load value into Timer0 Output Compare Register A.
 */
void timer0_setcompareA(uint8_t value)
{
    OCR0A = value;
}

/*
 * Load value into Timer0 Output Compare Register B.
 */
void timer0_setcompareB(uint8_t value)
{
    OCR0B = value;
}

/*
 * Enable Timer0 overflow interrupt.
 * TOIE0 = bit 0 in TIMSK0.
 */
void timer0_overflow_interrupt_enable(void)
{
    TIMSK0 |= (1 << 0);
}

/*
 * Disable Timer0 overflow interrupt.
 */
void timer0_overflow_interrupt_disable(void)
{
    TIMSK0 &= ~(1 << 0);
}

/*
 * Enable Timer0 Compare Match A interrupt.
 * OCIE0A = bit 1 in TIMSK0.
 */
void timer0_compareA_interrupt_enable(void)
{
    TIMSK0 |= (1 << 1);
}

/*
 * Disable Timer0 Compare Match A interrupt.
 */
void timer0_compareA_interrupt_disable(void)
{
    TIMSK0 &= ~(1 << 1);
}

/*
 * Clear Timer0 overflow flag.
 * TOV0 = bit 0 in TIFR0.
 * Timer flags are cleared by writing logic 1.
 */
void timer0_clear_overflow_flag(void)
{
    TIFR0 = (1 << 0);
}

/*
 * Clear Timer0 Compare Match A flag.
 * OCF0A = bit 1 in TIFR0.
 * Timer flags are cleared by writing logic 1.
 */
void timer0_clear_compareA_flag(void)
{
    TIFR0 = (1 << 1);
}

/* =========================================================
   TIMER1 FUNCTIONS
   ========================================================= */

/*
 * Select Timer1 operating mode.
 * Supported modes:
 * - Normal Mode
 * - CTC Mode with OCR1A as TOP
 * - Fast PWM 8-bit Mode
 * - Phase Correct PWM 8-bit Mode
 */
void timer1_setmode(uint16_t mode)
{
    if(mode == TIMER1_NORMAL_MODE)
    {
        // WGM13:0 = 0000
        TCCR1A &= ~((1 << 0) | (1 << 1));  // Clear WGM10, WGM11
        TCCR1B &= ~((1 << 3) | (1 << 4));  // Clear WGM12, WGM13
    }
    else if(mode == TIMER1_CTC_MODE)
    {
        // WGM13:0 = 0100
        TCCR1A &= ~((1 << 0) | (1 << 1));  // Clear WGM10, WGM11
        TCCR1B |=  (1 << 3);               // Set WGM12
        TCCR1B &= ~(1 << 4);               // Clear WGM13
    }
    else if(mode == TIMER1_FAST_PWM_MODE)
{
    // Fast PWM Mode 14, WGM13:0 = 1110
    // TOP = ICR1

    TCCR1A &= ~(1 << 0);   // WGM10 = 0
    TCCR1A |=  (1 << 1);   // WGM11 = 1

    TCCR1B |=  (1 << 3);   // WGM12 = 1
    TCCR1B |=  (1 << 4);   // WGM13 = 1
}
    else if(mode == TIMER1_PHASE_CORRECT_MODE)
    {
        // Phase Correct PWM 8-bit mode, WGM13:0 = 0001
        TCCR1A |=  (1 << 0);               // Set WGM10
        TCCR1A &= ~(1 << 1);               // Clear WGM11
        TCCR1B &= ~((1 << 3) | (1 << 4));  // Clear WGM12, WGM13
    }
}

void timer1_set_top(uint16_t top)
{
    ICR1 = top;
}
/*
 * Start Timer1 with selected prescaler.
 * Prescaler value is written into CS12:CS10 bits.
 */
void timer1_start(uint8_t prescaler)
{
    TCCR1B &= ~0x07;               // Clear old CS12:CS10 bits
    TCCR1B |= (prescaler & 0x07);  // Load new prescaler value
}

/*
 * Stop Timer1 by clearing CS12:CS10 bits.
 */
void timer1_stop(void)
{
    TCCR1B &= ~0x07;
}

/*
 * Load value into Timer1 counter register.
 */
void timer1_setcounter(uint16_t value)
{
    TCNT1 = value;
}

/*
 * Load value into Timer1 Output Compare Register A.
 */
void timer1_setcompareA(uint16_t value)
{
    OCR1A = value;
}

/*
 * Load value into Timer1 Output Compare Register B.
 */
void timer1_setcompareB(uint16_t value)
{
    OCR1B = value;
}

/*
 * Load value into Timer1 Output Compare Register C.
 */
void timer1_setcompareC(uint16_t value)
{
    OCR1C = value;
}

/*
 * Enable Timer1 overflow interrupt.
 * TOIE1 = bit 0 in TIMSK1.
 */
void timer1_overflow_interrupt_enable(void)
{
    TIMSK1 |= (1 << 0);
}

/*
 * Disable Timer1 overflow interrupt.
 */
void timer1_overflow_interrupt_disable(void)
{
    TIMSK1 &= ~(1 << 0);
}

/*
 * Enable Timer1 Compare Match A interrupt.
 * OCIE1A = bit 1 in TIMSK1.
 */
void timer1_compareA_interrupt_enable(void)
{
    TIMSK1 |= (1 << 1);
}

/*
 * Disable Timer1 Compare Match A interrupt.
 */
void timer1_compareA_interrupt_disable(void)
{
    TIMSK1 &= ~(1 << 1);
}

/*
 * Clear Timer1 overflow flag.
 * TOV1 = bit 0 in TIFR1.
 * Timer flags are cleared by writing logic 1.
 */
void timer1_clear_overflow_flag(void)
{
    TIFR1 = (1 << 0);
}

/*
 * Clear Timer1 Compare Match A flag.
 * OCF1A = bit 1 in TIFR1.
 * Timer flags are cleared by writing logic 1.
 */
void timer1_clear_compareA_flag(void)
{
    TIFR1 = (1 << 1);
}

/* =========================================================
   TIMER0 PWM FUNCTIONS
   ========================================================= */

/*
 * Timer0 OC0A Non-Inverting PWM
 * COM0A1:0 = 10
 */
void timer0_pwmA_non_inverting(void)
{
    TCCR0A |=  (1 << 7);   // COM0A1 = 1
    TCCR0A &= ~(1 << 6);   // COM0A0 = 0
}

/*
 * Timer0 OC0A Inverting PWM
 * COM0A1:0 = 11
 */
void timer0_pwmA_inverting(void)
{
    TCCR0A |= (1 << 7) | (1 << 6);
}

/*
 * Timer0 OC0B Non-Inverting PWM
 * COM0B1:0 = 10
 */
void timer0_pwmB_non_inverting(void)
{
    TCCR0A |=  (1 << 5);   // COM0B1 = 1
    TCCR0A &= ~(1 << 4);   // COM0B0 = 0
}

/*
 * Timer0 OC0B Inverting PWM
 * COM0B1:0 = 11
 */
void timer0_pwmB_inverting(void)
{
    TCCR0A |= (1 << 5) | (1 << 4);
}

/*
 * Timer0 Channel A Duty Cycle
 * 8-bit duty range: 0 to 255
 */
void timer0_set_duty_A(uint8_t duty)
{
    OCR0A = duty;
}

/*
 * Timer0 Channel B Duty Cycle
 * 8-bit duty range: 0 to 255
 */
void timer0_set_duty_B(uint8_t duty)
{
    OCR0B = duty;
}

/* =========================================================
   TIMER1 PWM FUNCTIONS
   ========================================================= */

/*
 * Timer1 OC1A Non-Inverting PWM
 * COM1A1:0 = 10
 */
void timer1_pwmA_non_inverting(void)
{
    TCCR1A |=  (1 << 7);   // COM1A1 = 1
    TCCR1A &= ~(1 << 6);   // COM1A0 = 0
}

/*
 * Timer1 OC1A Inverting PWM
 * COM1A1:0 = 11
 */
void timer1_pwmA_inverting(void)
{
    TCCR1A |= (1 << 7) | (1 << 6);
}

/*
 * Timer1 OC1B Non-Inverting PWM
 * COM1B1:0 = 10
 */
void timer1_pwmB_non_inverting(void)
{
    TCCR1A |=  (1 << 5);   // COM1B1 = 1
    TCCR1A &= ~(1 << 4);   // COM1B0 = 0
}

/*
 * Timer1 OC1B Inverting PWM
 * COM1B1:0 = 11
 */
void timer1_pwmB_inverting(void)
{
    TCCR1A |= (1 << 5) | (1 << 4);
}

/*
 * Timer1 OC1C Non-Inverting PWM
 * COM1C1:0 = 10
 */
void timer1_pwmC_non_inverting(void)
{
    TCCR1A |=  (1 << 3);   // COM1C1 = 1
    TCCR1A &= ~(1 << 2);   // COM1C0 = 0
}

/*
 * Timer1 OC1C Inverting PWM
 * COM1C1:0 = 11
 */
void timer1_pwmC_inverting(void)
{
    TCCR1A |= (1 << 3) | (1 << 2);
}

/*
 * Timer1 Channel A Duty Cycle
 * For 8-bit PWM: 0 to 255
 * For 10-bit PWM: 0 to 1023
 * For 16-bit/custom TOP PWM: depends on TOP value
 */
void timer1_set_duty_A(uint16_t duty)
{
    OCR1A = duty;
}

void timer1_set_duty_B(uint16_t duty)
{
    OCR1B = duty;
}

void timer1_set_duty_C(uint16_t duty)
{
    OCR1C = duty;
}
