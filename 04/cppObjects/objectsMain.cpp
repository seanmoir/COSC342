#include <iostream>
#include <memory>
#include <vector>

#include "Object.h"
#include "Derived.h"

int main(int argc, char *argv[])
{

    /* Your code goes here */
    Derived d1;
    Derived d2(d1);
    d2.setValue(5);
    d1 = d2;
    std::cout << "Derived d1 has value: " << d1.getValue() << std::endl;
    std::cout << "Derived d2 has value: " << d2.getValue() << std::endl;


    Object obj;
    Derived der;
    Object& ref = der;
    Object* ptr = new Derived();
    obj.whatAmI();
    der.whatAmI();
    ref.whatAmI();
    ptr->whatAmI();
    delete ptr;

    return 0;
}
