# Schaltplan: Startampel MVP (Feature 001)

## Zielbild
Elektrische Verdrahtung fuer 2 Spuren (erweiterbar), mit ESP32-CAM als Computing Unit.

## Komponentenliste
- 1x ESP32-CAM (AI Thinker)
- 2x 74HC595 (LED-Ausgaenge, in Serie geschaltet)
- 1x PCF8574/PCF8574A (Eingaenge)
- 10x LED (4x rot + 2x gelb + 4x gruen)
- 10x Vorwiderstand 330 Ohm (empfohlen)
- 4x KY-004 Taster Modul
- 1x IR-Lichtschranke (Digitalausgang)
- Breadboard + Jumperkabel
- Optional: 100 uF Elko zwischen 5V und GND
- Optional: 3x 100 nF (je 1x fuer 74HC595_1, 74HC595_2 und PCF8574 nah am IC)

## Verfuegbarer Bestand (13.05.2026)
- 2x ESP32-CAM
- 5x KY-004 Taster Modul
- 1x LED-Sortiment (AZDelivery, 350 Stueck)

Abgeleitete Nutzung:
- Controller: ESP32-CAM als primaerer Controller, zweiter ESP32-CAM als Backup
- Buttons: 4x KY-004 im Betrieb, 1x Reserve
- LEDs: Auswahl aus vorhandenem Sortiment (rot/gelb/gruen), RGB-LEDs optional als Ersatz

## LED-Belegung (10 Plaetze, exakte physische Montage)

**Spur 1 (links, via 74HC595_1):**
- 2x Rot oben (Q0, Q1)
- 1x Gelb Mitte oben (Q2)
- 2x Gruen unten (Q3, Q4)

**Spur 2 (rechts, via 74HC595_2):**
- 2x Rot oben (Q0, Q1)
- 1x Gelb Mitte unten (Q2)
- 2x Gruen unten (Q3, Q4)

**Reservekanaele:** 74HC595_1 Q5-Q fuer Dual 74HC595)

### ESP32-CAM zu 74HC595 (gemeinsam fuer beide ICs)
| Funktion | ESP32-CAM Pin |
|---|---|
| DS (Daten) | GPIO13 |
| SHCP (Takt) | GPIO14 |
| STCP (Latch) | GPIO15 |

### 74HC595 Verkettung
| Pin | Verbindung |
|---|---|
| 74HC595_1 QH' (9) | 74HC595_2 DS (14) |
| 74HC595_1/74HC595_2 SHCP | GPIO14 (gemeinsam) |
| 74HC595_1/74HC595_2 STCP | GPIO15 (gemeinsam)uf 3V3 betreiben

## ESP32-CAM Pinbelegung (Normativ)

### ESP32-CAM zu 74HC595
| Funktion | ESP32-CAM Pin |
|---|---|
| DS (Daten) | GPIO13 |
| SHCP (Takt) | GPIO14 |
| STCP (Lat_1 Ausgaenge (Spur 1)
| Ausgang | Funktion | Position |
|---|---|---|
| Q0 | LED Spur1 Rot 1 | oben links |
| Q1 | LED Spur1 Rot 2 | oben rechts |
| Q2 | LED Spur1 Gelb | Mitte oben |
| Q3 | LED Spur1 Gruen 1 | unten links |
| Q4 | LED Spur1 Gruen 2 | unten rechts |
| Q5-Q7 | Reserve | - |

### 74HC595_2 Ausgaenge (Spur 2)
| Ausgang | Funktion | Position |
|---|---|---|
| Q0 | LED Spur2 Rot 1 | oben links |
| Q1 | LED Spur2 Rot 2 | oben rechts |
| Q2 | LED Spur2 Gelb | Mitte unten |
| Q3 | LED Spur2 Gruen 1 | unten links |
| Q4 | LED Spur2 Gruen 2 | unten rechts |
| Q5-Q7 | Reserve | -0k Pulldown stabilisieren
- GPIO2 darf beim Boot nicht auf LOW gezogen werden
- GPIO12 nicht fuer Leitungen mit Pullup nutzen

## Funktionszuordnung ueber I/O-Erweiterung

### 74HC595 Ausgaenge, Dual 74HC595)

```text
5V ----+-------------------------- ESP32-CAM 5V
       |
       +--[100uF]-- GND

GPIO13 ---> 74HC595_1 DS
GPIO14 ---> 74HC595_1/74HC595_2 SHCP (gemeinsam)
GPIO15 ---> 74HC595_1/74HC595_2 STCP (gemeinsam)

74HC595_1 QH' ---> 74HC595_2 DS (Verkettung)

74HC595_1 Q0 ---[330R]---|>|--- GND   (LED L1 Rot 1)
74HC595_1 Q1 ---[330R]---|>|--- GND   (LED L1 Rot 2)
74HC595_1 Q2 ---[330R]---|>|--- GND   (LED L1 Gelb - Mitte oben)
74HC595_1 Q3 ---[330R]---|>|--- GND   (LED L1 Gruen 1)
74HC595_1 Q4 ---[330R]---|>|--- GND   (LED L1 Gruen 2)

74HC595_2 Q0 ---[330R]---|>|--- GND   (LED L2 Rot 1)
74HC595_2 Q1 ---[330R]---|>|--- GND   (LED L2 Rot 2)
74HC595_2 Q2 ---[330R]---|>|--- GND   (LED L2 Gelb - Mitte unten)
74HC595_2 Q3 ---[330R]---|>|--- GND   (LED L2 Gruen 1)
74HC595_2 Q4 ---[330R]---|>|--- GND   (LED L2 Gruen 2
| P2 | Button Reset |
| P3 | Button Mode |
| P4 | Trigger Start extern |
| P5 | Trigger Fruehstart extern |
| P6 | IR-Schranke OUT |
| P7 | Reserve |

## ASCII-Schaltplan (logisch)

```text
5V ----+-------------------------- ESP32-CAM 5V
       |
       +--[100uF]-- GND

GPIO13 ---> 74HC595 DS
GPIO14 ---> 74HC595 SHCP
GPIO15 ---> 74HC595 STCP

74HC595 Q0 ---[330R]---|>|--- GND   (LED L1 Rot)
74HC595 Q1 ---[330R]---|>|--- GND   (LED L1 Gelb)
74HC595 Q2 ---[330R]---|>|--- GND   (LED L1 Gruen)
74HC595 Q3 ---[330R]---|>|--- GND   (LED L2 Rot)
74HC595 Q4 ---[330R]---|>|--- GND   (LED L2 Gelb)
74HC595 Q5 ---[330R]---|>|--- GND   (LED L2 Gruen)

GPIO4  <--> PCF8574 SDA
GPIO2  ---> PCF8574 SCL

PCF8574 P0 ----[Button START]---- GND
PCF8574 P1 ----[Button STOP ]---- GND
PCF8574 P2 ----[Button RESET]---- GND
PCF8574 P3 ----[Button MODE ]---- GND

PCF8574 P4 ----[Extern START ]--- GND
PCF8574 P5 ----[Extern FALSE ]--- GND
PCF8574 P6 ----[IR SENSOR OUT]--- (Digital)
IR VCC ------------------- 3V3
IR GND ------------------- GND
```

## Validierungscheckliste
- Boot-Test: 10x Power-Cycle ohne Boot-Fehler
- LED-Test: jede LED einzeln ansteuerbar
- Taster-Test: stabile Flankenerkennung ohne Doppeltrigger
- IR-Test: Trigger nur bei Strahlunterbrechung
- Belastungstest: 30 Minuten Blinkbetrieb ohne Aussetzer
