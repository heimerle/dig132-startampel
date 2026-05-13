---
description: "Task list for implementing the Startampel feature"
---

# Tasks: Startampel für Carrera-Bahn

**Input**: Design documents from `/specs/001-startampel-carrera/`
**Prerequisites**: plan.md (required), spec.md (required for user stories), technical-design.md, schaltplan.md

**Tests**: Tests are included where explicitly requested in the feature specification.

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- Include exact file paths in descriptions

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization, architecture baseline, and hardware baseline

- [ ] T001 Align implementation summary and constraints in `specs/001-startampel-carrera/plan.md`
- [ ] T002 [P] Finalize architecture decisions in `specs/001-startampel-carrera/technical-design.md`
- [ ] T003 [P] Finalize wiring and pin mapping in `specs/001-startampel-carrera/schaltplan.md`
- [ ] T004 Resolve and document board-specific pin mapping in `src/config.h`
- [ ] T005 [P] Align hardware documentation with final pin map in `docs/wiring.md`
- [ ] T006 [P] Ensure CI build matrix covers D1 Mini and ESP32 in `.github/workflows/build.yml`

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Shared firmware infrastructure required by all user stories

- [ ] T007 Implement debounced input event normalization in `src/input_handler.cpp`
- [ ] T008 [P] Expose stable input API contracts in `src/input_handler.h`
- [ ] T009 Implement deterministic LED output primitives in `src/led_controller.cpp`
- [ ] T010 [P] Expose LED control API for steady/blink patterns in `src/led_controller.h`
- [ ] T011 Implement canonical state enum and transitions in `src/state_machine.cpp`
- [ ] T012 [P] Expose state transition interface in `src/state_machine.h`
- [ ] T013 Integrate foundational modules into main loop in `src/main.cpp`
- [ ] T014 [P] Add foundational unit tests for input and LED primitives in `tests/test_input_handler.cpp`
- [ ] T015 [P] Add foundational unit tests for state transitions in `tests/test_state_machine.cpp`

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 1 - Startsequenz & Startfreigabe (Priority: P1) 🎯 MVP

**Goal**: Implement the start sequence and start release functionality.

**Independent Test**: Verify that the start sequence and release work as described.

### Tests for User Story 1

- [ ] T016 [P] [US1] Add unit test for 5-step countdown timing in `tests/test_startsequenz.cpp`
- [ ] T017 [P] [US1] Add integration test for start trigger to green release flow in `tests/test_integration.cpp`
- [ ] T018 [P] [US1] Add reset-during-sequence regression test in `tests/test_edgecases.cpp`

### Implementation for User Story 1

- [ ] T019 [US1] Implement non-blocking start countdown (500 ms steps) in `src/ampel_controller.cpp`
- [ ] T020 [US1] Implement green release steady state in `src/ampel_controller.cpp`
- [ ] T021 [US1] Wire start and reset transitions for sequence lifecycle in `src/state_machine.cpp`
- [ ] T022 [US1] Route start/reset events through controller update loop in `src/main.cpp`

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently

---

## Phase 4: User Story 2 - Frühstart-Erkennung (Priority: P2)

**Goal**: Detect false starts using the IR sensor and indicate them with LEDs.

**Independent Test**: Verify that false starts are detected and indicated correctly.

### Tests for User Story 2

- [ ] T023 [P] [US2] Add unit test for false start trigger detection in `tests/test_fruehstart.cpp`
- [ ] T024 [P] [US2] Add integration test for yellow steady plus offender red blink in `tests/test_integration.cpp`
- [ ] T025 [P] [US2] Add simultaneous input arbitration test (Last-Input-Wins) in `tests/test_edgecases.cpp`

### Implementation for User Story 2

- [ ] T026 [US2] Implement IR-based false start event generation in `src/input_handler.cpp`
- [ ] T027 [US2] Implement false start LED pattern (yellow steady, red 250 ms blink) in `src/ampel_controller.cpp`
- [ ] T028 [US2] Add false start transition and recovery rules in `src/state_machine.cpp`
- [ ] T029 [US2] Integrate false start source priority handling in `src/main.cpp`

**Checkpoint**: At this point, User Story 2 should be fully functional and testable independently

---

## Phase 5: User Story 3 - Safety-Car/Pace-Car Modus (Priority: P3)

**Goal**: Implement the Safety-Car mode where all yellow LEDs blink synchronously.

**Independent Test**: Verify that the Safety-Car mode works as described.

### Tests for User Story 3

- [ ] T030 [P] [US3] Add unit test for synchronized yellow blink pattern in `tests/test_safetycar.cpp`
- [ ] T031 [P] [US3] Add integration test for entering and leaving safety-car mode in `tests/test_integration.cpp`

### Implementation for User Story 3

- [ ] T032 [US3] Implement synchronized yellow 250 ms blink mode in `src/ampel_controller.cpp`
- [ ] T033 [US3] Add safety-car activation and deactivation transitions in `src/state_machine.cpp`
- [ ] T034 [US3] Map safety-car trigger inputs to state transitions in `src/main.cpp`

**Checkpoint**: At this point, User Story 3 should be fully functional and testable independently

---

## Phase 6: User Story 4 - Rennunterbrechung/Chaos (Priority: P4)

**Goal**: Implement the Chaos mode where all red LEDs blink synchronously.

**Independent Test**: Verify that the Chaos mode works as described.

### Tests for User Story 4

- [ ] T035 [P] [US4] Add unit test for synchronized red blink pattern in `tests/test_chaos.cpp`
- [ ] T036 [P] [US4] Add integration test for chaos mode transition behavior in `tests/test_integration.cpp`

### Implementation for User Story 4

- [ ] T037 [US4] Implement synchronized red 250 ms blink mode in `src/ampel_controller.cpp`
- [ ] T038 [US4] Add chaos activation and reset behavior in `src/state_machine.cpp`
- [ ] T039 [US4] Map chaos trigger inputs to state transitions in `src/main.cpp`

**Checkpoint**: At this point, User Story 4 should be fully functional and testable independently

---

## Phase 7: User Story 5 - Rennende/Siegeranzeige (Priority: P5)

**Goal**: Implement the race end and winner indication functionality.

**Independent Test**: Verify that the race end and winner indication work as described.

### Tests for User Story 5

- [ ] T040 [P] [US5] Add unit test for race-end green blink plus winner red steady in `tests/test_rennende.cpp`
- [ ] T041 [P] [US5] Add integration test for race-end event flow in `tests/test_integration.cpp`

### Implementation for User Story 5

- [ ] T042 [US5] Implement race-end LED behavior (green blink + winner red steady) in `src/ampel_controller.cpp`
- [ ] T043 [US5] Add winner-state transition rules in `src/state_machine.cpp`
- [ ] T044 [US5] Map race-end and winner inputs into event handling in `src/main.cpp`

**Checkpoint**: At this point, User Story 5 should be fully functional and testable independently

---

## Phase 8: Polish & Cross-Cutting Concerns

**Purpose**: Finalize the implementation with cross-cutting concerns and polish.

- [ ] T045 [P] Run complete mode regression suite in `tests/test_integration.cpp`
- [ ] T046 [P] Add edge-case regression coverage (simultaneous inputs, reset during blink, power-cycle behavior) in `tests/test_edgecases.cpp`
- [ ] T047 Optimize timing and debounce constants against performance goals in `src/config.h`
- [ ] T048 [P] Sync implementation behavior with user docs in `docs/BEDIENUNG.md`
- [ ] T049 [P] Sync wiring and troubleshooting notes with final behavior in `docs/wiring.md`
- [ ] T050 Update feature completion checklist in `specs/001-startampel-carrera/checklists/requirements.md`

---

## Dependencies & Execution Order

### Phase Dependencies

- **Phase 1 (Setup)**: can start immediately
- **Phase 2 (Foundational)**: depends on Setup completion and blocks all user stories
- **Phase 3-7 (User Stories)**: depend on Foundational completion; run in priority order or in parallel by team capacity
- **Phase 8 (Polish)**: depends on completion of all selected user stories

### User Story Dependencies

- **US1 (P1)**: no dependency on other stories; establishes MVP baseline
- **US2 (P2)**: depends on US1 start-sequence context
- **US3 (P3)**: can start after foundational phase; integrates with race-running context
- **US4 (P4)**: can start after foundational phase; independent from US3 logic implementation
- **US5 (P5)**: depends on race-state model established by US1-US4

### Within Each User Story

- Tests first, then implementation
- Controller logic before final main-loop wiring
- Story must pass its independent test before moving forward

---

## Parallel Execution Examples

### User Story 1

- Run T016 and T017 in parallel (different test files)

### User Story 2

- Run T023 and T025 in parallel (different test files)

### Foundational

- Run T008, T010, and T012 in parallel (different header files)

---

## Implementation Strategy

### MVP First (US1)

1. Complete Phase 1 (Setup)
2. Complete Phase 2 (Foundational)
3. Complete Phase 3 (US1)
4. Validate US1 independently via T016-T018

### Incremental Delivery

1. Deliver US1 (MVP)
2. Deliver US2 (false start fairness)
3. Deliver US3 (safety-car mode)
4. Deliver US4 (chaos mode)
5. Deliver US5 (race-end winner indication)
6. Execute Phase 8 polish and regression

