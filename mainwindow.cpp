#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "keybinddialog.h"
#include <stylesdialog.h>

const QString FILE_NOT_FOUND { QObject::tr("Файл не найден") };
const QString TXT_FILE_ONLY { QObject::tr ("Текстовый файл(*.txt)") };
const QString CHOOSE_FILE_TO_OPEN { QObject::tr("Выберите файл для открытия") };
const QString CANT_OPEN_FILE { QObject::tr("Не могу открыть файл ") };
const QString FILE_SPACE { QObject::tr("Файл ") };

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      file(new QFile()), canSave(true),
      isModified(false),
      translator{new QTranslator()}
{

    currentColorTheme.firstColor = colorsArr[3].firstColor;
    currentColorTheme.secondColor = colorsArr[3].secondColor;
    currentColorTheme.thirdColor = colorsArr[3].thirdColor;
    currentColorTheme.fourthColor = colorsArr[3].fourthColor;
    currentColorTheme.textOne = colorsArr[3].textOne;
    currentColorTheme.textTwo = colorsArr[3].textTwo;



    //Warning: Do not change the order of pushing elements. It corresponds
    //vector 'actionsIndexes' (see keybinddialog.h). To avoid mismatches the
    //vector 'keys' has to be initialized from vector 'actionsIndexes' somehow.
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_O} );    // 0 - Open
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_R} ); // 1 - Rus
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_R} );	// 2 - read-only
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_X} ); 	// 3 - close
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_S} ); // 4 - save as
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_S} );    // 5 - save
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_Q} );    // 6 - quit
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_E} ); // 7 - Eng
    keys.push_back( { Qt::ControlModifier, Qt::NoModifier, Qt::Key_H} );    // 8 - help
    keys.push_back( { Qt::ControlModifier, Qt::ShiftModifier, Qt::Key_K} ); // 9 - bindings

    ui->setupUi(this);

    setWindowTitle(tr("Текстовый редактор"));

    ui->menuFile->setTitle(tr("Файл"));
    ui->actionOpen->setText(tr("Открыть"));
    ui->actionOpen_read_only_mode->setText(tr("Открыть только для чтения"));
    ui->actionClose->setText(tr("Закрыть"));
    ui->actionSave->setText(tr("Сохранить"));
    ui->actionSaveAs->setText(tr("Сохранить как"));
    ui->actionExit->setText(tr("Выход"));

    ui->menuSettings->setTitle(tr("Настройки"));

    ui->menuLanguage->setTitle(tr("Язык"));
    ui->actionRussian->setText(tr("Русский"));
    ui->actionEnglish->setText(tr("Английский"));

    ui->actionKey_bindings->setText(tr("Сочетания клавиш"));
    ui->actionChange_style->setText(tr("Сменить стиль"));

    ui->actionHelp->setText(tr("Помощь"));

    StylesDialog initTheme;
    initTheme.setAppStyle(currentColorTheme);

}

MainWindow::~MainWindow()
{
    delete translator;
    if (file->isOpen())
        file->close();
    delete file;

    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath { QFileDialog::getOpenFileName(this,
        CHOOSE_FILE_TO_OPEN, QDir::current().path(),
            TXT_FILE_ONLY) };

    if (filePath.length())
    {
         int index = filePath.indexOf(".txt");
         if (index != -1 && filePath.length() - 4 == index)
         {
             if (file->isOpen())
                    file->close();

             file->setFileName(filePath);
             if (file->open(QFile::ReadWrite | QFile::ExistingOnly))
             {
                 QTextStream stream(file);

                 disableSave(false);

                 ui->plainTextEdit->setPlainText(
                    stream.readAll());

                 ui->actionClose->setEnabled(true);
                 isModified = false;
                 ui->statusbar->showMessage(file->fileName());
             }
             else //!open
                 QMessageBox::warning(this, FILE_NOT_FOUND,
                    CANT_OPEN_FILE + filePath);

         }

    }

}


void MainWindow::on_actionOpen_read_only_mode_triggered()
{

    QString filePath { QFileDialog::getOpenFileName(this,
        CHOOSE_FILE_TO_OPEN, QDir::current().path(),
            TXT_FILE_ONLY) };

    if (filePath.length())
    {
         int index = filePath.indexOf(".txt");
         if (index != -1 && filePath.length() - 4 == index)
         {
             if (file->isOpen())
                    file->close();

             file->setFileName(filePath);
             if (file->open(QFile::ReadOnly | QFile::ExistingOnly))
             {
                 QTextStream stream(file);

                 ui->plainTextEdit->setPlainText(
                    stream.readAll());

                 file->close();

                 disableSave(true);

                 ui->actionClose->setEnabled(true);
                 isModified = false;

                 ui->statusbar->showMessage(FILE_SPACE + file->fileName() +
                    tr(" открыт в режиме \'только для чтения\'."));

             }
             else //!open
                 QMessageBox::warning(this, FILE_NOT_FOUND,
                    CANT_OPEN_FILE + filePath);

         }
    }

}


void MainWindow::on_actionSave_triggered()
{
    if (file->isOpen() && canSave)
    {
        QTextStream stream(file);
        stream.seek(0);
        stream << ui->plainTextEdit->toPlainText();

        ui->statusbar->showMessage(FILE_SPACE + file->fileName() +
            tr(" сохранён."));
    }
    else
        //на случай, если юзер захочет вывести help-text
        //в файл, а также создать новый текст и сохранить его
    {
        on_actionSaveAs_triggered();
        ui->actionClose->setEnabled(true);
    }

    isModified = false;
}

void MainWindow::on_actionSaveAs_triggered()
{
    if (file->isOpen()) file->close();

    QString filePath { QFileDialog::getSaveFileName(this,
         tr("Сохранить файл как"), QDir::current().path(),
            TXT_FILE_ONLY) };

    if (filePath.length())
    {
        QString ext { QString { &(filePath.data()
            [ filePath.length() - 4 ])}};

        file->setFileName(filePath);
        if (file->open(QFile::WriteOnly | QFile::NewOnly))
         {
           QTextStream stream(file);

           stream << ui->plainTextEdit->toPlainText();

           ui->statusbar->showMessage(tr("Файл сохранён как ") + file->fileName() + '.');
         }
        else //!open
        {
        QMessageBox::warning(this, FILE_NOT_FOUND,
             CANT_OPEN_FILE + filePath);

        }

    }
}


void MainWindow::on_actionExit_triggered()
{
   if (isModified && canSave)
   {


       QMessageBox msgBox(QMessageBox::Question,
                   tr("Текст изменён."),
                   tr("Хотите его сохранить?"),
                   QMessageBox::Save| QMessageBox::Cancel | QMessageBox::Discard,
                   this);

        msgBox.setButtonText(QMessageBox::Save, tr("Сохранить"));
        msgBox.setButtonText(QMessageBox::Cancel, tr("Отмена"));
        msgBox.setButtonText(QMessageBox::Discard, tr("Выйти без сохранения"));

        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
                on_actionSave_triggered();
                break;
          case QMessageBox::Discard:
                QApplication::quit();
                break;
          case QMessageBox::Cancel:
              break;
          default:
              //Недоступное ни в какое время место xD
              break;
        }
   }
   else
       QApplication::quit();
}


void MainWindow::on_actionHelp_triggered()
{

    if (file->isOpen()) file->close();

    ui->plainTextEdit->setPlainText(
        tr("Текстовый редактор с возможностью переключения языка интерфейса."));


     ui->statusbar->showMessage(tr("Краткая справка показана."));
     isModified = false;

}



void MainWindow::on_actionClose_triggered()
{
   if (file->isOpen())
       file->close();

   disableSave(false);

   ui->plainTextEdit->clear();

   ui->actionClose->setEnabled(false);

   ui->statusbar->clearMessage();
}

void MainWindow::disableSave(bool disableIt)
{
    if(disableIt)
    {
        canSave = false;
        ui->actionSave->setEnabled(false);
    }
    else
    {
        canSave = true;
        ui->actionSave->setEnabled(true);

    }
}


void MainWindow::on_actionRussian_triggered()
{

         translator->load(langRus);

         QApplication::installTranslator(translator);

         ui->actionEnglish->setChecked(false);
         ui->actionRussian->setChecked(true);

         ui->retranslateUi(this);

}


void MainWindow::on_actionEnglish_triggered()
{

         translator->load(langEng);

         QApplication::installTranslator(translator);

         ui->actionEnglish->setChecked(true);
         ui->actionRussian->setChecked(false);

         ui->retranslateUi(this);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    bool weHaveThisKey{ false };
    int i{};

    for (; i < keys.size(); ++i)
    {
        if ((event->key() == keys[i].key) && event->modifiers().testFlag(keys[i].mod1) &&
            event->modifiers().testFlag(keys[i].mod2))

            {
                weHaveThisKey = true;
                break;
            }
        else if ((event->key() == keys[i].key) &&
                  (event->modifiers().testFlag(keys[i].mod1)) &&
                    (keys[i].mod2 == Qt::NoModifier))
            {
                weHaveThisKey = true;
                break;
            }
        else if ((event->key() == keys[i].key) &&
                  (event->modifiers().testFlag(keys[i].mod2)) &&
                    (keys[i].mod1 == Qt::NoModifier))
            {
                weHaveThisKey = true;
                break;
            }

    }

    weHaveThisKey?
                actionChoosing(i):
                ui->statusbar->showMessage(": " + event->text());
}

void MainWindow::actionChoosing(int vectorIndex)
{
    switch (vectorIndex)
    {
        case 0:
            on_actionOpen_triggered();
            break;
        case 1:
            on_actionRussian_triggered();
            break;
        case 2:
            on_actionOpen_read_only_mode_triggered();
            break;
        case 3:
            on_actionClose_triggered();
            break;
        case 4:
            on_actionSaveAs_triggered();
            break;
        case 5:
            on_actionSave_triggered();
            break;
        case 6:
            on_actionExit_triggered();
            break;
        case 7:
            on_actionEnglish_triggered();
            break;
        case 8:
            on_actionHelp_triggered();
            break;
        case 9:
            on_actionKey_bindings_triggered();
            break;
        }
}

void MainWindow::on_actionKey_bindings_triggered()
{
    KeyBindDialog dialog(&keys);

    dialog.setModal(true);
    //
    dialog.exec();

    keys[dialog.getNewBinding().second] = dialog.getNewBinding().first;


}

void MainWindow::on_plainTextEdit_textChanged()
{
      isModified = true;
}


void MainWindow::on_actionChange_style_triggered()
{
    StylesDialog dialog(currentColorTheme);

    dialog.setModal(true);
    dialog.exec();

    currentColorTheme = dialog.getCurrentTheme();
}

