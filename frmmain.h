#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class FrmMain; }
QT_END_NAMESPACE

class FrmMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain() override;

    void setCurrentUser(int userId, const QString &role);

private slots:
    void loadTestData();
    void addGeraet();
    void deleteGeraet();
    void showAddPage();
    void onNavChanged(int currentRow);
    void openEditForIndex(const QModelIndex &index);

    // admin slots
    void on_btnAddUser_clicked();
    void on_btnEditUser_clicked();
    void on_btnDeleteUser_clicked();

    // ausleihe slots
    void on_btnAusleihen_clicked();
    void on_btnRueckgabe_clicked();

private:
    Ui::FrmMain *ui;
    QSqlTableModel *modelGeraete;
    QSqlTableModel *modelBenutzer;
    QSqlQueryModel *modelAusleihe;
    int m_userId = -1;
    QString m_role;
};

#endif // FRMMAIN_H
