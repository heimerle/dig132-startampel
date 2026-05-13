# Technical Design: Production Readiness & Extensions (Feature 002)

## Ziel
Dieses Dokument erweitert das MVP-Design um produktive und optionale Features:
- Hardware-Validierung
- Firmware-Optimierung
- Optionales Web-Interface
- Persistente Konfiguration
- OTA-Updates
- CI/CD und Betrieb

## Designprinzipien
- Nicht-blockierende Firmware (zeitgesteuert via `millis()`)
- Klare Trennung zwischen HAL, Domain-Logik und Interfaces
- Fehlertoleranz durch Watchdog, Fail-Safe-States und Logging
- Konfigurierbarkeit ohne Rebuild (EEPROM/JSON)

## Layered Architecture
- Hardware Layer: GPIO, LEDs, Buttons, IR, Versorgung
- HAL Layer: `InputHandler`, `LedController`
- Domain Layer: `StateMachine`, `AmpelController`
- Service Layer: `ConfigService`, `TelemetryService`, `OtaService`
- Interface Layer (optional): REST + WebSocket + Web-UI

## Moduldesign

### ConfigService
- Laden/Speichern von Konfiguration in EEPROM oder LittleFS
- Versionsfeld fuer Schema-Migrationen
- Validierung mit Grenzwerten und Fallback auf Defaults

### TelemetryService
- Ringbuffer fuer Fehlerereignisse
- Zeitmarke pro Event (Millis seit Boot)
- Export via Serial und optional REST

### OtaService
- Version-Check vor Update
- Dual-Step-Pruefung (Upload + Integritaet)
- Rollback-Markierung bei failed boot

### WebService (optional)
- REST Endpoints:
  - `GET /api/status`
  - `POST /api/control`
  - `GET /api/config`
  - `POST /api/config`
  - `POST /api/ota`
- WebSocket Kanal `/ws` fuer Statusstream

## NFR-Designziele
- Loopzeit < 20 ms
- Eingabelatenz < 50 ms
- Blinkjitter <= +/-10 ms
- RAM < 20 KB (D1 Mini Ziel)
- Flash < 300 KB (Basisbetrieb)
- 24h Dauerlauf ohne Crash

## Sicherheits- und Robustheitsdesign
- Eingabevalidierung fuer alle externen Trigger/API-Calls
- Rate-Limit fuer Web-Control Aktionen
- Watchdog aktiv im Produktionsprofil
- Safe-Boot-Modus bei 3 aufeinanderfolgenden Crashs

## Betriebsdesign
- Build-Profile in PlatformIO: `debug`, `release`, `production`
- Feature-Flags via `config.h`:
  - `ENABLE_WEB`
  - `ENABLE_OTA`
  - `ENABLE_PERSISTENCE`
- Strukturierte Logs fuer CI-Auswertung

## Testdesign
- Unit: Modulgrenzen + Validierung
- Integration: E2E-Zustandswechsel
- Hardware-in-the-loop: Timing und Lasttests
- Soak-Test: 24h mit kuenstlichen Triggern
- Regression: CI-Build + Testmatrix (ESP8266/ESP32)
