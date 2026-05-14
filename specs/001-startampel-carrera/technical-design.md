# Technical Design: Startampel fuer Carrera-Bahn (Feature 001)

## Ziel
Dieses Dokument beschreibt das technische Design fuer alle MVP-Features aus `spec.md`:
- Startsequenz und Startfreigabe
- Fruehstart-Erkennung
- Safety-Car-Modus
- Chaos-Modus
- Rennende/Siegeranzeige

## Systemarchitektur

### Komponenten
- `InputHandler`: Entprellung, Event-Erzeugung fuer Taster/GPIO/IR
- `StateMachine`: Zustaende und Uebergaenge
- `AmpelController`: Effektlogik fuer LEDs pro Zustand
- `LedController`: Hardware-nahe LED-Ausgabe, Blinkgenerator
- `config.h`: Pin- und Timing-Konfiguration

### Laufzeitmodell
- Main Loop Zyklus: 5-10 ms
- Event-Prioritaet:
  1. Reset (absolut)
  2. Fehler-/Safety-Ereignisse
  3. Moduswechsel
  4. Start/Stop
- Gleichzeitige Eingaben: Last-Input-Wins innerhalb eines 30 ms Debounce-Fensters

## Zustandsmodell

### Zustaende
- `IDLE`
- `START_SEQUENCE`
- `GREEN_RELEASE`
- `FALSE_START`
- `SAFETY_CAR`
- `CHAOS`
- `RACE_END`

### Uebergaenge
- `IDLE -> START_SEQUENCE` via Start-Event
- `START_SEQUENCE -> GREEN_RELEASE` nach 5 Countdown-Schritten
- `START_SEQUENCE -> FALSE_START` bei IR-Trigger
- `* -> IDLE` bei Reset
- `GREEN_RELEASE -> SAFETY_CAR/CHAOS/RACE_END` via externe Trigger
- `SAFETY_CAR/CHAOS -> GREEN_RELEASE` via Resume-Trigger

## Timing-Design
- Debounce: 30 ms fuer alle digitalen Eingaben
- Startsequenz: 5 Schritte, je 500 ms
- Blinkmodi (FALSE_START, SAFETY_CAR, CHAOS, RACE_END): 250 ms ON / 250 ms OFF
- Max. Eingabelatenz: < 50 ms

## Feature-spezifisches Design

### 1) Startsequenz und Startfreigabe
- Countdown-Schritte als nicht-blockierende Zeitmaschine auf `millis()`
- Nach Schritt 5 werden alle gruene Spur-LEDs auf STEADY gesetzt

### 2) Fruehstart
- Triggerquellen: IR-Schranke oder externer GPIO
- Verhalten:
  - Alle gelben LEDs: STEADY ON
  - Betroffene rote Spur-LED: blinkend (250 ms)
- Rueckkehr nur durch Reset oder expliziten Resume

### 3) Safety-Car
- Alle gelben LEDs synchron blinken
- Zustand priorisiert vor normalen Rennsignalen

### 4) Chaos
- Alle roten LEDs synchron blinken
- Sicherheitszustand, deaktiviert Startsequenz

### 5) Rennende/Sieger
- Alle gruene LEDs blinken
- Rote LED der Siegerbahn bleibt STEADY ON

## Fehler- und Randfallbehandlung
- Reset jederzeit: sofortiger Abbruch aller Sequenzen, alle LEDs aus, Zustand `IDLE`
- Stromausfall: Kaltstart in `IDLE` ohne Restzustand
- Gleichzeitige Trigger: Priorisierung + Last-Input-Wins
- Ungueltige Spur-ID: Event verwerfen, Fehlerzaehler inkrementieren

## Pin- und Hardware-Design (logisch)
Fuer ESP32-CAM wird eine I/O-Erweiterung eingesetzt, da die direkt verfuegbaren GPIOs fuer alle MVP-Signale nicht ausreichen.

### ESP32-CAM direkt genutzte Pins
- GPIO13: 74HC595 DS (LED-Daten)
- GPIO14: 74HC595 SHCP (LED-Takt)
- GPIO15: 74HC595 STCP (LED-Latch)
- GPIO4: I2C SDA zu PCF8574
- GPIO2: I2C SCL zu PCF8574

### I/O-Erweiterung
- 74HC595: 6 LED-Kanaele + 2 Reservekanaele
- PCF8574: 4 Buttons + 2 externe Trigger + 1 IR-Eingang + 1 Reserve

### Boot-Strapping Randbedingungen
- GPIO0 bleibt unbenutzt (nur Flash-Modus)
- GPIO15 mit Pulldown stabilisieren
- GPIO2 darf waehrend Boot nicht auf LOW gezogen werden
- GPIO12 nicht fuer Pullup-belastete Signale nutzen

## Testdesign
- Unit-Tests pro Modul (`InputHandler`, `LedController`, `StateMachine`, `AmpelController`)
- Integrations-Tests fuer End-to-End-Sequenzen
- Edge-Tests:
  - Reset waehrend Blinkmodus
  - Fruehstart waehrend Countdown
  - Gleichzeitige Eingaben im selben Takt

## Akzeptanz-Metriken
- Event-Latenz: < 50 ms
- Blinkjitter: <= +/-10 ms
- Keine undefinierten Zustaende in 10.000 Simulationszyklen
