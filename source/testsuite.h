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

std::vector<value_t>& registered_functions()
{
    static std::vector<value_t> functions;
    return functions;
}

void register_function(std::string name, func_t function, std::string file, int lnr)
{
    std::vector<value_t> funcs = registered_functions();

    if (std::find(funcs.begin(), funcs.end(), name) != funcs.end()) {
        throw std::invalid_argument("Test name '" + name + "' must be unique, file " + file +
                                    ", line " + std::to_string(lnr));
    }

    registered_functions().emplace_back(name, function);
}

void fail_test(std::string msg)
{
    testErrors.push_back(msg);
}

}  // namespace Details

void run_tests()
{
    unsigned int numPassed = 0;
    for (value_t testCase : Details::registered_functions()) {
        testErrors.clear();
        testCase.func();

        std::string name = testCase.key;
        if (testErrors.empty()) {
            printf("Test %s passed!\n", name.c_str());
            numPassed++;
        }
        else {
            printf("Test %s failed!\n", name.c_str());
            for (std::string error : testErrors) {
                printf("    %s\n", error.c_str());
            }
        }
    }

    printf("%d/%d tests passed\n", numPassed, Details::registered_functions().size());
}

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