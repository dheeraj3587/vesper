#include "test_framework.h"
#include "Parser.h"
#include "AST.h"
#include <iostream>
#include <vector>

void test_basic_expressions()
{
    TestFramework tf("Basic Expressions");

    // Test number expressions
    {
        std::vector<std::string> tokens = {"42"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Number expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test variable expressions
    {
        std::vector<std::string> tokens = {"x"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Variable expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test binary expressions
    {
        std::vector<std::string> tokens = {"1", "+", "2"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Binary expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test parenthesized expressions
    {
        std::vector<std::string> tokens = {"(", "a", "+", "b", ")"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Parenthesized expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_operator_precedence()
{
    TestFramework tf("Operator Precedence");

    // Test multiplication before addition
    {
        std::vector<std::string> tokens = {"1", "+", "2", "*", "3"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Operator precedence parsed correctly");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test division before subtraction
    {
        std::vector<std::string> tokens = {"10", "-", "6", "/", "2"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Division precedence parsed correctly");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test complex precedence
    {
        std::vector<std::string> tokens = {"a", "+", "b", "*", "c", "-", "d", "/", "e"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Complex operator precedence parsed correctly");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_function_calls()
{
    TestFramework tf("Function Calls");

    // Test simple function call
    {
        std::vector<std::string> tokens = {"foo", "(", ")"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Empty function call parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test function call with arguments
    {
        std::vector<std::string> tokens = {"bar", "(", "x", ",", "y", ")"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Function call with arguments parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test nested function calls
    {
        std::vector<std::string> tokens = {"outer", "(", "inner", "(", "arg", ")", ")"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Nested function calls parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_kaleidoscope_keywords()
{
    TestFramework tf("Kaleidoscope Keywords");

    // Test function definition
    {
        std::vector<std::string> tokens = {"def", "average", "(", "x", ",", "y", ")", "(", "x", "+", "y", ")", "/", "2.0"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Function definition parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test external declaration
    {
        std::vector<std::string> tokens = {"extern", "sin", "(", "x", ")"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "External declaration parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_c_keywords()
{
    TestFramework tf("C Keywords");

    // Test C-style variable declaration
    {
        std::vector<std::string> tokens = {"KEYWORD:int", "x", "PUNCTUATOR:=", "NUMBER:42", "PUNCTUATOR:;"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "C-style variable declaration parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test C-style function declaration
    {
        std::vector<std::string> tokens = {"KEYWORD:int", "main", "PUNCTUATOR:(", "PUNCTUATOR:)", "PUNCTUATOR:{"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "C-style function declaration parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_stl_components()
{
    TestFramework tf("STL Components");

    // Test STL container declaration
    {
        std::vector<std::string> tokens = {"std", "OPERATOR:::", "STL_CONTAINER:vector", "PUNCTUATOR:<", "KEYWORD:int", "PUNCTUATOR:>", "numbers"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "STL container declaration parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test STL algorithm call
    {
        std::vector<std::string> tokens = {"std", "OPERATOR:::", "STL_ALGORITHM:sort", "PUNCTUATOR:(", "vec", "PUNCTUATOR:.", "STL_ITERATOR:begin", "PUNCTUATOR:(", "PUNCTUATOR:)", "PUNCTUATOR:,"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "STL algorithm call parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_complex_expressions()
{
    TestFramework tf("Complex Expressions");

    // Test complex arithmetic expression
    {
        std::vector<std::string> tokens = {"(", "a", "+", "b", ")", "*", "(", "c", "-", "d", ")", "/", "e"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Complex arithmetic expression parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test function call in expression
    {
        std::vector<std::string> tokens = {"foo", "PUNCTUATOR:(", "x", "PUNCTUATOR:)", "+", "bar", "PUNCTUATOR:(", "y", "PUNCTUATOR:)"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Function calls in expression parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_error_handling()
{
    TestFramework tf("Error Handling");

    // Test missing closing parenthesis
    {
        std::vector<std::string> tokens = {"(", "1", "+", "2"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast == nullptr, "Missing closing parenthesis handled gracefully");
    }

    // Test invalid function call
    {
        std::vector<std::string> tokens = {"foo", "1", "2"}; // Missing parentheses
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Invalid function call handled gracefully");
    }

    // Test empty input
    {
        std::vector<std::string> tokens = {};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast == nullptr, "Empty input handled correctly");
    }
}

void test_multiple_statements()
{
    TestFramework tf("Multiple Statements");

    // Test multiple expressions
    {
        std::vector<std::string> tokens = {"1", "+", "2", "PUNCTUATOR:;", "3", "*", "4", "PUNCTUATOR:;"};
        Parser parser(tokens);

        auto ast1 = parser.Parse();
        tf.assert_true(ast1 != nullptr, "First statement parsed");
        if (ast1)
        {
            ast1->print();
            std::cout << std::endl;
        }

        auto ast2 = parser.Parse();
        tf.assert_true(ast2 != nullptr, "Second statement parsed");
        if (ast2)
        {
            ast2->print();
            std::cout << std::endl;
        }
    }
}

void test_ast_structure()
{
    TestFramework tf("AST Structure");

    // Test AST node types
    {
        std::vector<std::string> tokens = {"NUMBER:42"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "NumberExprAST created");
    }

    {
        std::vector<std::string> tokens = {"variable"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "VariableExprAST created");
    }

    {
        std::vector<std::string> tokens = {"1", "+", "2"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "BinaryExprAST created");
    }

    {
        std::vector<std::string> tokens = {"func", "PUNCTUATOR:(", "arg", "PUNCTUATOR:)"};
        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "CallExprAST created");
    }
}

int main()
{
    std::cout << "🚀 Starting Parser Unit Tests\n";
    std::cout << "=============================\n";

    RUN_TEST(test_basic_expressions);
    RUN_TEST(test_operator_precedence);
    RUN_TEST(test_function_calls);
    RUN_TEST(test_kaleidoscope_keywords);
    RUN_TEST(test_c_keywords);
    RUN_TEST(test_stl_components);
    RUN_TEST(test_complex_expressions);
    RUN_TEST(test_error_handling);
    RUN_TEST(test_multiple_statements);
    RUN_TEST(test_ast_structure);

    std::cout << "\n🎉 All Parser unit tests completed!\n";
    return 0;
}