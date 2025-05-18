#include "test.h"

test::test(QObject *parent)
    : QObject{parent}
{
    qInfo() << this << "construncted";
}

test::~test()
{
    qInfo() << this << "destructed";
}

void test::useWidget()
{
    if(!widget.data())
    {
        qInfo() << "No pointer !!!";
        return;
    }

    qInfo() << "Using widget";
    widget->setObjectName("Used Widget");
}

