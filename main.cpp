#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "frmmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // SQLite verbinden
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("smartdevice.db");

    if (!db.open()) {
        qFatal("Datenbank konnte nicht geöffnet werden!");
    }

    // Tabellen erzeugen
    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS benutzer ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "benutzername TEXT,"
           "passwort TEXT,"
           "rolle TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS geraete ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name TEXT, typ TEXT, seriennummer TEXT, standort TEXT, status TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS ausleihe ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "geraet_id INTEGER,"
           "benutzer_id INTEGER,"
           "ausleihdatum TEXT,"
           "rueckgabedatum TEXT)");

    // Hauptfenster anzeigen (kein FrmLogin vorhanden)
    FrmMain w;
    w.show();
    return a.exec();
}
