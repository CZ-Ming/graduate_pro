#include "ledctl.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LedCtl w;
    w.show();

    return a.exec();
}
