#include "head.h"

volatile uint16_t adc_value = 0;

uint8_t seg_code[11] =
{
    0xC0,   // 0
    0xF9,   // 1
    0xA4,   // 2
    0xB0,   // 3
    0x99,   // 4
    0x92,   // 5
    0x82,   // 6
    0xF8,   // 7
    0x80,   // 8
    0x90,   // 9
    0xFF    // blank
};

void small_delay(void)
{
    for (volatile long i = 0; i < 1500; i++);
}

void adc_init(void)
{
    ADMUX_REG = 0x40;
    ADCSRA_REG = 0x8F; // ADEN , ADIE, PRESCALAR(128)

}
void timer_init(){

    timer1_setmode(TIMER1_CTC_MODE);
    timer1_setcounter(0);
    timer1_setcompareA(31249);
    timer1_compareA_interrupt_enable();
    global_interrupt_enable();
    timer1_start(TIMER_PRESCALER_1024);
}
void app_init(void)
{
    gpio_port_config(GPIO_PORT_B, 0x7F); //display-1
    gpio_port_config(GPIO_PORT_L, 0xFF); //display-2
    gpio_port_config(GPIO_PORT_C, 0xFF); // digit selction

    adc_init();
    timer_init();
 
}

/* ADC display + voltage display together */

void display_adc_and_voltage(uint16_t adc)
{
    uint8_t adc_d1, adc_d2, adc_d3, adc_d4;
    uint8_t v_d1, v_d2, v_d3, v_d4;

    uint32_t voltage_mv;
    uint16_t voltage_display;

    uint8_t voltage_pattern;

    /*  ADC value digits */
    adc_d1 = adc / 1000;
    adc_d2 = (adc / 100) % 10;
    adc_d3 = (adc / 10) % 10;
    adc_d4 = adc % 10;

    /*
      Voltage calculation

      ADC range: 0 to 1023
      Voltage range: 0 to 5000mV

      voltage_mv = adc * 5000 / 1023

      Example:
      adc = 512
      voltage_mv approximately 2502mV
    */
    voltage_mv = ((uint32_t)adc * 5000UL) / 1023UL;

    /*
      To show 2.50, use:

      2500mV / 10 = 250

      Then:
      250 becomes 2 . 5 0 blank
    */
    voltage_display = voltage_mv / 10;

    v_d1 = voltage_display / 100;
    v_d2 = (voltage_display / 10) % 10;
    v_d3 = voltage_display % 10;
    v_d4 = 10;    // blank

   /* digit-1*/ 
    gpio_port_write(GPIO_PORT_C, 0x00); //initally all off
    gpio_port_write(GPIO_PORT_B, seg_code[adc_d1]);// adc value
    voltage_pattern = seg_code[v_d1] & 0x7F; //to have decimal point (bit7=0)
    gpio_port_write(GPIO_PORT_L, voltage_pattern);
    gpio_port_write(GPIO_PORT_C, 0x11);
    small_delay();

   /* digit-2 */
    gpio_port_write(GPIO_PORT_C, 0x00);

    gpio_port_write(GPIO_PORT_B, seg_code[adc_d2]);
    gpio_port_write(GPIO_PORT_L, seg_code[v_d2]);
    gpio_port_write(GPIO_PORT_C, 0x22);

    small_delay();

    /* digit-3 */
    gpio_port_write(GPIO_PORT_C, 0x00);

    gpio_port_write(GPIO_PORT_B, seg_code[adc_d3]);
    gpio_port_write(GPIO_PORT_L, seg_code[v_d3]);
    gpio_port_write(GPIO_PORT_C, 0x44);

    small_delay();

    /*  Digit-4 */
    gpio_port_write(GPIO_PORT_C, 0x00);

    gpio_port_write(GPIO_PORT_B, seg_code[adc_d4]);
    gpio_port_write(GPIO_PORT_L, seg_code[v_d4]);
    gpio_port_write(GPIO_PORT_C, 0x88);

    small_delay();
}

ISR(TIMER1_COMPA_vect)
{
    ADCSRA_REG |= 0x40;

}

ISR(ADC_vect)
{
    adc_value = ADCL_REG;
    adc_value |= (ADCH_REG << 8);
}