#include <QCoreApplication>
#include "interger.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    interger i1(10);

    interger i2(i1);
    return a.exec();
}
