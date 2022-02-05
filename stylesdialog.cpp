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

void StylesDialog::setAppStyle(const QString &style)
{
        QPalette palette;

        palette.setColor(QPalette::Window, darkGray);
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, black);
        palette.setColor(QPalette::AlternateBase, darkGray);
        palette.setColor(QPalette::ToolTipBase, blue);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, darkGray);
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::Link, blue);
        palette.setColor(QPalette::Highlight, blue);
        palette.setColor(QPalette::HighlightedText, Qt::black);

        palette.setColor(QPalette::Active, QPalette::Button, gray.darker());
        palette.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
        palette.setColor(QPalette::Disabled, QPalette::WindowText, gray);
        palette.setColor(QPalette::Disabled, QPalette::Text, gray);
        palette.setColor(QPalette::Disabled, QPalette::Light, darkGray);

        qApp->setPalette(palette);

}
