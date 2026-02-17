#include "testsuite.h"

#include <exception>
#include <string>


namespace UnitTest {

void run_tests()
{
    unsigned int numPassed = 0;
    for (Detail::test_t testCase : Detail::registered_functions()) {
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
        Detail::registered_functions().size());
}

template<>
std::string to_string_(const bool& value)
{
    return value ? "true" : "false";
}

template<>
std::string to_string_(const std::string& value)
{
    return value;
}

namespace Detail {
std::vector<test_t>& registered_functions()
{
    static std::vector<test_t> functions;
    return functions;
}

void register_function(std::string name,
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

}  // namespace Detail
}  // namespace UnitTest