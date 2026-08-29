#include "logindialog.h"
#include "ui_logindialog.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QMessageBox>
#include <QCryptographicHash>
#include <QPushButton>

#include "authutils.h"
#include "registrationdialog.h"

static QString computeHash(const QString &salt, const QString &password){
    QByteArray key = AuthUtils::pbkdf2_hmac_sha256(password.toUtf8(), salt.toUtf8(), 100000, 32);
    return AuthUtils::toHex(key);
}

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
//LoginDialog::~LoginDialog(){ delete ui; }

void LoginDialog::on_btnCancel_clicked(){ reject(); }

void LoginDialog::on_btnLogin_clicked(){
    QString user = ui->leUser->text().trimmed();
    QString pass = ui->lePassword->text();
    if(user.isEmpty() || pass.isEmpty()){ QMessageBox::warning(this, "Fehler", "Benutzer und Passwort erforderlich"); return; }
    QSqlQuery q;
    q.prepare("SELECT id, rolle, passwort, salt, approved FROM benutzer WHERE benutzername=:u");
    q.bindValue(":u", user);
    if(q.exec() && q.next()){
        int id = q.value(0).toInt();
        QString role = q.value(1).toString();
        QString stored = q.value(2).toString();
        QString salt = q.value(3).toString();
        int approved = 1;
        if(q.record().indexOf("approved")>=0) approved = q.value(4).toInt();
        if(approved != 1){
            QMessageBox::warning(this, "Login gesperrt", "Ihr Account wurde noch nicht vom Administrator freigeschaltet.");
            return;
        }
        QString hashed = computeHash(salt, pass);
        if(hashed == stored){
            m_userId = id;
            m_role = role;
            accept();
            return;
        }
    }
    QMessageBox::warning(this, "Login fehlgeschlagen", "Benutzername oder Passwort falsch");
}

