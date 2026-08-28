#ifndef DEVICEDIALOG_H
#define DEVICEDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui { class DeviceDialog; }

struct DeviceData { QString name; QString type; QString serial; QString location; QString status; };

class DeviceDialog : public QDialog {
    Q_OBJECT
public:
    explicit DeviceDialog(QWidget *parent=nullptr);
    ~DeviceDialog() override;
    DeviceData deviceData() const;
    void loadFromRecord(const QSqlRecord &rec);
private slots:
    void on_btnOk_clicked();
private:
    Ui::DeviceDialog *ui;
};

#endif // DEVICEDIALOG_H
