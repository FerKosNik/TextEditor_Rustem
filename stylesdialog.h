#ifndef STYLESDIALOG_H
#define STYLESDIALOG_H

#include <QDialog>

namespace Ui {
class StylesDialog;
}

struct StyleColors {
    QColor firstColor;
    QColor secondColor;
    QColor thirdColor;
    QColor fourthColor;
    QColor textOne;
    QColor textTwo;
};

class StylesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StylesDialog(QWidget *parent = nullptr);
    ~StylesDialog();

    void setAppStyle(const StyleColors&);

private slots:
    void on_btnClose_clicked();

    void on_rbLighter_clicked();

    void on_rbDarker_clicked();

private:
    Ui::StylesDialog *ui;
    QVector <QString> styleNames;
};

//colors
const StyleColors colorsArr [] =
{
   { { 255, 255, 0 },
     { 255, 255, 204 },
     { 255, 255, 230 },
     { 255, 255, 102 },
     Qt::black,
     Qt::white
   },
   { { 204, 255, 153 },
     { 204, 255, 51 },
     { 204, 255, 204 },
     { 204, 204, 0 },
     Qt::black,
     Qt::white
   },

   { { 25, 26, 255 },
     { 102, 102, 255 },
     { 25, 25, 25 },
     { 128, 128, 255 },
      Qt::white,
      Qt::black
   },

   { { 53, 53, 53 },
     { 128, 128, 128 },
     { 25, 25, 25 },
     { 42, 130, 218 },
      Qt::white,
      Qt::black
   }
};

#endif // STYLESDIALOG_H
