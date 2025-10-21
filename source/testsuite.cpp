#include "testsuite.h"


void UnitTest::run_tests()
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

std::vector<value_t>& UnitTest::Details::registered_functions()
{
    static std::vector<value_t> functions;
    return functions;
}

void UnitTest::Details::register_function(
    std::string name, func_t function, std::string file, int lnr)
{
    std::vector<value_t> funcs = registered_functions();

    if (std::find(funcs.begin(), funcs.end(), name) != funcs.end()) {
        throw std::invalid_argument("Test name '" + name + "' must be unique, file " + file +
                                    ", line " + std::to_string(lnr));
    }

    registered_functions().emplace_back(name, function);
}

void UnitTest::Details::fail_test(std::string msg)
{
    testErrors.push_back(msg);
}