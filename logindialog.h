#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog() override;

    int userId() const
    {
        return m_userId;
    }

    QString role() const
    {
        return m_role;
    }

private slots:
    void on_btnLogin_clicked();
    void on_btnCancel_clicked();

private:
    Ui::LoginDialog *ui;

    int m_userId = -1;
    QString m_role;
};

#endif
