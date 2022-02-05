#include "stylesdialog.h"
#include "ui_stylesdialog.h"
#include <QDebug>

StylesDialog::StylesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StylesDialog)
{
    ui->setupUi(this);
}

StylesDialog::~StylesDialog()
{
    delete ui;
}

void StylesDialog::on_btnClose_clicked()
{
    //qDebug() << ui->groupBoxStyle->isChecked();

//    QList<QRadioButton *> allRadioButtons = groupBox.findChildren<QRadioButton *>();
    QList<QRadioButton*> styleButtons = ui->groupBoxStyle->findChildren<QRadioButton*>();
    qDebug () << styleButtons.size();

    const auto checkedRadBtn {std::find_if(styleButtons.begin(), styleButtons.end(),
        [](const auto &radioButton){ return radioButton->isChecked(); }) };

    //qDebug() << *checkedRadBtn->text();
    qDebug() << (*checkedRadBtn)->text();

    /*
    for (const auto &elem: styleButtons)
    {
        if (elem->isChecked())
        {
            qDebug()<< elem->text() << " is checked.";
            if (elem->text() == "Summer")
            {
                qApp->setStyleSheet(
                    "QPushButton  {font: bold 14 px; background-color: red;}" \
                        "QMainWindow{background-color:grey}");
            }
            break;
        }
    }
    */
   close();
}
