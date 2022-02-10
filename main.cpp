#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile resFile { RESOURCE_FILE };
    if (!resFile.exists())
    {
        QMessageBox::warning(nullptr, FILE_NOT_FOUND,
            CANT_OPEN_FILE + RESOURCE_FILE);

    return -1;
    }

    QResource::registerResource(RESOURCE_FILE);

    MainWindow w;
    w.show();

    return a.exec();
}
