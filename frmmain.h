#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
<<<<<<< HEAD
#include <QSqlTableModel>

namespace Ui {
class FrmMain;
}
=======

QT_BEGIN_NAMESPACE
namespace Ui {
class FrmMain;
}
QT_END_NAMESPACE
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334

class FrmMain : public QWidget
{
    Q_OBJECT

public:
    explicit FrmMain(QWidget *parent = nullptr);
<<<<<<< HEAD
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


=======
    ~FrmMain() override;

private:
    Ui::FrmMain *ui;
};
#endif // FRMMAIN_H
>>>>>>> 79a5cd02d348e4b82d3f0ea836bd85144c6b2334
