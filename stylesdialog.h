#ifndef STYLESDIALOG_H
#define STYLESDIALOG_H

#include <QDialog>

namespace Ui {
class StylesDialog;
}

class StylesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StylesDialog(QWidget *parent = nullptr);
    ~StylesDialog();

private slots:
    void on_btnClose_clicked();

private:
    Ui::StylesDialog *ui;
};

#endif // STYLESDIALOG_H
