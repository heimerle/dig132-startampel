---
description: "Phase 2 Implementation Plan: Production Readiness & Extensions"
---

# Phase 2 Implementation Plan: Startampel Produktivierung & Erweiterungen

**Branch**: `002-production-ready` | **Date**: 2026-05-11  
**Previous Phase**: [Phase 1 Completed](./001-startampel-carrera/tasks.md)

## Summary

Nach erfolgreicher Implementierung der MVP-Features (Phase 1) folgt nun die Produktivierung und Optimierung:
- Hardware-Testing und Stabilisierung
- Firmware-Optimierung (Performance, Memory)
- Web-Interface für erweiterte Steuerung
- Persistente Konfiguration
- OTA-Updates (Over-the-Air)
- Erweiterte Fehlerbehandlung
- Logging & Monitoring

## Phase 2a: Hardware-Integration & Testing (Priorität: P1)

**Ziel**: Firmware auf echter Hardware (D1 Mini) testen und optimieren

### Komponenten
- Physische Verdrahtung nach wiring.md
- Hardware-Test-Suite
- Pin-Funktionalität validieren
- Performance-Messungen

### Dokumentation
- [x] Hardware-Schaltplan (docs/wiring.md)
- [ ] Verdrahtungs-Installationsanleitung
- [ ] Hardware-Troubleshooting-Guide
- [ ] Performance-Baseline-Messungen

### Bekannte Anforderungen
- Reaktionszeit <50ms auf Eingaben
- Stabiles LED-Blinken ohne Flackern
- Debounce-Delay 30ms für Taster
- IR-Sensor Zuverlässigkeit

---

## Phase 2b: Firmware-Optimierung (Priorität: P2)

**Ziel**: Memory, Performance, Stabilitätsverbesserung

### Code-Optimierungen
- Speicher-Profiling (RAM/Flash)
- Loop-Timing Optimierung
- Interrupt-Handling statt Polling
- Blinking-Genauigkeit erhöhen

### Fehlerbehandlung
- Watchdog-Timer implementieren
- Graceful Degradation bei Fehlerfall
- Error-Logging in EEPROM
- Factory-Reset Mechanismus

---

## Phase 2c: Web-Interface (Priorität: P3)

**Ziel**: Webbasierte Steuerung & Status-Anzeige (optional, für erweiterte Szenarien)

### Komponenten
- ESPAsyncWebServer Integration
- REST-API für Modi-Steuerung
- WebSocket für Echtzeit-Status
- HTML Dashboard (responsive)
- JSON-Konfiguration

### Features
- Start/Stop/Reset per Web-Button
- Modus-Auswahl (Start, FalseStart, SafetyCar, etc.)
- LED-Status Live-Anzeige
- Log-Viewer
- Statistiken (Anzahl Starts, etc.)

---

## Phase 2d: Persistente Konfiguration (Priorität: P3)

**Ziel**: Konfiguration auf D1 Mini speichern

### Features
- EEPROM-basierte Konfiguration
- JSON-Format für Settings
- Backup/Restore Funktion
- Migrations-Support für Firmware-Updates

### Konfigurierbare Parameter
- Anzahl der Spuren (2-4)
- LED-Timing (Sequenz-Dauer, Blink-Intervall)
- Button-Empfindlichkeit
- IR-Sensor Kalibrierung
- Debug-Level

---

## Phase 2e: OTA-Updates (Priorität: P4)

**Ziel**: Firmware-Updates über WLAN ohne physischen USB-Zugriff

### Komponenten
- ArduinoOTA Integration
- Web-based Firmware-Upload
- Version-Management
- Rollback-Mechanismus

---

## Phase 2f: Benutzer-Dokumentation (Priorität: P2)

**Ziel**: Endbenutzer-freundliche Anleitung

### Dokumente
- Schnellstart-Anleitung (5 Minuten)
- Bedienungsanleitung (detailliert)
- Troubleshooting-Guide
- FAQ
- Video-Tutorials (optional)

---

## Phase 2g: Erweiterte Features (Priorität: P5)

**Ziel**: Optionale Features für Advanced Users

### Features
- Multi-Controller (mehrere D1 Minis für >4 Spuren)
- Netzwerk-Synchronisation
- Mobile App (optional)
- Statistik-Export (CSV)
- Custom-Sound (Buzzer optional)
- Fernsteuerung (IR/RF)

---

## Phase 2h: CI/CD & Release (Priorität: P3)

**Ziel**: Automatisierte Tests und Releases

### Setup
- GitHub Actions für PlatformIO Build
- Automatische Binary-Generation
- Releases auf GitHub
- Changelog Auto-Generation

---

## Tech Stack für Phase 2

| Komponente | Technologie | Status |
|-----------|-------------|--------|
| Web-Server | ESPAsyncWebServer | Optional |
| Persistierung | EEPROM/LittleFS | Geplant |
| OTA-Updates | ArduinoOTA | Geplant |
| API | REST + WebSocket | Optional |
| Frontend | HTML5/CSS3/JS | Optional |
| CI/CD | GitHub Actions | Geplant |
| Docs | Markdown + HTML | In Progress |

---

## Komplexität & Justification

| Feature | Komplexität | Warum Nötig | Alternativen |
|---------|------------|-----------|-------------|
| Web-Interface | Mittel | Erweiterte Nutzung | USB-CLI statt Web |
| OTA-Updates | Mittel | Remote-Verwaltung | Manueller USB-Upload |
| Persistierung | Niedrig | Config-Speicherung | Hardcoded (nicht ideal) |
| Fehlerbehandlung | Mittel | Stabilität | Einfaches Reboot |
| Watchdog | Niedrig | Zuverlässigkeit | Ohne (akzeptabel für Hobby) |

---

## Success Criteria Phase 2

- [x] Alle Phase-1-Tasks abgeschlossen
- [ ] Hardware erfolgreich getestet & funktionsfähig
- [ ] Firmware auf echter Hardware stabil (24h Dauerbetrieb)
- [ ] Benutzer-Dokumentation vollständig
- [ ] Optional: Web-Interface funktionsfähig
- [ ] Optional: OTA-Updates funktioniert

---

## Abhängigkeiten & Reihenfolge

```
Phase 2a (Hardware-Test) [BLOCKER]
    ↓
Phase 2b (Firmware-Opt)
    ↓
Phase 2c (Web-IF) [Optional, parallel]
    ↓
Phase 2d (Config) [Optional]
    ↓
Phase 2e (OTA) [Optional]
    ↓
Phase 2f (Doku) [Parallel ab Phase 2a]
    ↓
Phase 2g (Features) [Optional, später]
    ↓
Phase 2h (CI/CD) [Abschließend]
```

---

## Ressourcen-Schätzung

| Phase | Aufwand | Priorität | Status |
|-------|---------|-----------|--------|
| 2a | 8h | P1 | Geplant |
| 2b | 4h | P2 | Geplant |
| 2c | 16h | P3 | Optional |
| 2d | 4h | P3 | Optional |
| 2e | 8h | P4 | Optional |
| 2f | 8h | P2 | In Progress |
| 2g | 20h | P5 | Later |
| 2h | 4h | P3 | Planned |

**Total Phase 2: 60-72h (mit Optionals)**  
**Essenziel (P1+P2): 20h**

---

## Nächste Schritte

1. **Phase 2a starten:** Hardware-Test durchführen
2. **Phase 2f fortsetzen:** Benutzer-Dokumentation schreiben
3. **Phase 2b:** Firmware-Optimierung basierend auf realen Tests
4. **Später:** Optional Phase 2c/2d/2e

---

## Verwandte Dokumentation

- [Phase 1 Plan](./001-startampel-carrera/plan.md)
- [Phase 1 Tasks](./001-startampel-carrera/tasks.md)
- [Hardware Wiring](../docs/wiring.md)
- [Benutzer-Dokumentation](../docs/EINKAUFSLISTE.md)

---

**Version**: 2.0.0 Draft  
**Created**: 2026-05-11  
**Status**: Planning
