#include "mainwindow.h"
#include "test_geometricoperations.h"

#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QTest::qExec(new Test_Geometricoperations());
    return a.exec();
}
