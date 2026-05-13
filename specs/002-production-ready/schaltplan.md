# Schaltplan: Production Setup und Erweiterungen (Feature 002)

## Zielbild
Produktionsnahe Verdrahtung mit Schutzmassnahmen, stabiler Versorgung und Erweiterbarkeit fuer Web/OTA-Betrieb.

## Basisschaltung (MVP-kompatibel)
- Gleich wie `specs/001-startampel-carrera/schaltplan.md`
- Ergaenzungen fuer Produktionsbetrieb siehe unten

## Produktions-Ergaenzungen
- 5V Versorgung >= 1A mit sauberer Massefuehrung
- 100 uF Bulk + 100 nF nahe MCU
- Optional TVS-Diode an externer Versorgung
- Schirmung oder Twisted Pair fuer lange IR-Leitungen
- Pull-up/Pull-down Netzwerke gemaess Sensormodul

## Empfohlener Aufbau
- Sternfoermige GND-Verteilung
- LED-Leitungen kurz halten
- Externe Trigger ueber Steckklemmen fuehren
- Trennung von Signal- und Versorgungspfaden auf Lochraster/PCB

## Erweiterte I/O-Zuordnung (ESP32 empfohlen)
| Gruppe | Signal | Pin |
|---|---|---|
| Lane 1 | R/Y/G | 16/17/18 |
| Lane 2 | R/Y/G | 19/21/22 |
| Buttons | Start/Stop/Reset/Mode | 23/25/26/27 |
| Trigger | Start extern / IR | 32/33 |
| Service | UART Debug | TX0/RX0 |

## OTA/Web-relevante Hardwarehinweise
- WLAN-Antenne frei positionieren (nicht neben 5V-Regler)
- Versorgungsspannung unter Last pruefen (keine Brownouts)
- Optional Status-LED fuer OTA-Zustand

## ASCII-Topologie

```text
[5V PSU 1A]---+--- MCU (ESP32/D1)
              +--- Sensor Rail (IR, Trigger)
              +--- LED Rail (via resistors)

MCU <---- Buttons (pullup, active low)
MCU <---- IR Sensor (digital)
MCU ----> LEDs (R/Y/G je Spur)
MCU <....> WLAN (Web/OTA optional)
```

## Produktions-Checkliste
- 24h Burn-in ohne Reset
- Brownout-Test bei Lastwechsel
- OTA-Test mit Rollback-Szenario
- WLAN-Reconnect nach AP-Neustart
- Trigger-Entprellung mit Kabeln >1m
