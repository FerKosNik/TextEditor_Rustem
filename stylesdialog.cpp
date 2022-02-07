#include "stylesdialog.h"
#include "ui_stylesdialog.h"

StylesDialog::StylesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StylesDialog)
    //currentColors { nullptr}
{
    ui->setupUi(this);
}

StylesDialog::StylesDialog(const StyleColors &inColors):
    StylesDialog()

{

    currentColors = inColors;


    styleNames.push_back(QObject::tr("Утро"));
    styleNames.push_back(QObject::tr("День"));
    styleNames.push_back(QObject::tr("Вечер"));
    styleNames.push_back(QObject::tr("Ночь"));

    initInterface();

}

StylesDialog::~StylesDialog()
{
    delete ui;
}

void StylesDialog::on_btnClose_clicked()
{

    QList<QRadioButton*> styleButtons = ui->groupBoxStyle->findChildren<QRadioButton*>();

    const auto checkedRadBtn { std::find_if(styleButtons.begin(), styleButtons.end(),
        [](const auto &radioButton){ return radioButton->isChecked(); }) };



    if ((*checkedRadBtn)->text() ==  styleNames.at(0))
    {
        currentColors = colorsArr[0];
    }

    else if ((*checkedRadBtn)->text() == styleNames.at(1))
    {
        currentColors = colorsArr[1];
    }

    else if ((*checkedRadBtn)->text() == styleNames.at(2))
    {
        currentColors = colorsArr[2];
    }

    else if ((*checkedRadBtn)->text() == styleNames.at(3))
    {
        currentColors = colorsArr[3];
    }
    else //this will never happens
        currentColors = colorsArr[3]; //default app style

    setAppStyle(currentColors);

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
    if (currentColors == colorsArr[0] || currentColors == colorsArr[1])
    {
        on_rbLighter_clicked();
        ui->rbLighter->setChecked(true);

        if (currentColors == colorsArr[0])
            ui->rbMorning->setChecked(true);
        else
            ui->rbDay->setChecked(true);
    }
    else if (currentColors == colorsArr[2] || currentColors == colorsArr[3])
    {
        on_rbDarker_clicked();
        ui->rbDarker->setChecked(true);

        if (currentColors == colorsArr[2])
            ui->rbEvening->setChecked(true);
        else
            ui->rbNight->setChecked(true);
    }
    else
    {
        on_rbDarker_clicked();
        ui->rbNight->setChecked(true);
    }

}

const StyleColors &StylesDialog::getCurrentTheme()const
{
//    qDebug () << currentColors.firstColor;
    return currentColors;
}
