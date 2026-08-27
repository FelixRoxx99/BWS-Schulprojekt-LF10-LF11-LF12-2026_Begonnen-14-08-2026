#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmMain;
}
QT_END_NAMESPACE

class FrmMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain() override;

private slots:
    void loadTestData();
    void addGeraet();
    void deleteGeraet();

private:
    Ui::FrmMain *ui;
    QSqlTableModel *modelGeraete;
};

#endif // FRMMAIN_H
