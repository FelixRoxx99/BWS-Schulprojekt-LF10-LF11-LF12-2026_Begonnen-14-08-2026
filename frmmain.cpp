#include "frmmain.h"
#include "ui_frmmain.h"
#include "statusdelegate.h"
#include "devicedialog.h"
#include "userdialog.h"
#include "ausleihedialog.h"
#include "authutils.h"

#include <QSqlQuery>
#include <QPushButton>
#include <QModelIndex>
#include <QMessageBox>
#include <QFile>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QMetaObject>
#include <QAction>
#include <QLabel>

FrmMain::FrmMain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FrmMain)
{
    ui->setupUi(this);

    // ============================================
    // GERÄTEÜBERSICHT - Modell initialisieren
    // ============================================
    modelGeraete = new QSqlTableModel(this);
    modelGeraete->setTable("geraete");
    modelGeraete->select();

    ui->tblGeraete->setModel(modelGeraete);
    ui->tblGeraete->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblGeraete->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // ============================================
    // BENUTZER-MODELL (für Admin-Seite)
    // ============================================
    modelBenutzer = new QSqlTableModel(this);
    modelBenutzer->setTable("benutzer");
    // Verstecke Passwort-Spalten
    modelBenutzer->setHeaderData(2, Qt::Horizontal, "***Passwort***");
    modelBenutzer->setHeaderData(4, Qt::Horizontal, "***Salt***");
    modelBenutzer->setHeaderData(5, Qt::Horizontal, "***KDF***");
    modelBenutzer->select();
    ui->tblBenutzer->setModel(modelBenutzer);

    // ============================================
    // AUSLEIH-HISTORY - Modell initialisieren
    // ============================================
    modelAusleihe = new QSqlQueryModel(this);
    ui->tblAusleihe->setModel(modelAusleihe);

    // initial load of ausleihe
    refreshAusleihe();

    // ============================================
    // STATUS-SPALTE: Custom Delegate für farbliche Darstellung
    // ============================================
    int statusCol = -1;
    for(int c=0; c<modelGeraete->columnCount(); ++c){
        if(modelGeraete->headerData(c, Qt::Horizontal).toString().toLower().contains("status")) {
            statusCol = c;
            break;
        }
    }
    if(statusCol >= 0) {
        ui->tblGeraete->setItemDelegateForColumn(statusCol, new StatusDelegate(this));
    }

    // Hide id column for overview
    if(modelGeraete->columnCount() > 0) {
        ui->tblGeraete->setColumnHidden(0, true);
    }

    // ============================================
    // NAVIGATION - Menu-Item Connections
    // ============================================
    connect(ui->navList, &QListWidget::currentRowChanged, this, &FrmMain::onNavChanged);
    ui->navList->setCurrentRow(0);

    // ============================================
    // BUTTONS: Überblick-Seite
    // ============================================
    connect(ui->btnTestdaten, &QPushButton::clicked, this, &FrmMain::loadTestData);
    connect(ui->btnAddGeraet, &QPushButton::clicked, this, &FrmMain::addGeraet);
    connect(ui->btnDelete, &QPushButton::clicked, this, &FrmMain::deleteGeraet);
    connect(ui->btnOpenAddDialog, &QPushButton::clicked, this, &FrmMain::showAddPage);

    // ============================================
    // BUTTONS: Admin-Seite
    // ============================================
    connect(ui->btnAddUser, &QPushButton::clicked, this, &FrmMain::on_btnAddUser_clicked);
    connect(ui->btnEditUser, &QPushButton::clicked, this, &FrmMain::on_btnEditUser_clicked);
    connect(ui->btnDeleteUser, &QPushButton::clicked, this, &FrmMain::on_btnDeleteUser_clicked);

    // Context-Action für Benutzer-Freischaltung (Rechtsklick)
    QAction *actApprove = new QAction("Freischalten", this);
    connect(actApprove, &QAction::triggered, this, &FrmMain::on_btnApproveUser_clicked);
    ui->tblBenutzer->addAction(actApprove);
    ui->tblBenutzer->setContextMenuPolicy(Qt::ActionsContextMenu);

    // ============================================
    // BUTTONS: Ausleihe-Seite
    // ============================================
    connect(ui->btnAusleihen, &QPushButton::clicked, this, &FrmMain::on_btnAusleihen_clicked);
    connect(ui->btnRueckgabe, &QPushButton::clicked, this, &FrmMain::on_btnRueckgaba_clicked);

    // ============================================
    // DOUBLE-CLICK: Geräte bearbeiten
    // ============================================
    connect(ui->tblGeraete, &QTableView::doubleClicked, this, &FrmMain::openEditForIndex);
}

FrmMain::~FrmMain()
{
    delete ui;
}

// ============================================
// KERNFUNKTION: Rollen-basierte UI-Anpassung
// ============================================
void FrmMain::setCurrentUser(int userId, const QString &role){
    m_userId = userId;
    m_role = role;
    
    qDebug() << "➜ setCurrentUser aufgerufen: userId=" << userId << "role=" << role;

    // ============================================
    // 1. NUTZER (einfacher Mitarbeiter - READ-ONLY)
    // ============================================
    if(role.toLower() == "nutzer") {
        qDebug() << "➜ Konfiguriere UI für NUTZER (Read-Only)";
        
        // Navigation: Nur "Übersicht" erlaubt
        for(int i=0; i<ui->navList->count(); ++i){
            QString text = ui->navList->item(i)->text();
            if(text == "Übersicht") {
                ui->navList->item(i)->setHidden(false);
            } else {
                ui->navList->item(i)->setHidden(true);
            }
        }
        
        // Buttons verstecken
        ui->btnTestdaten->setHidden(true);      // Testdaten
        ui->btnAddGeraet->setHidden(true);      // Gerät hinzufügen
        ui->btnDelete->setHidden(true);         // Löschen
        ui->btnOpenAddDialog->setHidden(true);  // Gerät erfassen
        
        // Admin-UI komplett verstecken
        ui->tblBenutzer->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->btnAddUser->setHidden(true);
        ui->btnEditUser->setHidden(true);
        ui->btnDeleteUser->setHidden(true);
        
        // Ausleihe-Buttons verstecken
        ui->btnAusleihen->setHidden(true);
        ui->btnRueckgaba->setHidden(true);
    }
    
    // ============================================
    // 2. MITARBEITER (Ausleihe/Rückgabe erlaubt)
    // ============================================
    else if(role.toLower() == "mitarbeiter") {
        qDebug() << "➜ Konfiguriere UI für MITARBEITER (Ausleihe erlaubt)";
        
        // Navigation: "Übersicht" + "Ausleihen" erlaubt
        for(int i=0; i<ui->navList->count(); ++i){
            QString text = ui->navList->item(i)->text();
            if(text == "Übersicht" || text == "Ausleihen") {
                ui->navList->item(i)->setHidden(false);
            } else {
                ui->navList->item(i)->setHidden(true);
            }
        }
        
        // Geräteverwaltungs-Buttons verstecken
        ui->btnTestdaten->setHidden(true);      // Testdaten
        ui->btnAddGeraet->setHidden(true);      // Gerät hinzufügen (Mitarbeiter NICHT)
        ui->btnDelete->setHidden(true);         // Löschen (Nur Admin)
        ui->btnOpenAddDialog->setHidden(true);  // Gerät erfassen (Nur Admin)
        
        // Admin-UI komplett verstecken
        ui->tblBenutzer->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->btnAddUser->setHidden(true);
        ui->btnEditUser->setHidden(true);
        ui->btnDeleteUser->setHidden(true);
        
        // Ausleihe-Buttons SICHTBAR
        ui->btnAusleihen->setHidden(false);
        ui->btnRueckgaba->setHidden(false);
    }
    
    // ============================================
    // 3. ADMINISTRATOR (volle Kontrolle)
    // ============================================
    else if(role.toLower() == "admin") {
        qDebug() << "➜ Konfiguriere UI für ADMIN (volle Rechte)";
        
        // Navigation: ALLES sichtbar
        for(int i=0; i<ui->navList->count(); ++i){
            ui->navList->item(i)->setHidden(false);
        }
        
        // Geräteverwaltungs-Buttons ALLE SICHTBAR
        ui->btnTestdaten->setHidden(false);      // Testdaten
        ui->btnAddGeraet->setHidden(false);      // Gerät hinzufügen
        ui->btnDelete->setHidden(false);         // Löschen
        ui->btnOpenAddDialog->setHidden(false);  // Gerät erfassen
        
        // Admin-Buttons SICHTBAR + editierbar
        ui->btnAddUser->setHidden(false);
        ui->btnEditUser->setHidden(false);
        ui->btnDeleteUser->setHidden(false);
        ui->tblBenutzer->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
        
        // Ausleihe-Buttons SICHTBAR
        ui->btnAusleihen->setHidden(false);
        ui->btnRueckgaba->setHidden(false);
    } 
    else {
        qWarning() << "⚠ Unbekannte Rolle:" << role;
    }
}

// ============================================
// AUSLEIHE-HISTORY: Refresh Funktion
// ============================================
void FrmMain::refreshAusleihe(){
    const QString sql =
        "SELECT a.id AS ausleihe_id, g.name AS geraet, b.benutzername AS benutzer, "
        "a.ausleihdatum, a.rueckgabedatum "
        "FROM ausleihe a "
        "JOIN geraete g ON a.geraet_id = g.id "
        "JOIN benutzer b ON a.benutzer_id = b.id "
        "ORDER BY a.ausleihdatum DESC";
    modelAusleihe->setQuery(sql);
    modelAusleihe->setHeaderData(0, Qt::Horizontal, "ID");
    modelAusleihe->setHeaderData(1, Qt::Horizontal, "Gerät");
    modelAusleihe->setHeaderData(2, Qt::Horizontal, "Benutzer");
    modelAusleihe->setHeaderData(3, Qt::Horizontal, "Ausleihdatum");
    modelAusleihe->setHeaderData(4, Qt::Horizontal, "Rückgabedatum");
    ui->tblAusleihe->resizeColumnsToContents();
}

// ============================================
// GERÄTE: Test-Daten laden
// ============================================
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
    refreshAusleihe();
    QMessageBox::information(this, "Erfolg", "Test-Daten hinzugefügt");
}

// ============================================
// GERÄTE: Neues Gerät hinzufügen
// ============================================
void FrmMain::addGeraet()
{
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Geräte hinzufügen.");
        return;
    }

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
        if(!q.exec()) {
            QMessageBox::critical(this, "Fehler", q.lastError().text());
        } else {
            QMessageBox::information(this, "Erfolg", "Gerät hinzugefügt");
            modelGeraete->select();
        }
    }
}

// ============================================
// GERÄTE: Gerät löschen (Nur Admin)
// ============================================
void FrmMain::deleteGeraet()
{
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Geräte löschen.");
        return;
    }

    QModelIndex idx = ui->tblGeraete->currentIndex();
    int row = idx.row();
    if (row < 0) {
        QMessageBox::warning(this, "Auswahl", "Bitte ein Gerät auswählen.");
        return;
    }

    if(QMessageBox::question(this, "Bestätigung", "Gerät wirklich löschen?") == QMessageBox::Yes){
        modelGeraete->removeRow(row);
        if(!modelGeraete->submitAll()){
            QMessageBox::critical(this, "Fehler", "Gerät konnte nicht gelöscht werden");
        } else {
            QMessageBox::information(this, "Erfolg", "Gerät gelöscht");
            modelGeraete->select();
            refreshAusleihe();
        }
    }
}

// ============================================
// GERÄTE: Dialog zum Hinzufügen
// ============================================
void FrmMain::showAddPage(){
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Geräte erfassen.");
        return;
    }

    DeviceDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        modelGeraete->select();
        refreshAusleihe();
    }
}

// ============================================
// NAVIGATION: Seiten umschalten
// ============================================
void FrmMain::onNavChanged(int currentRow){
    ui->stackedWidget->setCurrentIndex(currentRow);
}

// ============================================
// GERÄTE: Bearbeiten (Double-Click)
// ============================================
void FrmMain::openEditForIndex(const QModelIndex &index){
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Geräte bearbeiten.");
        return;
    }

    if(!index.isValid()) return;
    int row = index.row();
    int id = modelGeraete->data(modelGeraete->index(row, 0)).toInt();
    
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
        if(!q.exec()) {
            QMessageBox::critical(this, "Fehler", q.lastError().text());
        } else {
            QMessageBox::information(this, "Erfolg", "Gerät aktualisiert");
            modelGeraete->select();
            refreshAusleihe();
        }
    }
}

// ============================================
// ADMIN: Benutzer hinzufügen
// ============================================
void FrmMain::on_btnAddUser_clicked(){
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Benutzer anlegen.");
        return;
    }
    UserDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        QString uname = dlg.username();
        QString role = dlg.role();
        QString pass = dlg.password();
        QString salt = AuthUtils::makeSalt();
        int iter = 100000;
        QByteArray key = AuthUtils::pbkdf2_hmac_sha256(pass.toUtf8(), salt.toUtf8(), iter, 32);
        QString hashed = AuthUtils::toHex(key);
        QSqlQuery q;
        q.prepare("INSERT INTO benutzer (benutzername, passwort, rolle, salt, kdf, iter, approved) VALUES (:u,:p,:r,:s,:k,:i,:a)");
        q.bindValue(":u", uname);
        q.bindValue(":p", hashed);
        q.bindValue(":r", role);
        q.bindValue(":s", salt);
        q.bindValue(":k", "pbkdf2");
        q.bindValue(":i", iter);
        q.bindValue(":a", 1);  // Automatisch freigeschalten
        if(!q.exec()) {
            QMessageBox::critical(this, "Fehler", q.lastError().text());
        } else {
            QMessageBox::information(this, "Erfolg", "Benutzer hinzugefügt");
            modelBenutzer->select();
        }
    }
}

// ============================================
// ADMIN: Benutzer bearbeiten
// ============================================
void FrmMain::on_btnEditUser_clicked(){
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Benutzer bearbeiten.");
        return;
    }
    QModelIndex idx = ui->tblBenutzer->currentIndex();
    int row = idx.row();
    if(row < 0) {
        QMessageBox::warning(this, "Auswahl", "Bitte einen Benutzer auswählen.");
        return;
    }
    QSqlRecord rec = modelBenutzer->record(row);
    UserDialog dlg(this);
    dlg.loadFromRecord(rec);
    if(dlg.exec() == QDialog::Accepted){
        QString uname = dlg.username();
        QString role = dlg.role();
        QString pass = dlg.password();
        QSqlQuery q;
        if(!pass.isEmpty()){
            QString salt = AuthUtils::makeSalt();
            int iter = 100000;
            QByteArray key = AuthUtils::pbkdf2_hmac_sha256(pass.toUtf8(), salt.toUtf8(), iter, 32);
            QString hashed = AuthUtils::toHex(key);
            q.prepare("UPDATE benutzer SET benutzername=:u, rolle=:r, passwort=:p, salt=:s, kdf=:k, iter=:i WHERE id=:id");
            q.bindValue(":p", hashed);
            q.bindValue(":s", salt);
            q.bindValue(":k", "pbkdf2");
            q.bindValue(":i", iter);
        } else {
            q.prepare("UPDATE benutzer SET benutzername=:u, rolle=:r WHERE id=:id");
        }
        q.bindValue(":u", uname);
        q.bindValue(":r", role);
        q.bindValue(":id", rec.value("id"));
        if(!q.exec()) {
            QMessageBox::critical(this, "Fehler", q.lastError().text());
        } else {
            QMessageBox::information(this, "Erfolg", "Benutzer aktualisiert");
            modelBenutzer->select();
        }
    }
}

// ============================================
// ADMIN: Benutzer löschen
// ============================================
void FrmMain::on_btnDeleteUser_clicked(){
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Benutzer löschen.");
        return;
    }
    QModelIndex idx = ui->tblBenutzer->currentIndex();
    int row = idx.row();
    if(row < 0) {
        QMessageBox::warning(this, "Auswahl", "Bitte einen Benutzer auswählen.");
        return;
    }
    int id = modelBenutzer->record(row).value("id").toInt();
    if(id == m_userId){
        QMessageBox::warning(this, "Fehler", "Sie können sich selbst nicht löschen.");
        return;
    }
    if(QMessageBox::question(this, "Bestätigung", "Benutzer wirklich löschen?") == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("DELETE FROM benutzer WHERE id=:id");
        q.bindValue(":id", id);
        if(!q.exec()) {
            QMessageBox::critical(this, "Fehler", q.lastError().text());
        } else {
            QMessageBox::information(this, "Erfolg", "Benutzer gelöscht");
            modelBenutzer->select();
        }
    }
}

// ============================================
// ADMIN: Benutzer freischalten (Rechtsklick)
// ============================================
void FrmMain::on_btnApproveUser_clicked(){
    if(m_role.toLower() != "admin"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Administratoren dürfen Benutzer freischalten.");
        return;
    }
    QModelIndex idx = ui->tblBenutzer->currentIndex();
    int row = idx.row();
    if(row < 0) return;
    int id = modelBenutzer->record(row).value("id").toInt();
    QSqlQuery q;
    q.prepare("UPDATE benutzer SET approved=1 WHERE id=:id");
    q.bindValue(":id", id);
    if(!q.exec()) {
        QMessageBox::critical(this, "Fehler", q.lastError().text());
    } else {
        QMessageBox::information(this, "Erfolg", "Benutzer freigeschaltet");
        modelBenutzer->select();
    }
}

// ============================================
// AUSLEIHE: Gerät ausleihen (Mitarbeiter + Admin)
// ============================================
void FrmMain::on_btnAusleihen_clicked(){
    // Nur Mitarbeiter und Admin dürfen Geräte ausleihen
    if(m_role.toLower() == "nutzer"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Mitarbeiter oder Administratoren dürfen Geräte ausleihen.");
        return;
    }
    AusleiheDialog dlg(this);
    if(dlg.exec() == QDialog::Accepted){
        int gid = dlg.selectedGeraetId();
        int uid = dlg.selectedBenutzerId();
        if(gid <= 0 || uid <= 0) return;
        QSqlQuery q;
        // Check: ist Gerät verfügbar?
        q.prepare("SELECT status FROM geraete WHERE id=:id");
        q.bindValue(":id", gid);
        if(q.exec() && q.next()){
            QString st = q.value(0).toString();
            if(!st.toLower().contains("verfügbar")){
                QMessageBox::warning(this, "Nicht verfügbar", "Das Gerät ist nicht verfügbar.");
                return;
            }
        }
        // Transaktion für Datenkonsistenz
        QSqlDatabase db = QSqlDatabase::database();
        if(!db.transaction()){
            QMessageBox::critical(this, "Fehler", "Konnte keine DB-Transaktion starten.");
            return;
        }
        bool ok = true;
        q.prepare("INSERT INTO ausleihe (geraet_id, benutzer_id, ausleihdatum) VALUES (:g,:b,:d)");
        q.bindValue(":g", gid);
        q.bindValue(":b", uid);
        q.bindValue(":d", QDateTime::currentDateTime().toString(Qt::ISODate));
        if(!q.exec()){
            ok = false;
        }
        if(ok){
            QSqlQuery u;
            u.prepare("UPDATE geraete SET status='Ausgeliehen' WHERE id=:id AND status='Verfügbar'");
            u.bindValue(":id", gid);
            if(!u.exec() || u.numRowsAffected() == 0) ok = false;
        }
        if(!ok){
            db.rollback();
            QMessageBox::critical(this, "Fehler", "Ausleihe konnte nicht durchgeführt werden (konkurrierender Zugriff oder DB-Fehler).");
            return;
        }
        db.commit();
        QMessageBox::information(this, "Erfolg", "Gerät ausgeliehen");
        modelGeraete->select();
        refreshAusleihe();
    }
}

// ============================================
// AUSLEIHE: Gerät zurückgeben (Mitarbeiter + Admin)
// ============================================
void FrmMain::on_btnRueckgaba_clicked(){
    // Nur Mitarbeiter und Admin dürfen Rückgaben durchführen
    if(m_role.toLower() == "nutzer"){
        QMessageBox::warning(this, "Zugriff verweigert", "Nur Mitarbeiter oder Administratoren dürfen Rückgaben durchführen.");
        return;
    }
    QModelIndex idx = ui->tblAusleihe->currentIndex();
    if(!idx.isValid()){
        QMessageBox::warning(this, "Auswahl", "Bitte einen Ausleih-Eintrag auswählen.");
        return;
    }
    int row = idx.row();
    int ausleiheId = modelAusleihe->data(modelAusleihe->index(row, 0)).toInt();
    QString rueck = modelAusleihe->data(modelAusleihe->index(row, 4)).toString();
    if(!rueck.isEmpty()){
        QMessageBox::information(this, "Rückgabe", "Dieses Gerät wurde bereits zurückgegeben.");
        return;
    }
    // Gerät-ID für diese Ausleihe holen
    QSqlQuery q;
    q.prepare("SELECT geraet_id FROM ausleihe WHERE id=:id");
    q.bindValue(":id", ausleiheId);
    if(q.exec() && q.next()){
        int gid = q.value(0).toInt();
        // Transaktion für Rückgabe
        QSqlDatabase db = QSqlDatabase::database();
        if(!db.transaction()){
            QMessageBox::critical(this, "Fehler", "Konnte keine DB-Transaktion starten.");
            return;
        }
        bool ok = true;
        QSqlQuery u;
        u.prepare("UPDATE ausleihe SET rueckgabedatum=:d WHERE id=:id AND rueckgabedatum IS NULL");
        u.bindValue(":d", QDateTime::currentDateTime().toString(Qt::ISODate));
        u.bindValue(":id", ausleiheId);
        if(!u.exec() || u.numRowsAffected() == 0){ ok = false; }
        if(ok){
            QSqlQuery s;
            s.prepare("UPDATE geraete SET status='Verfügbar' WHERE id=:id AND status='Ausgeliehen'");
            s.bindValue(":id", gid);
            if(!s.exec() || s.numRowsAffected() == 0) ok = false;
        }
        if(!ok){
            db.rollback();
            QMessageBox::critical(this, "Fehler", "Rückgabe konnte nicht durchgeführt werden (konkurrierender Zugriff oder DB-Fehler).");
            return;
        }
        db.commit();
        QMessageBox::information(this, "Erfolg", "Gerät zurückgegeben");
        modelGeraete->select();
        refreshAusleihe();
    }
}
