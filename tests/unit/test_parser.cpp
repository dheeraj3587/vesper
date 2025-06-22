#include "test_framework.h"
#include "Parser.h"
#include "Lexer.h"
#include "AST.h"
#include <iostream>
#include <vector>

void test_basic_expressions()
{
    TestFramework tf("Basic Expressions");

    // Test number expressions
    {
        std::string code = "42;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Number expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test variable expressions
    {
        std::string code = "x;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Variable expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test binary expressions
    {
        std::string code = "1 + 2;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Binary expression parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test parenthesized expressions
    {
        std::string code = "(a + b);";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
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
        std::string code = "1 + 2 * 3;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Operator precedence parsed correctly");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test division before subtraction
    {
        std::string code = "10 - 6 / 2;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Division precedence parsed correctly");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test complex precedence
    {
        std::string code = "a + b * c - d / e;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
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
        std::string code = "foo();";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Empty function call parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test function call with arguments
    {
        std::string code = "bar(x, y);";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Function call with arguments parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test nested function calls
    {
        std::string code = "outer(inner(arg));";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Nested function calls parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_variable_declarations()
{
    TestFramework tf("Variable Declarations");

    // Test C-style variable declaration
    {
        std::string code = "int x = 42;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "C-style variable declaration parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test multiple variable declarations
    {
        std::string code = "int x = 1; float y = 3.14;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Multiple variable declarations parsed");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_control_flow()
{
    TestFramework tf("Control Flow");

    // Test if statement
    {
        std::string code = "if (x > 0) { y = 1; }";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "If statement parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test while loop
    {
        std::string code = "while (x > 0) { x = x - 1; }";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "While loop parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test for loop
    {
        std::string code = "for (int i = 0; i < 10; i++) { result = result + i; }";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "For loop parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_functions()
{
    TestFramework tf("Functions");

    // Test function definition
    {
        std::string code = "int add(int a, int b) { return a + b; }";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Function definition parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test function call
    {
        std::string code = "int result = add(x, y);";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Function call parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_parser_error_handling()
{
    TestFramework tf("Error Handling");

    // Test missing semicolon
    {
        std::string code = "int x = 42";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast == nullptr, "Missing semicolon should fail");
    }

    // Test invalid expression
    {
        std::string code = "int x = ;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast == nullptr, "Invalid expression should fail");
    }
}

void test_complex_program()
{
    TestFramework tf("Complex Program");

    // Test a complete program with multiple features
    {
        std::string code = R"(
            int x = 5;
            float y = 3.14;
            if (x > 0) {
                y = x * 2;
            }
            int result = add(x, y);
        )";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();
        Parser parser(tokens);
        auto ast = parser.ParseProgram();
        tf.assert_true(ast != nullptr, "Complex program parsed successfully");
        if (ast)
        {
            ast->print();
            std::cout << std::endl;
        }
    }
}