#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>

namespace Ui { class RegistrationDialog; }

class RegistrationDialog : public QDialog {
    Q_OBJECT
public:
    explicit RegistrationDialog(QWidget *parent=nullptr);
    ~RegistrationDialog() override;
    QString username() const;
    QString password() const;
private slots:
    void on_btnOk_clicked();
private:
    // no designer file used; we build UI in code to avoid adding .ui
    QWidget *m_widget = nullptr; // placeholder to keep header stable
};

#endif // REGISTRATIONDIALOG_H
