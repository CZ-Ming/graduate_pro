#include "homew.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeW w;
    w.show();

    return a.exec();
}
