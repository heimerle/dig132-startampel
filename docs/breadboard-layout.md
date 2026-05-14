# Breadboard Layout - Startampel mit ESP32-CAM

## Übersicht
Verdrahtung auf einem Standard-Breadboard (830 Löcher, doppelseite Stromschienen) mit:
- 1x ESP32-CAM (oben)
- 2x 74HC595 Schieberegister (für 10 LEDs)
- 1x PCF8574 I2C Expander (für Eingänge)

## Physikalische Anordnung

### Stromschienen-Layout
```
┌─────────────────────────────────────────────────┐
│ + | Red Power Rail    (+5V, +3V3)               │
│ - | Blue Ground Rail  (GND)                     │
│   | 30 colums, typical 2 × 15 holes/column     │
└─────────────────────────────────────────────────┘
```

### Detailliertes Breadboard (Vorderansicht)

```
        ESP32-CAM Module (oben)
        ┌──────────────────────────┐
    GND ├─────────────────────────┤ 5V
     3V3 ├─────────────────────────┤ GPIO13 (DS)
   GPIO2 ├─────────────────────────┤ GPIO14 (SHCP)
   GPIO4 ├─────────────────────────┤ GPIO15 (STCP)
        └──────────────────────────┘
         │            │            │
         │            │            └─────┐
         │            │                  │
         │            │           ┌──────┴──────────┐
         │            │           │   74HC595_1     │
         │            │     DS ───┤14   (Spur1)    │
         │            │     │     │                │
         │  ┌─────────┴─────┘     ├─ Q0-Q4: LEDs  │
         │  │                     ├─ Q5-Q7: Rsv   │
         │  │                     │                │
         │  │        ┌────────────┤QH'(9) ──┐     │
         │  │        │            └────┬────┘     │
         │  │        │                 │
         │  │        │        ┌────────┴────┐
         │  │        │        │ 74HC595_2   │
         │  │        └────DS──┤14 (Spur2)  │
         │  │                 │             │
         │  │    SHCP ────────┤11          │
         │  │                 ├─ Q0-Q4: LEDs│
         │  └─ STCP ───────┬──┤12          │
         │                 │  └─────┬───┬──┘
         │                 │        │   │
         │                 │        │   └─ Reserve Outputs
         │                 │        │
         │                 │      (LEDs via 330Ω → GND)
         │                 │
         │        ┌────────┴──┐
         │        │ PCF8574   │
         └─SDA───┤4  (I2C)   │
              │   ├─ P0-P3: Buttons
              └──┤2(SCL)    ├─ P4-P5: Triggers
              │  │  (GND)   ├─ P6: IR
         GND─┤A0 ├─ P7: Rsv  │
         GND─┤A1 └───────────┘
         GND─┤A2
            └─── I2C Addr: 0x20
```

## Schritt-für-Schritt Verkabelung

### 1. Stromversorgung (oben auf Breadboard)

```
            +5V (Netzteil/USB)  |  GND
            │                   │
            ├──[100µF Elko]──┬──┴──[GND Rail]
            │                │
         +5V Rail            GND Rail
            │                │
       ┌────┴────┐      ┌────┴────┐
       │  +5V    │      │   GND   │
       └────┬────┘      └────┬────┘
            │                │
         ESP32-CAM         (alle GND)
         (5V Pin)
         (GND Pin)
```

### 2. ESP32-CAM Anschlüsse

| ESP32-CAM Pin | Breadboard-Position | Verbindung |
|---|---|---|
| GND | Hauptreihe, Spalte 1 | → GND-Rail |
| 5V | Hauptreihe, Spalte 1 | → +5V-Rail |
| GPIO13 (DS) | Hauptreihe, Spalte 2 | → 74HC595_1 DS |
| GPIO14 (SHCP) | Hauptreihe, Spalte 3 | → 74HC595_1/2 SHCP |
| GPIO15 (STCP) | Hauptreihe, Spalte 4 | → 74HC595_1/2 STCP |
| GPIO4 (SDA) | Hauptreihe, Spalte 5 | → PCF8574 SDA |
| GPIO2 (SCL) | Hauptreihe, Spalte 6 | → PCF8574 SCL |

### 3. 74HC595_1 (Spur 1 LEDs) - IC links

```
       Oben (Pin 1-8):
┌─────────────────────┐
│  1    2    3    4   │ 74HC595_1
│  B    A    -    +   │
│  GND  MR   OE   VCC │
└─────────────────────┘

       Unten (Pin 16-9):
┌─────────────────────┐
│  16   15   14   13  │
│  +    -    DS   Q7' │
│  VCC  GND  DS   OE  │
└─────────────────────┘
```

**Pinbelegung 74HC595_1:**
- Pin 16 (VCC) → 3V3-Rail
- Pin 8 (GND) → GND-Rail
- Pin 14 (DS) ← GPIO13
- Pin 11 (SHCP) ← GPIO14
- Pin 12 (STCP) ← GPIO15
- Pin 13 (OE) → GND
- Pin 10 (MR) → 3V3
- Pins Q0-Q4 (Outputs 15, 1, 2, 3, 4) → [330Ω] → LED → GND

### 4. 74HC595_2 (Spur 2 LEDs) - IC rechts

**Pinbelegung 74HC595_2:**
- Pin 16 (VCC) → 3V3-Rail
- Pin 8 (GND) → GND-Rail
- Pin 14 (DS) ← 74HC595_1 Pin 9 (QH')
- Pin 11 (SHCP) ← GPIO14 (gemeinsam mit 74HC595_1)
- Pin 12 (STCP) ← GPIO15 (gemeinsam mit 74HC595_1)
- Pin 13 (OE) → GND
- Pin 10 (MR) → 3V3
- Pins Q0-Q4 (Outputs 15, 1, 2, 3, 4) → [330Ω] → LED → GND

### 5. PCF8574 (I2C Expander) - IC unten

```
PCF8574 (DIP-8 Modell typisch):
┌─────────────┐
│ 1   2   3   │
│ SDA SCL GND │
├─────────────┤
│ 8   7   6   │
│ VCC A0  A1  │
└─────────────┘
```

**Pinbelegung PCF8574:**
- Pin 1 (SDA) ← GPIO4
- Pin 2 (SCL) ← GPIO2
- Pin 3 (GND) → GND-Rail
- Pin 8 (VCC) → 3V3-Rail
- Pins 4, 5, 6 (A0, A1, A2) → GND (Adresse 0x20)
- Port P0-P7 → Taster/IR/Trigger (active-low gegen GND)

### 6. LED-Verdrahtung (je Kanal gleich)

```
74HC595 Qx
    ↓
[330Ω Widerstand]
    ↓
LED Anode (langer Bein)
    ↓
LED Kathode (kurzer Bein)
    ↓
GND
```

**LEDs pro Spur:**
- Rot 1, Rot 2, Gelb, Grün 1, Grün 2 = 5 pro Spur
- Total: 10 LEDs auf 2x5 Ausgängen

### 7. Taster & Trigger (via PCF8574)

```
Button/Trigger
    ↓
KY-004 Signal (nur Signal-Pin nutzen!)
    ↓
PCF8574 P0/P1/P2/P3/P4/P5/P6
    ↓
GND (Breadboard GND-Rail)
```

## Beispiel-Breadboard-Grid

```
Spalten:    a b | c d | e f | g h | i j | k l | m n | o p
            ─────────────────────────────────────────────
Reihe 1:    + + | + + | + + | + + | + + | + + | + + | + +    (+5V Rail)
Reihe 2:    - - | - - | - - | - - | - - | - - | - - | - -    (GND Rail)
            ─────────────────────────────────────────────
Reihe 3:    ESP32-CAM (oben, Breite 2cm)
            ─────────────────────────────────────────────
Reihe 5:    74HC595_1 | . | . | 74HC595_2
Reihe 10:   . | . | . | PCF8574
            ─────────────────────────────────────────────
Reihe 15:   [330Ω] | [330Ω] | ... (10x für LEDs)
Reihe 20:   LED Kategone (Rot, Rot, Gelb, Grün, Grün)
            ─────────────────────────────────────────────
Reihe 25:   KY-004 | KY-004 | KY-004 | KY-004 (Taster)
Reihe 28:   IR-Sensor, Trigger, Reserven
```

## Wichtige Punkte beim Aufbau

1. **GND-Verbindung**: Alle Masse-Punkte **strikt gemeinsam** (ESP32-CAM, 74HC595 x2, PCF8574, LEDs, Taster)
2. **Stromschienen nutzen**: +5V und GND-Rail reduzieren Jumperkabel
3. **Kurze Drähte**: Besonders bei Taktsignalen (GPIO14, GPIO15)
4. **Dekupplungs-Kondensatoren**: 100 nF je IC (optional, aber empfohlen)
5. **LED-Vorwiderstände**: Alle 10 LEDs brauchen eigenen 330 Ω Widerstand
6. **Boot-Pin stabilisieren**: GPIO15 mit 10 kΩ nach GND
7. **Testpunkte markieren**: GPIO13/14/15 mit Labels, damit Fehlersuche leicht fällt

## Häufige Fehler

- ❌ Vorwiderstand vergessen → LEDs gehen aus oder brennen durch
- ❌ GND nicht gemeinsam → Spannungsreferenz inkonsistent, Ausfälle
- ❌ 74HC595_1 QH' nicht mit 74HC595_2 DS verbunden → 2. IC reagiert nicht
- ❌ PCF8574 Adresse-Pins nicht auf GND → Falscher I2C-Zugriff (0x27 statt 0x20)
- ❌ GPIO15 nicht stabilisiert → ESP32-CAM bootet nicht zuverlässig

---

**Stand**: 2026-05-14
