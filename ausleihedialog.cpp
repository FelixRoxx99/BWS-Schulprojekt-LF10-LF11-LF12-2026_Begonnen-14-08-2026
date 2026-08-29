#include "ausleihedialog.h"
#include "ui_ausleihedialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlQueryModel>

AusleiheDialog::AusleiheDialog(QWidget *parent): QDialog(parent), ui(new Ui::AusleiheDialog){
    ui->setupUi(this);
    // use models for comboboxes so the UI updates automatically
    QSqlQueryModel *modelG = new QSqlQueryModel(this);
    // robust gegen Groß-/Kleinschreibung und verschiedene Status-Formate
    modelG->setQuery("SELECT id, name FROM geraete WHERE lower(status) LIKE 'verfügbar%';");
    ui->cbGeraet->setModel(modelG);
    ui->cbGeraet->setModelColumn(1); // display name

    QSqlQueryModel *modelB = new QSqlQueryModel(this);
    // nur freigeschaltete Benutzer anzeigen
    modelB->setQuery("SELECT id, benutzername FROM benutzer WHERE approved=1");
    ui->cbBenutzer->setModel(modelB);
    ui->cbBenutzer->setModelColumn(1); // display username
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

int AusleiheDialog::selectedGeraetId() const{
    int idx = ui->cbGeraet->currentIndex();
    if(idx < 0) return -1;
    QAbstractItemModel *m = ui->cbGeraet->model();
    QModelIndex mi = m->index(idx, 0);
    return m->data(mi).toInt();
}

int AusleiheDialog::selectedBenutzerId() const{
    int idx = ui->cbBenutzer->currentIndex();
    if(idx < 0) return -1;
    QAbstractItemModel *m = ui->cbBenutzer->model();
    QModelIndex mi = m->index(idx, 0);
    return m->data(mi).toInt();
}
