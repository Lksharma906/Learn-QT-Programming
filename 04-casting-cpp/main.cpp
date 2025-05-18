#include <QCoreApplication>
#include <iostream>
#include <string>
#include <exception>
class Int {
    int x;
public:
    Int(int x=0):x{x}{
        std::cout << "conversion constructor" << std::endl;
    }
    operator std::string() {
        std::cout << "conversion operator" << std::endl;
        return std::to_string(x);
    }
};


class Base {};
class Derived1: public Base {};
class Derived2: public Base {};

class dBase {
    virtual void print() {
        std::cout<< "base" << std::endl;
    }
};
class dDerived1: public dBase {
    void print() {
        std::cout<< "dDerived1" << std::endl;
    }
};
class dDerived2: public dBase {
    void print() {
        std::cout<< "dDerived2" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    // STATIC_CAST START HERE.....
    Int obj(3);

    std::string str1 = obj; // Conversion operator being called in this case.
    obj = 20; // conversion constructor is being called in this case.

    // However this is not distinguishable hence static_cast can be used to distinguish them.
    std::string str2 = static_cast<std::string>(obj);
    obj = static_cast<Int>(30);

    char c;
    int *p = (int*)&c; // This allows near by memeory access..
    //*p = 4; // may pass at compile time but fail at run time.
    //int *ip static_cast<int*>(&c); // Compile time error.


    /*Upcast and downcast*/
    Derived1 d1;
    Derived2 d2;

    Base *b1 = static_cast<Base*>(&d1);
    Base *b2 = static_cast<Base*>(&d2); // Upcast is fine.

    // confused downcast , do not know what we are downcasting.
    Derived1 *dp1 = static_cast<Derived1*>(b2); // Not a right practice.
    Derived2 *dp2 = static_cast<Derived2*>(b1); // Not a right practice.

    // STATIC_CAST END HERE.....
    // DYANMIC_CAST Start HERE.....

    dDerived1 dd1;
    dBase *bp = dynamic_cast<dBase*>(&dd1);
    dDerived2 *dd2 = dynamic_cast<dDerived2*>(&bp);
    if(dd2 == nullptr)
        std::cout<< "NULL"<< std::endl;


    try{
        dDerived2 &r1 = dynamic_cast<dDerived2&>(dd1);
    }
    catch(std:: exception& e) {
        std::cout << e.what() << std::endl;
    }


    // DYANMIC_CAST End HERE.....


    return a.exec();
}
