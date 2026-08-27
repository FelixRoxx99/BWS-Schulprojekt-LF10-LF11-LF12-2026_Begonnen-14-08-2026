#ifndef GERAETEVIEW_H
#define GERAETEVIEW_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class GeraeteView;
}

class GeraeteView : public QWidget
{
    Q_OBJECT

public:
    explicit GeraeteView(QWidget *parent = nullptr);
    ~GeraeteView();

private slots:
    void loadTestData();
    void addDevice();
    void deleteDevice();

private:
    Ui::GeraeteView *ui;
    QSqlTableModel *model;
};

#endif // GERAETEVIEW_H

