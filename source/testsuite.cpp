#include "testsuite.h"

#include <exception>
#include <string>


void UnitTest::run_tests()
{
    unsigned int numPassed = 0;
    for (test_t testCase : detail::registered_functions()) {
        std::string name = testCase.key;
        try {
            testCase.func();
            numPassed++;
            printf("Test %s passed!\n", name.c_str());
        } catch (const std::exception& e) {
            printf("Test %s failed!\n", name.c_str());
            printf("    %s\n", e.what());
        }
    }

    printf("%d/%d tests passed\n", numPassed,
        detail::registered_functions().size());
}

std::vector<test_t>& UnitTest::detail::registered_functions()
{
    static std::vector<test_t> functions;
    return functions;
}

void UnitTest::detail::register_function(std::string name,
    func_t function,
    std::string file,
    int lnr)
{
    std::vector<test_t> funcs = registered_functions();

    if (std::find(funcs.begin(), funcs.end(), name) != funcs.end()) {
        throw std::invalid_argument("Test name '" + name +
                                    "' must be unique, file " + file +
                                    ", line " + std::to_string(lnr));
    }

    registered_functions().emplace_back(name, function);
}