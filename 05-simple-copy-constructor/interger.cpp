#include "interger.h"

interger::interger(QObject *parent)
    : QObject{parent}
{
    cout<< "QT Constructor";
}

interger::interger() {
    ptr = new int(0);
    cout<< "Constructor";
}

interger::interger(int val)
{
    ptr = new int(val);
    cout<< "P Constructor";
}

int interger::getvalue()
{
    return *ptr;
}

void interger::setValue(int x)
{
    *ptr = x;
}

interger::interger(const interger & obj)
{
    cout <<" c constructor";
    ptr = new int(*obj.ptr);
}

interger::~interger()
{
    delete ptr;
}
