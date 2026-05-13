---
description: "Task list for Phase 2: Production Readiness & Extensions"
---

# Tasks: Phase 2 – Produktivierung & Erweiterungen

**Input**: specs/002-production-ready/plan.md

## Phase 0: Technisches Design & Schaltplan (P1)

**Goal**: Vollstaendiges technisches Design fuer alle Phase-2-Features festlegen
**Independent Test**: Architektur, Schnittstellen und Hardware-Zuordnung sind dokumentiert

- [ ] T100 [P] Erstelle technisches Design in `specs/002-production-ready/technical-design.md`
- [ ] T100a [P] Erstelle Produktions-Schaltplan in `specs/002-production-ready/schaltplan.md`
- [ ] T100b Leite Hardware-Checkliste aus dem Schaltplan in `docs/TESTING.md` ab

## Phase 1 ✓ (abgeschlossen, siehe [001-startampel-carrera/tasks.md](../001-startampel-carrera/tasks.md))

---

## Phase 9: Phase 2a – Hardware-Integration & Testing (P1)

**Goal**: Firmware auf echter Hardware validieren und stabilisieren  
**Independent Test**: Hardware verdrahtet, Alle LEDs & Taster funktionieren korrekt

- [ ] T101 [P] Verdrahte alle Komponenten nach docs/wiring.md auf Breadboard
- [ ] T102 [P] Teste D1 Mini USB-Erkennung und Programmierung
- [ ] T103 [P] Teste alle LED-Ausgänge (Pro Spur: rot, gelb, grün)
- [ ] T104 [P] Teste alle Button-Eingänge (Start, Stop, Reset, Mode)
- [ ] T105 [P] Teste IR-Lichtschranke Integration und Kalibrierung
- [ ] T106 Messe Reaktionszeit (<50ms) auf alle Eingaben
- [ ] T107 Validiere LED-Blinken Stabilität (keine Flacker, konstantes Timing)
- [ ] T108 Führe 24h Dauerbetrieb-Test durch
- [ ] T109 Dokumentiere Hardware-Test-Results in docs/TESTING.md
- [ ] T110 Erstelle Hardware-Troubleshooting-Guide in docs/

---

## Phase 10: Phase 2b – Firmware-Optimierung (P2)

**Goal**: Memory, Performance und Stabilität verbessern  
**Independent Test**: Speicher-Profiling durchführen, Performance messen

- [ ] T111 [P] Messe RAM/Flash-Nutzung mit Memory Profiler
- [ ] T112 [P] Optimiere Loop-Cycle-Zeit (ziel: <20ms)
- [ ] T113 Implementiere Interrupt-basiertes Input-Handling (statt Polling)
- [ ] T114 Verbessere LED-Blinken-Genauigkeit auf ±10ms
- [ ] T115 [P] Implementiere Watchdog-Timer (Auto-Reset nach 30s ohne Heartbeat)
- [ ] T116 Implementiere Graceful Degradation bei Fehlerfall
- [ ] T117 Implementiere Error-Logging in EEPROM (max 100 Einträge)
- [ ] T118 Implementiere Factory-Reset Mechanismus (5s Button-Press)
- [ ] T119 Optimiere Power-Consumption (Ziel: <500mW avg)
- [ ] T120 Teste und dokumentiere Optimierungen in docs/OPTIMIZATION.md

---

## Phase 11: Phase 2c – Web-Interface (P3, Optional)

**Goal**: Webbasierte Steuerung & Status-Anzeige  
**Independent Test**: Web-Interface erreichbar, Steuerung funktioniert

- [ ] T121 [P] Integriere ESPAsyncWebServer Bibliothek
- [ ] T122 [P] Implementiere REST-API Endpoints (GET /status, POST /control)
- [ ] T123 [P] Implementiere WebSocket für Echtzeit-Status Updates
- [ ] T124 Erstelle HTML Dashboard (responsive Design)
- [ ] T125 Implementiere Start/Stop/Reset/Mode Buttons im Web-UI
- [ ] T126 Implementiere LED-Status Live-Anzeige im Web-UI
- [ ] T127 Implementiere Modus-Auswahl Dropdown im Web-UI
- [ ] T128 Implementiere Log-Viewer im Web-UI
- [ ] T129 Implementiere Statistik-Seite (Anzahl Starts, etc.)
- [ ] T130 [P] Add test for Web-Interface in tests/test_webinterface.cpp

---

## Phase 12: Phase 2d – Persistente Konfiguration (P3, Optional)

**Goal**: Konfiguration auf D1 Mini speichern  
**Independent Test**: Config speichern & wiederherstellen

- [ ] T131 [P] Implementiere EEPROM-basierte Config-Verwaltung
- [ ] T132 [P] Erstelle Config-Struct mit allen Parametern
- [ ] T133 Implementiere JSON-Serialisierung für Config
- [ ] T134 Implementiere Config-Validator (Ranges prüfen)
- [ ] T135 Implementiere Backup/Restore Funktionen
- [ ] T136 Implementiere Migration für alte Config-Versionen
- [ ] T137 [P] Add test for Config-Management in tests/test_config.cpp
- [ ] T138 Implementiere Web-UI für Config-Editing
- [ ] T139 Dokumentiere alle Konfigurierbaren Parameter in docs/CONFIG.md

---

## Phase 13: Phase 2e – OTA-Updates (P4, Optional)

**Goal**: Firmware-Updates über WLAN  
**Independent Test**: OTA-Update erfolgreich, Firmware lädt neu

- [ ] T140 [P] Integriere ArduinoOTA Bibliothek
- [ ] T141 [P] Implementiere OTA-Server auf D1 Mini
- [ ] T142 Implementiere Version-String und Check in Firmware
- [ ] T143 Erstelle Web-Upload-Interface für OTA-Firmware
- [ ] T144 Implementiere Rollback-Mechanismus bei Update-Fehler
- [ ] T145 [P] Add test for OTA-Updates in tests/test_ota.cpp
- [ ] T146 Erstelle Update-Guide in docs/OTA.md

---

## Phase 14: Phase 2f – Benutzer-Dokumentation (P2)

**Goal**: Endbenutzer-freundliche Dokumentation  
**Independent Test**: Neuer Benutzer kann System bedienen

- [X] T147 [P] Erstelle Schnellstart-Anleitung (5 min Setup) → docs/QUICKSTART.md ✓
- [X] T148 [P] Erstelle ausführliche Bedienungsanleitung → docs/BEDIENUNG.md ✓
- [X] T149 [P] Erstelle Troubleshooting-Guide mit FAQ → docs/TROUBLESHOOTING.md ✓
- [ ] T150 Erstelle Video-Tutorial (optional, Screencast)
- [ ] T151 [P] Erstelle Wartungs-Anleitung (Reinigung, Kalibrierung)
- [ ] T152 Erstelle "Erste Hilfe" Guide für häufige Fehler (in T149 enthalten)
- [X] T153 [P] Überarbeite README.md mit Links zu neuer Doku ✓
- [ ] T154 Erstelle Druck-freundliche PDF-Version der Doku

---

## Phase 15: Phase 2g – Erweiterte Features (P5, Later)

**Goal**: Optionale Features für Advanced Users  
**Independent Test**: Features konfigurierbar und funktional

- [ ] T155 [P] [FUTURE] Implementiere Multi-Controller Support (Netzwerk)
- [ ] T156 [P] [FUTURE] Implementiere Netzwerk-Synchronisation
- [ ] T157 [FUTURE] Erstelle Mobile App (iOS/Android optional)
- [ ] T158 [FUTURE] Implementiere Statistik-Export (CSV)
- [ ] T159 [FUTURE] Implementiere Custom-Sound (Buzzer-Support)
- [ ] T160 [FUTURE] Implementiere IR-Fernsteuerung
- [ ] T161 [FUTURE] Implementiere MQTT Integration (Smart Home)
- [ ] T162 [FUTURE] Implementiere Home Assistant Integration

---

## Phase 16: Phase 2h – CI/CD & Release (P3)

**Goal**: Automatisierte Tests, Builds und Releases  
**Independent Test**: GitHub Actions läuft, Releases erstellt

- [X] T163 [P] Erstelle .github/workflows/build.yml für PlatformIO Build ✓
- [X] T164 [P] Erstelle .github/workflows/test.yml für Unit Tests (in build.yml enthalten) ✓
- [X] T165 [P] Konfiguriere Binary-Artifacts in GitHub Actions ✓
- [X] T166 Erstelle Release-Automation Script → .github/workflows/release.yml ✓
- [X] T167 [P] Erstelle Changelog-Auto-Generation (in release.yml) ✓
- [X] T168 Implementiere Semantic Versioning (dokumentiert) ✓
- [ ] T169 [P] Add GitHub Release-Template für neue Releases
- [X] T170 Dokumentiere CI/CD Setup in docs/CI-CD.md ✓

---

## Phase 17: Polish & Final Testing (P1)

**Goal**: Alles zusammen testen, dokumentieren, freigeben  
**Independent Test**: Komplettes System getestet

- [ ] T171 [P] Führe Full-System Integration Test durch
- [ ] T172 [P] Überprüfe alle Code-Comments und Dokumentation
- [ ] T173 [P] Führe Code-Review durch
- [ ] T174 [P] Erstelle Release Notes für Phase 2
- [ ] T175 Aktualisiere alle READMEs und Links
- [ ] T176 [P] Finaler Security-Check (Eingabe-Validierung, etc.)
- [ ] T177 [P] Performance-Test unter Last (100+ Button-Presses/sec)
- [ ] T178 [P] Erstelle Phase 2 Completion Report

---

## Dependencies

```
Phase 9 (Hardware-Test) [BLOCKER für alles andere]
    ↓
Phase 10 (Firmware-Opt)
    ↓
Phase 11,12,13 (Web/Config/OTA) [Parallel, Optional]
    ↓
Phase 14 (Doku) [Kann parallel ab Phase 9 laufen]
    ↓
Phase 15 (Features) [Later, Future]
    ↓
Phase 16 (CI/CD) [Abschließend]
    ↓
Phase 17 (Polish)
```

## Parallel Execution Examples

**Schnell (essenzielle P1+P2):**
- T101-T110 (Hardware): 8h
- T111-T120 (Firmware): 4h
- T147-T154 (Doku): 6h
- **Total essenziel: ~18h**

**Mittel (mit Optionals):**
- Alles oben + Phase 11-13
- **Total: ~50h**

**Vollständig:**
- Alles inkl. Phase 15
- **Total: ~70h**

## MVP Scope Phase 2

**Minimum für Production:**
- Phase 9: Hardware validiert
- Phase 10: Firmware optimiert
- Phase 14: Dokumentation

**Recommended:**
- Oben + Phase 11 (Web-Interface)
- Oben + Phase 16 (CI/CD)

---

## Success Criteria

- [x] Alle Phase 1 Tasks abgeschlossen
- [ ] Hardware erfolgreich getestet & stabil
- [ ] Firmware Speicher-optimiert (<300KB Flash, <20KB RAM)
- [ ] 24h Dauerlauf ohne Fehler
- [ ] Benutzer-Dokumentation vollständig
- [ ] (Optional) Web-Interface funktionsfähig
- [ ] (Optional) CI/CD Pipeline aktiv

---

## Links & Referenzen

- [Phase 1 Tasks](../001-startampel-carrera/tasks.md)
- [Phase 2 Plan](./plan.md)
- [Hardware Wiring](../../docs/wiring.md)
- [Testing Guide](../../docs/TESTING.md)

---

**Total Tasks**: 78 (44 Phase 2)  
**Status**: Planning  
**Created**: 2026-05-11
