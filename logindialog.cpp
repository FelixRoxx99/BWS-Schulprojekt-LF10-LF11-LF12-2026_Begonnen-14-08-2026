#include "logindialog.h"
#include "ui_logindialog.h"
#include <QSqlQuery>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent): QDialog(parent), ui(new Ui::LoginDialog){
    ui->setupUi(this);
}

LoginDialog::~LoginDialog(){ delete ui; }

void LoginDialog::on_btnCancel_clicked(){ reject(); }

void LoginDialog::on_btnLogin_clicked(){
    QString user = ui->leUser->text().trimmed();
    QString pass = ui->lePassword->text();
    if(user.isEmpty() || pass.isEmpty()){ QMessageBox::warning(this, "Fehler", "Benutzer und Passwort erforderlich"); return; }
    QSqlQuery q;
    q.prepare("SELECT id, rolle FROM benutzer WHERE benutzername=:u AND passwort=:p");
    q.bindValue(":u", user);
    q.bindValue(":p", pass);
    if(q.exec() && q.next()){
        m_userId = q.value(0).toInt();
        m_role = q.value(1).toString();
        accept();
    } else {
        QMessageBox::warning(this, "Login fehlgeschlagen", "Benutzername oder Passwort falsch");
    }
}
