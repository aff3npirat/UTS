A Library for C++ unit tests using Macros for test case registration.

# Example Usage
```c++
#include <testsuite.h>

int func_to_test() {...}

TEST_CASE("My Test")
{
  ASSERT_EQUALS(func_to_test(), 10);
}

int main()
{
  UnitTest::run_tests();

  return 0;
}
```

When testing with types which are not stream insertable either throw custom exceptions inside
TEST_CASE(...) body or provide explicit specialization for template `std::string to_string_(const T&)`.
```c++
// For example for some user defined class Foo
template<>
std::string UnitTest::to_string_(const Foo& value)
{
    return "Foo::" + value.some_member_string;
}

// Equality operator must be defined
bool operator==(const Foo& a, const Foo& b) ...

TEST_CASE("My Custom Error")
{
    Foo foo("some value");
    Foo foz("some other value");

    ASSERT_EQUALS(foo, foz)
}
```
