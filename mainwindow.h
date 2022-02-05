#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "main.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionOpen_read_only_mode_triggered();

    void on_actionSaveAs_triggered();

    void on_actionExit_triggered();

    void on_actionHelp_triggered();

    void on_actionSave_triggered();

    void on_actionClose_triggered();

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionKey_bindings_triggered();


    void on_plainTextEdit_textChanged();

    void on_actionChange_style_triggered();

private:
    Ui::MainWindow *ui;
    QFile *file;

    bool canSave;
    void disableSave(bool);

    QVector<KeyBind> keys;
    void actionChoosing(int);

    bool isModified;

    QTranslator *translator;

    StyleColors currentColorTheme;

protected:
    void keyReleaseEvent(QKeyEvent*) override;

};

#endif // MAINWINDOW_H
