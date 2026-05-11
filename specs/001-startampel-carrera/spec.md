# Feature Specification: Startampel für Carrera-Bahn

**Feature Branch**: `[001-startampel-carrera]`  
**Created**: 2026-05-11  
**Status**: Draft  
**Input**: User description: "Startampel für Carrera-Bahn\n\nZiel: Eine Startampel mit einzelnen LEDs (rot, gelb, grün) pro Spur, gesteuert von einem D1 Mini (ESP8266) oder ESP32. Die Steuerung erfolgt sowohl per Taster (manuell) als auch direkt per GPIO (z.B. Integration mit externer Bahnsteuerung).\n\nFrühstartsignal: Eine Infrarot-Lichtschranke vor der Pole Position erkennt einen Frühstart und ist als GPIO-Eingang am D1 Mini angebunden.\n\nFirmware: C++ (Arduino Core) ist Standard. MicroPython nur nach expliziter Entscheidung.\n\nSpurenzahl: Standardmäßig 2 Spuren, erweiterbar bis 4.\n\nFunktionen:\n- Startsequenz: 5 rote LEDs werden nacheinander eingeschaltet (Countdown).\n- Startfreigabe: Alle grünen LEDs leuchten.\n- Frühstart: Alle gelben LEDs leuchten, die betroffene rote LED blinkt. Frühstart wird durch Unterbrechung der IR-Schranke erkannt.\n- Pace-Car/Safety-Car: Alle gelben LEDs blinken.\n- Rennunterbrechung/Chaos: Alle roten LEDs blinken.\n- Rennende/Sieger: Alle grünen LEDs blinken, die rote LED der Siegerbahn bleibt an.\n\nHardware:\n- Einzelne LEDs (rot, gelb, grün) pro Spur, frei verdrahtet.\n- Steuerung über D1 Mini (ESP8266) oder ESP32.\n- Taster für manuelle Steuerung.\n- GPIO-Eingänge für externe Steuerung (z.B. von Carrera-Bahn).\n- Infrarot-Lichtschranke für Frühstart-Erkennung (GPIO-Eingang).\n\nBedienung:\n- Taster: Start, Stop, Reset, ggf. Moduswechsel.\n- GPIO: Externe Trigger für Start, Frühstart (IR-Schranke), Safety-Car, etc.\n\nEdge Cases: Gleichzeitige Eingaben, Stromausfall, Reset während Blinkmodus werden explizit getestet und behandelt."

## User Scenarios & Testing *(mandatory)*

### User Story 1 - Startsequenz & Startfreigabe (Priority: P1)

Ein Benutzer startet das Rennen per Taster oder externem GPIO-Trigger. Die Startampel zeigt einen Countdown mit 5 roten LEDs, danach leuchten alle grünen LEDs zur Startfreigabe.

**Why this priority**: Dies ist der Kernprozess für den Rennstart und für alle Nutzer essenziell.

**Independent Test**: Kann getestet werden, indem ein Start ausgelöst wird und die LED-Sequenz korrekt abläuft.

**Acceptance Scenarios**:

1. **Given** das System ist bereit, **When** der Start ausgelöst wird, **Then** leuchten die roten LEDs nacheinander auf und anschließend alle grünen LEDs.
2. **Given** die Startsequenz läuft, **When** ein Reset erfolgt, **Then** wird die Sequenz abgebrochen und alle LEDs gehen aus.

---

### User Story 2 - Frühstart-Erkennung (Priority: P2)

Ein Benutzer löst einen Frühstart aus (z.B. durch zu frühes Losfahren). Die betroffene rote LED blinkt, alle gelben LEDs leuchten.

**Why this priority**: Frühstart-Erkennung ist wichtig für faire Rennen und Regelkonformität.

**Independent Test**: Kann getestet werden, indem ein Frühstart simuliert wird und die LEDs entsprechend reagieren.

**Acceptance Scenarios**:

1. **Given** die Startsequenz läuft, **When** ein Frühstart erkannt wird, **Then** blinkt die rote LED der betroffenen Spur und alle gelben LEDs leuchten.

---

### User Story 3 - Safety-Car/Pace-Car Modus (Priority: P3)

Während des Rennens wird der Safety-Car-Modus aktiviert. Alle gelben LEDs blinken synchron.

**Why this priority**: Safety-Car-Phasen sind für Rennunterbrechungen und Sicherheit relevant.

**Independent Test**: Kann getestet werden, indem der Modus aktiviert wird und alle gelben LEDs blinken.

**Acceptance Scenarios**:

1. **Given** das Rennen läuft, **When** der Safety-Car-Modus aktiviert wird, **Then** blinken alle gelben LEDs synchron.

---

### User Story 4 - Rennunterbrechung/Chaos (Priority: P4)

Bei Rennunterbrechung oder Chaos blinken alle roten LEDs.

**Why this priority**: Klare Signalisierung von Rennunterbrechungen ist für alle Fahrer wichtig.

**Independent Test**: Kann getestet werden, indem der Modus ausgelöst wird und alle roten LEDs blinken.

**Acceptance Scenarios**:

1. **Given** das Rennen läuft, **When** Chaos/Rennunterbrechung ausgelöst wird, **Then** blinken alle roten LEDs.

---

### User Story 5 - Rennende/Siegeranzeige (Priority: P5)

Nach Rennende blinken alle grünen LEDs, die rote LED der Siegerbahn bleibt an.

**Why this priority**: Die Anzeige des Siegers ist für den Abschluss des Rennens relevant.

**Independent Test**: Kann getestet werden, indem das Rennende ausgelöst wird und die LEDs entsprechend anzeigen.

**Acceptance Scenarios**:

1. **Given** das Rennen ist beendet, **When** das Sieger-Event ausgelöst wird, **Then** blinken alle grünen LEDs und die rote LED der Siegerbahn bleibt an.

---

### Edge Cases

- Was passiert bei gleichzeitigem Drücken mehrerer Taster?
- Wie verhält sich das System bei Stromausfall während einer Sequenz?
- Was passiert, wenn ein externer Trigger und ein Taster gleichzeitig ausgelöst werden?
- Wie wird ein Reset während eines Blinkmodus behandelt?

## Requirements *(mandatory)*

1. Das System muss eine Startampel mit einzelnen LEDs (rot, gelb, grün) pro Spur unterstützen.
2. Die Steuerung muss sowohl per Taster als auch per GPIO-Eingang möglich sein.
3. Die Startsequenz muss einen Countdown mit 5 roten LEDs anzeigen.
4. Nach dem Countdown müssen alle grünen LEDs leuchten (Startfreigabe).
5. Bei Frühstart muss die betroffene rote LED blinken und alle gelben LEDs leuchten.
6. Im Safety-Car/Pace-Car-Modus müssen alle gelben LEDs blinken.
7. Bei Rennunterbrechung/Chaos müssen alle roten LEDs blinken.
8. Nach Rennende müssen alle grünen LEDs blinken, die rote LED der Siegerbahn bleibt an.
9. Das System muss auf gleichzeitige Eingaben (Taster/GPIO) robust reagieren.
10. Ein Reset muss jederzeit alle laufenden Sequenzen/Modi abbrechen und LEDs ausschalten.

## Success Criteria *(mandatory)*

- Nutzer können das Rennen zuverlässig per Taster oder externem Trigger starten.
- Die LED-Anzeigen entsprechen in allen Modi exakt den beschriebenen Abläufen.
- Frühstart, Safety-Car, Chaos und Rennende werden korrekt signalisiert.
- Das System reagiert robust auf gleichzeitige oder fehlerhafte Eingaben.
- Alle Funktionen sind unabhängig testbar und dokumentiert.

## Assumptions

- Es werden Standard-LEDs verwendet, keine speziellen LED-Module.
- Die Anzahl der Spuren ist konfigurierbar (Standard: 2).
- Die Steuerung erfolgt über einen D1 Mini (ESP8266) oder ESP32.
- Die externe Bahnsteuerung liefert saubere GPIO-Signale.
- Die Stromversorgung ist ausreichend dimensioniert.

## Key Entities

- Spur (Lane)
- LED (rot, gelb, grün)
- Taster (Button)
- GPIO-Trigger
- Modus (Start, Frühstart, Safety-Car, Chaos, Rennende)

---

[End of specification]
