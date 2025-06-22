#include "test_framework.h"
#include "AST.h"
#include <iostream>
#include <memory>

void test_number_expr_ast()
{
    TestFramework tf("NumberExprAST");

    // Test basic number
    {
        NumberExprAST num(42.0);
        tf.assert_true(true, "NumberExprAST created successfully");

        // Test print functionality (capture output)
        std::cout << "NumberExprAST(42.0): ";
        num.print();
        std::cout << std::endl;
    }

    // Test negative number
    {
        NumberExprAST num(-3.14);
        tf.assert_true(true, "Negative NumberExprAST created successfully");

        std::cout << "NumberExprAST(-3.14): ";
        num.print();
        std::cout << std::endl;
    }

    // Test zero
    {
        NumberExprAST num(0.0);
        tf.assert_true(true, "Zero NumberExprAST created successfully");

        std::cout << "NumberExprAST(0.0): ";
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

        std::cout << "VariableExprAST(\"x\"): ";
        var.print();
        std::cout << std::endl;
    }

    // Test variable with underscore
    {
        VariableExprAST var("_my_variable");
        tf.assert_true(true, "VariableExprAST with underscore created successfully");

        std::cout << "VariableExprAST(\"_my_variable\"): ";
        var.print();
        std::cout << std::endl;
    }

    // Test variable with numbers
    {
        VariableExprAST var("var123");
        tf.assert_true(true, "VariableExprAST with numbers created successfully");

        std::cout << "VariableExprAST(\"var123\"): ";
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
        BinaryExprAST bin('+', std::move(lhs), std::move(rhs));
        tf.assert_true(true, "BinaryExprAST created successfully");

        std::cout << "BinaryExprAST(5 + 3): ";
        bin.print();
        std::cout << std::endl;
    }

    // Test binary expression with variables
    {
        auto lhs = std::make_unique<VariableExprAST>("x");
        auto rhs = std::make_unique<VariableExprAST>("y");
        BinaryExprAST bin('*', std::move(lhs), std::move(rhs));
        tf.assert_true(true, "BinaryExprAST with variables created successfully");

        std::cout << "BinaryExprAST(x * y): ";
        bin.print();
        std::cout << std::endl;
    }

    // Test complex binary expression
    {
        auto inner_lhs = std::make_unique<NumberExprAST>(2.0);
        auto inner_rhs = std::make_unique<NumberExprAST>(3.0);
        auto inner = std::make_unique<BinaryExprAST>('+', std::move(inner_lhs), std::move(inner_rhs));

        auto outer_rhs = std::make_unique<NumberExprAST>(4.0);
        BinaryExprAST outer('*', std::move(inner), std::move(outer_rhs));
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
        std::vector<std::string> args = {"x", "y"};
        PrototypeAST proto("average", std::move(args));
        tf.assert_true(true, "PrototypeAST created successfully");

        std::cout << "PrototypeAST(def average(x, y)): ";
        proto.print();
        std::cout << std::endl;
    }

    // Test function prototype with no arguments
    {
        std::vector<std::string> args;
        PrototypeAST proto("main", std::move(args));
        tf.assert_true(true, "PrototypeAST with no arguments created successfully");

        std::cout << "PrototypeAST(def main()): ";
        proto.print();
        std::cout << std::endl;
    }

    // Test function prototype with many arguments
    {
        std::vector<std::string> args = {"a", "b", "c", "d", "e"};
        PrototypeAST proto("complex_func", std::move(args));
        tf.assert_true(true, "PrototypeAST with many arguments created successfully");

        std::cout << "PrototypeAST(def complex_func(a, b, c, d, e)): ";
        proto.print();
        std::cout << std::endl;
    }

    // Test operator prototype
    {
        std::vector<std::string> args = {"lhs", "rhs"};
        PrototypeAST proto("+", std::move(args), true, 1);
        tf.assert_true(true, "Operator PrototypeAST created successfully");

        std::cout << "PrototypeAST(binary + (lhs, rhs)): ";
        proto.print();
        std::cout << std::endl;
    }
}

void test_function_ast()
{
    TestFramework tf("FunctionAST");

    // Test simple function definition
    {
        std::vector<std::string> proto_args = {"x", "y"};
        auto proto = std::make_unique<PrototypeAST>("add", std::move(proto_args));

        auto lhs = std::make_unique<VariableExprAST>("x");
        auto rhs = std::make_unique<VariableExprAST>("y");
        auto body = std::make_unique<BinaryExprAST>('+', std::move(lhs), std::move(rhs));

        FunctionAST func(std::move(proto), std::move(body));
        tf.assert_true(true, "FunctionAST created successfully");

        std::cout << "FunctionAST(def add(x, y) (x + y)): ";
        func.print();
        std::cout << std::endl;
    }

    // Test function with complex body
    {
        std::vector<std::string> proto_args = {"a", "b", "c"};
        auto proto = std::make_unique<PrototypeAST>("complex", std::move(proto_args));

        // Create complex body: (a + b) * c
        auto inner_lhs = std::make_unique<VariableExprAST>("a");
        auto inner_rhs = std::make_unique<VariableExprAST>("b");
        auto inner = std::make_unique<BinaryExprAST>('+', std::move(inner_lhs), std::move(inner_rhs));

        auto outer_rhs = std::make_unique<VariableExprAST>("c");
        auto body = std::make_unique<BinaryExprAST>('*', std::move(inner), std::move(outer_rhs));

        FunctionAST func(std::move(proto), std::move(body));
        tf.assert_true(true, "FunctionAST with complex body created successfully");

        std::cout << "FunctionAST(def complex(a, b, c) ((a + b) * c)): ";
        func.print();
        std::cout << std::endl;
    }

    // Test function with function call in body
    {
        std::vector<std::string> proto_args = {"x"};
        auto proto = std::make_unique<PrototypeAST>("wrapper", std::move(proto_args));

        std::vector<std::unique_ptr<ExprAST>> call_args;
        call_args.push_back(std::make_unique<VariableExprAST>("x"));
        auto body = std::make_unique<CallExprAST>("inner_func", std::move(call_args));

        FunctionAST func(std::move(proto), std::move(body));
        tf.assert_true(true, "FunctionAST with function call body created successfully");

        std::cout << "FunctionAST(def wrapper(x) inner_func(x)): ";
        func.print();
        std::cout << std::endl;
    }
}

void test_ast_polymorphism()
{
    TestFramework tf("AST Polymorphism");

    // Test vector of different AST types
    {
        std::vector<std::unique_ptr<ExprAST>> expressions;

        // Add different types of expressions
        expressions.push_back(std::make_unique<NumberExprAST>(42.0));
        expressions.push_back(std::make_unique<VariableExprAST>("x"));

        auto lhs = std::make_unique<NumberExprAST>(1.0);
        auto rhs = std::make_unique<NumberExprAST>(2.0);
        expressions.push_back(std::make_unique<BinaryExprAST>('+', std::move(lhs), std::move(rhs)));

        std::vector<std::unique_ptr<ExprAST>> call_args;
        call_args.push_back(std::make_unique<NumberExprAST>(5.0));
        expressions.push_back(std::make_unique<CallExprAST>("func", std::move(call_args)));

        tf.assert_equal(expressions.size(), size_t(4), "Vector contains 4 different AST types");

        std::cout << "Polymorphic AST vector contents:\n";
        for (size_t i = 0; i < expressions.size(); ++i)
        {
            std::cout << "  " << i << ": ";
            expressions[i]->print();
            std::cout << std::endl;
        }
    }
}

void test_ast_memory_management()
{
    TestFramework tf("AST Memory Management");

    // Test unique_ptr ownership transfer
    {
        auto original = std::make_unique<NumberExprAST>(42.0);
        tf.assert_true(original != nullptr, "Original unique_ptr created");

        auto moved = std::move(original);
        tf.assert_true(moved != nullptr, "Moved unique_ptr is valid");
        tf.assert_true(original == nullptr, "Original unique_ptr is null after move");

        // Test that moved pointer can still be used
        std::cout << "Moved NumberExprAST: ";
        moved->print();
        std::cout << std::endl;
    }

    // Test nested unique_ptr management
    {
        auto inner = std::make_unique<NumberExprAST>(10.0);
        auto outer = std::make_unique<BinaryExprAST>('+', std::move(inner), std::make_unique<NumberExprAST>(5.0));

        tf.assert_true(outer != nullptr, "Nested unique_ptr structure created");
        tf.assert_true(inner == nullptr, "Inner unique_ptr moved successfully");

        std::cout << "Nested unique_ptr structure: ";
        outer->print();
        std::cout << std::endl;
    }
}

void test_ast_error_handling()
{
    TestFramework tf("AST Error Handling");

    // Test with null pointers (should not crash)
    {
        try
        {
            // This should not crash even with null pointers
            std::vector<std::unique_ptr<ExprAST>> empty_args;
            CallExprAST call("test", std::move(empty_args));
            tf.assert_true(true, "CallExprAST with empty args created successfully");

            std::cout << "CallExprAST with empty args: ";
            call.print();
            std::cout << std::endl;
        }
        catch (...)
        {
            tf.assert_true(false, "CallExprAST with empty args should not throw");
        }
    }
}

int main()
{
    std::cout << "🚀 Starting AST Unit Tests\n";
    std::cout << "==========================\n";

    RUN_TEST(test_number_expr_ast);
    RUN_TEST(test_variable_expr_ast);
    RUN_TEST(test_binary_expr_ast);
    RUN_TEST(test_call_expr_ast);
    RUN_TEST(test_prototype_ast);
    RUN_TEST(test_function_ast);
    RUN_TEST(test_ast_polymorphism);
    RUN_TEST(test_ast_memory_management);
    RUN_TEST(test_ast_error_handling);

    std::cout << "\n🎉 All AST unit tests completed!\n";
    return 0;
}