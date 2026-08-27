<<<<<<< HEAD
#include "frmMain.h"
#include "frmmain.ui"
#include <QSqlQuery>
=======
#include "frmmain.h"
#include "ui_frmmain.h"
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334

FrmMain::FrmMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);
<<<<<<< HEAD

    // Geräteübersicht laden
    modelGeraete = new QSqlTableModel(this);
    modelGeraete->setTable("geraete");
    modelGeraete->select();

    ui->tblGeraete->setModel(modelGeraete);

    // Buttons verbinden
    connect(ui->btnTestdaten, &QPushButton::clicked, this, &FrmMain::loadTestData);
    connect(ui->btnAddGeraet, &QPushButton::clicked, this, &FrmMain::addGeraet);
    connect(ui->btnDelete, &QPushButton::clicked, this, &FrmMain::deleteGeraet);
=======
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334
}

FrmMain::~FrmMain()
{
    delete ui;
}
<<<<<<< HEAD

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
    int row = ui->tblGeraete->currentIndex().row();
    if (row < 0) return;

    modelGeraete->removeRow(row);
    modelGeraete->submitAll();
    modelGeraete->select();
}

=======
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334
