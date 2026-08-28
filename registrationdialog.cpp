#include "registrationdialog.h"
#include "authutils.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

RegistrationDialog::RegistrationDialog(QWidget *parent): QDialog(parent){
    setWindowTitle("Registrierung");
    auto *lay = new QVBoxLayout(this);
    auto *userLay = new QHBoxLayout();
    userLay->addWidget(new QLabel("Benutzername:"));
    auto *leUser = new QLineEdit();
    leUser->setObjectName("leUsername");
    userLay->addWidget(leUser);
    lay->addLayout(userLay);

    auto *passLay = new QHBoxLayout();
    passLay->addWidget(new QLabel("Passwort:"));
    auto *lePass = new QLineEdit();
    lePass->setEchoMode(QLineEdit::Password);
    lePass->setObjectName("lePassword");
    passLay->addWidget(lePass);
    lay->addLayout(passLay);

    auto *btnLay = new QHBoxLayout();
    btnLay->addStretch();
    auto *btnOk = new QPushButton("OK");
    btnOk->setObjectName("btnOk");
    auto *btnCancel = new QPushButton("Abbrechen");
    btnCancel->setObjectName("btnCancel");
    btnLay->addWidget(btnOk);
    btnLay->addWidget(btnCancel);
    lay->addLayout(btnLay);

    connect(btnCancel, &QPushButton::clicked, this, &RegistrationDialog::reject);
    connect(btnOk, &QPushButton::clicked, [this]{
        // forward to slot implementation
        on_btnOk_clicked();
    });
}

RegistrationDialog::~RegistrationDialog(){ }

QString RegistrationDialog::username() const{
    QLineEdit *le = findChild<QLineEdit *>("leUsername");
    return le ? le->text().trimmed() : QString();
}
QString RegistrationDialog::password() const{
    QLineEdit *le = findChild<QLineEdit *>("lePassword");
    return le ? le->text() : QString();
}

void RegistrationDialog::on_btnOk_clicked(){
    QString u = username();
    QString p = password();
    if(u.isEmpty() || p.isEmpty()){
        QMessageBox::warning(this, "Validierung", "Benutzername und Passwort erforderlich");
        return;
    }
    QString salt = AuthUtils::makeSalt();
    int iter = 100000;
    QByteArray key = AuthUtils::pbkdf2_hmac_sha256(p.toUtf8(), salt.toUtf8(), iter, 32);
    QString hashed = AuthUtils::toHex(key);

    QSqlQuery q;
    q.prepare("INSERT INTO benutzer (benutzername, passwort, rolle, salt, kdf, iter, approved) "
              "VALUES (:u, :p, 'user', :s, 'pbkdf2', :i, 0)");
    q.bindValue(":u", u);
    q.bindValue(":p", hashed);
    q.bindValue(":s", salt);
    q.bindValue(":i", iter);
    if(!q.exec()){
        QMessageBox::critical(this, "Fehler", q.lastError().text());
        return;
    }
    QMessageBox::information(this, "Registrierung", "Registrierung erfolgreich. Ihr Account wird durch einen Administrator freigeschaltet.");
    accept();
}
