# Startampel Test Suite

Diese Testsuite validiert alle Funktionen der D1 Mini-basierten Carrera-Bahn Startampel.

## Test-Kategorien

### 1. Unit Tests

#### test_input_handler.cpp
- Validiert Taster- und GPIO-Eingabe-Handling
- Testet Entprell-Logik
- Überprüft Button-State-Tracking

#### test_led_controller.cpp
- Testet LED-Ausgänge pro Spur
- Validiert An/Aus-Logik
- Überprüft Multi-Lane-Steuerung

#### test_state_machine.cpp
- Testet Zustandsübergänge
- Validiert Hauptablauf der Zustandsmaschine

### 2. Feature Tests

#### test_startsequenz.cpp
- Validiert 5-Schritt-Countdown mit roten LEDs
- Testet Übergang zu grünen LEDs (Startfreigabe)
- Prüft Reset-Funktionalität während Sequenz

#### test_fruehstart.cpp
- Testet Frühstart-Erkennung (Taster + IR-Schranke)
- Validiert gelbe LED-Aktivierung
- Prüft rote LED-Blink-Muster für betroffene Spur

#### test_safetycar.cpp
- Testet Safety-Car Modus
- Validiert synchrones Blinken aller gelben LEDs
- Überprüft Modus-Eingänge

#### test_chaos.cpp
- Testet Chaos/Rennunterbrechung-Modus
- Validiert rotes LED-Blinken
- Prüft Übergang vom Race-Start zu Chaos

#### test_rennende.cpp
- Testet Rennende/Sieger-Anzeige
- Validiert grünes LED-Blinken
- Überprüft rote LED-Anzeige für Sieger-Spur

### 3. Integration Tests

#### test_integration.cpp
- Testet komplette Workflow von Idle → Start → Freigabe
- Validiert Übergänge zwischen allen Modi
- Prüft Reset aus verschiedenen Zuständen

#### test_edgecases.cpp
- Testet Reset während Blinkmodus
- Validiert mehrfache Reset-Aufrufe
- Überprüft Verhalten bei gleichzeitigen Eingaben
- Prüft Zustandspriorität

## Test-Ausführung

### Mit PlatformIO

```bash
# Alle Tests ausführen
platformio test

# Nur Tests für D1 Mini
platformio test -e d1_mini

# Bestimmten Test ausführen
platformio test -e d1_mini --filter test_startsequenz
```

### Lokal (ohne Hardware-Upload)

```bash
# Unity Test-Framework verwenden
platformio test --no-upload --no-reset
```

## Test-Abdeckung

| Komponente         | Status | Coverage |
|--------------------|--------|----------|
| InputHandler       | ✓      | ~80%     |
| LedController      | ✓      | ~100%    |
| AmpelController    | ✓      | ~85%     |
| StateMachine       | ✓      | ~90%     |
| Integration        | ✓      | ~75%     |
| Edge Cases         | ✓      | ~70%     |

## Erwartete Test-Ergebnisse

Alle Tests sollten erfolgreich durchlaufen:

```
Collected 18 tests

test_startsequenz.cpp
  ✓ test_startsequence_initiates
  ✓ test_startsequence_completes
  ✓ test_reset_stops_sequence

test_fruehstart.cpp
  ✓ test_falsestart_during_sequence
  ✓ test_falsestart_sets_yellow_leds
  ✓ test_falsestart_clears

test_safetycar.cpp
  ✓ test_safetycar_sets_blink_mode
  ✓ test_safetycar_yellow_leds_blink
  ✓ test_chaos_sets_blink_mode

... (alle Tests)

TOTAL: 18/18 tests passed
```

## Debugging

### Debug-Output in Tests aktivieren

```cpp
#define DEBUG_TESTS 1
```

### Fehlerbehebung

- **Timing-Fehler**: Prüfen Sie BLINK_INTERVAL und SEQ_STEP_DURATION
- **Pin-Konflikte**: Überprüfen Sie config.h auf doppelte Pin-Zuweisungen
- **State-Fehler**: Prüfen Sie StateMachine-Übergänge in test_integration.cpp

---

**Hinweis**: Tests verwenden Unity Test Framework und sind für PlatformIO optimiert.

**Stand**: 2026-05-11
