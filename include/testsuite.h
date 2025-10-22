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
namespace Details {

std::vector<value_t>& registered_functions();

void register_function(std::string name, func_t function, std::string file, int lnr);

void fail_test(std::string msg);

}  // namespace Details

void run_tests();

}  // namespace UnitTest

#define CONCAT_IMPLEMENT(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPLEMENT(a, b)

#define TEST_CASE(name)                                              \
    static_assert(true, name "");                                    \
    static void CONCAT(_test_, __LINE__)();                          \
    namespace {                                                      \
    struct CONCAT(_register_struct_t_, __LINE__) {                   \
        CONCAT(_register_struct_t_, __LINE__)()                      \
        {                                                            \
            UnitTest::Details::register_function(                    \
                name, CONCAT(_test_, __LINE__), __FILE__, __LINE__); \
        }                                                            \
    } CONCAT(_register_struct_, __LINE__);                           \
    }                                                                \
    static void CONCAT(_test_, __LINE__)()

#define ASSERT_MSG(expr)                                                               \
    "Assertion failed: " #expr ", file " __FILE__ ", line " + std::to_string(__LINE__)

#define ASSERT_TRUE(expr)                                     \
    if (!expr) UnitTest::Details::fail_test(ASSERT_MSG(expr))

#define ASSERT_FALSE(expr) ASSERT_TRUE(!expr)