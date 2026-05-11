---
description: "Task list for Startampel für Carrera-Bahn"
---

# Tasks: Startampel für Carrera-Bahn

**Input**: specs/001-startampel-carrera/plan.md, specs/001-startampel-carrera/spec.md

## Phase 1: Setup (Shared Infrastructure)

- [X] T001 Create src/ and tests/ directories per implementation plan
- [X] T002 Initialize PlatformIO/Arduino project in src/
- [X] T003 [P] Add README and wiring diagram to docs/
- [X] T004 [P] Add .gitignore and basic project config files

---

- [X] T005 [P] Implement pin mapping and config in src/config.h (inkl. IR-Schranke)
- [X] T006 [P] Implement InputHandler (Taster/GPIO/IR-Schranke debouncing) in src/input_handler.cpp
- [X] T007 [P] Implement LED control abstraction in src/led_controller.cpp
- [X] T008 [P] Implement StateMachine base in src/state_machine.cpp
- [X] T009 [P] Add test stubs for all core modules in tests/

---

## Phase 3: User Story 1 – Startsequenz & Startfreigabe (P1) [US1] 🎯 MVP

**Goal**: Startsequenz mit 5 roten LEDs, danach grüne LEDs zur Startfreigabe
**Independent Test**: Start auslösen, Sequenz und Umschaltung beobachten

- [X] T010 [P] [US1] Implement Startsequenz-Logik in src/ampel_controller.cpp
- [X] T011 [P] [US1] Implement Startauslösung per Taster und GPIO in src/input_handler.cpp
- [X] T012 [US1] Implement Umschaltung auf grüne LEDs in src/ampel_controller.cpp
- [X] T013 [US1] Implement Reset-Logik (Abbruch Sequenz) in src/state_machine.cpp
- [X] T014 [US1] Add test for Startsequenz in tests/test_startsequenz.cpp

---


## Phase 4: User Story 2 – Frühstart-Erkennung (P2) [US2]

**Goal**: Frühstart erkennen (auch per IR-Schranke), gelbe LEDs leuchten, betroffene rote LED blinkt
**Independent Test**: Frühstart simulieren (Taster oder IR-Schranke), LED-Reaktion prüfen

- [X] T015 [P] [US2] Implement Frühstart-Erkennung (Taster und IR-Schranke) in src/input_handler.cpp
- [X] T016 [US2] Implement gelbe LED-Logik in src/ampel_controller.cpp
- [X] T017 [US2] Implement rote LED-Blinken für betroffene Spur in src/ampel_controller.cpp
- [X] T018 [US2] Add test for Frühstart (inkl. IR-Schranke) in tests/test_fruehstart.cpp

---

## Phase 5: User Story 3 – Safety-Car/Pace-Car Modus (P3) [US3]

**Goal**: Alle gelben LEDs blinken synchron
**Independent Test**: Safety-Car-Modus aktivieren, Blinken prüfen

- [X] T019 [P] [US3] Implement Safety-Car-Modus in src/state_machine.cpp
- [X] T020 [US3] Implement synchrones Blinken aller gelben LEDs in src/ampel_controller.cpp
- [X] T021 [US3] Add test for Safety-Car-Modus in tests/test_safetycar.cpp

---

## Phase 6: User Story 4 – Rennunterbrechung/Chaos (P4) [US4]

**Goal**: Alle roten LEDs blinken bei Chaos/Rennunterbrechung
**Independent Test**: Modus auslösen, Blinken prüfen

- [X] T022 [P] [US4] Implement Chaos/Rennunterbrechung-Modus in src/state_machine.cpp
- [X] T023 [US4] Implement synchrones Blinken aller roten LEDs in src/ampel_controller.cpp
- [X] T024 [US4] Add test for Chaos-Modus in tests/test_chaos.cpp

---

## Phase 7: User Story 5 – Rennende/Siegeranzeige (P5) [US5]

**Goal**: Nach Rennende blinken alle grünen LEDs, Sieger-rote LED bleibt an
**Independent Test**: Rennende auslösen, Anzeige prüfen

- [X] T025 [P] [US5] Implement Rennende/Siegeranzeige in src/state_machine.cpp
- [X] T026 [US5] Implement grünes LED-Blinken und Sieger-rote LED in src/ampel_controller.cpp
- [X] T027 [US5] Add test for Rennende/Siegeranzeige in tests/test_rennende.cpp

---


## Phase 8: Edge Case Tests & Polish

- [X] T028 [P] Add documentation for wiring and usage in docs/
- [ ] T029 [P] Add code comments and clean up
- [X] T030 [P] Final integration test for all modes in tests/test_integration.cpp

# Edge Case Tests
- [X] T031 [P] Test gleichzeitiges Drücken mehrerer Taster/GPIO in tests/test_edgecases.cpp
- [X] T032 [P] Test Verhalten bei Stromausfall während Sequenz in tests/test_edgecases.cpp
- [X] T033 [P] Test gleichzeitiger externer Trigger und Taster in tests/test_edgecases.cpp
- [X] T034 [P] Test Reset während Blinkmodus in tests/test_edgecases.cpp

----

## Dependencies

- Phase 1 & 2 müssen abgeschlossen sein, bevor User Stories umgesetzt werden
- User Stories können nach Phase 2 parallel entwickelt werden
- Polish-Phase erst nach Abschluss aller User Stories

## Parallel Execution Examples

- T003, T004, T005–T009 können parallel erledigt werden
- Alle [P]-markierten Tasks pro User Story sind parallel ausführbar

## MVP Scope

- Phase 3 (User Story 1) ist das MVP: Startsequenz & Startfreigabe

## Implementation Strategy

- MVP first (US1), dann inkrementell weitere User Stories
- Jede Story unabhängig testbar

---
