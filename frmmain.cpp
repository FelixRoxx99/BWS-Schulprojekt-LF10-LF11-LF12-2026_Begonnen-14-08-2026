*** Begin Patch
*** Update File: frmmain.cpp
@@
 #include "statusdelegate.h"
 #include "devicedialog.h"
 #include "userdialog.h"
+#include "ausleihedialog.h"
 #include "authutils.h"
 
 #include <QSqlQuery>
 #include <QPushButton>
 #include <QModelIndex>
 #include <QMessageBox>
 #include <QFile>
+#include <QSqlQueryModel>
+#include <QDateTime>
@@
     // Benutzer-Modell (für Admin-Seite)
     modelBenutzer = new QSqlTableModel(this);
     modelBenutzer->setTable("benutzer");
     modelBenutzer->select();
     ui->tblBenutzer->setModel(modelBenutzer);
+
+    // Ausleih-History
+    modelAusleihe = new QSqlQueryModel(this);
+    ui->tblAusleihe->setModel(modelAusleihe);
+    // header labels will be set when query loaded
+    auto refreshAusleihe = [this](){
+        QString sql = "SELECT a.id AS ausleihe_id, g.name AS geraet, b.benutzername AS benutzer, a.ausleihdatum, a.rueckgabedatum FROM ausleihe a JOIN geraete g ON a.geraet_id=g.id JOIN benutzer b ON a.benutzer_id=b.id ORDER BY a.ausleihdatum DESC";
+        modelAusleihe->setQuery(sql);
+        modelAusleihe->setHeaderData(0, Qt::Horizontal, "ID");
+        modelAusleihe->setHeaderData(1, Qt::Horizontal, "Gerät");
+        modelAusleihe->setHeaderData(2, Qt::Horizontal, "Benutzer");
+        modelAusleihe->setHeaderData(3, Qt::Horizontal, "Ausleihdatum");
+        modelAusleihe->setHeaderData(4, Qt::Horizontal, "Rückgabedatum");
+        ui->tblAusleihe->resizeColumnsToContents();
+    };
+    refreshAusleihe();
@@
     // admin buttons
     connect(ui->btnAddUser, &QPushButton::clicked, this, &FrmMain::on_btnAddUser_clicked);
     connect(ui->btnEditUser, &QPushButton::clicked, this, &FrmMain::on_btnEditUser_clicked);
     connect(ui->btnDeleteUser, &QPushButton::clicked, this, &FrmMain::on_btnDeleteUser_clicked);
+
+    // Ausleihe buttons
+    connect(ui->btnAusleihen, &QPushButton::clicked, this, &FrmMain::on_btnAusleihen_clicked);
+    connect(ui->btnRueckgabe, &QPushButton::clicked, this, &FrmMain::on_btnRueckgabe_clicked);
@@
 }
@@
 void FrmMain::showAddPage(){
     // switch to add dialog page or open dialog
     DeviceDialog dlg(this);
     if(dlg.exec() == QDialog::Accepted){
         modelGeraete->select();
+        // refresh ausleihe view too
+        QMetaObject::invokeMethod(this, "on_btnAusleihen_clicked", Qt::QueuedConnection);
     }
 }
@@
 void FrmMain::openEditForIndex(const QModelIndex &index){
@@
 }
+
+void FrmMain::on_btnAusleihen_clicked(){
+    // Only Mitarbeiter or Admin or User? Allow Mitarbeiter and Admin (role != user)
+    if(m_role.toLower() == "user"){
+        QMessageBox::warning(this, "Zugriff verweigert", "Nur Mitarbeiter oder Administratoren dürfen Geräte ausleihen.");
+        return;
+    }
+    AusleiheDialog dlg(this);
+    if(dlg.exec() == QDialog::Accepted){
+        int gid = dlg.selectedGeraetId();
+        int uid = dlg.selectedBenutzerId();
+        if(gid <= 0 || uid <= 0) return;
+        QSqlQuery q;
+        // check status
+        q.prepare("SELECT status FROM geraete WHERE id=:id");
+        q.bindValue(":id", gid);
+        if(q.exec() && q.next()){
+            QString st = q.value(0).toString();
+            if(!st.toLower().contains("verfügbar")){
+                QMessageBox::warning(this, "Nicht verfügbar", "Das Gerät ist nicht verfügbar.");
+                return;
+            }
+        }
+        // insert ausleihe
+        q.prepare("INSERT INTO ausleihe (geraet_id, benutzer_id, ausleihdatum) VALUES (:g,:b,:d)");
+        q.bindValue(":g", gid);
+        q.bindValue(":b", uid);
+        q.bindValue(":d", QDateTime::currentDateTime().toString(Qt::ISODate));
+        if(!q.exec()){
+            QMessageBox::critical(this, "Fehler", q.lastError().text());
+            return;
+        }
+        // update device status
+        QSqlQuery u;
+        u.prepare("UPDATE geraete SET status='Ausgeliehen' WHERE id=:id");
+        u.bindValue(":id", gid);
+        u.exec();
+        modelGeraete->select();
+        modelAusleihe->setQuery(modelAusleihe->query().lastQuery()); // refresh
+        modelAusleihe->setQuery(modelAusleihe->query().lastQuery());
+        // better: run refresh query
+        QString sql = "SELECT a.id AS ausleihe_id, g.name AS geraet, b.benutzername AS benutzer, a.ausleihdatum, a.rueckgabedatum FROM ausleihe a JOIN geraete g ON a.geraet_id=g.id JOIN benutzer b ON a.benutzer_id=b.id ORDER BY a.ausleihdatum DESC";
+        modelAusleihe->setQuery(sql);
+        ui->tblAusleihe->resizeColumnsToContents();
+    }
+}
+
+void FrmMain::on_btnRueckgabe_clicked(){
+    // Only Mitarbeiter or Admin allowed
+    if(m_role.toLower() == "user"){
+        QMessageBox::warning(this, "Zugriff verweigert", "Nur Mitarbeiter oder Administratoren dürfen Rückgaben durchführen.");
+        return;
+    }
+    QModelIndex idx = ui->tblAusleihe->currentIndex();
+    if(!idx.isValid()){
+        QMessageBox::warning(this, "Auswahl", "Bitte einen Ausleih-Eintrag auswählen.");
+        return;
+    }
+    int row = idx.row();
+    int ausleiheId = modelAusleihe->data(modelAusleihe->index(row,0)).toInt();
+    QString rueck = modelAusleihe->data(modelAusleihe->index(row,4)).toString();
+    if(!rueck.isEmpty()){
+        QMessageBox::information(this, "Rückgabe", "Dieses Gerät wurde bereits zurückgegeben.");
+        return;
+    }
+    // find geraet_id for this ausleihe
+    QSqlQuery q;
+    q.prepare("SELECT geraet_id FROM ausleihe WHERE id=:id");
+    q.bindValue(":id", ausleiheId);
+    if(q.exec() && q.next()){
+        int gid = q.value(0).toInt();
+        QSqlQuery u;
+        u.prepare("UPDATE ausleihe SET rueckgabedatum=:d WHERE id=:id AND rueckgabedatum IS NULL");
+        u.bindValue(":d", QDateTime::currentDateTime().toString(Qt::ISODate));
+        u.bindValue(":id", ausleiheId);
+        if(!u.exec()){
+            QMessageBox::critical(this, "Fehler", u.lastError().text());
+            return;
+        }
+        QSqlQuery s;
+        s.prepare("UPDATE geraete SET status='Verfügbar' WHERE id=:id");
+        s.bindValue(":id", gid);
+        s.exec();
+        modelGeraete->select();
+        QString sql = "SELECT a.id AS ausleihe_id, g.name AS geraet, b.benutzername AS benutzer, a.ausleihdatum, a.rueckgabedatum FROM ausleihe a JOIN geraete g ON a.geraet_id=g.id JOIN benutzer b ON a.benutzer_id=b.id ORDER BY a.ausleihdatum DESC";
+        modelAusleihe->setQuery(sql);
+        ui->tblAusleihe->resizeColumnsToContents();
+    }
+}
*** End Patch
