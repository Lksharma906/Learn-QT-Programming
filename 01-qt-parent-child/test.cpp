#include "test.h"

test::test(QObject *parent)
    : QObject{parent}
{
    qInfo() <<this << "Construncted";
}

test::~test()
{
    qInfo() <<this << "Destructed";
}

void test::makechild(QString name)
{
    test * child = new test(this);
    child->setObjectName(name);
}

