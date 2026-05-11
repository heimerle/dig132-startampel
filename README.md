# Startampel für Carrera-Bahn

Eine Arduino-basierte Steuerung für eine Carrera-Bahn-Startampel mit individuellen LEDs pro Spur (rot, gelb, grün).

## Merkmale

- **Startsequenz**: 5 rote LEDs als Countdown
- **Startfreigabe**: Grüne LEDs zum Los-Signal
- **Frühstart-Erkennung**: IR-Lichtschranke vor der Pole Position
- **Safety-Car Modus**: Gelbe LEDs blinken synchron
- **Chaos/Rennunterbrechung**: Rote LEDs blinken
- **Rennende**: Grüne LEDs blinken, Sieger-rote LED bleibt an

## Hardware

### Microcontroller
- D1 Mini (ESP8266) oder ESP32

### Komponenten pro Spur (2 Spuren Standard)
- 1x Rote LED (220-470Ω Vorwiderstand)
- 1x Gelbe LED (220-470Ω Vorwiderstand)
- 1x Grüne LED (220-470Ω Vorwiderstand)

### Eingänge
- Taster für Start, Stop, Reset, Modus
- Externe GPIO-Trigger für Steuerung
- IR-Lichtschranke (GPIO-Eingang)

### Stromversorgung
- 5V USB oder Netzteil

## Pinbelegung (D1 Mini)

| Funktion         | Pin D1 Mini | Anmerkungen          |
|------------------|------------|----------------------|
| LED1 Rot         | D1         | Spur 1 - Rot         |
| LED1 Gelb        | D2         | Spur 1 - Gelb        |
| LED1 Grün        | D3         | Spur 1 - Grün        |
| LED2 Rot         | D4         | Spur 2 - Rot         |
| LED2 Gelb        | D5         | Spur 2 - Gelb        |
| LED2 Grün        | D6         | Spur 2 - Grün        |
| Taster Start     | D7         | Global               |
| Taster Stop      | D8         | Global               |
| Taster Reset     | RX         | Global               |
| Taster Modus     | TX         | Optional/Global      |
| GPIO Start       | A0         | Extern               |
| GPIO Frühstart   | D0         | Extern               |
| IR-Schranke      | D8         | Frühstart-Erkennung  |

## Bedienung

1. **Starten**: Taster "Start" drücken → Startsequenz beginnt
2. **Während Sequenz**: Taster "Reset" drücken → Sequenz abgebrochen, alle LEDs aus
3. **Nach Startfreigabe**: Rennen läuft
4. **Frühstart**: IR-Schranke unterbrochen → Frühstart-Anzeige (gelbe LEDs, rote LED blinkt)
5. **Safety-Car**: GPIO Trigger → Gelbe LEDs blinken
6. **Rennende**: GPIO Trigger → Grüne LEDs blinken, Sieger-rote LED an

## Installation & Kompilierung

### Voraussetzungen
- PlatformIO installiert
- Arduino Framework für D1 Mini oder ESP32

### Build
```bash
cd /path/to/dig132-startampel
platformio run -e d1_mini
```

### Upload
```bash
platformio run -e d1_mini -t upload
```

### Monitor
```bash
platformio device monitor -e d1_mini
```

## Projektstruktur

```
dig132-startampel/
├── src/
│   ├── main.cpp              # Haupteinstieg
│   ├── config.h              # Pin-Definitionen
│   ├── input_handler.h/.cpp  # Eingabe-Entprellung
│   ├── led_controller.h/.cpp # LED-Kontrolle
│   ├── state_machine.h/.cpp  # Zustandsautomat
│   ├── ampel_controller.h/.cpp # Sequenz-Logik
│   └── ...
├── tests/
│   ├── test_input_handler.cpp
│   ├── test_led_controller.cpp
│   ├── test_state_machine.cpp
│   ├── test_startsequenz.cpp
│   └── ...
├── docs/
│   └── wiring.md
├── platformio.ini            # Build-Konfiguration
└── README.md                 # Dieses Dokument
```

## Architektur

### Komponenten

1. **InputHandler**: Verwaltet Taster und GPIO-Eingänge mit Entprellung
2. **LedController**: Steuert LED-Ausgänge und Blinkmodi
3. **AmpelController**: Implementiert Sequenzen und Modi
4. **StateMachine**: Verwaltet Übergänge zwischen Betriebsmodi

### Zustandsdiagram

```
IDLE --[Start]--> STARTSEQUENCE --[Completion]--> STARTFREIGABE
  |                    |
  |                    +--[FalseStart]--> FRUEHSTART
  |                    |
  |                    +--[Reset]--> IDLE
  |
  +--[SafetyCar]--> SAFETYCAR
  |
  +--[Chaos]--> CHAOS
  |
  +--[Rennende]--> ENDE
```

## Test-Strategie

- **Unit Tests**: Für InputHandler, LedController, AmpelController
- **Integration Tests**: Für Zustandsübergänge und Sequenzen
- **Edge Cases**: Gleichzeitige Eingaben, Reset während Blinken, etc.

## Performance-Ziele

- Reaktionszeit auf Eingaben: < 50ms
- LED-Blinken: Stabil ohne Flackern
- Haupt-Loop: 10ms Cycle

## Verwandte Dokumente

- [Spezifikation](./specs/001-startampel-carrera/spec.md)
- [Implementierungsplan](./specs/001-startampel-carrera/plan.md)
- [Taskliste](./specs/001-startampel-carrera/tasks.md)
- [Wiring Diagram](./docs/wiring.md)

## Lizenz & Credits

Projekt für Carrera-Bahn-Steuerung mit Arduino/ESP8266.

---

**Status**: In Entwicklung  
**Branch**: `001-startampel-carrera`  
**Erstellt**: 2026-05-11
- For any issues or feature requests, please open an issue in the repository.
- Contributions are welcome! Please follow the contribution guidelines provided in the repository.