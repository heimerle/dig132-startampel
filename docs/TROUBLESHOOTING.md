# 🔧 Troubleshooting Guide: Startampel Fehlerbehandlung

**Version**: 2.0.0  
**Zielgruppe**: Alle Nutzer (Anfänger bis Fortgeschrittene)  
**Update**: 2026-05-11

---

## Quick Diagnosis

**Symptom schnell eingeben und Lösung finden:**

| Symptom | Erste Hilfe | Details |
|---------|-------------|---------|
| 🔴 **Keine Reaktion** | USB trennen, 10s warten, neu verbinden | [→ Power-Probleme](#power-und-verbindung) |
| 🟡 **Eine LED leuchtet nicht** | LED-Kabel prüfen, Polarität? | [→ LED-Defekte](#led-defekte) |
| 🟢 **Button funktioniert nicht** | Button-Verkabelung prüfen | [→ Button-Probleme](#button-probleme) |
| 🔵 **IR-Sensor reagiert nicht** | Sensor ausrichten, Kalibrierung | [→ IR-Sensor-Fehler](#ir-sensor-fehler) |
| ⚡ **Firmware lässt sich nicht uploaden** | COM-Port, Treiber, Reset | [→ Upload-Fehler](#upload-fehler) |

---

## Kategorized Troubleshooting

### Power und Verbindung

#### Problem: Keine Reaktion, keine LED aktiv

**Symptom**: D1 Mini reagiert gar nicht, kein Selbsttest

**Mögliche Ursachen**:
1. ❌ USB-Kabel nicht verbunden
2. ❌ USB-Kabel defekt (kein Daten-Kabel, nur Laden)
3. ❌ USB-Port am Laptop defekt
4. ❌ USB-Treiber nicht installiert
5. ❌ Falsche Firmware auf D1 Mini

**Lösungsschritte** (in dieser Reihenfolge):

**Schritt 1: Physikalisch prüfen**
```bash
□ USB-Kabel vom D1 Mini trennen
□ 10 Sekunden warten
□ Anderes USB-Kabel versuchen (mit Daten-Funktionalität!)
□ Zu anderes Laptop-Port verbinden
```

**Schritt 2: LED-Indikator prüfen**
```bash
□ Blaue LED auf D1 Mini sollte leuchten (falls verbunden)
□ Falls KEINE LED: Kabel defekt oder D1 Mini defekt → Austausch
□ Falls LED leuchtet: → Weiter Schritt 3
```

**Schritt 3: USB-Treiber**
```bash
□ Windows: "Device Manager" → CH340 Driver (Arduino-kompatibel)
□ macOS: Meist automatisch erkannt
□ Linux: sudo apt install ch340 (oder equivalend)
□ Nach Installation: Neu starten und USB neu verbinden
```

**Schritt 4: Firmware-Check**
```bash
□ PlatformIO: "platformio device list" ausführen
□ COM-Port sollte sichtbar sein
□ Falls nicht sichtbar: Treiber erneut prüfen (Schritt 3)
□ Falls sichtbar: → Firmware re-upload (Schritt 5)
```

**Schritt 5: Firmware neu uploaden**
```bash
□ Verbindung trennen
□ "Reset" Button auf D1 Mini drücken (2-3 Sekunden)
□ Sofort USB wieder verbinden
□ In PlatformIO: "Upload" Button
□ Warten bis "Successfully uploaded"
```

**✓ Wenn danach noch keine Reaktion:** D1 Mini ist wahrscheinlich defekt → Austausch nötig

---

#### Problem: D1 Mini wird erkannt, aber Firmware funktioniert nicht

**Symptom**: USB-Verbindung OK, aber LEDs reagieren nicht

**Lösungsschritte**:

1. **Serial Monitor öffnen** (Debugging):
```bash
# In PlatformIO:
platformio device monitor --port /dev/ttyUSB0 --baud 115200

# Sollte sehen:
# "System started..."
# "Waiting for input..."
# Etc.
```

2. **Wenn Serial Monitor nichts zeigt**:
```bash
□ Reset Button drücken
□ Serial Monitor sollte Startup-Messages zeigen
□ Falls nicht: Baud-Rate auf 115200 prüfen
```

3. **Wenn Serial Monitor Output zeigt, aber LEDs nicht reagieren**:
```bash
□ → LED-Fehler Problem (siehe unten)
```

---

### LED-Defekte

#### Problem: Eine oder mehrere LEDs leuchten nicht

**Szenario 1: Nur eine LED defekt (z.B. Spur 1 Rot)**

**Diagnose**:
```
1. Andere LEDs funktionieren → Problem ist diese spezifische LED
2. Prüfe Verdrahtung gegen wiring.md
```

**Lösungsschritte**:

**Schritt 1: Kabel prüfen**
```bash
□ LED-Kabel auf Lötstellen prüfen (Kaltstelle?)
□ Kabel mit Augen inspizieren auf Bruch
□ Mit Multimeter: Durchgangsprüfung (Ohm-Modus)
  - Ohne Strom durchmessen!
  - Sollte Durchgang zeigen (piepton)
□ Falls kein Durchgang: Kabel defekt → Neues Kabel
```

**Schritt 2: LED selbst prüfen**
```bash
□ LED-Polarität prüfen:
  - Längeres Bein (Anode) = +
  - Kürzeres Bein (Kathode) = -
  - Falsch gepolt? → Umdrehen
□ LED mit Durchgangsprüfer:
  - Sollte bei richtiger Polarität "durchgängig" zeigen
□ Mit Batterie-Test (3V):
  - + an lange Bein, - an kurze
  - LED sollte schwach leuchten
  - Nicht leuchten? → LED defekt
```

**Schritt 3: Widerstand prüfen**
```bash
□ Vorwiderstand (220Ω-470Ω) durchmessen
□ Sollte Durchgang zeigen
□ Kein Durchgang? → Widerstand defekt oder falsch gepolt
```

**Schritt 4: D1 Mini Pin prüfen**
```bash
□ In src/config.h: Pin-Nummer überprüfen
□ Beispiel: #define LED1_RED D1
□ D1 physikalisch auf D1 Mini? (Ja, auf Board gekennzeichnet)
□ Mit Multimeter: Pin gegen GND durchmessen
  - Sollte bei LED An: ~0Ω (GND-Connection)
  - Bei LED Aus: ∞Ω (keine Connection)
□ Immer ∞Ω? → Pin ist defekt oder nicht richtig angesteuert
```

**Repair Option 1: LED austauschen**
```bash
□ Alte LED auslöten (mit Lötkolben)
□ Neue LED gleicher Farbe & Helligkeit einlöten
□ Test durchführen
```

**Repair Option 2: Widerstand austauschen**
```bash
□ Alten Widerstand auslöten
□ Neuen 220Ω-470Ω Widerstand einlöten
□ Test durchführen
```

**Repair Option 3: Kompletter Schaltkreis umverdrahten**
```bash
□ Falls keine der oben zu finden: Auf Breadboard neu verdrahten
□ LED-Bein → Widerstand → D1 Mini Pin
□ Widerstand anderes Ende → GND
□ Test durchführen
```

---

#### Problem: Alle LEDs leuchten permanent oder unkontrolliert

**Symptom**: LEDs leuchten ständig, schalten nicht aus

**Ursache**: Wahrscheinlich Firmware-Bug oder Verdrahtungs-Kurschluss

**Lösungsschritte**:

**Schritt 1: Strom trennen**
```bash
□ USB sofort trennen (kann Hardware beschädigen)
□ 10 Sekunden warten
□ Langsam wieder anschließen
```

**Schritt 2: Firmware-Bug ausschließen**
```bash
□ Firmware neu uploaden:
  platformio run -e d1_mini -t upload
□ System neu starten (Reset Button)
□ Wenn Problem weg → War Firmware-Bug (gelöst)
```

**Schritt 3: Kurschluss überprüfen**
```bash
□ Visual Inspection:
  - LEDs und Kabel auf Beschädigungen
  - Besonders: Gelötete Stellen
  - Zwei Leitungen berühren sich?
□ Mit Multimeter (Ohm-Modus, kein Strom!):
  - GND gegen +5V messen
  - Sollte unendlich (∞) sein
  - Weniger? → Kurschluss vorhanden
□ Kurschluss localisieren:
  - Systematisch: Pin-Gruppe trennen
  - Gemäss wiring.md eine Spur deaktivieren
  - Wenn Problem weg → Spur war Kurschluss-Quelle
```

**Schritt 4: Problematische Spur reparieren**
```bash
□ Kurzsschluss-Stelle inspizieren
□ Beschädigte Leitungen trennen und neu isolieren
□ Falls gelötet: Lötstelle überarbeiten
□ Oder: Ganze Spur neu auf Breadboard verdrahten
```

---

### Button-Probleme

#### Problem: Button wird nicht erkannt

**Symptom**: Button drücken hat keine Wirkung

**Ursache**: Verdrahtung, Kontakt, oder Debounce-Timing

**Lösungsschritte**:

**Schritt 1: Button-Verdrahtung prüfen**
```bash
□ Gemäss wiring.md:
  - Button Bein 1 → D7 (oder D8, RX, TX)
  - Button Bein 2 → GND
  - Pull-up Widerstand (10kΩ) von D7 zu +5V
□ Alle Verbindungen prüfen (Locker?)
□ Mit Multimeter:
  - Button unpressed: D7 gegen GND = 5V (Plus)
  - Button pressed: D7 gegen GND = 0V (Ground)
□ Nicht so? → Verdrahtung falsch
```

**Schritt 2: Pull-up Widerstand überprüfen**
```bash
□ Widerstand vorhanden? (10kΩ von Pin zu +5V)
□ Falls nicht: Hinzufügen (kritisch!)
□ Widerstand mit Multimeter durchmessen
□ Sollte ~10kΩ zeigen
□ Nicht? → Widerstand austauschen
```

**Schritt 3: Button selbst testen**
```bash
□ Mit Durchgangsprüfer (Multimeter Ohm-Modus):
  - Button pressed: Durchgang (piepton)
  - Button released: Keine Durchgang
□ Immer Durchgang? → Button steckt fest oder defekt
□ Nie Durchgang? → Button-Kontakt abgerissen
□ → Button austauschen
```

**Schritt 4: Debounce-Timing**
```bash
□ Button muss 30ms gedrückt bleiben
□ Sehr kurzes Drücken (<30ms) wird nicht erkannt
□ Probieren: Button 1 Sekunde drücken
□ Falls funktioniert: War zu schnell
□ Falls nicht funktioniert: → Andere Schritte
```

**Schritt 5: Config und Code überprüfen**
```bash
□ src/config.h:
  #define START_BUTTON D7  // Ist das der richtige Pin?
□ src/input_handler.cpp:
  - Ist der Button in der Update-Funktion enthalten?
  - Wird der Pin als INPUT_PULLUP initialisiert?
□ Falls falsch: Korrigieren und neu uploaden
```

**Schritt 6: Bouncen? Längere Debounce Zeit**
```bash
□ Button drücken verursacht flackernde Ausgabe?
□ In src/config.h: DEBOUNCE_DELAY erhöhen
  #define DEBOUNCE_DELAY 50  // Statt 30
□ Neu uploaden und testen
```

---

### IR-Sensor-Fehler

#### Problem: IR-Sensor reagiert nicht / Frühstart wird nicht erkannt

**Symptom**: Schranke unterbrechen hat keine Wirkung, kein Frühstart-Signal

**Ursache**: Sensor nicht funktioniert, falsche Polarität, Ausrichtung

**Lösungsschritte**:

**Schritt 1: Sensor selbst überprüfen**
```bash
□ Sensor Typ bestimmen:
  - Reflex-Schranke (gibt selbst Licht ab)
  - Durchgangs-Schranke (Sender + Empfänger getrennt)
□ Batterie/Stromversorgung überprüfen
□ Mit Durchgangsprüfer:
  - Signal-Pin gegen GND messen
  - Sollte verändern, wenn unterbrochen
□ Falls nicht verändern: Sensor defekt
```

**Schritt 2: Verkabelung überprüfen**
```bash
□ Sensor Polarität:
  - VCC (Rot) → +5V
  - GND (Schwarz) → GND
  - OUT/Signal (Gelb) → D0 (oder A0)
□ Alle Verbindungen stabil?
□ Mit Multimeter: OUT gegen GND messen
  - Sollte zwischen 0V und 5V wechseln
□ Immer 0V oder immer 5V? → Verkabelung falsch oder Sensor defekt
```

**Schritt 3: D1 Mini Pin überprüfen**
```bash
□ src/config.h: Korrekter Pin definiert?
  #define IR_SENSOR D0  // Ist das richtig?
□ Sollte INPUT_PULLUP oder INPUT sein?
□ Code überprüfen: Wird der Pin gelesen?
```

**Schritt 4: Sensor Kalibrierung & Ausrichtung**
```bash
□ Reflex-Sensor:
  - Muss auf reflektierende Oberfläche ausgerichtet sein
  - Zum Testen: Weißes Papier darunter
  - Ausrichtung: LED sollte auf Oberfläche leuchten
□ Durchgangs-Schranke:
  - Sender und Empfänger müssen sich "sehen"
  - Genau ausrichten
  - Kleine Testobjekte durchführen
□ Test: Mit Objekt unterbrechen → Signal sollte wechseln
```

**Schritt 5: Software-Seite überprüfen**
```bash
□ Serial Monitor öffnen
□ IR-Sensor Wert auf Monitor ausgeben:
  Serial.println(digitalRead(IR_SENSOR));
□ Schranke unterbrechen:
  - Sollte zwischen HIGH/LOW wechseln
□ Wechselt nicht? → Siehe Schritte 1-4
```

**Schritt 6: Empfindlichkeit anpassen**
```bash
□ IR-Sensor oft zu empfindlich oder zu träge
□ In src/config.h (wenn vorhanden):
  #define IR_SENSITIVITY 100  // Wert justieren
□ Oder: Sensor physikalisch verstellen
  - Entfernung zur Oberfläche
  - Winkel anpassen
```

---

### Upload-Fehler

#### Problem: Firmware lässt sich nicht uploaden

**Symptom**: `Upload failed: Could not find board...` oder ähnlich

**Ursache**: COM-Port, Treiber, Board nicht erkannt

**Lösungsschritte**:

**Schritt 1: Board in Platform IO korrekt konfiguriert?**
```bash
□ platformio.ini überprüfen:
  [env:d1_mini]
  board = d1_mini
  framework = arduino
  upload_port = /dev/ttyUSB0  # oder COM3 auf Windows
□ Falls upload_port leer: Auto-Detection versuchen
□ Falls Problem: COM-Port manuell eintragen
```

**Schritt 2: COM-Port finden**
```bash
# Windows:
device manager → COM Ports → Arduino (oder CH340)

# macOS:
ls /dev/cu.* | grep -i usb  # oder usbserial

# Linux:
ls /dev/ttyUSB*  # oder ttyACM*
```

**Schritt 3: Treiber installieren**
```bash
□ Windows: CH340 USB-Treiber von AZ-Delivery oder GitHub
□ macOS: Meist auto-installed
□ Linux: sudo apt install ch340 (distributionsspezifisch)
□ Nach Installation: Neu starten!
```

**Schritt 4: D1 Mini in Bootloader-Modus versetzen**
```bash
□ USB trennen
□ Reset Button (kleine Taste auf Board) drücken & HALTEN
□ USB neu verbinden (während Reset gedrückt)
□ Nach 2 Sekunden: Reset loslassen
□ D1 Mini sollte jetzt im Upload-Modus sein
□ Upload versuchen: platformio run -e d1_mini -t upload
```

**Schritt 5: Anderer USB-Port versuchen**
```bash
□ D1 Mini zu anderem USB-Port am Laptop verbinden
□ COM-Port ändern in platformio.ini
□ Upload erneut versuchen
```

**Schritt 6: Anderes USB-Kabel versuchen**
```bash
□ Manche Kabel sind nur zum Laden, nicht zum Programmieren!
□ Kabel mit Daten-Funktionalität erforderlich
□ Mit bekanntem guten Kabel testen
```

**Schritt 7: PlatformIO Umgebung zurücksetzen**
```bash
platformio run -e d1_mini --verbose -t upload

# Falls immer noch nicht:
platformio project clean
platformio project init --board d1_mini
platformio run -e d1_mini -t upload
```

---

## Häufige Fehler-Meldungen

### Fehler: `Could not find PlatformIO`

**Lösung**:
```bash
# PlatformIO Core neu installieren
python -m pip install --upgrade platformio

# Oder: VS Code Extension neu installieren
# (Im Extensions Tab nach PlatformIO suchen)
```

---

### Fehler: `Upload error: Port does not exist`

**Lösung**:
```bash
# COM-Port überprüfen:
platformio device list

# In platformio.ini eintragen:
upload_port = /dev/cu.usbserial-1234  # macOS Beispiel
# oder
upload_port = COM3  # Windows Beispiel
```

---

### Fehler: `Board not supported`

**Lösung**:
```bash
# platformio.ini überprüfen:
board = d1_mini  # Richtig schreiben!

# PlatformIO Datenbank aktualisieren:
platformio update
```

---

### Fehler: `No module named 'esptool'`

**Lösung**:
```bash
# Tool neu installieren:
python -m pip install --upgrade esptool

# Oder: PlatformIO Core aktualisieren:
python -m pip install --upgrade platformio
```

---

## Wenn nichts funktioniert: Notfall-Plan

```
1. Schreite an Projekt-Issues:
   https://github.com/heimerle/dig132-startampel/issues

2. Stelle Frage mit:
   - OS (Windows/macOS/Linux)
   - Fehlermeldung (vollständig kopieren!)
   - Verdrahtungs-Foto
   - Was bereits versucht wurde

3. Warteanleitung mit Fotos:
   - Breadboard Aufbau
   - D1 Mini Verbindungen
   - Taster & LED Verdrahtung

4. Letztes Mittel: Komplett neu starten
   - Neue microSD/neue Breadboard
   - Nach Schritt-für-Schritt [QUICKSTART.md](./QUICKSTART.md) vorgehen
   - Ein Element nach dem anderen testen
```

---

## Tipps zur Prävention

| Tipp | Warum | Wirkung |
|------|-------|--------|
| **Nach dem Löten überprüfen** | Kaltstellen, Brücken | 80% der Fehler vermeiden |
| **Verdrahtung fotografieren** | Dokumentation für Recovery | Zeit sparen bei Reparatur |
| **Tests nach jedem Schritt** | Early error detection | Kleine Probleme vor großen |
| **Kommentare im Code** | Verständnis | Schnellere Bugfixes |
| **Backup der funktionierenden Firmware** | Notfall-Fallback | Nicht von vorn anfangen |

---

## Glossar

- **Debounce**: Verzögerung zum Filtern von Knackgeräuschen bei Schaltern
- **Durchgangsprüfung**: Elektrische Kontinuitätsprüfung mit Multimeter
- **IR-Sensor**: Infrarot-Lichtschranke zur Bewegungserkennung
- **Kurschluss**: Unerwünschte direkte Verbindung zwischen zwei Leitern
- **Kaltstelle**: Schlechte Lötverbindung, nicht mechanisch stabil
- **Pull-up**: Widerstand von Signal zu +5V (Standard-HIGH)

---

**Kontakt**: [GitHub Issues](https://github.com/heimerle/dig132-startampel/issues)  
**Version**: 2.0.0 | **Datum**: 2026-05-11  
**Autor**: Spec Kit Agent

*Viel Erfolg bei der Fehlersuche! 🔧*
