#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Store Management System");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("COS3711");

    MainWindow w;
    w.show();

    return a.exec();
}
