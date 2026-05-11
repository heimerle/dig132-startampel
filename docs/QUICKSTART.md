# 🚀 Schnellstart: Startampel in 5 Minuten

**Zielgruppe**: Erste-Zeit-Nutzer  
**Zeit**: 5 Minuten  
**Schwierigkeit**: ⭐ Einfach

---

## Schritt 1: Hardware Verdrahten (2 Minuten)

1. **D1 Mini mit USB verbinden** (Power & Programmierung)
2. **LEDs verdrahten nach [wiring.md](./wiring.md)**:
   - Spur 1: D1 (rot), D2 (gelb), D3 (grün)
   - Spur 2: D4 (rot), D5 (gelb), D6 (grün)
3. **Taster verbinden**:
   - D7 = Start-Button
   - D8 = Stop-Button
   - RX = Reset-Button
4. **Stromversorgung**: USB vom Laptop oder 5V Netzteil

**✓ Hardware ist bereit!**

---

## Schritt 2: Firmware Flashen (2 Minuten)

### Option A: Mit VS Code + PlatformIO (empfohlen)

```bash
# 1. Repository klonen
git clone https://github.com/heimerle/dig132-startampel.git
cd dig132-startampel

# 2. VS Code öffnen
code .

# 3. In PlatformIO: 
#    - "PlatformIO: Open Project" wählen
#    - Environment wählen: "d1_mini"
#    - "Upload" Button klicken (oder: platformio run -e d1_mini -t upload)

# 4. Warten bis "Successfully uploaded" erscheint
```

### Option B: Manuell via Arduino IDE

```bash
# 1. Arduino IDE öffnen
# 2. Tools → Board → "D1 Mini (ESP8266)"
# 3. Tools → Port → COM Port wählen (z.B. COM3 oder /dev/cu.*)
# 4. Sketch → Upload (Ctrl+U)
```

**✓ Firmware ist geflasht!**

---

## Schritt 3: Testen (1 Minute)

### LED-Test

1. **D1 Mini neu starten** (USB trennen/verbinden oder Reset-Button)
2. **Alle LEDs sollten kurz aufblinken** → Selbsttest erfolgreich
3. **System ist im IDLE-Modus** (wartet auf Start)

### Button-Test

**Drücke den Start-Button (D7):**
- ✅ **Rote LED blinkt 5x** (Countdown)
- ✅ **Dann grüne LED leuchtet** (Startfreigabe)
- ✅ **Rennen läuft!**

**Drücke Reset-Button während Rennen:**
- ✅ **Alle LEDs gehen aus**
- ✅ **Zurück zu IDLE**

**✓ System funktioniert!**

---

## Schritt 4: Erste Rennen fahren! 🏎️

### Bedienung

| Button | Aktion |
|--------|--------|
| **Start (D7)** | Starte Countdown + Rennen |
| **Reset (RX)** | Stoppe alles, zurück zu IDLE |
| **Stop (D8)** | Pause (optional) |

### Rennen-Modi

Während Rennen aktiv:

- **Frühstart erkannt?** → Gelbe LEDs leuchten + betroffene rote LED blinkt
- **Safety-Car?** → Alle gelben LEDs blinken
- **Rennunterbrechung?** → Alle roten LEDs blinken
- **Rennende?** → Alle grünen LEDs blinken + Sieger-rot steady

**Viel Spass! 🎉**

---

## Troubleshooting (30 Sekunden)

| Problem | Lösung |
|---------|--------|
| **Keine LEDs leuchten** | USB-Verbindung prüfen, D1 Mini USB-Treiber installieren |
| **LEDs leuchten unkontrolliert** | Verdrahtung gegen wiring.md prüfen, D1 Mini neustarten |
| **Button funktioniert nicht** | Verdrahtung prüfen, 30ms Debounce in config.h überprüfen |
| **Firmware-Upload fehlgeschlagen** | COM-Port in PlatformIO prüfen, D1 Mini zurücksetzen (RST Button) |

**Mehr Hilfe:** Siehe [TROUBLESHOOTING.md](./TROUBLESHOOTING.md) oder [Projekt-Issues](https://github.com/heimerle/dig132-startampel/issues)

---

## Nächste Schritte

- 📖 [Bedienungsanleitung](./BEDIENUNG.md) (vollständig)
- 🔧 [Troubleshooting Guide](./TROUBLESHOOTING.md) (erweitert)
- ⚙️ [Technische Dokumentation](./README.md)
- 🛒 [Hardware bestellen](./EINKAUFSLISTE.md)

---

**Status**: ✅ Bereit für den Einsatz!  
**Feedback**: Issues auf [GitHub](https://github.com/heimerle/dig132-startampel/issues)

*Viel Spass mit deiner Carrera-Startampel! 🚦*
