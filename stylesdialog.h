#ifndef STYLESDIALOG_H
#define STYLESDIALOG_H

#include <QDialog>
#include "main.h"

namespace Ui {
class StylesDialog;
}


class StylesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StylesDialog(QWidget *parent = nullptr);
    explicit StylesDialog(const StyleColors&);
    ~StylesDialog();

    void setAppStyle(const StyleColors&);
    const StyleColors &getCurrentTheme() const;

private slots:
    void on_btnClose_clicked();

    void on_rbLighter_clicked();

    void on_rbDarker_clicked();

private:
    Ui::StylesDialog *ui;
    QVector <QString> styleNames;
    void initInterface();
    //StyleColors *currentColors;
    StyleColors currentColors;
};

#endif // STYLESDIALOG_H
