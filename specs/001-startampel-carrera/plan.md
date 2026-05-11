
# Implementation Plan: Startampel für Carrera-Bahn


**Branch**: `[001-startampel-carrera]` | **Date**: 2026-05-11 | **Spec**: [specs/001-startampel-carrera/spec.md](specs/001-startampel-carrera/spec.md)
**Input**: Feature specification from `/specs/001-startampel-carrera/spec.md`

**Note**: This template is filled in by the `/speckit.plan` command. See `.specify/templates/plan-template.md` for the execution workflow.


## Summary

Die Startampel für die Carrera-Bahn steuert pro Spur einzelne LEDs (rot, gelb, grün) und unterstützt verschiedene Rennmodi (Startsequenz, Startfreigabe, Frühstart, Safety-Car, Chaos, Rennende/Sieger). Die Steuerung erfolgt über Taster und externe GPIO-Trigger. Ziel ist eine robuste, konfigurierbare und einfach bedienbare Lösung auf Basis von ESP32 oder D1 Mini (ESP8266).


## Technical Context

**Language/Version**: C++ (Arduino Core) – Standard für dieses Projekt. MicroPython nur nach expliziter Entscheidung.
**Primary Dependencies**: Arduino-Framework, ggf. ESPAsyncWebServer (optional für Websteuerung), Arduino GPIO/LED Libraries.
**Storage**: N/A (keine persistente Speicherung erforderlich)
**Testing**: Unit-Tests mit PlatformIO/Catch2 oder Arduino-Testframework.
**Target Platform**: ESP32 oder D1 Mini (ESP8266)
**Project Type**: Embedded Firmware für Microcontroller
**Performance Goals**: Reaktionszeit <50ms auf Eingaben, stabile LED-Steuerung ohne Flackern
**Constraints**: Robuste Entprellung der Taster, Schutz vor Kurzschluss, Stromversorgung 5V/USB, Pull-up/-down für Eingänge
**Scale/Scope**: Standard: 2 Spuren, konfigurierbar bis 4 Spuren (final: 2 Spuren, erweiterbar)


## Constitution Check

*GATE: Must pass before Phase 0 research. Re-check after Phase 1 design.*

- Test-First: Für alle Logikfunktionen müssen Unit-Tests existieren (ggf. Simulation auf Host).
- CLI Interface: Optional, falls Web- oder serielle Steuerung ergänzt wird.
- Integrationstests: Für alle Modi (Start, Frühstart, Safety-Car, Chaos, Rennende) müssen Testfälle existieren.
- Simplicity: Keine unnötige Komplexität, Fokus auf Zuverlässigkeit und einfache Bedienung.


## Hardware-Komponenten & Pinbelegung (Draft)

**Microcontroller:** ESP32 oder D1 Mini (ESP8266)
**LEDs pro Spur:** 1x Rot, 1x Gelb, 1x Grün (Standard: 2 Spuren, erweiterbar)
**Taster:** Start, Stop, Reset, Modus (ggf. pro Spur oder global)
**GPIO-Trigger:** Externe Eingänge für Start, Frühstart, Safety-Car etc.
**Vorwiderstände:** 220–470 Ohm für LEDs
**Pull-down/-up:** 10kΩ für Taster/GPIO
**Stromversorgung:** USB oder 5V-Netzteil


**Finale Pinbelegung (für 2 Spuren, D1 Mini):**

| Funktion         | Pin ESP32 | Pin D1 Mini | Kommentar                |
|------------------|-----------|------------|--------------------------|
| LED1 Rot         | 16        | D1         | Spur 1                   |
| LED1 Gelb        | 17        | D2         | Spur 1                   |
| LED1 Grün        | 18        | D3         | Spur 1                   |
| LED2 Rot         | 19        | D4         | Spur 2                   |
| LED2 Gelb        | 21        | D5         | Spur 2                   |
| LED2 Grün        | 22        | D6         | Spur 2                   |
| Taster Start     | 23        | D7         | global                   |
| Taster Stop      | 25        | D8         | global                   |
| Taster Reset     | 26        | RX         | global                   |
| Taster Modus     | 27        | TX         | optional/global          |
| GPIO Trigger 1   | 32        | A0         | extern, z.B. Start       |
| GPIO Trigger 2   | 33        | D0         | extern, z.B. Frühstart   |
| IR-Schranke      | —         | D8         | Frühstart-Erkennung      |
**Frühstart-Logik:**
- Die IR-Lichtschranke ist vor der Pole Position angebracht und mit D8 (D1 Mini) verbunden.
- Wird die Schranke während der Startsequenz unterbrochen, wird ein Frühstart ausgelöst.
- Die Software behandelt die IR-Schranke wie einen weiteren GPIO-Trigger.
**Edge Case Test:**
- Test: IR-Schranke wird während Countdown unterbrochen → Frühstart wird korrekt erkannt und angezeigt.

**Hinweis:** Für mehr als 2 Spuren müssen zusätzliche Pins zugeordnet werden.
## Edge Cases & Tests

- Gleichzeitiges Drücken mehrerer Taster/GPIO: System muss robust reagieren, keine undefinierten Zustände.
- Stromausfall während Sequenz: Nach Neustart alle LEDs aus, System im Grundzustand.
- Gleichzeitiger externer Trigger und Taster: Priorität nach Last-Input-Wins, Reset bricht alles ab.
- Reset während Blinkmodus: Sofortiger Abbruch, alle LEDs aus.

## Software-Architektur (Draft)

- **AmpelController**: Zentrale Steuerung der LED-Logik und Modi
- **InputHandler**: Entprellung und Auswertung der Taster/GPIO-Trigger
- **StateMachine**: Abbildung der Rennmodi (Start, Frühstart, Safety-Car, Chaos, Rennende)
- **Config**: Konfiguration der Spurenzahl, Pinbelegung, ggf. Web-Interface
- **(Optional) Web/Serial Interface**: Steuerung und Statusanzeige über Web oder serielle Konsole

**Ablauf:**
1. Initialisierung (Pins, Konfiguration, Selbsttest)
2. Warten auf Start (Taster oder GPIO)
3. Startsequenz (rote LEDs nacheinander)
4. Startfreigabe (grüne LEDs)
5. Überwachung auf Frühstart (Trigger während Countdown)
6. Moduswechsel (Safety-Car, Chaos, Rennende) per Taster/GPIO
7. Reset jederzeit möglich

**(NEEDS CLARIFICATION: Welche Software-Architektur bevorzugt? C++/Arduino-Klassenstruktur oder MicroPython?)**

### Documentation (this feature)

```text
specs/[###-feature]/
├── plan.md              # This file (/speckit.plan command output)
├── research.md          # Phase 0 output (/speckit.plan command)
├── data-model.md        # Phase 1 output (/speckit.plan command)
├── quickstart.md        # Phase 1 output (/speckit.plan command)
├── contracts/           # Phase 1 output (/speckit.plan command)
└── tasks.md             # Phase 2 output (/speckit.tasks command - NOT created by /speckit.plan)
```

### Source Code (repository root)
<!--
  ACTION REQUIRED: Replace the placeholder tree below with the concrete layout
  for this feature. Delete unused options and expand the chosen structure with
  real paths (e.g., apps/admin, packages/something). The delivered plan must
  not include Option labels.
-->

```text
# [REMOVE IF UNUSED] Option 1: Single project (DEFAULT)
src/
├── models/
├── services/
├── cli/
└── lib/

tests/
├── contract/
├── integration/
└── unit/

# [REMOVE IF UNUSED] Option 2: Web application (when "frontend" + "backend" detected)
backend/
├── src/
│   ├── models/
│   ├── services/
│   └── api/
└── tests/

frontend/
├── src/
│   ├── components/
│   ├── pages/
│   └── services/
└── tests/

# [REMOVE IF UNUSED] Option 3: Mobile + API (when "iOS/Android" detected)
api/
└── [same as backend above]

ios/ or android/
└── [platform-specific structure: feature modules, UI flows, platform tests]
```

**Structure Decision**: [Document the selected structure and reference the real
directories captured above]

## Complexity Tracking

> **Fill ONLY if Constitution Check has violations that must be justified**

| Violation | Why Needed | Simpler Alternative Rejected Because |
|-----------|------------|-------------------------------------|
| [e.g., 4th project] | [current need] | [why 3 projects insufficient] |
| [e.g., Repository pattern] | [specific problem] | [why direct DB access insufficient] |
