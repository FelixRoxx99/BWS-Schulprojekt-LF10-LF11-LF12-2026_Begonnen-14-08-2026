#include "frmmain.h"
#include "ui_frmmain.h"
#include "statusdelegate.h"
#include "devicedialog.h"

#include <QSqlQuery>
#include <QPushButton>
#include <QModelIndex>
#include <QMessageBox>
#include <QFile>

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
    ui->tblGeraete->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblGeraete->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Benutzer-Modell (für Admin-Seite)
    modelBenutzer = new QSqlTableModel(this);
    modelBenutzer->setTable("benutzer");
    modelBenutzer->select();
    ui->tblBenutzer->setModel(modelBenutzer);

    // Styling: Status Delegate
    // Find status column index by name
    int statusCol = -1;
    for(int c=0;c<modelGeraete->columnCount();++c){
        if(modelGeraete->headerData(c, Qt::Horizontal).toString().toLower().contains("status")) { statusCol = c; break; }
    }
    if(statusCol>=0) ui->tblGeraete->setItemDelegateForColumn(statusCol, new StatusDelegate(this));

    // Hide id column for overview
    if(modelGeraete->columnCount()>0) ui->tblGeraete->setColumnHidden(0, true);

    // Navigation
    connect(ui->navList, &QListWidget::currentRowChanged, this, &FrmMain::onNavChanged);
    ui->navList->setCurrentRow(0);

    // Buttons
    connect(ui->btnTestdaten, &QPushButton::clicked, this, &FrmMain::loadTestData);
    connect(ui->btnAddGeraet, &QPushButton::clicked, this, &FrmMain::addGeraet);
    connect(ui->btnDelete, &QPushButton::clicked, this, &FrmMain::deleteGeraet);
    connect(ui->btnOpenAddDialog, &QPushButton::clicked, this, &FrmMain::showAddPage);

    // Double click edit
    connect(ui->tblGeraete, &QTableView::doubleClicked, this, &FrmMain::openEditForIndex);
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::setCurrentUser(int userId, const QString &role){
    m_userId = userId;
    m_role = role;
    // show/hide admin nav
    if(role.toLower()=="admin"){
        // ensure admin page visible
        for(int i=0;i<ui->navList->count();++i){
            if(ui->navList->item(i)->text() == "Admin") { ui->navList->item(i)->setHidden(false); break; }
        }
    } else {
        for(int i=0;i<ui->navList->count();++i){
            if(ui->navList->item(i)->text() == "Admin") { ui->navList->item(i)->setHidden(true); break; }
        }
    }
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
    // öffne DeviceDialog
    DeviceDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        auto d = dlg.deviceData();
        QSqlQuery q;
        q.prepare("INSERT INTO geraete (name, typ, seriennummer, standort, status) VALUES (:n,:t,:s,:st,:stt)");
        q.bindValue(":n", d.name);
        q.bindValue(":t", d.type);
        q.bindValue(":s", d.serial);
        q.bindValue(":st", d.location);
        q.bindValue(":stt", d.status);
        if(!q.exec()) QMessageBox::critical(this, "Fehler", q.lastError().text());
        modelGeraete->select();
    }
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

void FrmMain::showAddPage(){
    // switch to add dialog page or open dialog
    DeviceDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        modelGeraete->select();
    }
}

void FrmMain::onNavChanged(int currentRow){
    ui->stackedWidget->setCurrentIndex(currentRow);
}

void FrmMain::openEditForIndex(const QModelIndex &index){
    if(!index.isValid()) return;
    int row = index.row();
    int id = modelGeraete->data(modelGeraete->index(row,0)).toInt();
    // load data into dialog
    DeviceDialog dlg(this);
    dlg.loadFromRecord(modelGeraete->record(row));
    if(dlg.exec() == QDialog::Accepted){
        auto d = dlg.deviceData();
        QSqlQuery q;
        q.prepare("UPDATE geraete SET name=:n, typ=:t, seriennummer=:s, standort=:st, status=:stt WHERE id=:id");
        q.bindValue(":n", d.name);
        q.bindValue(":t", d.type);
        q.bindValue(":s", d.serial);
        q.bindValue(":st", d.location);
        q.bindValue(":stt", d.status);
        q.bindValue(":id", id);
        if(!q.exec()) QMessageBox::critical(this, "Fehler", q.lastError().text());
        modelGeraete->select();
    }
}

// aktueller Stand -27-08-2026 um 18:11 Uhr
