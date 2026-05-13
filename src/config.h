#pragma once

// Board-specific pin mapping
#if defined(ARDUINO_ARCH_ESP32)
#define LED1_RED     16
#define LED1_YELLOW  17
#define LED1_GREEN   18
#define LED2_RED     19
#define LED2_YELLOW  21
#define LED2_GREEN   22
#define BUTTON_START 23
#define BUTTON_STOP  25
#define BUTTON_RESET 26
#define BUTTON_MODE  27
#define GPIO_START   32
#define GPIO_FRUEH   33
#define IR_SCHRANKE  33
#else
// D1 Mini (ESP8266)
#define LED1_RED     D1
#define LED1_YELLOW  D2
#define LED1_GREEN   D3
#define LED2_RED     D4
#define LED2_YELLOW  D5
#define LED2_GREEN   D6
#define BUTTON_START D7
#define BUTTON_STOP  D8
#define BUTTON_RESET RX
#define BUTTON_MODE  TX
#define GPIO_START   A0
#define GPIO_FRUEH   D0
#define IR_SCHRANKE  D0
#endif

// Number of lanes
#define NUM_LANES 2
