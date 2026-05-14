# Wiring Diagram - Startampel mit ESP32-CAM

## Ziel
Vollstaendige Verdrahtung fuer den MVP mit ESP32-CAM als Recheneinheit, inklusive I/O-Erweiterung fuer alle benoetigten Signale.

## Warum I/O-Erweiterung notwendig ist
Der ESP32-CAM hat nur wenige frei nutzbare GPIOs. Fuer den MVP werden gleichzeitig benoetigt:
- 6 LED-Ausgaenge (2 Spuren x Rot/Gelb/Gruen)
- 4 Taster (Start, Stop, Reset, Mode)
- 2 externe Trigger (Start, Fruehstart)
- 1 IR-Sensor-Eingang

Das sind 13 Signale und damit mehr als direkt verfuegbare sichere Pins. Daher wird die Verdrahtung mit:
- 1x 74HC595 (8 Ausgaenge fuer LEDs)
- 1x PCF8574 (8 Eingaenge fuer Taster/Trigger/IR)
umgesetzt.

## Komponenten
- 1x ESP32-CAM (AI Thinker)
- 1x 74HC595 (LED-Ausgaenge)
- 1x PCF8574 oder PCF8574A (Eingaenge)
- 6x LED (Rot/Gelb/Gruen x 2 Spuren) + 4 Reserve
- 6x Vorwiderstand 220-470 Ohm (empfohlen 330 Ohm)
- 4x KY-004 Tastermodul
- 1x IR-Lichtschranke mit Digitalausgang
- 1x Elko 100 uF zwischen 5V und GND
- Optional: 2x 100 nF (je einer nahe 74HC595/PCF8574)

## Versorgungsplan
- ESP32-CAM an 5V (Pin 5V), nicht an 3V3 versorgen
- 74HC595 und PCF8574 auf 3V3 betreiben (logiksicher zum ESP32)
- Alle GND strikt gemeinsam verbinden (ESP32-CAM, 74HC595, PCF8574, Taster, IR)

## ESP32-CAM Pinzuordnung

### Direkt am ESP32-CAM
| Funktion | ESP32-CAM Pin |
|---|---|
| Schieberegister Daten | GPIO13 |
| Schieberegister Takt | GPIO14 |
| Schieberegister Latch | GPIO15 |
| I2C SCL (PCF8574) | GPIO2 |
| I2C SDA (PCF8574) | GPIO4 |

### Boot-Hinweise (wichtig)
- GPIO0 nur fuer Flash-Modus verwenden, nicht in der Applikationsverdrahtung belegen.
- GPIO15 ist Boot-Strapping-Pin: mit 10k Pulldown nach GND absichern.
- GPIO2 muss beim Boot HIGH bleiben; I2C-Pullup auf 3V3 ist daher korrekt.
- GPIO12 nicht fuer Signale mit externem Pullup verwenden.

## 74HC595 Verdrahtung (LED-Ausgaenge)

### 74HC595 zu ESP32-CAM
| 74HC595 Pin | Verbindung |
|---|---|
| DS (14) | GPIO13 |
| SHCP (11) | GPIO14 |
| STCP (12) | GPIO15 |
| OE (13) | GND |
| MR (10) | 3V3 |
| VCC (16) | 3V3 |
| GND (8) | GND |

### 74HC595 LED-Kanaele
| Ausgang | Funktion |
|---|---|
| Q0 | LED Spur1 Rot |
| Q1 | LED Spur1 Gelb |
| Q2 | LED Spur1 Gruen |
| Q3 | LED Spur2 Rot |
| Q4 | LED Spur2 Gelb |
| Q5 | LED Spur2 Gruen |
| Q6 | Reserve LED 1 |
| Q7 | Reserve LED 2 |

LED-Verdrahtung je Kanal:
74HC595 Qx -> Vorwiderstand 330 Ohm -> LED Anode, LED Kathode -> GND

## PCF8574 Verdrahtung (Eingaenge)

### PCF8574 zu ESP32-CAM
| PCF8574 Pin | Verbindung |
|---|---|
| VCC | 3V3 |
| GND | GND |
| SDA | GPIO4 |
| SCL | GPIO2 |
| A0/A1/A2 | GND (I2C Adresse 0x20) |

### PCF8574 Eingangskanaele
| Port | Funktion |
|---|---|
| P0 | Button START |
| P1 | Button STOP |
| P2 | Button RESET |
| P3 | Button MODE |
| P4 | Trigger START extern |
| P5 | Trigger FRUEHSTART extern |
| P6 | IR Sensor OUT |
| P7 | Reserve Eingang |

Eingangslogik:
- PCF8574 Ports als Input mit High-Grundpegel betreiben
- Signal aktiv gegen GND schalten (active-low)
- Debounce weiterhin in Firmware (30 ms)

## KY-004 Tastermodule
- KY-004 VCC -> 3V3
- KY-004 GND -> GND
- KY-004 Signal -> PCF8574 P0..P3

## IR-Lichtschranke
- IR VCC -> 3V3 (oder 5V nur wenn Ausgang 3V3-kompatibel)
- IR GND -> GND
- IR OUT -> PCF8574 P6

## ASCII-Schaltbild (komplett, logisch)

```text
5V Netzteil/USB
    |
    +--> ESP32-CAM 5V
    +--> [100uF] --> GND

ESP32-CAM (3V3)
    |
    +--> 74HC595 VCC
    +--> PCF8574 VCC

ESP32-CAM GPIO13 ---> 74HC595 DS
ESP32-CAM GPIO14 ---> 74HC595 SHCP
ESP32-CAM GPIO15 ---> 74HC595 STCP

ESP32-CAM GPIO4  <--> PCF8574 SDA
ESP32-CAM GPIO2  ---> PCF8574 SCL

74HC595 Q0 ---> [330R] ---> LED_L1_R ---> GND
74HC595 Q1 ---> [330R] ---> LED_L1_Y ---> GND
74HC595 Q2 ---> [330R] ---> LED_L1_G ---> GND
74HC595 Q3 ---> [330R] ---> LED_L2_R ---> GND
74HC595 Q4 ---> [330R] ---> LED_L2_Y ---> GND
74HC595 Q5 ---> [330R] ---> LED_L2_G ---> GND

PCF8574 P0 <--- Button START --- GND
PCF8574 P1 <--- Button STOP ---- GND
PCF8574 P2 <--- Button RESET --- GND
PCF8574 P3 <--- Button MODE ---- GND
PCF8574 P4 <--- Trigger START -- GND
PCF8574 P5 <--- Trigger FALSE -- GND
PCF8574 P6 <--- IR OUT
IR VCC --------> 3V3
IR GND --------> GND
```

## Inbetriebnahme-Reihenfolge
1. Nur Versorgung und GND aufbauen, Spannungen messen.
2. I2C (PCF8574) anschliessen und Eingangsbits pruefen.
3. 74HC595 anschliessen, LED-Kanaele einzeln durchtesten.
4. Taster und Trigger anbinden, Debounce verifizieren.
5. IR-Sensor zuletzt anschliessen und Schwellwert/Signal pruefen.

## Fehlerbehebung

### Keine stabile Funktion nach Power-On
- Boot-Strapping Pins pruefen (GPIO0/GPIO2/GPIO15)
- Sicherstellen, dass GPIO15 nicht versehentlich auf HIGH gezogen wird

### LEDs reagieren nicht korrekt
- 74HC595 OE muss fest auf GND liegen
- 74HC595 MR muss auf 3V3 liegen
- DS/SHCP/STCP Signalreihenfolge in Firmware pruefen

### Buttons/IR reagieren invertiert oder verrauscht
- Active-low Logik in Firmware kontrollieren
- GND-Fuehrung und Leitungslaengen minimieren
- Debounce/Filter in Input-Handler aktiv lassen

---

Stand: 2026-05-14
