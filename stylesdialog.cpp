#include "stylesdialog.h"
#include "ui_stylesdialog.h"
#include <QDebug>

StylesDialog::StylesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StylesDialog),
    currentColors { nullptr}
{
    ui->setupUi(this);
}

StylesDialog::StylesDialog(StyleColors *inColors):
    StylesDialog()

{

    currentColors = inColors;

    styleNames.push_back(QObject::tr("Morning"));
    styleNames.push_back(QObject::tr("Day"));
    styleNames.push_back(QObject::tr("Evening"));
    styleNames.push_back(QObject::tr("Night"));

    initInterface();

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


    StyleColors applyingColors{};

    if ((*checkedRadBtn)->text() ==  styleNames.at(0))
    {
        applyingColors = colorsArr[0];
    }

    else if ((*checkedRadBtn)->text() == styleNames.at(1))
    {
        applyingColors = colorsArr[1];
    }

    else if ((*checkedRadBtn)->text() == styleNames.at(2))
    {
        applyingColors = colorsArr[3];
    }

    else if ((*checkedRadBtn)->text() == styleNames.at(3))
    {
        applyingColors = colorsArr[4];
    }

    setAppStyle(applyingColors);

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

void StylesDialog::setAppStyle(const StyleColors &colorStyle)
{
        QPalette palette;

        palette.setColor(QPalette::Window, colorStyle.firstColor);
        palette.setColor(QPalette::WindowText, colorStyle.textOne);
        palette.setColor(QPalette::Base, colorStyle.thirdColor);
        palette.setColor(QPalette::AlternateBase, colorStyle.firstColor);
        palette.setColor(QPalette::ToolTipBase, colorStyle.fourthColor);
        palette.setColor(QPalette::ToolTipText, colorStyle.textOne);
        palette.setColor(QPalette::Text, colorStyle.textOne);
        palette.setColor(QPalette::Button, colorStyle.firstColor);
        palette.setColor(QPalette::ButtonText, colorStyle.textOne);
        palette.setColor(QPalette::Link, colorStyle.fourthColor);
        palette.setColor(QPalette::Highlight, colorStyle.fourthColor);
        palette.setColor(QPalette::HighlightedText, colorStyle.textTwo);

        palette.setColor(QPalette::Active, QPalette::Button, colorStyle.secondColor.darker());
        palette.setColor(QPalette::Disabled, QPalette::ButtonText, colorStyle.secondColor);
        palette.setColor(QPalette::Disabled, QPalette::WindowText, colorStyle.secondColor);
        palette.setColor(QPalette::Disabled, QPalette::Text, colorStyle.secondColor);
        palette.setColor(QPalette::Disabled, QPalette::Light, colorStyle.firstColor);

        qApp->setPalette(palette);
}

void StylesDialog::initInterface()
{
    if (*currentColors == colorsArr[0] || *currentColors == colorsArr[1])
    {
        qDebug() << "light";
        on_rbLighter_clicked();
        ui->rbLighter->setChecked(true);

        if (*currentColors == colorsArr[0])
            ui->rbMorning->setChecked(true);
        else
            ui->rbDay->setChecked(true);
    }
    else if (*currentColors == colorsArr[2] || *currentColors == colorsArr[3])
    {
        qDebug() <<"dark";
        on_rbDarker_clicked();
        ui->rbDarker->setChecked(true);

        if (*currentColors == colorsArr[2])
            ui->rbEvening->setChecked(true);
        else
            ui->rbNight->setChecked(true);
    }
    else
    {
        on_rbDarker_clicked();
        ui->rbDarker->setChecked(true);
        ui->rbEvening->setChecked(true);
    }


}
