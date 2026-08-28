# Geraeteverwaltung - Schulprojekt

Dieses Repository enthält eine Qt-Widgets-Anwendung zur Verwaltung von IT-Geräten (Geräte erfassen, bearbeiten, Status verwalten, Benutzerverwaltung mit Rollen). Die Implementierung erfüllt die Pflichtanforderungen des Kurses "Benutzerschnittstellen gestalten und entwickeln" (Anmeldung/Berechtigungen, UI-Bereiche, MVC-Grundstruktur, Projektplanung). 

Kurzanleitung

1. Projekt in Qt Creator öffnen (Gereateverwaltung_Neu_21-08-2026.pro)
2. Build & Run
3. Login-Dialog erscheint. Test-Accounts:
   - admin / admin (Rolle: admin)
   - user / user (Rolle: user)

Wichtige Implementierungsdetails

- Passwortspeicherung: Passwörter werden nicht mehr im Klartext gespeichert. Bei Erststart oder vorhandenen Einträgen werden vorhandene Klartext-Passwörter migriert (mit Salt + SHA-256). Neue Benutzer werden mit Salt+Hash angelegt.
- Rollen: Die Rolle wird beim Login geladen und steuert Sichtbarkeit/Aktivierbarkeit (z. B. Löschen von Geräten ist admin-only).
- GUI: Hauptfenster verwendet Navigation (QListWidget) + QStackedWidget; es gibt DeviceDialog für Erfassen/Bearbeiten, eine Admin-Seite für Benutzer.
- Styling: Einfache QSS-Datei (theme.qss) und farbige Status-Badges (StatusDelegate) sind enthalten.

Was noch verbessert werden kann (Empfehlungen)

- Password Hashing: In einer produktiven Umgebung sollte ein stärkeren KDF (bcrypt/argon2) verwendet werden. Qt bietet hierfür keine eingebaute Funktion; externe Bibliothek empfohlen.
- Benutzerverwaltung (Admin-Page): aktuell grundlegend; weitere Funktionen wie Benutzer anlegen/löschen sollten über Dialoge ergänzt werden.
- Tests: Ergänze Abnahme-Tests und Testskripte dokumentiert in testcases.md

Dokumente im Repo

- README.md (dieses File)
- backlog.md (Product Backlog & Sprints)
- userstories.md (User Stories + Akzeptanzkriterien)
- testcases.md (Abnahmetests)

