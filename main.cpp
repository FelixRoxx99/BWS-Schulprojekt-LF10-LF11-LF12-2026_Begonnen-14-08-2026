#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "frmmain.h"
#include "logindialog.h"
#include <QFile>
#include <QCryptographicHash>
#include <QUuid>
#include <QScreen>
#include <QGuiApplication>

static QString hashPassword(const QString &salt, const QString &password){
    QByteArray input = (salt + password).toUtf8();
    return QString(QCryptographicHash::hash(input, QCryptographicHash::Sha256).toHex());
}

static QString makeSalt(){
    return QUuid::createUuid().toString(QUuid::WithoutBraces);
}

static bool hasColumn(QSqlDatabase &db, const QString &table, const QString &column){
    QSqlQuery q(db);
    q.prepare(QString("PRAGMA table_info(%1)").arg(table));
    if(!q.exec()) return false;
    while(q.next()){
        if(q.value(1).toString() == column) return true;
    }
    return false;
}

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

    // enable foreign keys for safety
    QSqlQuery pragma(db);
    pragma.exec("PRAGMA foreign_keys = ON;");

    // Tabellen erzeugen
    QSqlQuery q(db);
    q.exec("CREATE TABLE IF NOT EXISTS benutzer ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "benutzername TEXT UNIQUE,"
           "passwort TEXT,"
           "rolle TEXT,"
           "salt TEXT,"
           "kdf TEXT,"
           "iter INTEGER)");

    // add approved column if missing
    if(!hasColumn(db, "benutzer", "approved")){
        QSqlQuery q2(db);
        q2.exec("ALTER TABLE benutzer ADD COLUMN approved INTEGER DEFAULT 0");
    }

    q.exec("CREATE TABLE IF NOT EXISTS geraete ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name TEXT, typ TEXT, seriennummer TEXT, standort TEXT, status TEXT)");

{
