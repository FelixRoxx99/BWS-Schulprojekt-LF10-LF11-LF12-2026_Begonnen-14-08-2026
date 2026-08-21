#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>

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

private:
    Ui::FrmMain *ui;
};
#endif // FRMMAIN_H
