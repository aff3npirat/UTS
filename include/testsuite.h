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
struct value_t {
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
    std::vector<value_t>& registered_functions();

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
#define CONCAT_IMPLEMENT(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPLEMENT(a, b)

// main registration macro
#define TEST_CASE(name)                                                      \
    static_assert(true, name ""); /* provides more informative error*/       \
    namespace detail {                                                       \
        static void CONCAT(_test_, __LINE__)();                              \
        namespace {                                                          \
            struct CONCAT(_register_struct_t_, __LINE__) {                   \
                CONCAT(_register_struct_t_, __LINE__)()                      \
                {                                                            \
                    UnitTest::detail::register_function(                     \
                        name, CONCAT(_test_, __LINE__), __FILE__, __LINE__); \
                }                                                            \
            } CONCAT(_register_struct_, __LINE__);                           \
        } /* namespace */                                                    \
    } /* namespace detail */                                                 \
    static void detail::CONCAT(_test_, __LINE__)()

// macro to get assertion-like strings
#define ASSERT_MSG(expr)                                                               \
    "Assertion failed: " #expr ", file " __FILE__ ", line " + std::to_string(__LINE__)

// check if expr evaluates to true
#define ASSERT_TRUE(expr)                                    \
    if (!expr) UnitTest::detail::fail_test(ASSERT_MSG(expr))
// check if expr evaluates to false
#define ASSERT_FALSE(expr) ASSERT_TRUE(!expr)