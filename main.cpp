#include "mainwindow.h"

#include <QApplication>
#include <QResource>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile resFile { RESOURCE_FILE };
    if (!resFile.exists())
    {
        QMessageBox::warning(nullptr, QObject::tr("Не найден ресурс"),
            QObject::tr("Не обнаружер файл ресурсов ") + RESOURCE_FILE);

    return -1;
    }

    QResource::registerResource(RESOURCE_FILE);

    MainWindow w;
    w.show();

    return a.exec();
}
