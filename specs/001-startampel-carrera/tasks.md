---
description: "Task list for implementing the Startampel feature"
---

# Tasks: Startampel für Carrera-Bahn

**Input**: Design documents from `/specs/001-startampel-carrera/`
**Prerequisites**: plan.md (required), spec.md (required for user stories)

**Tests**: Tests are included where explicitly requested in the feature specification.

**Organization**: Tasks are grouped by user story to enable independent implementation and testing of each story.

## Format: `[ID] [P?] [Story] Description`

- **[P]**: Can run in parallel (different files, no dependencies)
- **[Story]**: Which user story this task belongs to (e.g., US1, US2, US3)
- Include exact file paths in descriptions

---

## Phase 0: Technical Design & Schematic

**Purpose**: Lock architecture, interfaces, timing, and hardware wiring before implementation.

- [ ] T000 [P] Create technical architecture document in `specs/001-startampel-carrera/technical-design.md`
- [ ] T000a [P] Create wiring/schematic document in `specs/001-startampel-carrera/schaltplan.md`
- [ ] T000b Resolve D1 Mini pin conflicts (IR vs Stop) in `src/config.h` and align docs

---

## Phase 1: Setup (Shared Infrastructure)

**Purpose**: Project initialization and basic structure

- [ ] T001 Create project structure per implementation plan
- [ ] T002 Initialize PlatformIO project with Arduino Core dependencies
- [ ] T003 [P] Configure linting and formatting tools (e.g., clang-format)
- [ ] T004 [P] Setup CI/CD workflows for build and test automation
- [ ] T005 [P] Create base configuration file `src/config.h` with pin definitions

---

## Phase 2: Foundational (Blocking Prerequisites)

**Purpose**: Core infrastructure that MUST be complete before ANY user story can be implemented

- [ ] T006 Implement `InputHandler` for button debouncing in `src/input_handler.cpp`
- [ ] T007 Implement `LedController` for LED abstraction in `src/led_controller.cpp`
- [ ] T008 Implement `StateMachine` for managing race states in `src/state_machine.cpp`
- [ ] T009 Create unit tests for foundational components in `tests/`

**Checkpoint**: Foundation ready - user story implementation can now begin in parallel

---

## Phase 3: User Story 1 - Startsequenz & Startfreigabe (Priority: P1) 🎯 MVP

**Goal**: Implement the start sequence and start release functionality.

**Independent Test**: Verify that the start sequence and release work as described.

### Tests for User Story 1

- [ ] T010 [P] [US1] Unit test for start sequence in `tests/test_startsequenz.cpp`
- [ ] T011 [P] [US1] Integration test for start sequence in `tests/test_integration.cpp`

### Implementation for User Story 1

- [ ] T012 [P] [US1] Implement start sequence logic in `src/ampel_controller.cpp`
- [ ] T013 [US1] Add start release logic to `src/ampel_controller.cpp`
- [ ] T014 [US1] Integrate start sequence with `StateMachine` in `src/state_machine.cpp`
- [ ] T015 [US1] Add logging for start sequence events

**Checkpoint**: At this point, User Story 1 should be fully functional and testable independently

---

## Phase 4: User Story 2 - Frühstart-Erkennung (Priority: P2)

**Goal**: Detect false starts using the IR sensor and indicate them with LEDs.

**Independent Test**: Verify that false starts are detected and indicated correctly.

### Tests for User Story 2

- [ ] T016 [P] [US2] Unit test for false start detection in `tests/test_fruehstart.cpp`
- [ ] T017 [P] [US2] Integration test for false start handling in `tests/test_integration.cpp`

### Implementation for User Story 2

- [ ] T018 [P] [US2] Implement false start detection logic in `src/input_handler.cpp`
- [ ] T019 [US2] Add false start indication logic to `src/ampel_controller.cpp`
- [ ] T020 [US2] Integrate false start handling with `StateMachine` in `src/state_machine.cpp`
- [ ] T021 [US2] Add logging for false start events

**Checkpoint**: At this point, User Story 2 should be fully functional and testable independently

---

## Phase 5: User Story 3 - Safety-Car/Pace-Car Modus (Priority: P3)

**Goal**: Implement the Safety-Car mode where all yellow LEDs blink synchronously.

**Independent Test**: Verify that the Safety-Car mode works as described.

### Tests for User Story 3

- [ ] T022 [P] [US3] Unit test for Safety-Car mode in `tests/test_safetycar.cpp`
- [ ] T023 [P] [US3] Integration test for Safety-Car mode in `tests/test_integration.cpp`

### Implementation for User Story 3

- [ ] T024 [P] [US3] Implement Safety-Car mode logic in `src/ampel_controller.cpp`
- [ ] T025 [US3] Integrate Safety-Car mode with `StateMachine` in `src/state_machine.cpp`
- [ ] T026 [US3] Add logging for Safety-Car mode events

**Checkpoint**: At this point, User Story 3 should be fully functional and testable independently

---

## Phase 6: User Story 4 - Rennunterbrechung/Chaos (Priority: P4)

**Goal**: Implement the Chaos mode where all red LEDs blink synchronously.

**Independent Test**: Verify that the Chaos mode works as described.

### Tests for User Story 4

- [ ] T027 [P] [US4] Unit test for Chaos mode in `tests/test_chaos.cpp`
- [ ] T028 [P] [US4] Integration test for Chaos mode in `tests/test_integration.cpp`

### Implementation for User Story 4

- [ ] T029 [P] [US4] Implement Chaos mode logic in `src/ampel_controller.cpp`
- [ ] T030 [US4] Integrate Chaos mode with `StateMachine` in `src/state_machine.cpp`
- [ ] T031 [US4] Add logging for Chaos mode events

**Checkpoint**: At this point, User Story 4 should be fully functional and testable independently

---

## Phase 7: User Story 5 - Rennende/Siegeranzeige (Priority: P5)

**Goal**: Implement the race end and winner indication functionality.

**Independent Test**: Verify that the race end and winner indication work as described.

### Tests for User Story 5

- [ ] T032 [P] [US5] Unit test for race end in `tests/test_rennende.cpp`
- [ ] T033 [P] [US5] Integration test for race end in `tests/test_integration.cpp`

### Implementation for User Story 5

- [ ] T034 [P] [US5] Implement race end logic in `src/ampel_controller.cpp`
- [ ] T035 [US5] Integrate race end logic with `StateMachine` in `src/state_machine.cpp`
- [ ] T036 [US5] Add logging for race end events

**Checkpoint**: At this point, User Story 5 should be fully functional and testable independently

---

## Final Phase: Polish & Cross-Cutting Concerns

**Purpose**: Finalize the implementation with cross-cutting concerns and polish.

- [ ] T037 Conduct full-system integration tests
- [ ] T038 Perform code review and add comments
- [ ] T039 Optimize performance (e.g., debounce timing, LED updates)
- [ ] T040 Update documentation (README, user guides)
- [ ] T041 Prepare final release (versioning, changelog)

---
