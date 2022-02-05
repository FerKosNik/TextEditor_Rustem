#include "stylesdialog.h"
#include "ui_stylesdialog.h"

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
