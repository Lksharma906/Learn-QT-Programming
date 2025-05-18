#include <QCoreApplication>
#include "test.h"
#include <QPointer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject *obj = new QObject(nullptr); // Not following parent child relation ship.
    obj->setObjectName("Test Object");

    QPointer<QObject> p(obj);

    test t;
    t.widget = p;
    t.useWidget();

    delete obj; // We have deleted the object which we casted to Qpointer. In normal C++ it creates a dangling pointer.
    t.useWidget(); // Here its get cleared automatically when reference is destroyed.




    return a.exec();
}
