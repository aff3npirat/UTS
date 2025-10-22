#include <cstdio>
#include <iostream>

#include "class_under_test.h"
#include "testsuite.h"


TEST_CASE("SomeClass")
{
    SomeClass uut;

    ASSERT_TRUE(uut.publicFunc(10));
    ASSERT_FALSE(uut.publicFunc(-2));
}

TEST_CASE("SomeClass") {}


int main()
{
    UnitTest::run_tests();

    return 0;
}