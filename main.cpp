#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication burya(argc, argv);
    MainWindow w;
    w.showMaximized();
    return burya.exec();
}
