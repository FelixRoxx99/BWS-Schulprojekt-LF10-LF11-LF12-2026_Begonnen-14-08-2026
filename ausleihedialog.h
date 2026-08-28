#ifndef AUSLEIHEDIALOG_H
#define AUSLEIHEDIALOG_H

#include <QDialog>

namespace Ui { class AusleiheDialog; }

class AusleiheDialog : public QDialog {
    Q_OBJECT
public:
    explicit AusleiheDialog(QWidget *parent=nullptr);
    ~AusleiheDialog() override;
    int selectedGeraetId() const;
    int selectedBenutzerId() const;
private slots:
    void on_btnOk_clicked();
private:
    Ui::AusleiheDialog *ui;
};

#endif // AUSLEIHEDIALOG_H
