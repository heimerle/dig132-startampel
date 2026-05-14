# Detailliertes Breadboard-Aufbau-Diagramm

## Draufsicht auf ein Standard-Breadboard (830 Löcher)

```
                    ← oben (Stromschiene +5V, GND)
        
        +5V RAIL                            GND RAIL
        │ │ │                               │ │ │
    ┌───┴─┴─┴────────────────────────────────┴─┴─┴───┐
    │   +        Spalten 1-30                 -     │
    │                                                  │
 R  │  ┌─────────────────────────────────────────┐  │
 1  │  │ ESP32-CAM (Pin-Header)                  │  │ GND
 2  │  │ GND  5V  GPIO13  GPIO14  GPIO15 GPIO4   │  │ GND
 3  │  │ GPIO2                                    │  │ GND
 4  │  └─────────────────────────────────────────┘  │
    │                                                  │
 5  │  Schreib-Daten: GPIO13 → 74HC595_1 DS         │
 6  │  Clock: GPIO14 → beide 74HC595 (gemeinsam)   │
 7  │  Latch: GPIO15 → beide 74HC595 (gemeinsam)   │
    │                                                  │
 8  │  ┌─────────────┐  ┌─────────────┐            │
 9  │  │ 74HC595_1   │  │ 74HC595_2   │            │
10  │  │ Spur 1 LEDs │  │ Spur 2 LEDs │            │
11  │  │ Q0-Q4:      │  │ Q0-Q4:      │            │
12  │  │ R1,R2,Y,G1,2│ →│ R1,R2,Y,G1,2│ (Chain)   │
    │  │ Q5-7: Rsv   │  │ Q5-7: Rsv   │            │
13  │  └─────────────┘  └─────────────┘            │
    │         ↓                ↓                      │
14  │    [330Ω] x 5     [330Ω] x 5    (Vorwiderstände)
15  │         ↓                ↓                      │
16  │    LED Rot 1      LED Rot 1                   │
17  │    LED Rot 2      LED Rot 2                   │
18  │    LED Gelb       LED Gelb                    │
19  │    LED Grün 1     LED Grün 1                  │
20  │    LED Grün 2     LED Grün 2                  │
    │         ↓ (alle LEDs Kathode → GND)           │
    │                                                  │
21  │  ┌───────────────────────┐                     │
22  │  │ PCF8574 (I2C)         │                     │
23  │  │ P0-P3: Buttons        │                     │
24  │  │ P4-P5: Trigger        │                     │
25  │  │ P6: IR-Sensor         │                     │
26  │  │ P7: Reserve           │                     │
27  │  └───────────────────────┘                     │
    │         ↓ (active-low → GND)                   │
    │                                                  │
28  │  [KY-004 Button 1] (START)   →  P0            │
29  │  [KY-004 Button 2] (STOP)    →  P1            │
30  │  [KY-004 Button 3] (RESET)   →  P2            │
    │  [KY-004 Button 4] (MODE)    →  P3            │
    │                                                  │
    │  [Trigger GPIO 1] (Start ext) → P4            │
    │  [Trigger GPIO 2] (Früh ext)  → P5            │
    │  [IR-Sensor Output]           → P6            │
    │                                                  │
    │  GND: Alle Masseverbindungen                  │
    │  3V3: 74HC595_1, 74HC595_2, PCF8574 VCC      │
    │  +5V: ESP32-CAM Power, Kondensator            │
    │                                                  │
    └──────────────────────────────────────────────┘
                    ← unten
```

## Schritt-für-Schritt Aufbau-Anleitung

### Phase 1: Stromversorgung (Reihen 1-4)

**⚠️ WARNUNG: ESP32-CAM hat ZWEI verschiedene Spannungen!**

```
Externe Stromquelle (USB oder Netzteil):
5V  ──→ ESP32-CAM "5V" Pin (NICHT an VCC!)
GND ──→ ESP32-CAM "GND" Pin

         ↓
    [100µF Kondensator]  (zur Glättung)
         ↓
       GND

       ↓ (intern reguliert auf 3.3V)

ESP32-CAM "3V3" Output ──→ 74HC595_1 VCC
ESP32-CAM "3V3" Output ──→ 74HC595_2 VCC
ESP32-CAM "3V3" Output ──→ PCF8574 VCC

         ✓ RICHTIG:
         ├─ 5V an "5V" Pin
         ├─ 3V3 an externe ICs
         └─ Alle GND gemeinsam

         ❌ FALSCH (zerstört ESP32-CAM):
         ├─ 5V an "VCC" oder "3V3"
         ├─ Mehrere GND-Punkte
         └─ I2C Pullups auf 5V

### Phase 2: ESP32-CAM Platzierung (Reihen 5-7)

```
Platziere ESP32-CAM mit Breite über Reihentrennsteg:

  a   b  |  c   d  |  e   f  |  g   h  |  i   j
─────────┼─────────┼─────────┼─────────┼─────────
 +5V GND |         |         |         |
─────────┼─────────┼─────────┼─────────┼─────────
  1  2   | 3 (GND) | 4       | 5       | 6
GND 5V ← | ← GPIO13│GPIO14  │GPIO15  │GPIO4
(aus     │(DS)    │(SHCP)  │(STCP)  │(SDA)
Netzteil)└────────┴────────┴────────┘
│                   │
└─── ⚠️ Pin "5V" (NICHT VCC!)
      ← ⚠️ Pin "GND" (gemeinsam mit allem)

         │ GPIO2 (SCL) - Row 7
         └────→ zum PCF8574

Stromverbindungen ESP32-CAM:
- GND Pin (Row 1, Spalte a) → GND Rail (durchgehend zu allen ICs)
- 5V Pin (Row 2, Spalte a)  → +5V Rail (5V von USB/Netzteil)
- 3V3 Pin (Row 3/4)         → +3V3 Rail (zu 74HC595 x2, PCF8574)

Nicht verwechseln: 5V Pin ≠ VCC Pin!
```

### Phase 3: 74HC595_1 (Spur 1, Reihen 9-12)

```
Position: Spalten m-p (rechts)

  m   n   o   p
───────────────  Row 8  (obere Reihe)
│ 1   2   3   4  │ DIP-8 IC
│ B   A   -   +  │
│ GND MR  OE  VCC│
├───────────────┤
│16  15  14  13  │ DIP-8 IC (unten)
│ +   -  DS  Q7' │
│VCC GND DS  OE  │
───────────────  Row 9

Verdrahtung 74HC595_1:
- Pin 16 (VCC) → Spalte p, Row 9 → dann zu +3V3 Rail
- Pin  8 (GND) → Spalte m, Row 9 → dann zu GND Rail
- Pin 14 (DS)  ← GPIO13 (e, Row 7)
- Pin 11 (SHCP)← GPIO14 (f, Row 7)
- Pin 12 (STCP)← GPIO15 (g, Row 7)
- Pin 13 (OE)  → GND
- Pin 10 (MR)  → +3V3

- Pin 15 (Q0)  → [330Ω] → LED_RED_1 → GND
- Pin  1 (Q1)  → [330Ω] → LED_RED_2 → GND
- Pin  2 (Q2)  → [330Ω] → LED_YELLOW → GND
- Pin  3 (Q3)  → [330Ω] → LED_GREEN_1 → GND
- Pin  4 (Q4)  → [330Ω] → LED_GREEN_2 → GND
- Pin  9 (QH') → Spalte p, Row 12 → zu 74HC595_2 DS
```

### Phase 4: 74HC595_2 (Spur 2, Reihen 10-13)

```
Position: Spalten m-p (rechts, unter 74HC595_1)

  m   n   o   p
───────────────  Row 10 (obere Reihe)
│ 1   2   3   4  │ DIP-8 IC
│ B   A   -   +  │
│ GND MR  OE  VCC│
├───────────────┤
│16  15  14  13  │ DIP-8 IC (unten)
│ +   -  DS  Q7' │
│VCC GND DS  OE  │
───────────────  Row 11

Verdrahtung 74HC595_2:
- Pin 14 (DS)  ← Pin 9 (QH') von 74HC595_1 (von oben, Row 9 P-Spalte)
- Pin 11 (SHCP)← GPIO14 (gemeinsam mit 74HC595_1, von Row 7 f)
- Pin 12 (STCP)← GPIO15 (gemeinsam mit 74HC595_1, von Row 7 g)
- Pin 16 (VCC) → +3V3
- Pin  8 (GND) → GND

- Pin 15 (Q0)  → [330Ω] → LED2_RED_1 → GND
- Pin  1 (Q1)  → [330Ω] → LED2_RED_2 → GND
- Pin  2 (Q2)  → [330Ω] → LED2_YELLOW → GND
- Pin  3 (Q3)  → [330Ω] → LED2_GREEN_1 → GND
- Pin  4 (Q4)  → [330Ω] → LED2_GREEN_2 → GND
```

### Phase 5: LED-Anschlüsse (Reihen 14-20)

```
Für jede LED gleich:

  (Q-Pin aus 74HC595)
       ↓
  [330Ω Widerstand]    ← Spalten e-h
       ↓
  [LED Anode (langer Fuß)]   Row 14-20
       ↓
  [LED Kathode (kurzer Fuß)]  → zur GND Rail
       ↓
     GND

Beispiel LED_RED_1 (74HC595_1 Q0):
Spalte p (Q0 aus IC), Row 9:
  p9 (Q0 Pin 15) → Jump zu f14
  f14 → [330Ω] → e14 → LED Anode
  LED Kathode → GND Rail (Spalte b oder a)
```

### Phase 6: PCF8574 (Reihen 22-24)

```
Position: Spalten j-l

  j   k   l
───────────────  Row 22
│ 1   2   3  │ DIP-8
│SDA SCL GND │
├───────────┤
│ 8   7   6  │ DIP-8
│VCC A0  A1  │
───────────  Row 23

Verdrahtung PCF8574:
- Pin 1 (SDA)  ← GPIO4 (h, Row 7)
- Pin 2 (SCL)  ← GPIO2 (i, Row 7)
- Pin 3 (GND)  → GND Rail
- Pin 8 (VCC)  → +3V3 Rail
- Pin 4 (A0)   → GND
- Pin 5 (A1)   → GND
- Pin 6 (A2)   → GND
(I2C Adresse: 0x20)

Eingangspins (P0-P7):
P0 (Pin ?) → Button START → Spalte f, Row 28 → KY-004 Signal
P1 (Pin ?) → Button STOP  → Spalte g, Row 28 → KY-004 Signal
P2 (Pin ?) → Button RESET → Spalte h, Row 29 → KY-004 Signal
P3 (Pin ?) → Button MODE  → Spalte i, Row 29 → KY-004 Signal
P4 (Pin ?) → Trigger Start → Spalte j, Row 30 → GPIO Signal
P5 (Pin ?) → Trigger Früh  → Spalte k, Row 30 → GPIO Signal
P6 (Pin ?) → IR Sensor    → Spalte l, Row 30 → IR OUT
P7 (Pin ?) → Reserve      → Spalte c, Row 31

Alle Button/Trigger-Signale → GND über KY-004 oder direktes Schalten
```

### Phase 7: Taster, Trigger, IR (Reihen 25-31)

```
KY-004 Module (4x für Buttons):
VCC → +3V3
GND → GND Rail
OUT → zu PCF8574 Pn (active-low)

Taster-Layout:
  c   d   e   f   g   h   i   j
───────────────────────────────  Row 25
[KY-004] [KY-004] [KY-004] [KY-004]
 START    STOP     RESET    MODE
   ↓       ↓        ↓        ↓
  P0      P1       P2       P3  (via PCF8574)

IR-Sensor:
VCC → +3V3
GND → GND
OUT → PCF8574 P6

Externe Trigger:
GPIO_START_EXT → PCF8574 P4
GPIO_FRUEH_EXT → PCF8574 P5
```

## Kabel-Zusammenfassung

| Signaltyp | Menge | Länge | Farbe |
|---|---|---|---|
| +5V Versorgung | 1 | kurz | Rot |
| +3V3 Versorgung | 1 | kurz | Orange |
| GND | 15+ | variabel | Schwarz |
| Taktsignale (GPIO13/14/15) | 3 | kurz | Gelb |
| I2C (GPIO2/4) | 2 | kurz | Blau |
| LED-Daten | 10 | mittel | Grün |
| Button-Eingänge | 4 | mittel | Violett |
| Externe Trigger | 2 | variabel | Grau |
| IR-Sensor | 1 | lang | Weiß |

## Häufige Fehlerkonfigurationen (zu vermeiden!)

### ❌ Fehler 1: GND nicht durchgehend
```
Falsch:
GND Rail  Reihe 2 endet
           ↓
    GND nur bis Spalte h, danach nicht mehr durchgehend
    → PCF8574 und rechte LEDs haben keine Referenzmasse
```

### ❌ Fehler 2: 74HC595 Verkettung vergessen
```
Falsch:
74HC595_1 Pin 9 (QH') nicht verbunden
→ 74HC595_2 sieht nur Nullen
→ Spur 2 LEDs gehen nicht
```

### ❌ Fehler 3: Vorwiderstände falsch
```
Falsch:
[LED] → [330Ω] → GPIO  (Widerstand auf LED-Anode-Seite)
→ LEDs brennen durch

Richtig:
GPIO → [330Ω] → [LED Anode]
         ↓
      LED Kathode → GND
```

### ❌ Fehler 4: PCF8574 Adress-Pins offen
```
Falsch:
A0, A1, A2 nicht angebunden (floating)
→ I2C Adresse unvorhersehbar (0x20..0x27)
→ Taster-Eingänge reagieren nicht

Richtig:
A0, A1, A2 → alle zu GND
→ I2C Adresse = 0x20 (fest)
```

---

**Stand**: 2026-05-14
