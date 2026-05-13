# Wiring Diagram - Startampel für Carrera-Bahn

## Aktuell verfuegbare Hardware

- 2x ESP32-CAM
- 5x KY-004 Taster Modul
- 1x LED-Sortiment (350 LEDs, 3mm/5mm)

Praktische Nutzung:
- 1x ESP32-CAM als aktiver Controller, 1x als Reserve/Testgeraet
- KY-004 Module fuer Start/Stop/Reset/Mode + 1 Reserve
- LEDs aus dem vorhandenen Sortiment entnehmen (rot/gelb/gruen bevorzugt 5mm)

## Komponenten übersicht

```
D1 Mini (ESP8266)
├── Power: 5V USB oder Netzteil
├── GND: Ground
├── Digital Pins (D0-D8)
├── Analog Pins (A0)
└── Special: RX, TX
```

## LED-Anschlüsse pro Spur

### Spur 1 (Lane 1)
```
D1 --[220Ω]-- LED_ROT_1 -- GND
D2 --[220Ω]-- LED_GELB_1 -- GND
D3 --[220Ω]-- LED_GRÜN_1 -- GND
```

### Spur 2 (Lane 2)
```
D4 --[220Ω]-- LED_ROT_2 -- GND
D5 --[220Ω]-- LED_GELB_2 -- GND
D6 --[220Ω]-- LED_GRÜN_2 -- GND
```

## Button-Anschlüsse (mit Pull-Up intern)

```
D7 -- [Button_START] -- GND
D8 -- [Button_STOP] -- GND
RX -- [Button_RESET] -- GND
TX -- [Button_MODE] -- GND
```

Hinweis zu KY-004:
- Das KY-004 ist ein digitales Tastermodul und kann direkt als Schaltsignal auf GPIO genutzt werden.
- Logik im Code weiterhin mit Debounce (30ms) behandeln.

## GPIO-Trigger (externe Steuerung)

```
A0 -- [GPIO_START_EXT] -- GND (Start-Trigger von extern)
D0 -- [GPIO_FRUEH_EXT] -- GND (Frühstart-Trigger)
```

## IR-Lichtschranke (Frühstart-Erkennung)

```
IR_SENSOR_OUT -- D8 -- (mit Pull-Up intern)
IR_SENSOR_GND -- GND
IR_SENSOR_VCC -- 5V
```

## Spannungsversorgung

```
5V USB/Netzteil
    |
    +-- 5V (D1 Mini Power)
    |
    +-- GND (gemeinsamer Masseanschluss)
    |
    +-- [100µF Kondensator] (Glättung)
```

## Vollständiges Schaltplan-Beispiel (ASCII)

```
┌─────────────────────────────────────────────────────┐
│                   D1 Mini (ESP8266)                 │
├─────────────────────────────────────────────────────┤
│                                                      │
│  5V ──── [Kondensator 100µF] ──── GND              │
│   │                                 │               │
│   ├─ LED1_ROT (D1)──[220Ω]─────────┤               │
│   │                                 │               │
│   ├─ LED1_GELB (D2)──[220Ω]────────┤               │
│   │                                 │               │
│   ├─ LED1_GRÜN (D3)──[220Ω]────────┤               │
│   │                                 │               │
│   ├─ LED2_ROT (D4)──[220Ω]─────────┤               │
│   │                                 │               │
│   ├─ LED2_GELB (D5)──[220Ω]────────┤               │
│   │                                 │               │
│   ├─ LED2_GRÜN (D6)──[220Ω]────────┤               │
│   │                                 │               │
│   ├─ [Button] (D7)──────────────────┤               │
│   │ [Button] (D8)──────────────────┤               │
│   │ [Button] (RX)──────────────────┤               │
│   │ [Button] (TX)──────────────────┤               │
│   │                                 │               │
│   └─ [GPIO_START] (A0)──────────────┤               │
│   └─ [GPIO_FRUEH] (D0)──────────────┤               │
│   └─ [IR_SENSOR] (D8)────────────────┤               │
│                                      │               │
└──────────────────────────────────────────────────────┘
```

## Anforderungen für Lötverhältnisse

- **LEDs**: Vorwiderstand 220-470Ω (je nach LED-Helligkeit)
- **Taster**: Pull-Up intern (INPUT_PULLUP in Arduino)
- **Spannungsversorgung**: 5V stabil, mindestens 500mA (besser 1A)
- **GND**: Alle Komponenten an gemeinsamen GND

## Fehlerbehebung

### LEDs leuchten nicht
- Überprüfen Sie die Pinbelegung in `config.h`
- Testen Sie mit simplem digitalWrite Test
- Überprüfen Sie Vorwiderstände (sollten nicht offen sein)

### Taster reagieren nicht
- Überprüfen Sie Pull-Up-Logik (Button an GND, HIGH wenn nicht gedrückt)
- Prüfen Sie Entprellung (30ms Debounce-Delay)

### IR-Schranke funktioniert nicht
- Überprüfen Sie Sensor-Spannung (meist 5V)
- Testen Sie Sensor-Output mit Multimeter
- Überprüfen Sie Blockade-Winkel

---

**Hinweis**: Alle Schaltpläne und Definitionen finden Sie auch in `src/config.h`.

**Stand**: 2026-05-11
