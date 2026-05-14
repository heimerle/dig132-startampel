# Schaltplan: Startampel MVP (Feature 001)

## Zielbild
Elektrische Verdrahtung fuer 2 Spuren (erweiterbar), mit ESP32-CAM als Computing Unit.

## Komponentenliste
- 1x ESP32-CAM (AI Thinker)
- 1x 74HC595 (8 digitale Ausgaenge fuer LED-Kanaele)
- 1x PCF8574/PCF8574A (8 digitale Eingaenge fuer Taster/Trigger/IR)
- 10 LED-Plaetze gesamt (6 aktiv + 4 Reserve), Farben Rot/Gelb/Gruen
- 6x Vorwiderstand 220-470 Ohm (empfohlen 330 Ohm)
- 4x Taster (Start, Stop, Reset, Mode)
- 1x IR-Lichtschranke (Digitalausgang)
- Breadboard + Jumperkabel
- Optional: 100 uF Elko zwischen 5V und GND
- Optional: 2x 100 nF (je 1x fuer 74HC595 und PCF8574 nah am IC)

## Verfuegbarer Bestand (13.05.2026)
- 2x ESP32-CAM
- 5x KY-004 Taster Modul
- 1x LED-Sortiment (AZDelivery, 350 Stueck)

Abgeleitete Nutzung:
- Controller: ESP32-CAM als primaerer Controller, zweiter ESP32-CAM als Backup
- Buttons: 4x KY-004 im Betrieb, 1x Reserve
- LEDs: Auswahl aus vorhandenem Sortiment (rot/gelb/gruen), RGB-LEDs optional als Ersatz

## LED-Belegung (10 Plaetze)
- Aktiv im MVP: 6 Plaetze (2x Rot, 2x Gelb, 2x Gruen)
- Reserve/Erweiterung: 4 Plaetze (z. B. Status, Spur-Upgrade, Debug)
- RGB-Einsatz: pro LED-Platz nur ein Kanal nutzen und pro Kanal Vorwiderstand vorsehen

## Schaltregeln
- Jede LED in Serie mit eigenem Vorwiderstand
- Gemeinsame Masse (Common GND) fuer alle Komponenten
- Eingaenge active-low gegen GND schalten
- Externe Trigger galvanisch sauber an GND-Referenz binden
- 74HC595 und PCF8574 auf 3V3 betreiben

## ESP32-CAM Pinbelegung (Normativ)

### ESP32-CAM zu 74HC595
| Funktion | ESP32-CAM Pin |
|---|---|
| DS (Daten) | GPIO13 |
| SHCP (Takt) | GPIO14 |
| STCP (Latch) | GPIO15 |

### ESP32-CAM zu PCF8574
| Funktion | ESP32-CAM Pin |
|---|---|
| I2C SDA | GPIO4 |
| I2C SCL | GPIO2 |

### Boot-Strapping Hinweise
- GPIO0 unbenutzt lassen (nur fuer Flash-Modus)
- GPIO15 mit 10k Pulldown stabilisieren
- GPIO2 darf beim Boot nicht auf LOW gezogen werden
- GPIO12 nicht fuer Leitungen mit Pullup nutzen

## Funktionszuordnung ueber I/O-Erweiterung

### 74HC595 Ausgaenge
| Ausgang | Funktion |
|---|---|
| Q0 | LED Spur1 Rot |
| Q1 | LED Spur1 Gelb |
| Q2 | LED Spur1 Gruen |
| Q3 | LED Spur2 Rot |
| Q4 | LED Spur2 Gelb |
| Q5 | LED Spur2 Gruen |
| Q6 | Reserve |
| Q7 | Reserve |

### PCF8574 Eingaenge
| Port | Funktion |
|---|---|
| P0 | Button Start |
| P1 | Button Stop |
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
