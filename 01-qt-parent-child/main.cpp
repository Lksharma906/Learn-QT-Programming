#include <QCoreApplication>
#include "test.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    test *t = new test(nullptr);
    t->setObjectName("parent");

    for(int i = 0 ; i< 5; i++){
        t->makechild(QString::number(i));
    }

    delete t; // Even though we have deleted only the parent object but due to parent child relation-ship in QT child object also gets deleted.

    return a.exec();
}
