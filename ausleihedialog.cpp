#include "ausleihedialog.h"
#include "ui_ausleihedialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

AusleiheDialog::AusleiheDialog(QWidget *parent): QDialog(parent), ui(new Ui::AusleiheDialog){
    ui->setupUi(this);
    // populate available devices (status = Verfügbar)
    QSqlQuery q;
    q.exec("SELECT id, name FROM geraete WHERE status='Verfügbar'");
    while(q.next()){
        int id = q.value(0).toInt();
        QString name = q.value(1).toString();
        ui->cbGeraet->addItem(name, id);
    }
    // populate users
    QSqlQuery q2;
    q2.exec("SELECT id, benutzername FROM benutzer");
    while(q2.next()){
        int id = q2.value(0).toInt();
        QString uname = q2.value(1).toString();
        ui->cbBenutzer->addItem(uname, id);
    }
}

AusleiheDialog::~AusleiheDialog(){ delete ui; }

void AusleiheDialog::on_btnOk_clicked(){
    if(ui->cbGeraet->currentIndex() < 0){
        QMessageBox::warning(this, "Validierung", "Bitte ein verfügbares Gerät wählen.");
        return;
    }
    if(ui->cbBenutzer->currentIndex() < 0){
        QMessageBox::warning(this, "Validierung", "Bitte einen Benutzer wählen.");
        return;
    }
    accept();
}

int AusleiheDialog::selectedGeraetId() const{ return ui->cbGeraet->currentData().toInt(); }
int AusleiheDialog::selectedBenutzerId() const{ return ui->cbBenutzer->currentData().toInt(); }
