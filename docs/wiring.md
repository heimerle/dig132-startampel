# Wiring Diagram - Startampel mit ESP32-CAM

## Ziel
Vollstaendige Verdrahtung fuer den MVP mit ESP32-CAM als Recheneinheit, inklusive I/O-Erweiterung fuer alle benoetigten Signale.

## Warum I/O-Erweiterung notwendig ist
Der ESP32-CAM hat nur wenige frei nutzbare GPIOs. Fuer den MVP werden gleichzeitig benoetigt:
- 10 LED-Ausgaenge (2 Spuren: je 2 Rot + 1 Gelb + 2 Gruen + 2 Reserven)
- 4 Taster (Start, Stop, Reset, Mode)
- 2 externe Trigger (Start, Fruehstart)
- 1 IR-Sensor-Eingang

Das erfordert 17 Signale, daher wird die Verdrahtung mit:
- 2x 74HC595 (16 Ausgaenge fuer LEDs in Serie geschaltet)
- 1x PCF8574 (8 Eingaenge fuer Taster/Trigger/IR)
umgesetzt.

## Komponenten
- 1x ESP32-CAM (AI Thinker)
- 2x 74HC595 (LED-Ausgaenge, in Serie geschaltet)
- 1x PCF8574 oder PCF8574A (Eingaenge)
- 10x LED (4x rot + 2x gelb + 4x gruen)
- 10x Vorwiderstand 330 Ohm (pro LED)
- 4x KY-004 Tastermodul
- 1x IR-Lichtschranke mit Digitalausgang
- 1x Elko 100 uF zwischen 5V und GND
- Optional: 3x 100 nF (je einer nahe 74HC595_1/74HC595_2/PCF8574)

## Versorgungsplan

### ⚠️ Kritisch: Richtige Stromversorgung am ESP32-CAM

Der ESP32-CAM hat **zwei verschiedene Spannungen**. Falscher Anschluss zerstört das Board sofort!

| Pin | Spannung | Verbindung | ⚠️ Warnung |
|---|---|---|---|
| **5V** | 5V Input | USB/Netzteil 5V | ✓ **Richtig** |
| **GND** | 0V Masse | USB/Netzteil GND | ✓ **Richtig** |
| **VCC/3V3** | 3.3V Output | 74HC595, PCF8574 | ✓ **Nur für externe ICs** |
| ❌ VCC als Input | - | **NICHT** 5V anschließen | 🔥 Zerstört ESP32-CAM |

**Verdrahtung Stromversorgung:**
1. USB 5V oder Netzteil 5V → ESP32-CAM **5V Pin**
2. USB GND oder Netzteil GND → ESP32-CAM **GND Pin** (gemeinsam mit allem)
3. ESP32-CAM **3V3 Pin** → 74HC595_1 VCC
4. ESP32-CAM **3V3 Pin** → 74HC595_2 VCC
5. ESP32-CAM **3V3 Pin** → PCF8574 VCC
6. Alle GND strikt gemeinsam: ESP32-CAM GND, 74HC595 GND, PCF8574 GND, LEDs, Taster

## ESP32-CAM Pinzuordnung

### Direkt am ESP32-CAM (für beide 74HC595 in Serie)
| Funktion | ESP32-CAM Pin |
|---|---|
| Schieberegister Daten (DS) | GPIO13 |
| Schieberegister Takt (SHCP) | GPIO14 |
| Schieberegister Latch (STCP) | GPIO15 |
| I2C SCL (PCF8574) | GPIO2 |
| I2C SDA (PCF8574) | GPIO4 |

### Boot-Hinweise (wichtig)
- GPIO0 nur fuer Flash-Modus verwenden, nicht in der Applikationsverdrahtung belegen.
- GPIO15 ist Boot-Strapping-Pin: mit 10k Pulldown nach GND absichern.
- GPIO2 muss beim Boot HIGH bleiben; I2C-Pullup auf 3V3 ist daher korrekt.
- GPIO12 nicht fuer Signale mit externem Pullup verwenden.

## 74HC595 Verdrahtung (LED-Ausgaenge, zwei ICs in Serie)

### 74HC595_1 (erster IC, Spur 1) zu ESP32-CAM
| 74HC595_1 Pin | Verbindung |
|---|---|
| DS (14) | GPIO13 |
| SHCP (11) | GPIO14 |
| STCP (12) | GPIO15 |
| QH' (9) | 74HC595_2 DS (14) |
| OE (13) | GND |
| MR (10) | 3V3 |
| VCC (16) | 3V3 |
| GND (8) | GND |

### 74HC595_2 (zweiter IC, Spur 2) zu 74HC595_1
| 74HC595_2 Pin | Verbindung |
|---|---|
| DS (14) | 74HC595_1 QH' (9) |
| SHCP (11) | GPIO14 |
| STCP (12) | GPIO15 |
| OE (13) | GND |
| MR (10) | 3V3 |
| VCC (16) | 3V3 |
| GND (8) | GND |

### 74HC595 LED-Kanaele (Bit-Reihenfolge, MSB → LSB)

**74HC595_1 Ausgaenge (Q0-Q7 fuer Spur 1)**
| Ausgang | Funktion |
|---|---|
| Q0 | LED Spur1 Rot 1 (oben links) |
| Q1 | LED Spur1 Rot 2 (oben rechts) |
| Q2 | LED Spur1 Gelb (Mitte oben) |
| Q3 | LED Spur1 Gruen 1 (unten links) |
| Q4 | LED Spur1 Gruen 2 (unten rechts) |
| Q5 | Reserve 1 |
| Q6 | Reserve 2 |
| Q7 | Reserve 3 |

**74HC595_2 Ausgaenge (Q0-Q7 fuer Spur 2)**
| Ausgang | Funktion |
|---|---|
| Q0 | LED Spur2 Rot 1 (oben links) |
| Q1 | LED Spur2 Rot 2 (oben rechts) |
| Q2 | LED Spur2 Gelb (Mitte unten) |
| Q3 | LED Spur2 Gruen 1 (unten links) |
| Q4 | LED Spur2 Gruen 2 (unten rechts) |
| Q5 | Reserve 4 |
| Q6 | Reserve 5 |
| Q7 | Reserve 6 |

LED-Verdrahtung je Kanal (alle 10 LEDs gleich):
74HC595_n Qx -> Vorwiderstand 330 Ohm -> LED Anode, LED Kathode -> GND

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
