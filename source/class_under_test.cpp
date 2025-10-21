#include "class_under_test.h"


SomeClass::SomeClass()
{
    a = 0;
}


bool SomeClass::publicFunc(int a)
{
    this->a = a;
    return a >= 0;
}
