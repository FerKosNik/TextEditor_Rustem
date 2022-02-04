#include "keybinddialog.h"
#include "ui_keybinddialog.h"

KeyBindDialog::KeyBindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyBindDialog),
    keyBind { nullptr }
{
    ui->setupUi(this);
}

KeyBindDialog::KeyBindDialog(QVector<KeyBind> *iKeysVec) :
    KeyBindDialog()
{
    keyBind = iKeysVec;

    //Warning: The order should be the same as filling QVector
    //in MainWindow constructor. Later I will decide how to
    //manage it more properly.
    actionsIndexes.push_back({ 0, QObject::tr("Открыть") });
    actionsIndexes.push_back({ 1, QObject::tr("Русский") });
    actionsIndexes.push_back({ 2, QObject::tr("Открыть для чтения") });
    actionsIndexes.push_back({ 3, QObject::tr("Закрыть") });
    actionsIndexes.push_back({ 4, QObject::tr("Сохранить как") });
    actionsIndexes.push_back({ 5, QObject::tr("Сохранить") });
    actionsIndexes.push_back({ 6, QObject::tr("Выход") });
    actionsIndexes.push_back({ 7, QObject::tr("Английский") });
    actionsIndexes.push_back({ 8, QObject::tr("Помощь") });
    actionsIndexes.push_back({ 9, QObject::tr("Забиндить клавиши") });

    modsTranslator.push_back({ Qt::NoModifier, tr("Пусто") });
    modsTranslator.push_back({ Qt::ControlModifier, "Cntrl" });
    modsTranslator.push_back({ Qt::ShiftModifier, "Shift" });

    //Unite these four loops to one function in the future
    for (int i{}; i < actionsIndexes.size(); ++i)
        ui->cbAction->addItem(actionsIndexes[i].second);

    for (int i{}; i < modsTranslator.size(); ++i)
        ui->cbMod1->addItem(modsTranslator[i].second);

    for (int i{}; i < modsTranslator.size(); ++i)
        ui->cbMod2->addItem(modsTranslator[i].second);

    for (int i{}; i < keyTranslator.size(); ++i)
        ui->cbKey->addItem(keyTranslator[i].second);

    ui->cbAction->setCurrentIndex(0);
    assert(ui->cbAction->currentText() == actionsIndexes[0].second);
    updateInterface(0);

}

KeyBindDialog::~KeyBindDialog()
{
    delete ui;
}

void KeyBindDialog::on_btnCancel_clicked()
{
   close();
}

void KeyBindDialog::updateInterface(int index) const
{

    //These loops could also possible be united in
    //a more smaller code, но так пока нагляднее
    for (int i{}; i < modsTranslator.size(); ++i)
    {
       if (keyBind->at(index).mod1 == modsTranslator[i].first)
       {
           ui->cbMod1->setCurrentText(modsTranslator[i].second);
           break;
       }
    }

    for (int i{}; i < modsTranslator.size(); ++i)
    {
       if (keyBind->at(index).mod2 == modsTranslator[i].first)
       {
           ui->cbMod2->setCurrentText(modsTranslator[i].second);
           break;
       }
    }

    for (int i{}; i < keyTranslator.size(); ++i)
    {
       if (keyBind->at(index).key == keyTranslator[i].first)
       {
           ui->cbKey->setCurrentText(keyTranslator[i].second);
           break;
       }
    }
}

void KeyBindDialog::on_cbAction_activated(const QString /*&arg1*/)
{
    updateInterface(ui->cbAction->currentIndex());
}

//Заметка на будущее развитие: здесь нет проверок на затирание
//других, уже имеющихся для других целей комбинаций как для
//самой программы, так и для системы в целом.
void KeyBindDialog::on_btnOk_clicked()
{

    newKeyBind.second = ui->cbAction->currentIndex();

    for (int i{}; i < modsTranslator.size(); ++i)
    {
        if (modsTranslator[i].second == ui->cbMod1->currentText())
        {
            newKeyBind.first.mod1 = modsTranslator[i].first;
            break;
        }
    }

    for (int i{}; i < modsTranslator.size(); ++i)
    {
        if (modsTranslator[i].second == ui->cbMod2->currentText())
        {
            newKeyBind.first.mod2 = modsTranslator[i].first;
            break;
        }
    }

    for (int i{}; i < keyTranslator.size(); ++i)
    {
        if (keyTranslator[i].second == ui->cbKey->currentText())
        {
            newKeyBind.first.key = keyTranslator[i].first;
            break;
        }
    }

    close();
}

const QPair<KeyBind, int> &KeyBindDialog::getNewBinding() const {

   return newKeyBind;
}
