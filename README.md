A Framework to write unit tests in C++ using Macros.

# Example Usage
```c++
#include <testsuite.h>

int func_to_test() {...}

TEST_CASE("My Test")
{
  ASSERT_TRUE(10 == func_to_test());
}

int main()
{
  UnitTest::run_tests();

  return 0;
}
```
