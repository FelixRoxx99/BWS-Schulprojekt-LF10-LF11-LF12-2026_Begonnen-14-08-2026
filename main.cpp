#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "frmmain.h"
#include "logindialog.h"
#include <QFile>
#include <QCryptographicHash>
#include <QUuid>

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

    // Tabellen erzeugen
    QSqlQuery q(db);
    q.exec("CREATE TABLE IF NOT EXISTS benutzer ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "benutzername TEXT,"
           "passwort TEXT,"
           "rolle TEXT)");

    // ensure salt column exists (SQLite supports ADD COLUMN)
    if(!hasColumn(db, "benutzer", "salt")){
        q.exec("ALTER TABLE benutzer ADD COLUMN salt TEXT");
    }

    q.exec("CREATE TABLE IF NOT EXISTS geraete ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name TEXT, typ TEXT, seriennummer TEXT, standort TEXT, status TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS ausleihe ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "geraet_id INTEGER,"
           "benutzer_id INTEGER,"
           "ausleihdatum TEXT,"
           "rueckgabedatum TEXT)");

    // ensure an admin user exists for testing. If users exist with plaintext passwords, migrate to hashed + salt.
    // Insert default entries only if username not exists.
    auto ensureUser = [&](const QString &username, const QString &plainPassword, const QString &role){
        QSqlQuery q2(db);
        q2.prepare("SELECT id, passwort, salt FROM benutzer WHERE benutzername=:u");
        q2.bindValue(":u", username);
        if(q2.exec() && q2.next()){
            // user exists -> ensure password is hashed (if not already)
            QString stored = q2.value(1).toString();
            QString salt = q2.value(2).toString();
            QRegularExpression re("^[0-9a-fA-F]{64}$");
            if(!re.match(stored).hasMatch()){
                // treat stored as plaintext, generate salt and hash
                QString s = makeSalt();
                QString hashed = hashPassword(s, stored);
                QSqlQuery u(db);
                u.prepare("UPDATE benutzer SET passwort=:p, salt=:s WHERE id=:id");
                u.bindValue(":p", hashed);
                u.bindValue(":s", s);
                u.bindValue(":id", q2.value(0).toInt());
                u.exec();
            }
        } else {
            // create user
            QString s = makeSalt();
            QString hashed = hashPassword(s, plainPassword);
            QSqlQuery ins(db);
            ins.prepare("INSERT INTO benutzer (benutzername, passwort, rolle, salt) VALUES (:u,:p,:r,:s)");
            ins.bindValue(":u", username);
            ins.bindValue(":p", hashed);
            ins.bindValue(":r", role);
            ins.bindValue(":s", s);
            ins.exec();
        }
    };

    ensureUser("admin", "admin", "admin");
    ensureUser("user", "user", "user");

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
