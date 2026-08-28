# Testfälle / Abnahme

1. Login positiv
   - Schritte: App starten -> Login mit admin/admin
   - Erwartet: Hauptfenster öffnet, Admin-Page sichtbar

2. Login negativ
   - Schritte: falsches Passwort
   - Erwartet: Fehlermeldung, kein Zugang

3. Gerät erfassen
   - Schritte: "Gerät hinzufügen" -> neues Gerät mit gültigen Daten speichern
   - Erwartet: Gerät in Übersicht sichtbar

4. Validierung
   - Schritte: Neues Gerät ohne Name speichern
   - Erwartet: Validierungsfehler, Dialog bleibt offen

5. Rollen-Test
   - Schritte: Login als user -> Versuch löschen
   - Erwartet: Aktion verweigert (Nachricht)

Negativer Test: Versuch, Admin-Seite als Nicht-Admin aufzurufen -> nicht sichtbar

