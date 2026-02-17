#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace UnitTest {

/// @brief runs all registered tests and provides summary to @code std::out
/// @endcode. Tests should be registered using the macro @code TEST_CASE(name)
/// @endcode with a unique string literal as name.
void run_tests();

namespace Detail {
// signature of test functions
using func_t = void (*)();

// wrapper for registered functions
struct test_t {
    std::string key;
    func_t func;

    bool operator==(std::string other) { return other == key; }
};

class AssertException : public std::exception {
  public:
    AssertException(std::string msg) : msg(msg) {}

    virtual const char* what() const noexcept { return msg.c_str(); }

  private:
    std::string msg;
};

// returns reference to registered functions
std::vector<test_t>& registered_functions();

// registers a new test function
void register_function(std::string name,
    func_t function,
    std::string file,
    int lnr);

}  // namespace Detail
}  // namespace UnitTest

// two step macro to concat expanded macros
#define _CONCAT_IMPLEMENT(a, b) a##b
#define _CONCAT(a, b) _CONCAT_IMPLEMENT(a, b)

// main registration macro
#define TEST_CASE(name)                                                \
    static_assert(true, name ""); /* provides more informative error*/ \
    namespace UnitTest::TestCases {                                    \
    static void _CONCAT(_test_, __LINE__)();                           \
    struct _CONCAT(_register_struct_t_, __LINE__) {                    \
        _CONCAT(_register_struct_t_, __LINE__)()                       \
        {                                                              \
            UnitTest::Detail::register_function(name,                  \
                _CONCAT(_test_, __LINE__), __FILE__, __LINE__);        \
        }                                                              \
    } _CONCAT(_register_struct_, __LINE__);                            \
    } /* namespace UnitTest::Detail::TestCases */                      \
    static void UnitTest::TestCases::_CONCAT(_test_, __LINE__)()

namespace UnitTest {
template<typename T>
std::string to_string_(const T& value)
{
    std::ostringstream ss;
    ss << value;
    return ss.str();
}

template<>
std::string to_string_(const bool& value);

template<>
std::string to_string_(const std::string& value);
}  // namespace UnitTest

// macro to get assertion-like strings
#define _ASSERT_MSG(expr, value)                                        \
    "File " __FILE__ ", line " + std::to_string(__LINE__) +             \
        ": Assertion Failed, expected " + UnitTest::to_string_(value) + \
        " got " + UnitTest::to_string_(expr)

#define _CHECK_VALUE(expr, value)                                     \
    if (expr != value)                                                \
    throw UnitTest::Detail::AssertException(_ASSERT_MSG(expr, value))

// expr mus evaluate to type bool
#define ASSERT_TRUE(expr) _CHECK_VALUE(expr, true);
#define ASSERT_FALSE(expr) _CHECK_VALUE(expr, false);
// value/expr must have stream insert operator (<<) defined
#define ASSERT_EQUALS(expr, value) _CHECK_VALUE(expr, value);