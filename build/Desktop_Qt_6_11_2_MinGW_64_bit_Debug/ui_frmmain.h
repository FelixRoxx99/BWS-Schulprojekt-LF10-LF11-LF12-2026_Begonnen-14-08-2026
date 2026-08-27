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
    QTableView *tableView;
    QPushButton *btnLoadTestData;
    QPushButton *btnAdd;
    QPushButton *pushButton_3;

    void setupUi(QWidget *FrmMain)
    {
        if (FrmMain->objectName().isEmpty())
            FrmMain->setObjectName("FrmMain");
        FrmMain->resize(800, 600);
        tableView = new QTableView(FrmMain);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(370, 200, 256, 192));
        btnLoadTestData = new QPushButton(FrmMain);
        btnLoadTestData->setObjectName("btnLoadTestData");
        btnLoadTestData->setGeometry(QRect(140, 480, 171, 61));
        btnAdd = new QPushButton(FrmMain);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(370, 480, 161, 61));
        pushButton_3 = new QPushButton(FrmMain);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(580, 480, 141, 61));

        retranslateUi(FrmMain);

        QMetaObject::connectSlotsByName(FrmMain);
    } // setupUi

    void retranslateUi(QWidget *FrmMain)
    {
        FrmMain->setWindowTitle(QCoreApplication::translate("FrmMain", "FrmMain", nullptr));
        btnLoadTestData->setText(QCoreApplication::translate("FrmMain", "Ger\303\244t Hinzuf\303\274gen", nullptr));
        btnAdd->setText(QCoreApplication::translate("FrmMain", "bearbeiten", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FrmMain", "l\303\266schen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmMain: public Ui_FrmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
