#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>


namespace {

// signature of test functions
using func_t = void (*)();

// wrapper for registered functions
struct test_t {
    std::string key;
    func_t func;

    bool operator==(std::string other) { return other == key; }
};

// stores error messages of failed tests
std::vector<std::string> testErrors;

}  // namespace

namespace UnitTest {
namespace detail {

    // returns reference to registered functions
    std::vector<test_t>& registered_functions();

    // registers a new test function
    void register_function(std::string name, func_t function, std::string file, int lnr);

    void fail_test(std::string msg);

}  // namespace detail

/// @brief runs all registered tests and provides summary to @code std::out @endcode.
/// Tests should be registered using the macro @code TEST_CASE(name) @endcode with a unique string
/// literal as name.
void run_tests();

}  // namespace UnitTest

// two step macro to concat expanded macros
#define _CONCAT_IMPLEMENT(a, b) a##b
#define _CONCAT(a, b) _CONCAT_IMPLEMENT(a, b)

// main registration macro
#define TEST_CASE(name)                                                       \
    static_assert(true, name ""); /* provides more informative error*/        \
    namespace detail {                                                        \
        static void _CONCAT(_test_, __LINE__)();                              \
        namespace {                                                           \
            struct _CONCAT(_register_struct_t_, __LINE__) {                   \
                _CONCAT(_register_struct_t_, __LINE__)()                      \
                {                                                             \
                    UnitTest::detail::register_function(                      \
                        name, _CONCAT(_test_, __LINE__), __FILE__, __LINE__); \
                }                                                             \
            } _CONCAT(_register_struct_, __LINE__);                           \
        } /* namespace */                                                     \
    } /* namespace detail */                                                  \
    static void detail::_CONCAT(_test_, __LINE__)()

// macro to get assertion-like strings
#define _ASSERT_MSG(expr)                                                              \
    "Assertion failed: " #expr ", file " __FILE__ ", line " + std::to_string(__LINE__)

#define _CHECK_VALUE(expr, value)                                              \
    if (expr != value) UnitTest::detail::fail_test(_ASSERT_MSG(expr == value))

// check if expr evaluates to true
#define ASSERT_TRUE(expr) _CHECK_VALUE(expr, true)
// check if expr evaluates to false
#define ASSERT_FALSE(expr) _CHECK_VALUE(expr, false)