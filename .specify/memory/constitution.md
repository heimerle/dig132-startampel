
# Startampel Project Constitution

## Core Principles

### I. Test-First (NON-NEGOTIABLE)
Alle Logikfunktionen und Zustandsautomaten müssen durch Unit- und Integrationstests abgedeckt werden. Red-Green-Refactor-Zyklus ist Pflicht.

### II. Simplicity & Robustness
Die Implementierung muss so einfach wie möglich gehalten werden. Keine unnötige Komplexität. Fehlerfälle (z.B. gleichzeitige Eingaben, Stromausfall) müssen robust behandelt werden.

### III. Embedded Focus
Alle Komponenten müssen für Embedded-Umgebungen (ESP32/D1 Mini) optimiert sein. Ressourcenverbrauch und Reaktionszeit sind kritisch.

### IV. Review & Traceability
Jede Änderung muss per Review geprüft werden. Jede Anforderung muss auf mindestens eine Task und einen Test rückverfolgbar sein.

### V. Documentation
Schaltplan, Pinbelegung und Bedienung müssen dokumentiert und versioniert werden.

## Additional Constraints

- C++ (Arduino Core) ist Standard, MicroPython nur nach expliziter Entscheidung.
- Pinbelegung und Spurenzahl müssen vor Implementierung finalisiert werden.
- Alle Tasks und Tests müssen im tasks.md dokumentiert sein.

## Development Workflow

- Vor jeder Implementierung: Tests schreiben, Review einholen.
- Nach jedem Commit: Tests ausführen, Ergebnisse dokumentieren.
- Änderungen an der Architektur oder Pinbelegung nur nach Review und Update der Dokumentation.

## Governance

Diese Constitution ist verbindlich für alle Projektbeteiligten. Änderungen bedürfen eines dokumentierten Reviews und einer neuen Versionierung.

**Version**: 1.0.0 | **Ratified**: 2026-05-11 | **Last Amended**: 2026-05-11
