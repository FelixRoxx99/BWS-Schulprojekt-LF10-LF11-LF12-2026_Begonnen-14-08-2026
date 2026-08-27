<<<<<<< HEAD
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "frmMain.h"
=======
#include "frmmain.h"

#include <QApplication>
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

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

    // Login anzeigen
    FrmLogin login;
    if (login.exec() == QDialog::Accepted) {
        FrmMain w;
        w.show();
        return a.exec();
    }

    return 0;
=======
    FrmMain w;
    w.show();
    return QApplication::exec();
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334
}
