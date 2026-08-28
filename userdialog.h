#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui { class UserDialog; }

class UserDialog : public QDialog {
    Q_OBJECT
public:
    explicit UserDialog(QWidget *parent=nullptr);
    ~UserDialog() override;
    QString username() const;
    QString role() const;
    QString password() const;
    void loadFromRecord(const QSqlRecord &rec);
private slots:
    void on_btnOk_clicked();
private:
    Ui::UserDialog *ui;
};

#endif // USERDIALOG_H
