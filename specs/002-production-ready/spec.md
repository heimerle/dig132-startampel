---
description: "Phase 2 Specification: Production Readiness & Extensions"
---

# Specification: Phase 2 – Produktivierung & Erweiterungen

**Version**: 1.0.0  
**Status**: Planning  
**Predecessor**: [Phase 1 Spec](../001-startampel-carrera/spec.md)

## Executive Summary

Nach erfolgreicher MVP-Implementierung (Phase 1) wird die Startampel nun für den Produktionsbetrieb vorbereitet. Dies umfasst Hardware-Validierung, Firmware-Optimierung, optionale Web-Steuerung und umfassende Dokumentation.

---

## Business Goals

1. **Produktionsreife**: Hardware & Firmware stabil für 24/7 Betrieb
2. **Benutzerfreundlichkeit**: Einfache Bedienung auch für nicht-technische Nutzer
3. **Wartbarkeit**: Einfache Updates und Konfiguration ohne USB-Zugriff
4. **Skalierbarkeit**: Vorbereitung für mehrere Spuren / Multi-Controller Setup

---

## User Stories

### US1: Hardware-Integration & Validierung
**As a** Hobby-Rennfahrer  
**I want to** meine Carrera-Bahn mit echter Hardware betreiben  
**So that** ich die Startampel im realen Setup testen kann

**Acceptance Criteria**:
- Alle Komponenten korrekt verdrahtet
- Alle Eingabe-Sensoren funktionieren zuverlässig
- LED-Ausgaben stabil und flimmerfrei
- Reaktionszeit <50ms auf Tastereingaben
- IR-Sensor erklärt Frühstart zuverlässig
- 24h Dauerbetrieb ohne Ausfälle

**Priority**: P1 – BLOCKING (Alles andere hängt davon ab)

---

### US2: Firmware-Optimierung
**As a** Developer  
**I want to** die Firmware speicher- und energieeffizient machen  
**So that** sie auf begrenzten Embedded-Systemen zuverlässig läuft

**Acceptance Criteria**:
- RAM-Nutzung <20KB
- Flash-Nutzung <300KB
- Loop-Cycle <20ms
- Power-Consumption <500mW im Normalbetrieb
- Watchdog-Reset funktioniert bei Fehler
- Error-Logging in EEPROM gespeichert

**Priority**: P2 – Wichtig (Nach Hardware-Validierung)

---

### US3: Web-Interface für erweiterte Steuerung
**As a** Rennveranstalter  
**I want to** die Startampel von meinem Laptop/Smartphone steuern  
**So that** ich flexiblere Szenarien wie mehrspurige Rennen oder Remote-Events unterstützen kann

**Acceptance Criteria**:
- Web-Interface auf http://d1mini.local:8080 erreichbar
- Steuerung: Start, Stop, Reset, Modus-Auswahl
- Live-Status von LEDs und Sensoren
- Responsive Design (Desktop, Tablet, Mobile)
- Echtzeitkommunikation via WebSocket
- Kein Lag bei Steuerung (<200ms RTT)

**Priority**: P3 – Nett zu haben (Optional, später)

---

### US4: Persistente Konfiguration
**As a** Techniker  
**I want to** die Ampel-Parameter speichern und abrufen können  
**So that** ich Kalibrierungen nicht bei jedem Neustart neu machen muss

**Acceptance Criteria**:
- Parameter in EEPROM persistiert
- JSON-basiertes Format
- Backup/Restore-Funktionen
- Version-Migration bei Firmware-Updates
- Web-UI für Config-Editing

**Priority**: P3 – Optional

---

### US5: OTA-Firmware-Updates
**As a** Hauptentwickler  
**I want to** neue Firmware-Versionen über WLAN pushen  
**So that** ich Nutzer nicht zum manuellen USB-Upload anleiten muss

**Acceptance Criteria**:
- OTA-Update ohne USB möglich
- Version-Check vor Update
- Rollback bei Update-Fehler
- Web-Interface für Firmware-Upload
- Update-Logs für Debugging

**Priority**: P4 – Später (Nice-to-have)

---

### US6: Benutzer-Dokumentation
**As a** Neuer Nutzer  
**I want to** das System in 5 Minuten zum Laufen bringen  
**So that** ich nicht warten muss, um die Ampel zu testen

**Acceptance Criteria**:
- Schnellstart-Anleitung <5 Minuten
- Video-Tutorial (optional)
- Bedienungsanleitung ausführlich
- FAQ mit 10+ häufigen Fragen
- Troubleshooting-Guide
- Deutsche & englische Versionen

**Priority**: P2 – Wichtig (Parallel zu Hardware-Test)

---

### US7: CI/CD Pipeline
**As a** Maintainer  
**I want to** Builds und Tests automatisiert durchführen  
**So that** ich Regressions früh erkenne und Releases schnell machen kann

**Acceptance Criteria**:
- GitHub Actions für PlatformIO Build
- Automatische Unit Tests
- Automatische Binary-Generation
- Releases auf GitHub mit Changelog
- Automatisierte Versioning

**Priority**: P3 – Optional (Nach Phase 2 Core)

---

### US8: Erweiterte Features (FUTURE)
**As a** Power-User  
**I want to** Multi-Controller und erweiterte Modi  
**So that** ich komplexere Rennszenarios unterstützen kann (>4 Spuren, Statistiken, etc.)

**Acceptance Criteria**:
- Multi-D1-Mini Synchronisation
- Netzwerk-Koordination
- Statistik-Export (CSV)
- Optional: Mobile App
- Optional: Home Assistant Integration

**Priority**: P5 – Später (Phase 3+)

---

## Functional Requirements

| ID | Anforderung | Priorität | Us |
|----|------------|-----------|-----|
| FR1 | Hardware-Komponenten verdrahtet & getestet | P1 | US1 |
| FR2 | LED-Ausgaben stabil & zuverlässig | P1 | US1 |
| FR3 | Button-Eingaben mit Debounce | P1 | US1 |
| FR4 | IR-Sensor Integration | P1 | US1 |
| FR5 | RAM-Nutzung <20KB | P2 | US2 |
| FR6 | Flash-Nutzung <300KB | P2 | US2 |
| FR7 | Loop-Cycle <20ms | P2 | US2 |
| FR8 | Watchdog-Timer | P2 | US2 |
| FR9 | Error-Logging | P2 | US2 |
| FR10 | Web-Interface | P3 | US3 |
| FR11 | REST API | P3 | US3 |
| FR12 | WebSocket Echtzeit | P3 | US3 |
| FR13 | EEPROM Config Storage | P3 | US4 |
| FR14 | JSON Config Format | P3 | US4 |
| FR15 | OTA-Updates | P4 | US5 |
| FR16 | Quickstart Guide | P2 | US6 |
| FR17 | Video Tutorial | P2 | US6 |
| FR18 | GitHub Actions | P3 | US7 |
| FR19 | Multi-Controller (Future) | P5 | US8 |

---

## Non-Functional Requirements

| Kategorie | Anforderung | Zielwert |
|-----------|------------|---------|
| **Performance** | Loop-Cycle Zeit | <20ms |
| | Button Response | <50ms |
| | LED Blink Genauigkeit | ±10ms |
| **Speicher** | RAM-Nutzung | <20KB |
| | Flash-Nutzung | <300KB |
| **Zuverlässigkeit** | MTBF (Mean Time Between Failures) | >1000h |
| | Verfügbarkeit | 99.5% |
| **Sicherheit** | Eingabe-Validierung | 100% |
| | Error Handling | Graceful Degradation |
| **Wartbarkeit** | Watchdog-Reset | Auto-Recovery |
| | Update Rollback | Funktional |
| **Benutzerfreundlichkeit** | Setup-Zeit | <15 min |
| | Learning Curve | <5 min |

---

## Architecture

### Komponenten-Schichten

```
┌─────────────────────────────────────┐
│  Web-Interface (Optional, P3)       │
│  REST API + WebSocket               │
└────────────┬────────────────────────┘
             │
┌────────────▼─────────────────────┐
│ Config Management (P3)            │
│ EEPROM + JSON Serialization       │
└────────────┬─────────────────────┘
             │
┌────────────▼──────────────────────────────┐
│ Firmware Core (Phase 1 + Optim P2)        │
│ StateMachine + AmpelController             │
└────────────┬───────────────────────────────┘
             │
┌────────────▼──────────────────────┐
│ HAL (Hardware Abstraction)         │
│ InputHandler + LedController       │
└────────────┬──────────────────────┘
             │
┌────────────▼──────────────────────────────┐
│ Hardware (Validated in Phase 9)           │
│ D1 Mini + LEDs + Buttons + IR-Sensor     │
└───────────────────────────────────────────┘
```

---

## Success Metrics

| Metrik | Zielwert | Messmethode |
|--------|----------|------------|
| Hardware-Zuverlässigkeit | 100% funktionstüchtig | Physical Testing (24h) |
| Speicher-Effizienz | RAM <20KB, Flash <300KB | Memory Profiler |
| Performance | Loop <20ms | Timing Instrumentation |
| Dokumentation Vollständigkeit | 100% | Checklist Review |
| Test Coverage | >80% | gcov Report |
| Build Success Rate | 100% | CI/CD Logs |
| Update Success Rate | 100% | OTA Test |

---

## Risks & Mitigations

| Risiko | Wahrscheinlichkeit | Impact | Mitigation |
|--------|-------------------|--------|-----------|
| Hardware-Kompatibilität | Mittel | Hoch | Extensive Testing in Phase 9 |
| Memory-Overflow | Niedrig | Kritisch | Early Profiling in Phase 10 |
| Timing-Issues | Mittel | Mittel | Interrupt-basiertes Design |
| Web-Server Crashes | Niedrig | Mittel | Watchdog + Graceful Degradation |
| EEPROM Corruption | Niedrig | Mittel | Backup/Versioning System |
| OTA Update Failure | Niedrig | Hoch | Rollback + Validation |

---

## Timeline

| Phase | Dauer | Start | End |
|-------|-------|-------|-----|
| Phase 9 (Hardware) | 8h | Week 1 | Week 2 |
| Phase 10 (Firmware Opt) | 4h | Week 2 | Week 2 |
| Phase 14 (Doku) | 6h | Week 1 | Week 2 |
| Phase 11 (Web) | 16h | Week 3 | Week 4 |
| Phase 12 (Config) | 4h | Week 4 | Week 4 |
| Phase 13 (OTA) | 8h | Week 4 | Week 5 |
| Phase 16 (CI/CD) | 4h | Week 5 | Week 5 |
| Phase 17 (Polish) | 8h | Week 5 | Week 6 |
| **Total** | **~58h** | Week 1 | Week 6 |

---

## Dependencies

- ✓ Phase 1 (MVP Firmware) – COMPLETE
- ✓ Phase 1 Dokumentation (wiring.md) – COMPLETE
- ✓ Phase 1 Tests – COMPLETE
- → Hardware verfügbar für Phase 9 Testing

---

## Out of Scope

- Mobile Native App (nur optional)
- Internationale Sprachunterstützung (vorerst Deutsch)
- Zigbee/BLE Integration (später)
- Custom PCB Design (Breadboard genug)
- Commercial Distribution

---

## Related Documents

- [Phase 2 Plan](./plan.md)
- [Phase 2 Tasks](./tasks.md)
- [Phase 1 Spec](../001-startampel-carrera/spec.md)
- [Hardware Wiring](../../docs/wiring.md)

---

**Version**: 1.0.0  
**Status**: DRAFT  
**Last Updated**: 2026-05-11  
**Author**: Spec Kit Agent
