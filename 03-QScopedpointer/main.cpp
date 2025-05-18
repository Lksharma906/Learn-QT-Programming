#include <QCoreApplication>
#include <QObject>
#include <QScopedPointer>
#include "test.h"
#include <QDebug>


void takeReference(QScopedPointer<test> &t){
    // We can pass Scoped pointer or extend its scope using refrence but not by copy.

    qInfo() << "taking reference";
}

void takeCopy(QScopedPointer<test> t){
    // We can pass Scoped pointer or extend its scope using refrence but not by copy.

    qInfo() << "taking by copy";
}
void testSomething(test* t)
{
    if(!t) return; // If null return

    qInfo() <<"using it";
}

void doStuff()
{
    QScopedPointer<test> ptr(new test()); // Created a scoped pointer for test object.
    qInfo() << "doing stuff" ;
    testSomething(ptr.data());
    takeReference(ptr);
    //takeCopy(ptr); // This is not viable, as this is a call to deleted object.
    // This ptr will get deconstructed as it gets out of this scope.
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    for(int i =0; i< 10; i++)
        doStuff();


    return a.exec();
}
