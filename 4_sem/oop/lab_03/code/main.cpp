#include "mainwindow.h"

#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
