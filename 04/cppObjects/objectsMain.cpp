#include <iostream>
#include <memory>
#include <vector>

#include "Object.h"
#include "Derived.h"

int main(int argc, char *argv[])
{

    /* Your code goes here */
    Object obj1;
    Object obj2(5);
    Object obj3(obj1);
    Object obj4 = obj2;
    Object ref = obj3;
    std::unique_ptr<Object> sptr(new Object());
    //Object *ptr = new Object();
    obj3 = obj2;

    Derived d1;
    Derived d2(d1);
    d2.setValue(5);
    d1 = d2;
    std::cout << "Derived d1 has value: " << d1.getValue() << std::endl;
    std::cout << "Derived d2 has value: " << d2.getValue() << std::endl;

    return 0;
}
