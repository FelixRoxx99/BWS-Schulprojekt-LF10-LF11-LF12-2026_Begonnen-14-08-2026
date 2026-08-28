#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "frmmain.h"
#include "logindialog.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // optional theme
    QFile f("theme.qss");
    if(f.open(QFile::ReadOnly)) qApp->setStyleSheet(f.readAll());

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

    // ensure an admin user exists for testing
    q.exec("INSERT OR IGNORE INTO benutzer (id, benutzername, passwort, rolle) VALUES (1, 'admin', 'admin', 'admin')");
    q.exec("INSERT OR IGNORE INTO benutzer (id, benutzername, passwort, rolle) VALUES (2, 'user', 'user', 'user')");

    // Show login dialog
    LoginDialog login;
    if(login.exec() != QDialog::Accepted){
        return 0;
    }

    FrmMain w;
    w.setCurrentUser(login.userId(), login.role());
    w.show();
    return a.exec();
}
