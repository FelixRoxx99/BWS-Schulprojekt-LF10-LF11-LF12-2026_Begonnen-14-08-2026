#include "frmmain.h"
#include "ui_frmmain.h"

#include <QSqlQuery>
#include <QPushButton>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QMessageBox>

FrmMain::FrmMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    // Geräteübersicht laden
    modelGeraete = new QSqlTableModel(this);
    modelGeraete->setTable("geraete");
    modelGeraete->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelGeraete->select();

    ui->tblGeraete->setModel(modelGeraete);

    // TableView optisch anpassen wie im Mockup
    ui->tblGeraete->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblGeraete->verticalHeader()->setVisible(true); // Zeilennummern
    ui->tblGeraete->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblGeraete->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tblGeraete->setAlternatingRowColors(true);
    ui->tblGeraete->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tblGeraete->setShowGrid(true);

    // Kopfzeilen freundlicher Benennung
    modelGeraete->setHeaderData(modelGeraete->fieldIndex("id"), Qt::Horizontal, tr("id"));
    modelGeraete->setHeaderData(modelGeraete->fieldIndex("name"), Qt::Horizontal, tr("name"));
    modelGeraete->setHeaderData(modelGeraete->fieldIndex("typ"), Qt::Horizontal, tr("typ"));
    modelGeraete->setHeaderData(modelGeraete->fieldIndex("seriennummer"), Qt::Horizontal, tr("seriennummer"));
    modelGeraete->setHeaderData(modelGeraete->fieldIndex("standort"), Qt::Horizontal, tr("standort"));
    modelGeraete->setHeaderData(modelGeraete->fieldIndex("status"), Qt::Horizontal, tr("status"));

    // Buttons verbinden
    connect(ui->btnTestdaten, &QPushButton::clicked, this, &FrmMain::loadTestData);
    connect(ui->btnAddGeraet, &QPushButton::clicked, this, &FrmMain::addGeraet);
    connect(ui->btnDelete, &QPushButton::clicked, this, &FrmMain::deleteGeraet);

    // Optional: leichtes Styling, so dass Buttons wie im Mockup wirken
    QString btnStyle = "QPushButton { background: #ffffff; border: 1px solid #e0e0e0; border-radius: 6px; padding: 12px; }"
                       "QPushButton:hover { background: #f7f7f7; }";
    ui->btnTestdaten->setStyleSheet(btnStyle);
    ui->btnAddGeraet->setStyleSheet(btnStyle);
    ui->btnDelete->setStyleSheet(btnStyle);
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
    QItemSelectionModel *sel = ui->tblGeraete->selectionModel();
    QModelIndexList indexes = sel->selectedRows();
    if (indexes.isEmpty()) {
        return;
    }

    if (QMessageBox::question(this, tr("Löschen bestätigen"), tr("Markierte Geräte wirklich löschen?"),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    // Um Reihen korrekt zu entfernen, sortiere absteigend
    std::sort(indexes.begin(), indexes.end(), [](const QModelIndex &a, const QModelIndex &b){ return a.row() > b.row(); });

    for (const QModelIndex &idx : indexes) {
        modelGeraete->removeRow(idx.row());
    }

    // Änderungen abschicken und neu laden
    if (!modelGeraete->submitAll()) {
        QMessageBox::warning(this, tr("Fehler"), tr("Fehler beim Löschen: %1").arg(modelGeraete->lastError().text()));
        modelGeraete->revertAll();
    }

    modelGeraete->select();
}
