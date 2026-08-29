# SmartDevice - Geräteverwaltung (MVP)

Dieses Repository enthält die C++/Qt Widgets Implementierung für die Geräteverwaltung.

## Ziel
Die Anwendung unterstützt einen einfachen betrieblichen Prozess: Geräte erfassen, ausleihen und zurückgeben. Sie erfüllt die Pflichtanforderungen der Aufgabenstellung (Anmeldung, Rollen, GUI, MVC, Tests).

## Quick Start (Qt Creator)
1. Clone das Repository:
   git clone https://github.com/FelixRoxx99/BWS-Schulprojekt-LF10-LF11-LF12-2026_Begonnen-14-08-2026.git
2. Öffne das Projekt in Qt Creator:
   Datei -> Projekt öffnen -> wähle `Gereateverwaltung_Neu_21-08-2026.pro`
3. Wähle ein Qt Kit (z. B. Qt 6.x MinGW 64-bit).
4. Build → Clean Project
5. Build → Run qmake
6. Build → Rebuild Project
7. Run (F5)

> Wichtig: Wenn du alte generierte Dateien (z.B. aus einem `build/` Ordner) committed hast, empfehle ich diese zu entfernen und `build/` in `.gitignore` aufzunehmen. Falls die Navigation/Seiten fehlen, führe Clean → Run qmake → Rebuild aus.

## Test-Accounts (vorinstalliert)
- admin01 / admin123  (Rolle: admin)
- mit01   / mit123    (Rolle: mitarbeiter)
- nutzer01 / nutzer123 (Rolle: nutzer)

## Akzeptanz-Checkliste (Auswahl)
1. Anmeldung & Rollen
   - Login mit admin01 → vollständiger Zugriff (Übersicht, Gerät hinzufügen, Ausleihen, Admin)
   - Login mit mit01 → nur Übersicht + Ausleihen
   - Login mit nutzer01 → nur Übersicht (read-only)

2. Geräteverwaltung
   - Admin kann Geräte hinzufügen, bearbeiten (doppelklick) und löschen.
   - Beim Hinzufügen werden Name und Seriennummer validiert.
   - Seriennummer ist unique (bei Konflikt: aussagekräftige Fehlermeldung).

3. Ausleihe
   - Nur Mitarbeiter/Admin dürfen ausleihen/rückgeben.
   - Ausleihe erstellt einen Eintrag in `ausleihe` und setzt Geräte‑Status auf `Ausgeliehen`.
   - Rückgabe setzt `rueckgabedatum` und Status auf `Verfügbar`.

4. Negative Tests
   - Falsches Passwort → Login fehlgeschlagen.
   - Gerät hinzufügen ohne Pflichtfelder → Validierungsfehler.
   - Ausleihe eines nicht verfügbaren Geräts → Warnung.

## MVC‑Struktur (Kurz)
- Model: QSqlTableModel (geraete, benutzer), QSqlQueryModel (ausleihe)
- View: .ui Dateien (frmmain.ui, devicedialog.ui, ausleihedialog.ui, userdialog.ui, logindialog.ui)
- Controller: FrmMain + Dialog Slots (verarbeiten Benutzerinteraktionen und sprechen SQL aus)

## Tests & Abnahme
Siehe die Abnahme‑Checkliste oben. Für jede User Story sind eindeutige Akzeptanzkriterien formuliert.

## Änderungen in Branch `fix/login-navigation`
- UI‑Verifikation in FrmMain nach ui->setupUi
- Robustere SQL‑Query in AusleiheDialog (case-insensitive) und Auswahl nur approvter Benutzer
- Validierung in DeviceDialog für Name und Seriennummer
- .gitignore hinzugefügt
- README mit Build‑ und Test‑Anleitung hinzugefügt

---
Wenn du möchtest, öffne ich jetzt den Pull Request gegen `main` und poste hier den Link.
