#include "userdialog.h"
#include "ui_userdialog.h"
#include <QMessageBox>

UserDialog::UserDialog(QWidget *parent): QDialog(parent), ui(new Ui::UserDialog){
    ui->setupUi(this);
    ui->cbRole->addItems({"user","admin","mitarbeiter"});
}

UserDialog::~UserDialog(){ delete ui; }

void UserDialog::loadFromRecord(const QSqlRecord &rec){
    if(rec.isEmpty()) return;
    ui->leUsername->setText(rec.value("benutzername").toString());
    ui->cbRole->setCurrentText(rec.value("rolle").toString());
}

QString UserDialog::username() const{ return ui->leUsername->text().trimmed(); }
QString UserDialog::role() const{ return ui->cbRole->currentText(); }
QString UserDialog::password() const{ return ui->lePassword->text(); }

void UserDialog::on_btnOk_clicked(){
    if(username().isEmpty()){
        QMessageBox::warning(this, "Validierung", "Benutzername ist Pflicht");
        return;
    }
    accept();
}
