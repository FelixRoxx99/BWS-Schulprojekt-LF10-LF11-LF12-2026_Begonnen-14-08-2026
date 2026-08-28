#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QCryptographicHash>
#include <QUuid>
#include <QScreen>
#include "frmmain.h"
#include "logindialog.h"
#include "authutils.h"

// Hilfsfunktion: Prüfe ob Spalte in Tabelle existiert
static bool hasColumn(QSqlDatabase &db, const QString &table, const QString &column){
    QSqlQuery q(db);
    q.prepare(QString("PRAGMA table_info(%1)").arg(table));
    if(!q.exec()) return false;
    while(q.next()){
        if(q.value(1).toString() == column) return true;
    }
    return false;
}

// Hilfsfunktion: Erstelle Standard Test-Accounts
static void initializeTestAccounts(QSqlDatabase &db) {
    QSqlQuery q(db);
    
    // Prüfe ob Benutzer bereits existieren
    q.prepare("SELECT COUNT(*) FROM benutzer");
    if (!q.exec() || !q.next()) return;
    
    if (q.value(0).toInt() > 0) {
        qDebug() << "✓ Test-Accounts existieren bereits";
        return;
    }
    
    qDebug() << "→ Erstelle Test-Accounts...";
    
    // Test-Accounts anlegen
    struct TestUser {
        QString username;
        QString password;
        QString role;
    };
    
    QList<TestUser> testUsers = {
        {"nutzer01", "nutzer123", "nutzer"},
        {"mit01", "mit123", "mitarbeiter"},
        {"admin01", "admin123", "admin"}
    };
    
    for (const auto& user : testUsers) {
        QString salt = AuthUtils::makeSalt();
        int iter = 100000;
        QByteArray key = AuthUtils::pbkdf2_hmac_sha256(user.password.toUtf8(), salt.toUtf8(), iter, 32);
        QString hashed = AuthUtils::toHex(key);
        
        q.prepare("INSERT INTO benutzer (benutzername, passwort, rolle, salt, kdf, iter, approved) "
                  "VALUES (:u, :p, :r, :s, :k, :i, 1)");
        q.bindValue(":u", user.username);
        q.bindValue(":p", hashed);
        q.bindValue(":r", user.role);
        q.bindValue(":s", salt);
        q.bindValue(":k", "pbkdf2");
        q.bindValue(":i", iter);
        
        if (!q.exec()) {
            qWarning() << "Fehler beim Anlegen von" << user.username << ":" << q.lastError().text();
        } else {
            qDebug() << "✓ Test-Account erstellt:" << user.username << "(" << user.role << ")";
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // ============================================
    // SCHRITT 1: Stylesheet laden (optional)
    // ============================================
    QFile f("theme.qss");
    if(f.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(f.readAll());
        f.close();
    }
    
    // ============================================
    // SCHRITT 2: Datenbankverbindung öffnen
    // ============================================
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("smartdevice.db");
    
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Fehler", 
            "Datenbank konnte nicht geöffnet werden:\n" + db.lastError().text());
        return 1;
    }
    
    qDebug() << "✓ Datenbankverbindung hergestellt";
    
    // Foreign Keys aktivieren
    QSqlQuery pragma(db);
    if (!pragma.exec("PRAGMA foreign_keys = ON;")) {
        qWarning() << "Warnung: Foreign Keys konnten nicht aktiviert werden";
    }
    
    // ============================================
    // SCHRITT 3: Tabellen erstellen/aktualisieren
    // ============================================
    QSqlQuery q(db);
    
    // Benutzer-Tabelle
    if (!q.exec("CREATE TABLE IF NOT EXISTS benutzer ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "benutzername TEXT UNIQUE,"
               "passwort TEXT,"
               "rolle TEXT,"
               "salt TEXT,"
               "kdf TEXT,"
               "iter INTEGER)")) {
        qWarning() << "Fehler bei benutzer-Tabelle:" << q.lastError().text();
    } else {
        qDebug() << "✓ benutzer-Tabelle OK";
    }
    
    // approved-Spalte hinzufügen, wenn nicht vorhanden
    if(!hasColumn(db, "benutzer", "approved")){
        QSqlQuery q2(db);
        if (q2.exec("ALTER TABLE benutzer ADD COLUMN approved INTEGER DEFAULT 0")) {
            qDebug() << "✓ approved-Spalte hinzugefügt";
        }
    }
    
    // Geräte-Tabelle
    if (!q.exec("CREATE TABLE IF NOT EXISTS geraete ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name TEXT,"
               "typ TEXT,"
               "seriennummer TEXT UNIQUE,"
               "standort TEXT,"
               "status TEXT)")) {
        qWarning() << "Fehler bei geraete-Tabelle:" << q.lastError().text();
    } else {
        qDebug() << "✓ geraete-Tabelle OK";
    }
    
    // Ausleihe-Tabelle
    if (!q.exec("CREATE TABLE IF NOT EXISTS ausleihe ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "geraet_id INTEGER NOT NULL,"
               "benutzer_id INTEGER NOT NULL,"
               "ausleihdatum DATETIME,"
               "rueckgabedatum DATETIME,"
               "FOREIGN KEY(geraet_id) REFERENCES geraete(id) ON DELETE CASCADE,"
               "FOREIGN KEY(benutzer_id) REFERENCES benutzer(id) ON DELETE CASCADE)")) {
        qWarning() << "Fehler bei ausleihe-Tabelle:" << q.lastError().text();
    } else {
        qDebug() << "✓ ausleihe-Tabelle OK";
    }
    
    // ============================================
    // SCHRITT 4: Test-Accounts initialisieren
    // ============================================
    initializeTestAccounts(db);
    
    qDebug() << "\n=== Test-Accounts für Login ===";
    qDebug() << "Nutzer (Read-Only):       nutzer01 / nutzer123";
    qDebug() << "Mitarbeiter (Ausleihe):   mit01 / mit123";
    qDebug() << "Administrator (Admin):    admin01 / admin123";
    qDebug() << "================================\n";
    
    // ============================================
    // SCHRITT 5: LOGIN-DIALOG anzeigen
    // ============================================
    LoginDialog loginDlg;
    if(loginDlg.exec() != QDialog::Accepted) {
        qDebug() << "Login abgebrochen";
        return 0;  // Benutzer hat Abgebrochen → Programm beenden
    }
    
    // ============================================
    // SCHRITT 6: Hauptfenster anzeigen (NUR nach erfolgreichem Login)
    // ============================================
    FrmMain w;
    
    // Benutzerinformationen setzen (wichtig für Rollenprüfung!)
    w.setCurrentUser(loginDlg.userId(), loginDlg.role());
    
    // Fenster anzeigen
    w.setWindowTitle(QString("SmartDevice - Geräteverwaltung [%1]")
                     .arg(loginDlg.role().toUpper()));
    w.show();
    
    qDebug() << "✓ Benutzer eingeloggt:" << "ID=" << loginDlg.userId() 
             << "Rolle=" << loginDlg.role();
    
    return a.exec();
}
