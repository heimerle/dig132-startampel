# Einkaufsliste - Startampel für Carrera-Bahn

Vollständige Komponentenliste für den D1 Mini-basierten Startampel mit Links zu **AZ-Delivery** und **Amazon** (Deutschland).

## Aktueller Bestand (Stand: 14.05.2026)

- 2x ESP32-CAM
- 5x AZDelivery KY-004 Taster Modul
- 1x AZDelivery LED Leuchtdioden Sortiment (350 Stueck, 3mm/5mm, 5 Farben, UV/RGB CC/CA)

### Widerstands-Bestand

- 10 Ohm x 10
- 220 Ohm x 20
- 330 Ohm x 10
- 1 kOhm x 10
- 2 kOhm x 10
- 5,1 kOhm x 10
- 10 kOhm x 9
- 100 kOhm x 10
- 1 MOhm x 10

### Kondensator-Bestand

- 1000 uF 35V x ca. 20
- 1000 uF 63V x 4
- 15 uF x 1
- 100 nF (104) x 2
- 1 nF 1kV x 5
- B20 x 5

### Halbleiter-Bestand

- BC548B x 3

Hinweis:
- Fuer die aktuelle Firmware werden Standard-LEDs (rot/gelb/gruen) und digitale Taster-Eingaenge genutzt.
- Ein ESP32-CAM kann als Controller verwendet werden, der zweite als Reserve/Test-Controller.
- Durch den vorhandenen Bestand reduziert sich die notwendige Neubeschaffung deutlich.
- Es sind 10 LED-Plaetze vorgesehen; aktuell werden 6 aktiv genutzt und 4 als Reserve/Erweiterung eingeplant.
- Vorhandene RGB-LEDs koennen optional genutzt werden (pro Kanal mit eigenem Vorwiderstand).
- 220 Ohm Widerstaende sind fuer LED-Vorwiderstaende ausreichend vorhanden.
- 10 kOhm Widerstaende sind fast ausreichend (9 vorhanden), ein Reservekauf ist optional.
- 1000 uF 35V Kondensatoren sind als Bulk-Puffer ausreichend vorhanden.
- 100 nF (104) sind vorhanden, aber nur 2 Stueck; fuer saubere Entkopplung sind ggf. weitere 100 nF sinnvoll.

## 📋 Komponenten-Übersicht

| # | Komponente | Menge | AZ-Delivery | Amazon | Preis (ca.) |
|---|-----------|-------|-------------|--------|------------|
| 1 | D1 Mini (ESP8266) | 1x | [Link](#d1-mini) | [Link](#d1-mini-amazon) | €8-12 |
| 2 | LED rot 5mm | 2x aktiv (Reserve verfuegbar) | [Link](#led-rot) | [Link](#led-rot-amazon) | €0,50-1 |
| 3 | LED gelb 5mm | 2x aktiv (Reserve verfuegbar) | [Link](#led-gelb) | [Link](#led-gelb-amazon) | €0,50-1 |
| 4 | LED grün 5mm | 2x aktiv (Reserve verfuegbar) | [Link](#led-gruen) | [Link](#led-gruen-amazon) | €0,50-1 |
| 5 | Widerstand 220Ω | 10x benoetigt (20x vorhanden) | [Link](#r220) | [Link](#r220-amazon) | €1-2 |
| 6 | Widerstand 10kΩ | 10x benoetigt (9x vorhanden) | [Link](#r10k) | [Link](#r10k-amazon) | €1-2 |
| 7 | Kondensator 100µF | 2x | [Link](#c100) | [Link](#c100-amazon) | €1-2 |
| 8 | Taster (6x6mm) | 5x | [Link](#button) | [Link](#button-amazon) | €2-3 |
| 9 | IR-Lichtschranke | 1x | [Link](#ir) | [Link](#ir-amazon) | €5-8 |
| 10 | USB-Kabel (Micro-B) | 1x | [Link](#usb) | [Link](#usb-amazon) | €3-5 |
| 11 | Breadboard 830 Löcher | 1x | [Link](#breadboard) | [Link](#breadboard-amazon) | €5-8 |
| 12 | Jumper Kabel Set | 1x | [Link](#jumper) | [Link](#jumper-amazon) | €3-5 |
| 13 | Power Bank/Netzteil 5V | 1x | [Link](#power) | [Link](#power-amazon) | €10-20 |

**Gesamtbudget: ca. €45-70**

---

## 🛒 Detaillierte Links

### Mikrocontroller

#### D1 Mini (ESP8266)
**AZ-Delivery:**
- [D1 mini (ESP8266) - AZ-Delivery](https://www.az-delivery.de/products/d1-mini)
- Baugleich mit NodeMCU, aber kleinere Abmessungen
- Inkl. USB-Kabel

**Amazon:**
- [D1 mini 4MB ESP8266 - Amazon](https://www.amazon.de/s?k=D1+mini+ESP8266+4MB)
- Variante: Mehrfach-Pack (3er oder 5er) empfohlen für Experimente

**Alternative:**
- ESP32 DevKit C (größer, aber mehr Pins): [AZ-Delivery ESP32](https://www.az-delivery.de/products/esp32-devkit-c-v4)

---

### LEDs

#### LED rot 5mm (2 Stück für Spur 1 + Spur 2)
**AZ-Delivery:**
- [LED rot 5mm 1000er Set - AZ-Delivery](https://www.az-delivery.de/products/led-rot-5mm)
- Oder einzeln kaufen

**Amazon:**
- [LED 5mm rot - Amazon](https://www.amazon.de/s?k=LED+5mm+rot)
- Sets zu 10-20 Stück empfohlen

#### LED gelb 5mm (2 Stück)
**AZ-Delivery:**
- [LED gelb 5mm - AZ-Delivery](https://www.az-delivery.de/products/led-gelb-5mm)

**Amazon:**
- [LED 5mm gelb - Amazon](https://www.amazon.de/s?k=LED+5mm+gelb)

#### LED grün 5mm (2 Stück)
**AZ-Delivery:**
- [LED grün 5mm - AZ-Delivery](https://www.az-delivery.de/products/led-gruen-5mm)

**Amazon:**
- [LED 5mm grün - Amazon](https://www.amazon.de/s?k=LED+5mm+gruen)

**Hinweis:** LED-Sets (rot/grün/gelb Mix) sind meist günstiger:
- [LED 5mm Sortiment - AZ-Delivery](https://www.az-delivery.de/products/led-sortiment)
- [LED 5mm Mix Set - Amazon](https://www.amazon.de/s?k=LED+5mm+sortiment)

---

### Widerstände

#### Widerstand 220Ω (für LED-Strombegrenzung)
**AZ-Delivery:**
- [Kohleschicht Widerstände Sortiment - AZ-Delivery](https://www.az-delivery.de/products/widerstandssortiment)

**Amazon:**
- [Widerstand 220Ω Set - Amazon](https://www.amazon.de/s?k=widerstand+220+ohm)

**Empfehlung:** Widerstandssortiment kaufen (100er/200er Sets)

#### Widerstand 10kΩ (für Pull-up/Pull-down)
**AZ-Delivery:**
- [Widerstandssortiment mit 10kΩ - AZ-Delivery](https://www.az-delivery.de/products/widerstandssortiment)

**Amazon:**
- [Widerstand 10k Ohm - Amazon](https://www.amazon.de/s?k=10k+ohm+widerstand)

---

### Kondensatoren

#### Kondensator 100µF / 25V
**AZ-Delivery:**
- [Kondensator Sortiment - AZ-Delivery](https://www.az-delivery.de/products/kondensator-sortiment)

**Amazon:**
- [Elko 100µF 25V - Amazon](https://www.amazon.de/s?k=kondensator+100uf+25v)

**Zweck:** Spannungsglättung für stabile 5V-Versorgung

---

### Eingabe-Komponenten

#### Taster 6x6mm (5 Stück für Start, Stop, Reset, Mode, Extra)
**AZ-Delivery:**
- [Taster 6x6x6mm - AZ-Delivery](https://www.az-delivery.de/products/drucktaster)

**Amazon:**
- [Drucktaster 6x6mm - Amazon](https://www.amazon.de/s?k=taster+6x6+mm)

**Menge:** 5 Stück (Start, Stop, Reset, Mode + 1 Reserve)

#### IR-Lichtschranke (1 Stück)
**AZ-Delivery:**
- [Infrarot-Lichtschranke Modul - AZ-Delivery](https://www.az-delivery.de/products/infrarot-lichtschranke)
- Breakout-Board mit Modul + Sensorpaar

**Amazon:**
- [IR Light Barrier Module - Amazon](https://www.amazon.de/s?k=IR+lichtschranke)

**Alternative (einfacher zu verdrahten):**
- [TCRT5000 IR Sensor - AZ-Delivery](https://www.az-delivery.de/products/tcrt5000-ir-sensor)

**Hinweis:** Für die Pole Position-Erkennung vor der Startstrecke

---

### Verkabelung & Stromversorgung

#### USB-Kabel Micro-B (für D1 Mini Programmierung)
**AZ-Delivery:**
- [Micro-USB-Kabel - AZ-Delivery](https://www.az-delivery.de/products/micro-usb-kabel)

**Amazon:**
- [Micro USB Kabel - Amazon](https://www.amazon.de/s?k=micro+usb+kabel)

**Länge:** Mind. 1,5-2m empfohlen

#### Breadboard 830 Löcher
**AZ-Delivery:**
- [Breadboard 830er - AZ-Delivery](https://www.az-delivery.de/products/steckplatine-830-er)

**Amazon:**
- [Breadboard 830 - Amazon](https://www.amazon.de/s?k=breadboard+830)

**Alternativen:**
- Mini-Breadboard: Günstiger, aber weniger Platz
- Experimentierplatine (für Dauerlösung)

#### Jumper Kabel Set (flexible Verbindungen)
**AZ-Delivery:**
- [Jumper Kabel Sortiment - AZ-Delivery](https://www.az-delivery.de/products/jumper-kabel)

**Amazon:**
- [Jumper Wire Set - Amazon](https://www.amazon.de/s?k=jumper+kabel+set)

**Längen:** 10cm, 20cm Mix empfohlen

#### Power Bank oder 5V-Netzteil
**AZ-Delivery:**
- [5V USB Netzteil 2A - AZ-Delivery](https://www.az-delivery.de/products/5v-2a-usb-netzteil)

**Amazon:**
- [5V 2A USB Netzteil - Amazon](https://www.amazon.de/s?k=5v+netzteil+2a+usb)

**Alternative (mobil):**
- [Power Bank 10000mAh - Amazon](https://www.amazon.de/s?k=power+bank+10000mah)

**Anforderung:** Mind. 1A, besser 2A (für alle LEDs + D1 Mini)

---

## 📦 Bundle-Empfehlungen

### Komplettes Starter-Kit
Falls einzeln teuer erscheint, diese Sets:

**AZ-Delivery:**
- [AZ-Delivery D1 mini Starter Set](https://www.az-delivery.de/products/d1-mini-esp8266-starter-set)
- Inkludiert: D1 Mini, Breadboard, Jumper Kabel, USB-Kabel

**Amazon:**
- [ESP8266 D1 Mini Starter Kit](https://www.amazon.de/s?k=D1+mini+starter+kit)

---

## 🔧 Nützliche Zusatz-Komponenten

### Optionale Komponenten
| Komponente | Zweck | Link |
|-----------|-------|------|
| Gehäuse/Enclosure | Schutz | [Gehäuse - AZ](https://www.az-delivery.de/products/kunststoff-gehaeuse-l-m-s) |
| Lötkabel | Dauerhaft löten | [Schaltdraht - AZ](https://www.az-delivery.de/products/schaltdraht-set) |
| LED-Holder | Befestigung | [LED Fassung - AZ](https://www.az-delivery.de/products/led-fassung) |
| IC-Sockel | Modularität | [16er IC-Sockel - AZ](https://www.az-delivery.de/products/ic-sockel) |

---

## 📝 Einkaufs-Checkliste

### Bereits vorhanden
- [x] 2x ESP32-CAM
- [x] 5x KY-004 Taster Modul
- [x] 1x LED-Sortiment (AZDelivery, 350 Stueck)
- [x] 220 Ohm Widerstaende (20x)
- [x] Weitere Widerstandswerte fuer Tests/Erweiterungen (10 Ohm, 330 Ohm, 1 kOhm, 2 kOhm, 5.1 kOhm, 100 kOhm, 1 MOhm)

### Schritt 1: Essenzielle Komponenten (Priorität 1)
- [ ] 1x D1 Mini ESP8266
- [ ] 1x USB Micro-B Kabel
- [ ] 6x LEDs (2x rot, 2x gelb, 2x grün)
- [ ] Optional: 1-5x Widerstand 10kΩ als Reserve
- [ ] 2x Kondensator 100µF
- [ ] 5x Taster 6x6mm
- [ ] 1x Breadboard 830
- [ ] 1x Jumper Kabel Set

**Kosten Priorität 1: ca. €30-40**

### Schritt 2: Spezielle Komponenten (Priorität 2)
- [ ] 1x IR-Lichtschranke
- [ ] 1x 5V USB Netzteil 2A

**Kosten Priorität 2: ca. €12-15**

### Schritt 3: Optional/Zusatz (Priorität 3)
- [ ] 1x Gehäuse
- [ ] 1x Lötkabel-Set
- [ ] 1x LED-Halter

**Kosten Priorität 3: ca. €8-15**

---

## 💡 Bestell-Tipps

1. **AZ-Delivery vs. Amazon**
   - AZ-Delivery: Günstiger, schnelle Lieferung (oft nächster Tag)
   - Amazon: Schneller (Prime), breiter sortiert

2. **Versand-Kosten sparen**
   - AZ-Delivery: Ab €50 versandkostenfrei (oder Prime-ähnlicher AZ-Club)
   - Amazon: Prime-Vorteile nutzen

3. **Sets kaufen**
   - LED-Sets statt einzeln: 50-70% günstiger
   - Widerstand-Sortimente: Günstiger + vielseitig nutzbar

4. **Lieferzeiten**
   - Normal: 2-3 Tage
   - Express möglich, aber teurer

5. **Lagerbestand prüfen**
   - Beliebte Komponenten können ausverkauft sein
   - Alternativ-Links bereithalten

---

## 🚀 Bestell-Reihenfolge

**Empfohlene Reihenfolge:**

1. **Zuerst bestellen (essenzielle Komponenten):**
   - D1 Mini
   - USB-Kabel
   - Breadboard
   - Jumper Kabel

2. **Parallel bestellen (passive Komponenten):**
   - LEDs
   - Widerstände (Sets)
   - Kondensatoren
   - Taster

3. **Später bestellen (Spezial-Komponenten):**
   - IR-Lichtschranke
   - Netzteil (oder Power Bank verwenden)

---

## 📊 Kostenübersicht

```
Essenzielle Komponenten (P1):  €30-40
+ Spezielle Komponenten (P2):  €12-15
+ Optionale Komponenten (P3):  €8-15
────────────────────────────────────
GESAMTBUDGET:                 €50-70
```

**Mit Rabatt/Sets:**
- Minimum möglich: €40-50
- Realistisch: €55-65

---

## ✅ Inbetriebs-Check

Nach Erhalt alle Komponenten prüfen:

- [ ] D1 Mini funktioniert (USB erkannt)
- [ ] LEDs leuchten bei Stromzufuhr
- [ ] Taster drücken/federn zurück
- [ ] IR-Sensor am USB getestet
- [ ] Alle Widerstände vorhanden

---

## 📚 Zusätz-Links

- [Arduino IDE Download](https://www.arduino.cc/en/software)
- [PlatformIO für VS Code](https://platformio.org/)
- [D1 Mini Dokumentation](https://www.wemos.cc/en/latest/d1/d1_mini.html)
- [Pinout D1 Mini](https://escapequontrol.com/d1-mini-esp8266-pinout/)

---

**Stand**: 2026-05-11  
**Projektlink**: https://github.com/heimerle/dig132-startampel  
**Branch**: `001-startampel-carrera`

Viel Erfolg beim Aufbau! 🚀
