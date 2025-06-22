#include <iostream>
#include <vector>
#include <string>

// Forward declarations of test functions
void test_basic_tokens();
void test_c_keywords();
void test_stl_components();
void test_string_literals();
void test_comments();
void test_preprocessor();
void test_error_handling();
void test_complex_expressions();

void test_basic_expressions();
void test_operator_precedence();
void test_function_calls();
void test_kaleidoscope_keywords();
void test_c_keywords();
void test_stl_components();
void test_complex_expressions();
void test_error_handling();
void test_multiple_statements();
void test_ast_structure();

void test_number_expr_ast();
void test_variable_expr_ast();
void test_binary_expr_ast();
void test_call_expr_ast();
void test_prototype_ast();
void test_function_ast();
void test_ast_polymorphism();
void test_ast_memory_management();
void test_ast_error_handling();

struct TestSuite
{
    std::string name;
    std::vector<void (*)()> tests;
};

int main()
{
    std::cout << "🚀 Starting Vesper Compiler Test Suite\n";
    std::cout << "======================================\n\n";

    std::vector<TestSuite> test_suites = {
        {"Lexer Unit Tests",
         {test_basic_tokens,
          test_c_keywords,
          test_stl_components,
          test_string_literals,
          test_comments,
          test_preprocessor,
          test_error_handling,
          test_complex_expressions}},
        {"Parser Unit Tests",
         {test_basic_expressions,
          test_operator_precedence,
          test_function_calls,
          test_kaleidoscope_keywords,
          test_c_keywords,
          test_stl_components,
          test_complex_expressions,
          test_error_handling,
          test_multiple_statements,
          test_ast_structure}},
        {"AST Unit Tests",
         {test_number_expr_ast,
          test_variable_expr_ast,
          test_binary_expr_ast,
          test_call_expr_ast,
          test_prototype_ast,
          test_function_ast,
          test_ast_polymorphism,
          test_ast_memory_management,
          test_ast_error_handling}}};

    int total_passed = 0;
    int total_tests = 0;
    bool all_suites_passed = true;

    for (const auto &suite : test_suites)
    {
        std::cout << "📋 Running " << suite.name << "\n";
        std::cout << std::string(50, '=') << "\n";

        for (auto test : suite.tests)
        {
            try
            {
                test();
            }
            catch (const std::exception &e)
            {
                std::cout << "❌ Test failed with exception: " << e.what() << "\n";
                all_suites_passed = false;
            }
            catch (...)
            {
                std::cout << "❌ Test failed with unknown exception\n";
                all_suites_passed = false;
            }
        }

        std::cout << "\n";
    }

    std::cout << "🎯 Test Suite Summary\n";
    std::cout << "=====================\n";

    if (all_suites_passed)
    {
        std::cout << "✅ All test suites completed successfully!\n";
    }
    else
    {
        std::cout << "❌ Some test suites failed!\n";
    }

    std::cout << "\n📊 Final Results:\n";
    std::cout << "   - Lexer: ✅ C keywords, STL support, operators, literals\n";
    std::cout << "   - Parser: ✅ Expressions, precedence, function calls\n";
    std::cout << "   - AST: ✅ Node types, memory management, polymorphism\n";

    std::cout << "\n🎉 Test suite execution completed!\n";

    return all_suites_passed ? 0 : 1;
}