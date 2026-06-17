# ADC Data Acquisition System

A register-level ATmega2560 application demonstrating:

- Timer1 Compare Match Interrupt
- ADC Interrupt-based Conversion
- Dual 4-Digit Seven Segment Displays
- Real-time ADC Value Display
- Voltage Conversion and Display

## Peripherals Used

- GPIO Driver
- Timer Driver
- ADC Driver

## Project Flow

Potentiometer → ADC0 → Timer1 Interrupt → ADC Conversion → Voltage Calculation → Seven Segment Display

## Output

Display 1:
ADC Value (0000–1023)

Display 2:
Voltage (0.00V–5.00V)