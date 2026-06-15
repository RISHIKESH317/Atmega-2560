#ifndef KEYPAD_CONFIGURE_H
#define KEYPAD_CONFIGURE_H

#include <stdint.h>
#include "gpio_configure.h"

/*
 * ATmega2560 4x4 Keypad Library
 *
 * Features:
 * - 4x4 matrix keypad scanning
 * - Software debounce
 * - Wait-for-release support
 * - Uses GPIO library
 *
 * Hardware assumption:
 * - One GPIO port is used
 * - Lower nibble  bits 0-3 are row inputs
 * - Upper nibble  bits 4-7 are column outputs
 */

/* ================= KEYPAD DEFINITIONS ================= */

#define KEYPAD_NOT_PRESSED   '\0'

/* ================= KEYPAD FUNCTIONS ================= */

void keypad_init(uint8_t port);
char keypad_scan(uint8_t port);
char keypad_getkey(uint8_t port);

#endif