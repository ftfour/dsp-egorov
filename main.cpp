#include "dspmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DSPMainWindow w;
    w.show();
    return a.exec();
}
