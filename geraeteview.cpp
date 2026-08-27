#include "geraeteview.h"
#include "ui_frmmain.h""
#include <QSqlQuery>
#include <QMessageBox>

GeraeteView::GeraeteView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeraeteView)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("geraete");
    model->select();

    ui->tableView->setModel(model);

    connect(ui->btnLoadTestData, &QPushButton::clicked, this, &GeraeteView::loadTestData);
    connect(ui->btnAdd, &QPushButton::clicked, this, &GeraeteView::addDevice);
    connect(ui->bnDelete, &QPushButton::clicked, this, &GeraeteView::deleteDevice);
}

GeraeteView::~GeraeteView()
{
    delete ui;
}

void GeraeteView::loadTestData()
{
    QSqlQuery q;
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Laptop-01', 'Laptop', 'LTP100456', 'Büro 2', 'Verfügbar')");
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Tablet-02', 'Tablet', 'TBL200123', 'Büro 1', 'Ausgeliehen')");
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Beamer-05', 'Beamer', 'BMR500789', 'Konferenzraum', 'Defekt')");

    model->select();
}

void GeraeteView::addDevice()
{
    QSqlQuery q;
    q.exec("INSERT INTO geraete (name, typ, seriennummer, standort, status) "
           "VALUES ('Neues Gerät', 'Laptop', 'XXX', 'Büro 3', 'Verfügbar')");
    model->select();
}

void GeraeteView::deleteDevice()
{
    int row = ui->tableView->currentIndex().row();
    if (row < 0) return;

    model->removeRow(row);
    model->submitAll();
    model->select();
}
