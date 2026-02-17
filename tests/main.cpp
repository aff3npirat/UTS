#include <cstdio>
#include <iostream>

#include "class_under_test.h"
#include "testsuite.h"


TEST_CASE("Assert_1")
{
    SomeClass uut;

    ASSERT_TRUE(uut.publicFunc(10));
    ASSERT_FALSE(uut.publicFunc(10));
}


TEST_CASE("Assert_2")
{
    int a = 20;

    ASSERT_EQUALS(a, 20);
    ASSERT_EQUALS(a, 25);
}


TEST_CASE("Assert_3")
{
    int a = 0;
    int b = 1;

    ASSERT_EQUALS(a, b);
}


TEST_CASE("Throw")
{
    SomeClass uut;
    uut.testThrow();
}


TEST_CASE("Empty Body") {}


int main()
{
    UnitTest::run_tests();

    return 0;
}