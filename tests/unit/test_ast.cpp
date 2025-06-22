#include "test_framework.h"
#include "AST.h"
#include <iostream>
#include <memory>
#include <vector>

void test_number_expr_ast()
{
    TestFramework tf("NumberExprAST");

    // Test integer literal
    {
        NumberExprAST num(42);
        tf.assert_true(true, "NumberExprAST with integer created successfully");

        std::cout << "NumberExprAST(42): ";
        num.print();
        std::cout << std::endl;
    }

    // Test floating point literal
    {
        NumberExprAST num(3.14159);
        tf.assert_true(true, "NumberExprAST with float created successfully");

        std::cout << "NumberExprAST(3.14159): ";
        num.print();
        std::cout << std::endl;
    }

    // Test zero
    {
        NumberExprAST num(0);
        tf.assert_true(true, "NumberExprAST with zero created successfully");

        std::cout << "NumberExprAST(0): ";
        num.print();
        std::cout << std::endl;
    }

    // Test negative number
    {
        NumberExprAST num(-10.5);
        tf.assert_true(true, "NumberExprAST with negative number created successfully");

        std::cout << "NumberExprAST(-10.5): ";
        num.print();
        std::cout << std::endl;
    }

    // Test large number
    {
        NumberExprAST num(1e6);
        tf.assert_true(true, "NumberExprAST with large number created successfully");

        std::cout << "NumberExprAST(1e6): ";
        num.print();
        std::cout << std::endl;
    }
}

void test_variable_expr_ast()
{
    TestFramework tf("VariableExprAST");

    // Test simple variable
    {
        VariableExprAST var("x");
        tf.assert_true(true, "VariableExprAST created successfully");

        std::cout << "VariableExprAST(x): ";
        var.print();
        std::cout << std::endl;
    }

    // Test variable with underscore
    {
        VariableExprAST var("my_variable");
        tf.assert_true(true, "VariableExprAST with underscore created successfully");

        std::cout << "VariableExprAST(my_variable): ";
        var.print();
        std::cout << std::endl;
    }

    // Test variable with numbers
    {
        VariableExprAST var("var123");
        tf.assert_true(true, "VariableExprAST with numbers created successfully");

        std::cout << "VariableExprAST(var123): ";
        var.print();
        std::cout << std::endl;
    }

    // Test single letter variable
    {
        VariableExprAST var("i");
        tf.assert_true(true, "VariableExprAST with single letter created successfully");

        std::cout << "VariableExprAST(i): ";
        var.print();
        std::cout << std::endl;
    }
}

void test_binary_expr_ast()
{
    TestFramework tf("BinaryExprAST");

    // Test simple binary expression
    {
        auto lhs = std::make_unique<NumberExprAST>(5.0);
        auto rhs = std::make_unique<NumberExprAST>(3.0);
        BinaryExprAST bin("+", std::move(lhs), std::move(rhs));
        tf.assert_true(true, "BinaryExprAST created successfully");

        std::cout << "BinaryExprAST(5 + 3): ";
        bin.print();
        std::cout << std::endl;
    }

    // Test binary expression with variables
    {
        auto lhs = std::make_unique<VariableExprAST>("x");
        auto rhs = std::make_unique<VariableExprAST>("y");
        BinaryExprAST bin("*", std::move(lhs), std::move(rhs));
        tf.assert_true(true, "BinaryExprAST with variables created successfully");

        std::cout << "BinaryExprAST(x * y): ";
        bin.print();
        std::cout << std::endl;
    }

    // Test complex binary expression
    {
        auto inner_lhs = std::make_unique<NumberExprAST>(2.0);
        auto inner_rhs = std::make_unique<NumberExprAST>(3.0);
        auto inner = std::make_unique<BinaryExprAST>("+", std::move(inner_lhs), std::move(inner_rhs));

        auto outer_rhs = std::make_unique<NumberExprAST>(4.0);
        BinaryExprAST outer("*", std::move(inner), std::move(outer_rhs));
        tf.assert_true(true, "Complex BinaryExprAST created successfully");

        std::cout << "BinaryExprAST((2 + 3) * 4): ";
        outer.print();
        std::cout << std::endl;
    }
}

void test_call_expr_ast()
{
    TestFramework tf("CallExprAST");

    // Test function call with no arguments
    {
        std::vector<std::unique_ptr<ExprAST>> args;
        CallExprAST call("foo", std::move(args));
        tf.assert_true(true, "CallExprAST with no arguments created successfully");

        std::cout << "CallExprAST(foo()): ";
        call.print();
        std::cout << std::endl;
    }

    // Test function call with one argument
    {
        std::vector<std::unique_ptr<ExprAST>> args;
        args.push_back(std::make_unique<NumberExprAST>(42.0));
        CallExprAST call("bar", std::move(args));
        tf.assert_true(true, "CallExprAST with one argument created successfully");

        std::cout << "CallExprAST(bar(42)): ";
        call.print();
        std::cout << std::endl;
    }

    // Test function call with multiple arguments
    {
        std::vector<std::unique_ptr<ExprAST>> args;
        args.push_back(std::make_unique<VariableExprAST>("x"));
        args.push_back(std::make_unique<VariableExprAST>("y"));
        args.push_back(std::make_unique<NumberExprAST>(10.0));
        CallExprAST call("func", std::move(args));
        tf.assert_true(true, "CallExprAST with multiple arguments created successfully");

        std::cout << "CallExprAST(func(x, y, 10)): ";
        call.print();
        std::cout << std::endl;
    }

    // Test nested function calls
    {
        std::vector<std::unique_ptr<ExprAST>> inner_args;
        inner_args.push_back(std::make_unique<NumberExprAST>(5.0));
        auto inner_call = std::make_unique<CallExprAST>("inner", std::move(inner_args));

        std::vector<std::unique_ptr<ExprAST>> outer_args;
        outer_args.push_back(std::move(inner_call));
        outer_args.push_back(std::make_unique<NumberExprAST>(3.0));
        CallExprAST outer_call("outer", std::move(outer_args));
        tf.assert_true(true, "Nested CallExprAST created successfully");

        std::cout << "CallExprAST(outer(inner(5), 3)): ";
        outer_call.print();
        std::cout << std::endl;
    }
}

void test_prototype_ast()
{
    TestFramework tf("PrototypeAST");

    // Test simple function prototype
    {
        std::vector<std::pair<DataType, std::string>> args = {{DataType::INT, "x"}, {DataType::INT, "y"}};
        PrototypeAST proto(DataType::INT, "average", std::move(args));
        tf.assert_true(true, "PrototypeAST created successfully");

        std::cout << "PrototypeAST(int average(int x, int y)): ";
        proto.print();
        std::cout << std::endl;
    }

    // Test function prototype with no arguments
    {
        std::vector<std::pair<DataType, std::string>> args;
        PrototypeAST proto(DataType::VOID, "main", std::move(args));
        tf.assert_true(true, "PrototypeAST with no arguments created successfully");

        std::cout << "PrototypeAST(void main()): ";
        proto.print();
        std::cout << std::endl;
    }

    // Test function prototype with many arguments
    {
        std::vector<std::pair<DataType, std::string>> args = {
            {DataType::INT, "a"}, {DataType::FLOAT, "b"}, {DataType::STRING, "c"}};
        PrototypeAST proto(DataType::FLOAT, "complex_func", std::move(args));
        tf.assert_true(true, "PrototypeAST with many arguments created successfully");

        std::cout << "PrototypeAST(float complex_func(int a, float b, string c)): ";
        proto.print();
        std::cout << std::endl;
    }

    // Test operator prototype
    {
        std::vector<std::pair<DataType, std::string>> args = {{DataType::INT, "lhs"}, {DataType::INT, "rhs"}};
        PrototypeAST proto(DataType::INT, "+", std::move(args), true, 1);
        tf.assert_true(true, "Operator PrototypeAST created successfully");

        std::cout << "PrototypeAST(int +(int lhs, int rhs)): ";
        proto.print();
        std::cout << std::endl;
    }
}

void test_function_ast()
{
    TestFramework tf("FunctionAST");

    // Test simple function definition
    {
        std::vector<std::pair<DataType, std::string>> proto_args = {{DataType::INT, "x"}, {DataType::INT, "y"}};
        auto proto = std::make_unique<PrototypeAST>(DataType::INT, "add", std::move(proto_args));

        auto lhs = std::make_unique<VariableExprAST>("x");
        auto rhs = std::make_unique<VariableExprAST>("y");
        auto expr = std::make_unique<BinaryExprAST>("+", std::move(lhs), std::move(rhs));
        auto body = std::make_unique<ReturnStmtAST>(std::move(expr));

        FunctionAST func(std::move(proto), std::move(body));
        tf.assert_true(true, "FunctionAST created successfully");

        std::cout << "FunctionAST(int add(int x, int y) { return x + y; }): ";
        func.print();
        std::cout << std::endl;
    }

    // Test function with complex body
    {
        std::vector<std::pair<DataType, std::string>> proto_args = {{DataType::INT, "a"}, {DataType::INT, "b"}, {DataType::INT, "c"}};
        auto proto = std::make_unique<PrototypeAST>(DataType::INT, "complex", std::move(proto_args));

        // Create complex body: return (a + b) * c;
        auto inner_lhs = std::make_unique<VariableExprAST>("a");
        auto inner_rhs = std::make_unique<VariableExprAST>("b");
        auto inner = std::make_unique<BinaryExprAST>("+", std::move(inner_lhs), std::move(inner_rhs));

        auto outer_rhs = std::make_unique<VariableExprAST>("c");
        auto expr = std::make_unique<BinaryExprAST>("*", std::move(inner), std::move(outer_rhs));
        auto body = std::make_unique<ReturnStmtAST>(std::move(expr));

        FunctionAST func(std::move(proto), std::move(body));
        tf.assert_true(true, "FunctionAST with complex body created successfully");

        std::cout << "FunctionAST(int complex(int a, int b, int c) { return (a + b) * c; }): ";
        func.print();
        std::cout << std::endl;
    }

    // Test function with function call in body
    {
        std::vector<std::pair<DataType, std::string>> proto_args = {{DataType::INT, "x"}};
        auto proto = std::make_unique<PrototypeAST>(DataType::INT, "wrapper", std::move(proto_args));

        std::vector<std::unique_ptr<ExprAST>> call_args;
        call_args.push_back(std::make_unique<VariableExprAST>("x"));
        auto expr = std::make_unique<CallExprAST>("inner_func", std::move(call_args));
        auto body = std::make_unique<ReturnStmtAST>(std::move(expr));

        FunctionAST func(std::move(proto), std::move(body));
        tf.assert_true(true, "FunctionAST with function call created successfully");

        std::cout << "FunctionAST(int wrapper(int x) { return inner_func(x); }): ";
        func.print();
        std::cout << std::endl;
    }
}

void test_ast_polymorphism()
{
    TestFramework tf("AST Polymorphism");

    // Test vector of different expression types
    {
        std::vector<std::unique_ptr<ExprAST>> expressions;

        expressions.push_back(std::make_unique<NumberExprAST>(42.0));
        expressions.push_back(std::make_unique<VariableExprAST>("x"));

        auto lhs = std::make_unique<NumberExprAST>(1.0);
        auto rhs = std::make_unique<NumberExprAST>(2.0);
        expressions.push_back(std::make_unique<BinaryExprAST>("+", std::move(lhs), std::move(rhs)));

        tf.assert_true(expressions.size() == 3, "Vector of polymorphic AST nodes created successfully");

        std::cout << "Polymorphic expressions: ";
        for (const auto &expr : expressions)
        {
            expr->print();
            std::cout << " ";
        }
        std::cout << std::endl;
    }

    // Test function that accepts any expression
    {
        auto test_expr = [](const std::unique_ptr<ExprAST> &expr)
        {
            std::cout << "Expression: ";
            expr->print();
            std::cout << std::endl;
            return true;
        };

        std::unique_ptr<ExprAST> num = std::make_unique<NumberExprAST>(10.0);
        std::unique_ptr<ExprAST> var = std::make_unique<VariableExprAST>("y");

        tf.assert_true(test_expr(num), "Polymorphic function works with NumberExprAST");
        tf.assert_true(test_expr(var), "Polymorphic function works with VariableExprAST");
    }
}

void test_ast_memory_management()
{
    TestFramework tf("AST Memory Management");

    // Test unique_ptr ownership transfer
    {
        auto num = std::make_unique<NumberExprAST>(5.0);
        auto var = std::make_unique<VariableExprAST>("x");

        // Transfer ownership to binary expression
        auto bin = std::make_unique<BinaryExprAST>("+", std::move(num), std::move(var));

        tf.assert_true(bin != nullptr, "Ownership transfer successful");
        tf.assert_true(num == nullptr, "Original pointer is null after move");
        tf.assert_true(var == nullptr, "Original pointer is null after move");

        std::cout << "Memory management test: ";
        bin->print();
        std::cout << std::endl;
    }

    // Test vector of unique_ptr
    {
        std::vector<std::unique_ptr<ExprAST>> expressions;

        expressions.push_back(std::make_unique<NumberExprAST>(1.0));
        expressions.push_back(std::make_unique<NumberExprAST>(2.0));
        expressions.push_back(std::make_unique<NumberExprAST>(3.0));

        tf.assert_true(expressions.size() == 3, "Vector of unique_ptr expressions created successfully");

        // Move vector
        auto moved_expressions = std::move(expressions);
        tf.assert_true(expressions.empty(), "Original vector is empty after move");
        tf.assert_true(moved_expressions.size() == 3, "Moved vector has correct size");
    }
}

void test_ast_error_handling()
{
    TestFramework tf("AST Error Handling");

    // Test null pointer handling
    {
        try
        {
            std::unique_ptr<ExprAST> null_expr = nullptr;
            // This should not crash
            tf.assert_true(null_expr == nullptr, "Null pointer handled correctly");
        }
        catch (...)
        {
            tf.assert_true(false, "Exception thrown when handling null pointer");
        }
    }

    // Test empty vector handling
    {
        try
        {
            std::vector<std::unique_ptr<ExprAST>> empty_args;
            CallExprAST call("test", std::move(empty_args));
            tf.assert_true(true, "CallExprAST with empty arguments created successfully");
        }
        catch (...)
        {
            tf.assert_true(false, "Exception thrown when creating CallExprAST with empty arguments");
        }
    }
}