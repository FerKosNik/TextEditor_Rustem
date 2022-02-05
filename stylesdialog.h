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

    void setAppStyle(const QString &);

private slots:
    void on_btnClose_clicked();

    void on_rbLighter_clicked();

    void on_rbDarker_clicked();

private:
    Ui::StylesDialog *ui;
};

   //colors
   const QColor darkGray(53, 53, 53);
   const QColor gray(128, 128, 128);
   const QColor black(25, 25, 25);
   const QColor blue(42, 130, 218);

#endif // STYLESDIALOG_H
