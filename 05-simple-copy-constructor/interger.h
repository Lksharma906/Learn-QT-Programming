#ifndef INTERGER_H
#define INTERGER_H

#include <QObject>
#include <iostream>
using namespace std;

class interger : public QObject
{
    Q_OBJECT
    int * ptr;
public:
    explicit interger(QObject *parent = nullptr);
    explicit interger();
    explicit interger(int val);
    int getvalue();
    void setValue(int x);
    interger(const interger &obj); // take object by ref and to avoid modification use const.
    ~interger();

signals:
};

#endif // INTERGER_H
