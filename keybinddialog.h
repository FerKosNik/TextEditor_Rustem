#ifndef KEYBINDDIALOG_H
#define KEYBINDDIALOG_H

#include <QDialog>
#include "main.h"

namespace Ui {
class KeyBindDialog;
}

class KeyBindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyBindDialog(QWidget *parent = nullptr);
    explicit KeyBindDialog(QVector<KeyBind>*);
    ~KeyBindDialog();

    void updateInterface(int) const;

    const QPair<KeyBind, int> &getNewBinding() const;

private slots:
    void on_btnCancel_clicked();

    void on_cbAction_activated(const QString);

    void on_btnOk_clicked();

private:
    Ui::KeyBindDialog *ui;
    QVector<KeyBind> *keyBind;
    QPair<KeyBind, int> newKeyBind;
    QVector <QPair <int, QString> > actionsIndexes;
    QVector <QPair <Qt::KeyboardModifier, QString>> modsTranslator;
};

//Тут тоже пока не вся клава
const QVector<QPair<Qt::Key, QString>> keyTranslator  {
    { Qt::Key_A, "A" },
    { Qt::Key_B, "B" },
    { Qt::Key_C, "C" },
    { Qt::Key_D, "D" },
    { Qt::Key_E, "E" },
    { Qt::Key_H, "H" },
    { Qt::Key_K, "K" },
    { Qt::Key_O, "O" },
    { Qt::Key_Q, "Q" },
    { Qt::Key_R, "R" },
    { Qt::Key_S, "S" },
    { Qt::Key_X, "X" },
    { Qt::Key_F1, "F1" },
    { Qt::Key_F2, "F2" },
    { Qt::Key_F3, "F3" }
};

#endif // KEYBINDDIALOG_H
