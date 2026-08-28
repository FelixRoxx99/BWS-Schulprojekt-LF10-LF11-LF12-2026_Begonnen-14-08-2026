# SmartDevice - Geräteverwaltung (MVP, MVC, Qt5)

Dieses Branch enthält eine funktionale Minimal‑Implementierung (MVP) des SmartDevice‑Projekts, umgesetzt in C++/Qt5 (qmake). Ziel ist die vollständige Erfüllung der MUSS‑Kriterien: Login mit Rollen, Geräte‑CRUD, Ausleihe/Rückgabe, Historie, SQLite‑Persistenz und MVC‑Struktur.

Kurzanleitung (Windows MinGW)
1. Pull the branch:
   git checkout mvp-mvc-qt5
   git pull origin mvp-mvc-qt5

2. Öffne das Projekt in Qt Creator:
   Datei → Projekt öffnen → Gereateverwaltung_Neu_21-08-2026.pro
   Wähle ein Qt5 Kit (MinGW) aus.

3. Build:
   Build → Run qmake
   Build → Build Project

4. Run:
   Run (oder aus dem Build-Ordner die EXE starten)

Test-Accounts:
- admin / admin (Rolle: admin)
- user  / user  (Rolle: user)

Wichtige Dateien
- src/: Quellcode (main.cpp, models, controllers, views)
- forms/: .ui Dateien
- README.md, testcases.md

