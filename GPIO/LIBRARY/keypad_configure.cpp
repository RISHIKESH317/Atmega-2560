#include "keypad_configure.h"

/* =========================================================
   PRIVATE SOFTWARE DELAY
   ========================================================= */

/*
 * Small blocking delay used only for keypad debounce.
 *
 * This is not a general delay library.
 * It is kept private inside keypad driver.
 */
static void keypad_debounce_delay(void)
{
    for(volatile uint32_t i = 0; i < 25000; i++);
}

/* =========================================================
   KEYPAD MAP
   ========================================================= */

/*
 * Keypad layout:
 *
 * 1   2   3   +
 * 4   5   6   -
 * 7   8   9   *
 * ~   0   =   /
 */
static const char keypad_map[4][4] =
{
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'~', '0', '=', '/'}
};

/* =========================================================
   KEYPAD FUNCTIONS
   ========================================================= */

/*
 * Initialize keypad port.
 *
 * Lower nibble  bits 0-3 = input rows
 * Upper nibble  bits 4-7 = output columns
 *
 * DDRx  = 0xF0
 * PORTx = 0xFF
 *
 * PORTx lower bits HIGH enables internal pull-up for rows.
 * PORTx upper bits HIGH keeps all columns inactive initially.
 */
void keypad_init(uint8_t port)
{
    gpio_port_config(port, 0xF0);
    gpio_port_write(port, 0xFF);
}

/*
 * Scan keypad once.
 *
 * Returns:
 * KEYPAD_NOT_PRESSED if no key is pressed
 * actual character if key is pressed
 */
char keypad_scan(uint8_t port)
{
    uint8_t row_value;
    uint8_t row;

    for(uint8_t col = 0; col < 4; col++)
    {
        /*
         * First make all columns HIGH.
         */
        gpio_port_write(port, 0xFF);

        /*
         * Drive one column LOW at a time.
         * Column pins are bits 4,5,6,7.
         */
        gpio_pin_write(port, col + 4, GPIO_LOW);

        /*
         * Small settling delay.
         */
        for(volatile uint16_t i = 0; i < 500; i++);

        /*
         * Read lower nibble.
         * Rows are connected to bits 0,1,2,3.
         */
        row_value = gpio_port_read(port) & 0x0F;

        /*
         * If all rows are HIGH, no key is pressed in this column.
         */
        if(row_value == 0x0F)
        {
            continue;
        }

        /*
         * Debounce delay.
         */
        keypad_debounce_delay();

        /*
         * Confirm key press after debounce.
         */
        row_value = gpio_port_read(port) & 0x0F;

        if(row_value == 0x0F)
        {
            return KEYPAD_NOT_PRESSED;
        }

        /*
         * Decode row.
         *
         * With pull-up:
         * no press = 1111
         * row 0 press = 1110 = 0x0E
         * row 1 press = 1101 = 0x0D
         * row 2 press = 1011 = 0x0B
         * row 3 press = 0111 = 0x07
         */
        if(row_value == 0x0E)
        {
            row = 0;
        }
        else if(row_value == 0x0D)
        {
            row = 1;
        }
        else if(row_value == 0x0B)
        {
            row = 2;
        }
        else if(row_value == 0x07)
        {
            row = 3;
        }
        else
        {
            return KEYPAD_NOT_PRESSED;
        }

        /*
         * Wait until key is released.
         */
        while((gpio_port_read(port) & 0x0F) != 0x0F);

        keypad_debounce_delay();

        /*
         * Return actual key.
         */
        return keypad_map[row][col];
    }

    return KEYPAD_NOT_PRESSED;
}

/*
 * Blocking key read.
 *
 * This function waits until one key is pressed.
 */
char keypad_getkey(uint8_t port)
{
    char key;

    do
    {
        key = keypad_scan(port);
    }
    while(key == KEYPAD_NOT_PRESSED);

    return key;
}