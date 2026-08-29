/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FrmMain
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *navList;
    QStackedWidget *stackedWidget;
    QWidget *pageOverview;
    QVBoxLayout *verticalLayout_overview;
    QTableView *tblGeraete;
    QHBoxLayout *horizontalLayout_buttons;
    QPushButton *btnTestdaten;
    QPushButton *btnAddGeraet;
    QPushButton *btnDelete;
    QWidget *pageAdd;
    QVBoxLayout *verticalLayout_add;
    QPushButton *btnOpenAddDialog;
    QWidget *pageAusleihe;
    QVBoxLayout *verticalLayout_ausleihe;
    QTableView *tblAusleihe;
    QHBoxLayout *ausleiheButtons;
    QPushButton *btnAusleihen;
    QPushButton *btnRueckgabe;
    QWidget *pageAdmin;
    QVBoxLayout *verticalLayout_admin;
    QTableView *tblBenutzer;
    QHBoxLayout *adminButtons;
    QPushButton *btnAddUser;
    QPushButton *btnEditUser;
    QPushButton *btnDeleteUser;

    void setupUi(QWidget *FrmMain)
    {
        if (FrmMain->objectName().isEmpty())
            FrmMain->setObjectName("FrmMain");
        FrmMain->resize(900, 600);
        horizontalLayout = new QHBoxLayout(FrmMain);
        horizontalLayout->setObjectName("horizontalLayout");
        navList = new QListWidget(FrmMain);
        new QListWidgetItem(navList);
        new QListWidgetItem(navList);
        new QListWidgetItem(navList);
        new QListWidgetItem(navList);
        navList->setObjectName("navList");

        horizontalLayout->addWidget(navList);

        stackedWidget = new QStackedWidget(FrmMain);
        stackedWidget->setObjectName("stackedWidget");
        pageOverview = new QWidget();
        pageOverview->setObjectName("pageOverview");
        verticalLayout_overview = new QVBoxLayout(pageOverview);
        verticalLayout_overview->setObjectName("verticalLayout_overview");
        tblGeraete = new QTableView(pageOverview);
        tblGeraete->setObjectName("tblGeraete");

        verticalLayout_overview->addWidget(tblGeraete);

        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setObjectName("horizontalLayout_buttons");
        btnTestdaten = new QPushButton(pageOverview);
        btnTestdaten->setObjectName("btnTestdaten");

        horizontalLayout_buttons->addWidget(btnTestdaten);

        btnAddGeraet = new QPushButton(pageOverview);
        btnAddGeraet->setObjectName("btnAddGeraet");

        horizontalLayout_buttons->addWidget(btnAddGeraet);

        btnDelete = new QPushButton(pageOverview);
        btnDelete->setObjectName("btnDelete");

        horizontalLayout_buttons->addWidget(btnDelete);


        verticalLayout_overview->addLayout(horizontalLayout_buttons);

        stackedWidget->addWidget(pageOverview);
        pageAdd = new QWidget();
        pageAdd->setObjectName("pageAdd");
        verticalLayout_add = new QVBoxLayout(pageAdd);
        verticalLayout_add->setObjectName("verticalLayout_add");
        btnOpenAddDialog = new QPushButton(pageAdd);
        btnOpenAddDialog->setObjectName("btnOpenAddDialog");

        verticalLayout_add->addWidget(btnOpenAddDialog);

        stackedWidget->addWidget(pageAdd);
        pageAusleihe = new QWidget();
        pageAusleihe->setObjectName("pageAusleihe");
        verticalLayout_ausleihe = new QVBoxLayout(pageAusleihe);
        verticalLayout_ausleihe->setObjectName("verticalLayout_ausleihe");
        tblAusleihe = new QTableView(pageAusleihe);
        tblAusleihe->setObjectName("tblAusleihe");

        verticalLayout_ausleihe->addWidget(tblAusleihe);

        ausleiheButtons = new QHBoxLayout();
        ausleiheButtons->setObjectName("ausleiheButtons");
        btnAusleihen = new QPushButton(pageAusleihe);
        btnAusleihen->setObjectName("btnAusleihen");

        ausleiheButtons->addWidget(btnAusleihen);

        btnRueckgabe = new QPushButton(pageAusleihe);
        btnRueckgabe->setObjectName("btnRueckgabe");

        ausleiheButtons->addWidget(btnRueckgabe);


        verticalLayout_ausleihe->addLayout(ausleiheButtons);

        stackedWidget->addWidget(pageAusleihe);
        pageAdmin = new QWidget();
        pageAdmin->setObjectName("pageAdmin");
        verticalLayout_admin = new QVBoxLayout(pageAdmin);
        verticalLayout_admin->setObjectName("verticalLayout_admin");
        tblBenutzer = new QTableView(pageAdmin);
        tblBenutzer->setObjectName("tblBenutzer");

        verticalLayout_admin->addWidget(tblBenutzer);

        adminButtons = new QHBoxLayout();
        adminButtons->setObjectName("adminButtons");
        btnAddUser = new QPushButton(pageAdmin);
        btnAddUser->setObjectName("btnAddUser");

        adminButtons->addWidget(btnAddUser);

        btnEditUser = new QPushButton(pageAdmin);
        btnEditUser->setObjectName("btnEditUser");

        adminButtons->addWidget(btnEditUser);

        btnDeleteUser = new QPushButton(pageAdmin);
        btnDeleteUser->setObjectName("btnDeleteUser");

        adminButtons->addWidget(btnDeleteUser);


        verticalLayout_admin->addLayout(adminButtons);

        stackedWidget->addWidget(pageAdmin);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(FrmMain);

        QMetaObject::connectSlotsByName(FrmMain);
    } // setupUi

    void retranslateUi(QWidget *FrmMain)
    {
        FrmMain->setWindowTitle(QCoreApplication::translate("FrmMain", "Geraeteverwaltung", nullptr));

        const bool __sortingEnabled = navList->isSortingEnabled();
        navList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = navList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("FrmMain", "\303\234bersicht", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = navList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("FrmMain", "Ger\303\244t hinzuf\303\274gen", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = navList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("FrmMain", "Ausleihen", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = navList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("FrmMain", "Admin", nullptr));
        navList->setSortingEnabled(__sortingEnabled);

        btnTestdaten->setText(QCoreApplication::translate("FrmMain", "Ger\303\244t Hinzuf\303\274gen (Testdaten)", nullptr));
        btnAddGeraet->setText(QCoreApplication::translate("FrmMain", "Ger\303\244t hinzuf\303\274gen", nullptr));
        btnDelete->setText(QCoreApplication::translate("FrmMain", "l\303\266schen", nullptr));
        btnOpenAddDialog->setText(QCoreApplication::translate("FrmMain", "Neues Ger\303\244t erfassen", nullptr));
        btnAusleihen->setText(QCoreApplication::translate("FrmMain", "Ausleihen", nullptr));
        btnRueckgabe->setText(QCoreApplication::translate("FrmMain", "R\303\274ckgabe", nullptr));
        btnAddUser->setText(QCoreApplication::translate("FrmMain", "Benutzer hinzuf\303\274gen", nullptr));
        btnEditUser->setText(QCoreApplication::translate("FrmMain", "Bearbeiten", nullptr));
        btnDeleteUser->setText(QCoreApplication::translate("FrmMain", "Benutzer l\303\266schen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FrmMain: public Ui_FrmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
