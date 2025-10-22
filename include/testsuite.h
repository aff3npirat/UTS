#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>


namespace {
using func_t = void (*)();

struct value_t {
    std::string key;
    func_t func;

    bool operator==(std::string other) { return other == key; }
};

std::vector<std::string> testErrors;

}  // namespace

namespace UnitTest {
namespace detail {

    std::vector<value_t>& registered_functions();

    void register_function(std::string name, func_t function, std::string file, int lnr);

    void fail_test(std::string msg);

}  // namespace detail

void run_tests();

}  // namespace UnitTest

#define CONCAT_IMPLEMENT(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPLEMENT(a, b)

#define TEST_CASE(name)                                                      \
    namespace detail {                                                       \
        static_assert(true, name "");                                        \
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

#define ASSERT_MSG(expr)                                                               \
    "Assertion failed: " #expr ", file " __FILE__ ", line " + std::to_string(__LINE__)

#define ASSERT_TRUE(expr)                                    \
    if (!expr) UnitTest::detail::fail_test(ASSERT_MSG(expr))

#define ASSERT_FALSE(expr) ASSERT_TRUE(!expr)