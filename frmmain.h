#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class FrmMain;
}

class FrmMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private slots:
    void loadTestData();
    void addGeraet();
    void deleteGeraet();

private:
    Ui::FrmMain *ui;
    QSqlTableModel *modelGeraete;
};

#endif // FRMMAIN_H


