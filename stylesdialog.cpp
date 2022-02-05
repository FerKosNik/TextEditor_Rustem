#include "stylesdialog.h"
#include "ui_stylesdialog.h"
#include <QDebug>

StylesDialog::StylesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StylesDialog)
{
    ui->setupUi(this);

    const QString styles [] = {
        { tr("Morning") },
        { tr("Day") },
        { tr("Evening") },
        { tr("Evening") },
        { tr("Night") }

    };

}

StylesDialog::~StylesDialog()
{
    delete ui;
}

void StylesDialog::on_btnClose_clicked()
{

    QList<QRadioButton*> styleButtons = ui->groupBoxStyle->findChildren<QRadioButton*>();
    qDebug () << styleButtons.size();

    const auto checkedRadBtn { std::find_if(styleButtons.begin(), styleButtons.end(),
        [](const auto &radioButton){ return radioButton->isChecked(); }) };

    qDebug() << (*checkedRadBtn)->text();

    if ((*checkedRadBtn)->text() == "Summer")
    {
    }
    else
    {
        QPalette lightPalette;
        lightPalette.setColor(QPalette::Window, QColor(11,11,11));
        qApp->setPalette(lightPalette);
    }

   close();
}

void StylesDialog::on_rbLighter_clicked()
{
    ui->rbEvening->setEnabled(false);
    ui->rbNight->setEnabled(false);

    ui->rbMorning->setEnabled(true);
    ui->rbDay->setEnabled(true);
}


void StylesDialog::on_rbDarker_clicked()
{
    ui->rbEvening->setEnabled(true);
    ui->rbNight->setEnabled(true);

    ui->rbMorning->setEnabled(false);
    ui->rbDay->setEnabled(false);

}

void StylesDialog::setAppStyle(const FourColors &colorStyle)
{
        QPalette palette;

        palette.setColor(QPalette::Window, colorStyle.firstColor);
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, colorStyle.thirdColor);
        palette.setColor(QPalette::AlternateBase, colorStyle.firstColor);
        palette.setColor(QPalette::ToolTipBase, colorStyle.fourthColor);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, colorStyle.firstColor);
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::Link, colorStyle.fourthColor);
        palette.setColor(QPalette::Highlight, colorStyle.fourthColor);
        palette.setColor(QPalette::HighlightedText, Qt::black);

        palette.setColor(QPalette::Active, QPalette::Button, colorStyle.secondColor.darker());
        palette.setColor(QPalette::Disabled, QPalette::ButtonText, colorStyle.secondColor);
        palette.setColor(QPalette::Disabled, QPalette::WindowText, colorStyle.secondColor);
        palette.setColor(QPalette::Disabled, QPalette::Text, colorStyle.secondColor);
        palette.setColor(QPalette::Disabled, QPalette::Light, colorStyle.firstColor);

        qApp->setPalette(palette);

}
