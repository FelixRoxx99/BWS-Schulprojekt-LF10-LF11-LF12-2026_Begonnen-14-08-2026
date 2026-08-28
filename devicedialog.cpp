#include "devicedialog.h"
#include "ui_devicedialog.h"
#include <QMessageBox>

DeviceDialog::DeviceDialog(QWidget *parent): QDialog(parent), ui(new Ui::DeviceDialog){
    ui->setupUi(this);
    ui->cbType->addItems({"Laptop","Tablet","Beamer","Sonstiges"});
    ui->cbStatus->addItems({"Verfügbar","Ausgeliehen","Defekt"});
}

DeviceDialog::~DeviceDialog(){ delete ui; }

DeviceData DeviceDialog::deviceData() const {
    DeviceData d;
    d.name = ui->leName->text();
    d.type = ui->cbType->currentText();
    d.serial = ui->leSerial->text();
    d.location = ui->leLocation->text();
    d.status = ui->cbStatus->currentText();
    return d;
}

void DeviceDialog::loadFromRecord(const QSqlRecord &rec){
    if(rec.isEmpty()) return;
    ui->leName->setText(rec.value("name").toString());
    ui->cbType->setCurrentText(rec.value("typ").toString());
    ui->leSerial->setText(rec.value("seriennummer").toString());
    ui->leLocation->setText(rec.value("standort").toString());
    ui->cbStatus->setCurrentText(rec.value("status").toString());
}

void DeviceDialog::on_btnOk_clicked(){
    if(ui->leName->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Validierung", "Name ist Pflicht");
        return;
    }
    accept();
}
