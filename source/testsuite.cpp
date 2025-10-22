#include "testsuite.h"


void UnitTest::run_tests()
{
    unsigned int numPassed = 0;
    for (test_t testCase : detail::registered_functions()) {
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

    testErrors.clear();

    printf("%d/%d tests passed\n", numPassed, detail::registered_functions().size());
}

std::vector<test_t>& UnitTest::detail::registered_functions()
{
    static std::vector<test_t> functions;
    return functions;
}

void UnitTest::detail::register_function(
    std::string name, func_t function, std::string file, int lnr)
{
    std::vector<test_t> funcs = registered_functions();

    if (std::find(funcs.begin(), funcs.end(), name) != funcs.end()) {
        throw std::invalid_argument("Test name '" + name + "' must be unique, file " + file +
                                    ", line " + std::to_string(lnr));
    }

    registered_functions().emplace_back(name, function);
}

void UnitTest::detail::fail_test(std::string msg)
{
    testErrors.push_back(msg);
}