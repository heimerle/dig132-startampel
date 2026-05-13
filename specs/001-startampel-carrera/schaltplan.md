# Schaltplan: Startampel MVP (Feature 001)

## Zielbild
Elektrische Verdrahtung fuer 2 Spuren (erweiterbar auf 4), ausgelegt fuer D1 Mini (ESP8266) und alternativ ESP32.

## Komponentenliste
- 1x D1 Mini (ESP8266) oder ESP32 Dev Board
- 6x LED (2x rot, 2x gelb, 2x gruen)
- 6x Vorwiderstand 220-470 Ohm
- 4x Taster (Start, Stop, Reset, Mode)
- 1x IR-Lichtschranke (Digitalausgang)
- Breadboard + Jumperkabel
- Optional: 100 uF Elko zwischen 5V und GND

## Verfuegbarer Bestand (13.05.2026)
- 2x ESP32-CAM
- 5x KY-004 Taster Modul
- 1x LED-Sortiment (AZDelivery, 350 Stueck)

Abgeleitete Nutzung:
- Controller: ESP32-CAM als primaerer Controller, zweiter ESP32-CAM als Backup
- Buttons: 4x KY-004 im Betrieb, 1x Reserve
- LEDs: Auswahl aus vorhandenem Sortiment (rot/gelb/gruen)

## Schaltregeln
- Jede LED in Serie mit eigenem Vorwiderstand
- Gemeinsame Masse (Common GND) fuer alle Komponenten
- Buttons als `INPUT_PULLUP` gegen GND
- Externe Trigger galvanisch sauber an GND-Referenz binden

## D1 Mini Pinbelegung (Normativ)
| Funktion | Pin |
|---|---|
| LED Spur1 Rot | D1 |
| LED Spur1 Gelb | D2 |
| LED Spur1 Gruen | D3 |
| LED Spur2 Rot | D4 |
| LED Spur2 Gelb | D5 |
| LED Spur2 Gruen | D6 |
| Button Start | D7 |
| Button Stop | D8 |
| Button Reset | RX |
| Button Mode | TX |
| Trigger Start extern | A0 |
| Trigger Fruehstart extern | D0 |
| IR-Schranke | D0 (geteilt) oder separater GPIO |

Hinweis: Fuer stabile Fruehstart-Erkennung wird ein dedizierter IR-Pin empfohlen. Beim D1 Mini ist die GPIO-Anzahl begrenzt.

## ESP32 Pinbelegung (Empfohlen)
| Funktion | Pin |
|---|---|
| LED Spur1 Rot | 16 |
| LED Spur1 Gelb | 17 |
| LED Spur1 Gruen | 18 |
| LED Spur2 Rot | 19 |
| LED Spur2 Gelb | 21 |
| LED Spur2 Gruen | 22 |
| Button Start | 23 |
| Button Stop | 25 |
| Button Reset | 26 |
| Button Mode | 27 |
| Trigger Start extern | 32 |
| IR-Schranke | 33 |

## ASCII-Schaltplan (logisch)

```text
5V ----+-------------------------- MCU VCC
       |
       +--[100uF]-- GND

D1 ----[220R]----|>|---- GND   (LED L1 Rot)
D2 ----[220R]----|>|---- GND   (LED L1 Gelb)
D3 ----[220R]----|>|---- GND   (LED L1 Gruen)
D4 ----[220R]----|>|---- GND   (LED L2 Rot)
D5 ----[220R]----|>|---- GND   (LED L2 Gelb)
D6 ----[220R]----|>|---- GND   (LED L2 Gruen)

D7 ----[Button START]---- GND
D8 ----[Button STOP ]---- GND
RX ----[Button RESET]---- GND
TX ----[Button MODE ]---- GND

A0 ----[Extern START ]--- GND
D0 ----[Extern FALSE ]--- GND
D0 ----[IR SENSOR OUT]--- (Digital)
IR VCC ------------------- 5V
IR GND ------------------- GND
```

## Validierungscheckliste
- LED-Test: jede LED einzeln ansteuerbar
- Taster-Test: stabile Flankenerkennung ohne Doppeltrigger
- IR-Test: Trigger nur bei Strahlunterbrechung
- Belastungstest: 30 Minuten Blinkbetrieb ohne Aussetzer
