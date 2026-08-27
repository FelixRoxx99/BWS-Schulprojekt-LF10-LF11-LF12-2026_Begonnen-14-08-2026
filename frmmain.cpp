#include "frmmain.h"
#include "ui_frmmain.h"

#include <QSqlQuery>
#include <QPushButton>
#include <QModelIndex>

FrmMain::FrmMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    // Geräteübersicht laden
    modelGeraete = new QSqlTableModel(this);
    modelGeraete->setTable("geraete");
    modelGeraete->select();

    ui->tblGeraete->setModel(modelGeraete);

    // Buttons verbinden
    connect(ui->btnTestdaten, &QPushButton::clicked, this, &FrmMain::loadTestData);
    connect(ui->btnAddGeraet, &QPushButton::clicked, this, &FrmMain::addGeraet);
    connect(ui->btnDelete, &QPushButton::clicked, this, &FrmMain::deleteGeraet);
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::loadTestData()
{
    QSqlQuery q;
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Laptop-01', 'Laptop', 'LTP100456', 'Büro 2', 'Verfügbar')");
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Tablet-02', 'Tablet', 'TBL200123', 'Büro 1', 'Ausgeliehen')");
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Beamer-05', 'Beamer', 'BMR500789', 'Konferenzraum', 'Defekt')");

    modelGeraete->select();
}

void FrmMain::addGeraet()
{
    QSqlQuery q;
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Neues Gerät', 'Laptop', 'XXX', 'Büro 3', 'Verfügbar')");
    modelGeraete->select();
}

void FrmMain::deleteGeraet()
{
    QModelIndex idx = ui->tblGeraete->currentIndex();
    int row = idx.row();
    if (row < 0) return;

    modelGeraete->removeRow(row);
    modelGeraete->submitAll();
    modelGeraete->select();
}
