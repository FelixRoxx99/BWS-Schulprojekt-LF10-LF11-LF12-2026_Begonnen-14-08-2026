#include "userdialog.h"
#include "ui_userdialog.h"
#include <QMessageBox>

UserDialog::UserDialog(QWidget *parent): QDialog(parent), ui(new Ui::UserDialog){
    ui->setupUi(this);
    ui->cbRole->addItems({"user","mitarbeiter","admin"});
}
UserDialog::~UserDialog(){ delete ui; }
QString UserDialog::username() const{ return ui->leUsername->text().trimmed(); }
QString UserDialog::role() const{ return ui->cbRole->currentText(); }
QString UserDialog::password() const{ return ui->lePassword->text(); }
void UserDialog::loadFromRecord(const QSqlRecord &rec){
    ui->leUsername->setText(rec.value("benutzername").toString());
    ui->cbRole->setCurrentText(rec.value("rolle").toString());
}
void UserDialog::on_btnOk_clicked(){
    if(ui->leUsername->text().trimmed().isEmpty()){ QMessageBox::warning(this, "Validierung", "Benutzername ist Pflicht"); return; }
    accept();
}
