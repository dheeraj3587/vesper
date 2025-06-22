#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cassert>

class TestFramework
{
private:
    std::string test_name;
    int passed_tests = 0;
    int total_tests = 0;
    std::vector<std::string> failed_tests;

public:
    TestFramework(const std::string &name) : test_name(name)
    {
        std::cout << "\n🧪 Running " << test_name << " tests...\n";
        std::cout << "================================\n";
    }

    ~TestFramework()
    {
        std::cout << "\n📊 Test Results for " << test_name << ":\n";
        std::cout << "✅ Passed: " << passed_tests << "/" << total_tests << "\n";
        if (!failed_tests.empty())
        {
            std::cout << "❌ Failed tests:\n";
            for (const auto &test : failed_tests)
            {
                std::cout << "   - " << test << "\n";
            }
        }
        std::cout << "================================\n";
    }

    template <typename T>
    void assert_equal(const T &actual, const T &expected, const std::string &test_name)
    {
        total_tests++;
        if (actual == expected)
        {
            passed_tests++;
            std::cout << "✅ " << test_name << "\n";
        }
        else
        {
            failed_tests.push_back(test_name);
            std::cout << "❌ " << test_name << " - Expected: " << expected << ", Got: " << actual << "\n";
        }
    }

    // Specialized string comparison
    void assert_equal(const std::string &actual, const char *expected, const std::string &test_name)
    {
        assert_equal(actual, std::string(expected), test_name);
    }

    void assert_equal(const char *actual, const std::string &expected, const std::string &test_name)
    {
        assert_equal(std::string(actual), expected, test_name);
    }

    void assert_equal(const char *actual, const char *expected, const std::string &test_name)
    {
        assert_equal(std::string(actual), std::string(expected), test_name);
    }

    void assert_true(bool condition, const std::string &test_name)
    {
        total_tests++;
        if (condition)
        {
            passed_tests++;
            std::cout << "✅ " << test_name << "\n";
        }
        else
        {
            failed_tests.push_back(test_name);
            std::cout << "❌ " << test_name << " - Expected true, got false\n";
        }
    }

    void assert_false(bool condition, const std::string &test_name)
    {
        total_tests++;
        if (!condition)
        {
            passed_tests++;
            std::cout << "✅ " << test_name << "\n";
        }
        else
        {
            failed_tests.push_back(test_name);
            std::cout << "❌ " << test_name << " - Expected false, got true\n";
        }
    }

    void assert_throws(std::function<void()> func, const std::string &test_name)
    {
        total_tests++;
        try
        {
            func();
            failed_tests.push_back(test_name);
            std::cout << "❌ " << test_name << " - Expected exception, but none was thrown\n";
        }
        catch (...)
        {
            passed_tests++;
            std::cout << "✅ " << test_name << "\n";
        }
    }

    void assert_contains(const std::string &haystack, const std::string &needle, const std::string &test_name)
    {
        total_tests++;
        if (haystack.find(needle) != std::string::npos)
        {
            passed_tests++;
            std::cout << "✅ " << test_name << "\n";
        }
        else
        {
            failed_tests.push_back(test_name);
            std::cout << "❌ " << test_name << " - Expected to find '" << needle << "' in '" << haystack << "'\n";
        }
    }

    void assert_contains(const std::string &haystack, const char *needle, const std::string &test_name)
    {
        assert_contains(haystack, std::string(needle), test_name);
    }

    int get_passed() const { return passed_tests; }
    int get_total() const { return total_tests; }
    bool all_passed() const { return failed_tests.empty(); }
};

#define RUN_TEST(test_func)                                    \
    do                                                         \
    {                                                          \
        std::cout << "\n🔍 Running " << #test_func << "...\n"; \
        test_func();                                           \
    } while (0)

#endif // TEST_FRAMEWORK_H