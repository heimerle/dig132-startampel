# 📖 Bedienungsanleitung: Startampel für Carrera-Bahn

**Version**: 2.0.0  
**Zielgruppe**: Rennfahrer, Veranstalter  
**Sprache**: Deutsch

---

## Inhaltsverzeichnis

1. [System-Übersicht](#system-übersicht)
2. [Bedienelemente](#bedienelemente)
3. [Rennmodi](#rennmodi)
4. [Praktische Szenarien](#praktische-szenarien)
5. [Wartung & Kalibrierung](#wartung--kalibrierung)
6. [FAQ](#faq)

---

## System-Übersicht

### Was macht die Startampel?

Die **Startampel** ist ein Steuergerät für Carrera-Bahnen mit automatischer Rennmanagement:

- 🟥 **Rote LED**: Countdown (Vorbereitung) oder Sieger-Anzeige
- 🟨 **Gelbe LED**: Frühstart oder Safety-Car
- 🟩 **Grüne LED**: Startfreigabe (Rennen läuft)

**Pro Spur einzelne LEDs** - ideal für 2-4 spurige Rennstrecken.

### Komponenten

```
┌─────────────────────────────┐
│  D1 Mini (Microcontroller)  │ ← Gehirn
├─────────────────────────────┤
│  LEDs (rot/gelb/grün)       │ ← Sichtbare Signale
│  Taster (Start/Stop/Reset)  │ ← Manuelle Steuerung
│  IR-Sensor (optional)       │ ← Frühstart-Erkennung
└─────────────────────────────┘
         │
    Breadboard oder Gehäuse
         │
      5V USB Stromversorgung
```

---

## Bedienelemente

### Taster (Buttons)

| Button | Pin | Funktion | Aktion |
|--------|-----|----------|--------|
| **START** | D7 | Rennen starten | Löst Countdown aus, dann Freigabe |
| **STOP** | D8 | Rennen pausieren | (Optional: Nicht implementiert in Phase 1) |
| **RESET** | RX | Alles abbrechen | Schaltet sofort in IDLE-Modus |
| **MODE** | TX | Moduswechsel | (Optional: In Phase 2 geplant) |

**Hinweis**: Debounce 30ms - Taster müssen 30ms gedrückt bleiben, um erkannt zu werden.

### LED-Anzeigen

#### Pro Spur (Standard: 2 Spuren)

| LED Farbe | Normal | Frühstart | Safety-Car | Chaos | Rennende |
|-----------|--------|-----------|-----------|-------|----------|
| 🔴 Rot | Aus | **Blinkt** | Aus | **Blinkt** | **Steady** (Sieger) |
| 🟡 Gelb | Aus | **Steady** | **Blinkt** | Aus | Aus |
| 🟢 Grün | Aus | Aus | Aus | Aus | **Blinkt** |

**Blink-Timing**: 250ms an, 250ms aus = 4 Blinke/Sekunde (klare Sichtbarkeit)

---

## Rennmodi

### 1️⃣ IDLE-Modus (Wartebereitschaft)

**Status**: Alle LEDs aus, System bereit

**Auslöser**: System startet in diesem Modus, oder nach RESET

**Übergang**: START-Button → STARTSEQUENZ

```
IDLE
 ↓
START gedrückt
 ↓
STARTSEQUENZ
```

---

### 2️⃣ STARTSEQUENZ (Countdown)

**Visual**: Rote LED blinkt 5x (je 500ms) = Countdown von 5 → 1

**Audio**: (Optional: Buzzer möglich)

**Timing**:
- Schritt 1: Rot an 500ms
- Schritt 2: Rot an 500ms
- Schritt 3: Rot an 500ms
- Schritt 4: Rot an 500ms
- Schritt 5: Rot an 500ms
- → Dann STARTFREIGABE

**Optionen während Countdown**:
- ✅ **Reset**: Sequenz abbrechen → IDLE
- ❌ **Frühstart**: Auslöst FRUEHSTART-Modus

```
STARTSEQUENZ (Countdown 5x rot)
 ├─→ Fertig
 │   ↓
 │   STARTFREIGABE (Grün steady)
 │
 └─→ Frühstart erkannt
     ↓
     FRUEHSTART (Gelb steady + Rot blink)
```

---

### 3️⃣ STARTFREIGABE (Rennen läuft)

**Visual**: Alle grünen LEDs leuchten STEADY

**Bedeutung**: "Los!" - Rennen hat begonnen

**Dauer**: Bis ein Event ausgelöst wird (Frühstart, Chaos, Rennende, etc.)

**Mögliche Übergänge**:
- **Frühstart erkannt** → FRUEHSTART
- **Safety-Car ausgelöst** → SAFETYCAR
- **Rennunterbrechung** → CHAOS
- **Rennende** → RENNENDE

---

### 4️⃣ FRUEHSTART (False Start)

**Visual**: 
- 🟡 Alle gelben LEDs leuchten STEADY
- 🔴 Betroffene rote LED blinkt (250ms on/off)

**Auslöser**:
- IR-Schranke unterbrochen während STARTSEQUENZ
- Oder: Frühstart-Button gedrückt
- Nur während STARTSEQUENZ gültig

**Bedeutung**: Fahrer der betroffenen Spur hat zu früh losgefahren

**Rückkehr**: 
- RESET → IDLE
- Neuer START für neuen Versuch

**Szenario**:
```
"Spur 1 Fahrer zieht zu früh los während Countdown"
                ↓
Fahrer fährt IR-Schranke
                ↓
FRUEHSTART ausgelöst:
- Gelb an (alle Spuren)
- Spur 1 Rot blinkt
                ↓
Reset drücken → Neuer Versuch
```

---

### 5️⃣ SAFETYCAR (Pace Car Phase)

**Visual**: Alle gelben LEDs blinken synchron (250ms on/off)

**Bedeutung**: Rennen unterbrochen, Safety-Car ist aktiv, Fahrer fahren langsam hintereinander

**Auslöser**: 
- Safety-Car Button
- Oder: Externe GPIO Trigger

**Rückkehr**:
- Neue STARTSEQUENZ für Restart
- Oder: RESET → IDLE

---

### 6️⃣ CHAOS (Rennunterbrechung)

**Visual**: Alle roten LEDs blinken synchron (250ms on/off)

**Bedeutung**: Rennunterbrechung, Fahrer müssen anhalten, es gibt ein Problem

**Auslöser**:
- Chaos-Button
- Oder: Externe GPIO Trigger (z.B. Kollisionssensor)

**Rückkehr**:
- RESET → IDLE (klare Situation)
- Oder: Neue STARTSEQUENZ

---

### 7️⃣ RENNENDE (Zieleinlauf)

**Visual**:
- 🟢 Alle grünen LEDs blinken (250ms on/off)
- 🔴 Rote LED des Siegers bleibt STEADY an

**Bedeutung**: Rennen beendet, Sieger bekannt

**Auslöser**:
- Rennende-Button
- Oder: Externe GPIO Trigger (z.B. Zielschranke)

**Parameter**: 
- Lane/Spur des Siegers (1-4)

**Dauer**: Bis RESET

**Beispiel**:
```
"Spur 2 Fahrer überquert Zielschranke"
                ↓
RENNENDE ausgelöst:
- Alle grünen LEDs blinken
- Spur 2 rote LED bleibt AN
                ↓
Sieger bekannt! 🏆
```

---

## Praktische Szenarien

### Szenario 1: Einzelrennen (1 Runde)

**Ziel**: Ein sauberes Rennen fahren

**Schritte**:
1. Fahrer auf den Startpositionen bereit
2. Durchsage: "Achtung, bereit..."
3. **START-Button drücken**
   - Countdown: Rot blinkt 5x
4. Nach Countdown: Grün blinkt = LOS!
5. Fahrer fahren, erste Zielschranke gewinnt
6. **RENNENDE-Button** (mit Spur des Gewinners)
   - Grün blinkt + Sieger-rot steady
7. Gratulation zum Sieger! 🎉
8. **RESET** für nächstes Rennen

**Dauer**: ~3 Sekunden bis zum Start

---

### Szenario 2: Frühstart Straße

**Ziel**: Fair rennende Fahrer bestrafen

**Ablauf**:
1. **START-Button** → Countdown läuft
2. **Spur 1 Fahrer zieht zu früh los**
   - IR-Schranke registriert Bewegung
3. **System erkennt Frühstart**:
   - Gelbe LEDs an (Warnung!)
   - Spur 1 rote LED blinkt (Fahrer identifiziert)
4. **Strafe anwenden**:
   - Spur 1 muss stoppen/zurück
   - Andere Spuren weiterfahren (optional)
5. **Neuer Start oder RESET**

**Timing**: Frühstart nur während Countdown gültig

---

### Szenario 3: Safety-Car Intervention

**Ziel**: Rennen sicher unterbrechen (Unfall, Behinderung)

**Ablauf**:
1. Rennen läuft (grüne LEDs)
2. **Unfall auf der Bahn erkannt**
3. **SAFETY-CAR Button drücken** (oder externe GPIO)
   - Alle gelben LEDs blinken
   - Fahrer fahren langsam hintereinander
4. **Nach Sicherung der Situation**:
   - **Neue STARTSEQUENZ** für Restart
   - Oder: **RESET** für vollständigen Neustart

---

### Szenario 4: Rennen abbrechen (Chaos)

**Ziel**: Alles stoppen, Problem bearbeiten

**Ablauf**:
1. Rennen läuft oder in einem Modus
2. **Rennen abbrechen erforderlich** (Stromausfall, Unfall, Regelverstoß)
3. **CHAOS-Button drücken** (oder externe GPIO)
   - Alle roten LEDs blinken
   - Fahrer wissen: STOP!
4. **Nach Problem-Behebung**:
   - **RESET** → IDLE
   - Dann neuer Start möglich

---

## Wartung & Kalibrierung

### Tägliche Kontrolle (vor dem Fahren)

- ✅ **LED-Funktionstest**: LEDs aufblinken beim Start?
- ✅ **Button-Test**: Alle Buttons funktionieren?
- ✅ **IR-Sensor-Test** (falls vorhanden): Schranke funktioniert?
- ✅ **Stromversorgung**: D1 Mini mit Strom versorgt?

### Wöchentliche Wartung

- 🔧 LEDs prüfen auf Beschädigungen (Kratzer, defekte)
- 🔧 Verdrahtung auf Locker prüfen (vibrieren)
- 🔧 Taster auf korrekten Sitz prüfen

### IR-Sensor Kalibrierung (falls installiert)

```bash
1. IR-Sensor bei Ruhe messen (kein Objekt in Schranke)
2. Sollwert: IR-Ausgabe ~LOW (oder ~HIGH, je nach Typ)
3. Mit Objekt in Schranke: Ausgabe wechselt
4. Bei Problemen: Sensor ausrichten oder Sensibilität in config.h anpassen
```

### Fehlerhafte LEDs austauschen

**Wenn eine LED nicht funktioniert:**

1. D1 Mini ausschalten (USB trennen)
2. LED überprüfen: Korrekte Polarität? (+/- richtig?)
3. LED oder Widerstand prüfen (Durchgangsprüfer)
4. Bei Defekt: Neue LED einlöten
5. Test durchführen

---

## FAQ

### F: Was ist, wenn ich während der Startsequenz RESET drücke?

**A:** Die Sequenz wird sofort abgebrochen, alle LEDs gehen aus, System zurück zu IDLE.

### F: Kann ich zwei LEDs gleichzeitig verschiedene Farben zeigen?

**A:** Nein, pro Spur gibt es nur 3 LEDs. Es ist aber möglich, beispielsweise Rot UND Grün zusammen zu blinken (erfolgt sequenziell, wahrnehmbar als Farbwechsel).

### F: Was ist die minimale Reaktionszeit auf einen Button-Druck?

**A:** ~50ms (schnell genug für menschliche Wahrnehmung).

### F: Kann ich die Countdown-Dauer anpassen?

**A:** Ja, in `src/config.h` Konstante `SEQ_STEP_DURATION` von 500ms ändern.

### F: Funktioniert die Ampel auch offline (ohne WLAN)?

**A:** Ja, Phase 1 braucht kein WLAN. Phase 2 (optional) bietet Web-Interface mit WLAN.

### F: Wie viele Spuren können maximal angesteuert werden?

**A:** Phase 1: 2 Spuren (fest). Phase 2: erweiterbar auf 4 mit Konfig-Änderung.

### F: Was passiert bei Stromausfall?

**A:** Alle LEDs gehen aus, D1 Mini startet neu (AUTO-RESET). System ist dann wieder in IDLE.

### F: Kann ich eigene Button-Funktionen programmieren?

**A:** Ja, siehe `src/state_machine.cpp` - neue Modi sind hinzufügbar.

### F: Unterstützt die Ampel externe Trigger?

**A:** Ja, über GPIO Pins (A0, D0). Details: siehe [README.md](../README.md).

---

## Kontakt & Support

- **Bug-Report**: [GitHub Issues](https://github.com/heimerle/dig132-startampel/issues)
- **Frage?**: Diskussionen im [GitHub Projekt](https://github.com/heimerle/dig132-startampel)
- **Dokumentation**: [README.md](../README.md), [Wiring Guide](./wiring.md)

---

**Version**: 2.0.0 | **Datum**: 2026-05-11  
**Autorin**: Spec Kit Agent | **Sprache**: Deutsch  
**Letzte Änderung**: 2026-05-11

*Viel Erfolg mit deiner Carrera-Startampel! 🏎️🚦*
