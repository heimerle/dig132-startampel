# 🤖 CI/CD Pipeline: Automatisierte Tests und Releases

**Version**: 2.0.0  
**Status**: Active  
**Platform**: GitHub Actions

---

## Übersicht

Die Startampel nutzt **GitHub Actions** für:

1. **Automatisierte Builds** – Bei jedem Push
2. **Tests** – Unit Tests + Integration Tests
3. **Code-Qualität** – Static Analysis (Cppcheck)
4. **Dokumentation Check** – Verlinkte Dateien existieren
5. **Automatisierte Releases** – Mit Firmware-Binaries bei Tags

---

## Workflows

### 1. Build & Test CI (`build.yml`)

**Auslöser**: Push auf `main`, `001-startampel-carrera`, `002-production-ready`

**Umgebungen**:
- `d1_mini` (ESP8266)
- `esp32dev` (ESP32)

**Schritte**:

```
1. Code auschecken
   ↓
2. Python 3.10 installieren
   ↓
3. PlatformIO installieren
   ↓
4. Packages cachen (schneller Rebuild)
   ↓
5. Firmware bauen (beide Umgebungen)
   ↓
6. Tests ausführen
   ↓
7. Build-Artefakte speichern (30 Tage)
```

**Ausgabe**: 
- Build-Artefakte (`.bin`, `.elf`, etc.)
- Test-Reports
- Status-Badge

**Beispiel-Ausführung**:
```
✓ Checkout code
✓ Set up Python 3.10
✓ Install PlatformIO
✓ Cache packages
✓ Build firmware for d1_mini
  - Compilation successful
  - Size: 258.4 KB (84% of 308KB)
✓ Run tests
  - 18 tests passed
  - 0 tests failed
✓ Build firmware for esp32dev
  - Compilation successful
  - Size: 312.5 KB (72% of 434KB)
✓ Run tests
  - 18 tests passed
  - 0 tests failed
✓ Upload artifacts (d1_mini)
✓ Upload artifacts (esp32dev)

✅ Build successful (2 min 34 sec)
```

---

### 2. Release & Generate Binaries (`release.yml`)

**Auslöser**: Push mit Git-Tag `v*` (z.B. `v2.0.0`)

**Schritte**:

```
1. Code auschecken
   ↓
2. Build für beide Umgebungen
   ↓
3. Binaries umbenennen (mit Version)
   ↓
4. Changelog generieren (seit letztem Tag)
   ↓
5. GitHub Release erstellen
   ↓
6. Binaries als Attachments hinzufügen
```

**Ausgegebene Dateien**:
- `startampel-d1_mini-v2.0.0.bin`
- `startampel-d1_mini-v2.0.0.elf`
- `startampel-esp32dev-v2.0.0.bin`
- `startampel-esp32dev-v2.0.0.elf`

**Release-Seite**: [GitHub Releases](https://github.com/heimerle/dig132-startampel/releases)

---

## Wie man einen Release erstellt

### Schritt 1: Vorbereitung

```bash
# Lokal: Alle Changes committet?
git status  # Sollte "working tree clean" zeigen

# Alle Tests müssen grün sein
platformio test -e d1_mini
platformio test -e esp32dev
```

### Schritt 2: Version bestimmen

**Semantic Versioning**:
- `v1.0.0` – Major release (große Changes)
- `v1.1.0` – Minor release (neue Features)
- `v1.0.1` – Patch release (Bugfixes)

### Schritt 3: Release-Tag erstellen

```bash
# Tag erstellen (lokal)
git tag -a v2.0.0 -m "Release v2.0.0: Phase 2 Dokumentation und CI/CD"

# Tag pushen (triggert GitHub Actions)
git push origin v2.0.0
```

### Schritt 4: GitHub Actions abwarten

1. Gehe zu [GitHub Actions](https://github.com/heimerle/dig132-startampel/actions)
2. "Release & Generate Binaries" Workflow sollte laufen
3. Warten bis Workflow erfolgreich (grüner Haken)
4. Automatisch Release auf [Releases](https://github.com/heimerle/dig132-startampel/releases) erstellt

### Schritt 5: Release prüfen

```
Klicke auf Release → Prüfe:
- ✓ Version korrekt
- ✓ Changelog vorhanden
- ✓ 4 Binaries angehängt (2 Env × 2 Dateitypen)
- ✓ Release-Notes beschreiben Änderungen
```

---

## Status Badges

### Einbinden im README

```markdown
[![Build Status](https://github.com/heimerle/dig132-startampel/actions/workflows/build.yml/badge.svg?branch=main)](https://github.com/heimerle/dig132-startampel/actions)
```

**Ergebnis im README**:
- 🟢 Build passing – Alles OK
- 🔴 Build failing – Fehler vorhanden

---

## Fehlerbehandlung

### Fall 1: Build schlägt fehl

**Symptom**: Rote ✗ im Workflow

**Ursachen**:
- Code kompiliert nicht
- Tests schlagen fehl
- Abhängigkeiten fehlen

**Lösung**:
```bash
1. Workflow-Logs prüfen (GitHub Actions → Workflow → Logs)
2. Lokal reproduzieren:
   platformio run -e d1_mini
   platformio test -e d1_mini
3. Fehler lokale beheben
4. Neu committen & pushen
```

### Fall 2: Release schlägt fehl

**Symptom**: Release-Workflow zeigt Error

**Lösungen**:
```bash
1. Alle Builds erfolgreich? (Falls nicht: Fall 1)
2. Tag korrekt erstellt? git tag -l sollte Tag zeigen
3. Netzwerk OK? GitHub erreichbar?
4. GitHub Token OK? (normalerweise auto-handled)

# Wenn nötig: Tag löschen und neu erstellen
git tag -d v2.0.0
git push origin :v2.0.0  # Remote-Tag löschen
git tag -a v2.0.0 -m "Release v2.0.0 (retry)"
git push origin v2.0.0
```

---

## Erweiterte Konfiguration

### Custom Environment Variablen

In `.github/workflows/build.yml` hinzufügen:

```yaml
env:
  BUILD_FLAGS: "-DDEBUG"
  COMPILER_WARNINGS: "all"
```

### Matrix Builds

Aktuell unterstützt:
- `d1_mini` (ESP8266)
- `esp32dev` (ESP32)

Weitere hinzufügen in `platformio.ini`:
```ini
[env:esp32s3dev]
board = esp32-s3-devkitc-1
framework = arduino
```

Dann in `build.yml`:
```yaml
environment:
  - d1_mini
  - esp32dev
  - esp32s3dev  # Neu
```

### Notifications

Beim Implementieren von Phase 2c (optional):
```yaml
- name: Notify on failure
  if: failure()
  uses: actions/github-script@v6
  with:
    script: |
      github.rest.issues.createComment({
        issue_number: context.issue.number,
        owner: context.repo.owner,
        repo: context.repo.repo,
        body: '❌ Build failed!'
      })
```

---

## Performance-Tipps

### Schnellere Builds

1. **Caching nutzen** (bereits implementiert):
   ```yaml
   - uses: actions/cache@v3
     with:
       path: ~/.platformio
   ```

2. **Parallel Builds** (aktuell mit matrix):
   ```yaml
   strategy:
     matrix:
       environment: [d1_mini, esp32dev]
   ```

3. **Selective Testing**:
   ```bash
   # Nur d1_mini bauen (schneller)
   platformio run -e d1_mini
   ```

### Aktuelle Zeiten

- Erstes Build: ~3-4 min (Dependencies download)
- Nachfolgende: ~1-2 min (Cached)
- Tests: +1-2 min

---

## Monitoring & Debugging

### Live Logs ansehen

```
GitHub Repository
  ↓
Actions Tab
  ↓
Latest Workflow Run
  ↓
Build Job
  ↓
Schritt klicken für Details
```

### Local Simulation

```bash
# Build lokal genau wie CI:
platformio run -e d1_mini

# Tests lokal:
platformio test -e d1_mini

# Verbose Output:
platformio run -e d1_mini --verbose
```

### Artifact Download

```bash
1. Actions Tab → Workflow-Run → Build Job
2. "Artifacts" Section
3. Firmware herunterladen
4. Mit OTA oder USB flashen
```

---

## Roadmap für Phase 2

- [ ] T163 (T164) – Build Workflow (✓ DONE)
- [ ] T165 – Binary Artifacts (✓ DONE)
- [ ] T166 – Release Automation (✓ DONE)
- [ ] T167 – Changelog Auto-Generation (✓ DONE)
- [ ] T168 – Semantic Versioning Policy (✓ DONE)
- [ ] T169 – GitHub Release Template (Planned)
- [ ] T170 – CI/CD Doku (✓ DONE)

---

## Häufige Fragen (FAQ)

### F: Kann ich lokal ohne GitHub Actions bauen?

**A:** Ja! Nicht erforderlich:
```bash
platformio run -e d1_mini
platformio test -e d1_mini
```

### F: Was sind die Anforderungen für CI/CD?

**A**: 
- `platformio.ini` mit Environments
- `src/` mit Code
- `tests/` mit Tests
- `.github/workflows/` mit Workflows

### F: Kann ich CI/CD auf andere Plattformen portieren (GitLab, etc.)?

**A:** Ja, Logik ist Plattform-agnostisch. Nur Workflow-Syntax ändert sich.

### F: Wie lange speichert GitHub die Artefakte?

**A:** Standard 30 Tage (konfigurierbar in `retention-days`)

### F: Kann ich Workflow-Secrets verwenden (API Keys, etc.)?

**A:** Ja! Unter Settings → Secrets → New Repository Secret

---

## Ressourcen

- [GitHub Actions Dokumentation](https://docs.github.com/en/actions)
- [PlatformIO CI Integration](https://docs.platformio.org/en/latest/ci/index.html)
- [Semantic Versioning](https://semver.org/lang/de/)
- [Changelog Best Practices](https://keepachangelog.com/de-DE/1.0.0/)

---

**Status**: ✅ Aktiv  
**Datum**: 2026-05-11  
**Version**: 2.0.0

*CI/CD ist aktiviert und bereit! 🚀*
