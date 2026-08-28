*** Begin Patch
*** Update File: frmmain.h
@@
     void onNavChanged(int currentRow);
     void openEditForIndex(const QModelIndex &index);
+
+    // ausleihe slots
+    void on_btnAusleihen_clicked();
+    void on_btnRueckgabe_clicked();
@@
     QSqlTableModel *modelBenutzer;
+    QSqlQueryModel *modelAusleihe;
*** End Patch
