#pragma once

// Board-specific pin mapping for ESP32-CAM with dual 74HC595 + PCF8574

#if defined(ARDUINO_ARCH_ESP32)
// ESP32-CAM: Shift register control pins for 74HC595
#define SHIFT_DS   13  // GPIO13: Data (DS)
#define SHIFT_SHCP 14  // GPIO14: Clock (SHCP)
#define SHIFT_STCP 15  // GPIO15: Latch (STCP)

// I2C pins for PCF8574 (input expander)
#define PCF8574_SDA 4  // GPIO4: I2C SDA
#define PCF8574_SCL 2  // GPIO2: I2C SCL

// Shift Register 1 (74HC595_1) - Spur 1 LEDs
#define LED1_RED_1   0  // Q0: Spur 1 Rot 1 (oben links)
#define LED1_RED_2   1  // Q1: Spur 1 Rot 2 (oben rechts)
#define LED1_YELLOW  2  // Q2: Spur 1 Gelb (Mitte oben)
#define LED1_GREEN_1 3  // Q3: Spur 1 Gruen 1 (unten links)
#define LED1_GREEN_2 4  // Q4: Spur 1 Gruen 2 (unten rechts)

// Shift Register 2 (74HC595_2) - Spur 2 LEDs (bits 8-15)
#define LED2_RED_1   8   // Q0: Spur 2 Rot 1 (oben links)
#define LED2_RED_2   9   // Q1: Spur 2 Rot 2 (oben rechts)
#define LED2_YELLOW  10  // Q2: Spur 2 Gelb (Mitte unten)
#define LED2_GREEN_1 11  // Q3: Spur 2 Gruen 1 (unten links)
#define LED2_GREEN_2 12  // Q4: Spur 2 Gruen 2 (unten rechts)

// PCF8574 Eingaenge (I2C Adresse 0x20)
#define PCF8574_BUTTON_START  0  // P0: Button Start
#define PCF8574_BUTTON_STOP   1  // P1: Button Stop
#define PCF8574_BUTTON_RESET  2  // P2: Button Reset
#define PCF8574_BUTTON_MODE   3  // P3: Button Mode
#define PCF8574_GPIO_START    4  // P4: Trigger Start extern
#define PCF8574_GPIO_FRUEH    5  // P5: Trigger Fruehstart extern
#define PCF8574_IR_SCHRANKE   6  // P6: IR-Schranke OUT
#define PCF8574_RESERVE       7  // P7: Reserve

#else
// Legacy support (D1 Mini / ESP8266) - not recommended for full feature set
#define SHIFT_DS     D8
#define SHIFT_SHCP   D7
#define SHIFT_STCP   D6
#define LED1_RED_1   0
#define LED1_RED_2   1
#define LED1_YELLOW  2
#define LED1_GREEN_1 3
#define LED1_GREEN_2 4
#endif

// Number of lanes
#define NUM_LANES 2

// Shift register: 16 bits total (2 x 74HC595)
#define SHIFT_REG_BITS 16
