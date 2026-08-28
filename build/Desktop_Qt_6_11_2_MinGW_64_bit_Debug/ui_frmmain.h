/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmMain
{
public:
    QTableView *tblGeraete;
    QPushButton *btnTestdaten;
    QPushButton *btnAddGeraet;
    QPushButton *btnDelete;

    void setupUi(QWidget *FrmMain)
    {
        if (FrmMain->objectName().isEmpty())
            FrmMain->setObjectName("FrmMain");
        FrmMain->resize(800, 600);
        tblGeraete = new QTableView(FrmMain);
        tblGeraete->setObjectName("tblGeraete");
        tblGeraete->setGeometry(QRect(70, 100, 651, 351));
        btnTestdaten = new QPushButton(FrmMain);
        btnTestdaten->setObjectName("btnTestdaten");
        btnTestdaten->setGeometry(QRect(70, 480, 171, 61));
        btnAddGeraet = new QPushButton(FrmMain);
        btnAddGeraet->setObjectName("btnAddGeraet");
        btnAddGeraet->setGeometry(QRect(320, 480, 161, 61));
        btnDelete = new QPushButton(FrmMain);
        btnDelete->setObjectName("btnDelete");
        btnDelete->setGeometry(QRect(580, 480, 141, 61));

        retranslateUi(FrmMain);

        QMetaObject::connectSlotsByName(FrmMain);
    } // setupUi

    void retranslateUi(QWidget *FrmMain)
    {
        FrmMain->setWindowTitle(QCoreApplication::translate("FrmMain", "FrmMain", nullptr));
        btnTestdaten->setText(QCoreApplication::translate("FrmMain", "Ger\303\244t Hinzuf\303\274gen (Testdaten)", nullptr));
        btnAddGeraet->setText(QCoreApplication::translate("FrmMain", "Ger\303\244t hinzuf\303\274gen", nullptr));
        btnDelete->setText(QCoreApplication::translate("FrmMain", "l\303\266schen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmMain: public Ui_FrmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
