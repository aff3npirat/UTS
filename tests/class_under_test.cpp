#include "class_under_test.h"

#include <stdexcept>

SomeClass::SomeClass()
{
    a = 0;
}


bool SomeClass::publicFunc(int a)
{
    this->a = a;
    return a >= 0;
}


void SomeClass::testThrow()
{
    throw std::runtime_error("Function failed!");
}
