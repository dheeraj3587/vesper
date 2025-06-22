#include "test_framework.h"
#include <iostream>

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
void test_variable_declarations();
void test_control_flow();
void test_functions();
void test_parser_error_handling();
void test_complex_program();

void test_number_expr_ast();
void test_variable_expr_ast();
void test_binary_expr_ast();
void test_call_expr_ast();
void test_prototype_ast();
void test_function_ast();
void test_ast_polymorphism();
void test_ast_memory_management();
void test_ast_error_handling();

int main()
{
    std::cout << "🚀 Starting Comprehensive Test Suite" << std::endl;
    std::cout << "====================================" << std::endl;

    // Lexer Tests
    std::cout << "\n📝 Running Lexer Tests..." << std::endl;
    test_basic_tokens();
    test_c_keywords();
    test_stl_components();
    test_string_literals();
    test_comments();
    test_preprocessor();
    test_error_handling();
    test_complex_expressions();

    // Parser Tests
    std::cout << "\n🔍 Running Parser Tests..." << std::endl;
    test_basic_expressions();
    test_operator_precedence();
    test_function_calls();
    test_variable_declarations();
    test_control_flow();
    test_functions();
    test_parser_error_handling();
    test_complex_program();

    // AST Tests
    std::cout << "\n🌳 Running AST Tests..." << std::endl;
    test_number_expr_ast();
    test_variable_expr_ast();
    test_binary_expr_ast();
    test_call_expr_ast();
    test_prototype_ast();
    test_function_ast();
    test_ast_polymorphism();
    test_ast_memory_management();
    test_ast_error_handling();

    std::cout << "\n🎉 All tests completed successfully!" << std::endl;
    return 0;
}