#include "test_framework.h"
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"
#include <iostream>
#include <vector>

void test_basic_kaleidoscope_integration()
{
    TestFramework tf("Basic Kaleidoscope Integration");

    // Test simple arithmetic expression
    {
        std::string code = "1 + 2 * 3";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_equal(tokens.size(), size_t(5), "Correct number of tokens");
        tf.assert_contains(tokens[0], "NUMBER:1", "First token is number 1");
        tf.assert_contains(tokens[1], "PUNCTUATOR:+", "Second token is plus operator");
        tf.assert_contains(tokens[2], "NUMBER:2", "Third token is number 2");
        tf.assert_contains(tokens[3], "PUNCTUATOR:*", "Fourth token is multiply operator");
        tf.assert_contains(tokens[4], "NUMBER:3", "Fifth token is number 3");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "AST created successfully");

        if (ast)
        {
            std::cout << "AST for '1 + 2 * 3': ";
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test function definition
    {
        std::string code = "def average(x, y) (x + y) / 2.0";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_true(tokens.size() > 0, "Tokens generated for function definition");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Function definition AST created");

        if (ast)
        {
            std::cout << "AST for function definition: ";
            ast->print();
            std::cout << std::endl;
        }
    }
}

void test_c_language_integration()
{
    TestFramework tf("C Language Integration");

    // Test C-style variable declaration
    {
        std::string code = "int x = 42;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_contains(tokens[0], "KEYWORD:int", "int keyword recognized");
        tf.assert_equal(tokens[1], "x", "Variable name recognized");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator recognized");
        tf.assert_contains(tokens[3], "NUMBER:42", "Number literal recognized");
        tf.assert_contains(tokens[4], "PUNCTUATOR:;", "Semicolon recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "C-style declaration parsed");
    }

    // Test C-style function declaration
    {
        std::string code = "int main() { return 0; }";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_contains(tokens[0], "KEYWORD:int", "int keyword recognized");
        tf.assert_equal(tokens[1], "main", "Function name recognized");
        tf.assert_contains(tokens[2], "PUNCTUATOR:(", "Opening parenthesis recognized");
        tf.assert_contains(tokens[3], "PUNCTUATOR:)", "Closing parenthesis recognized");
        tf.assert_contains(tokens[4], "PUNCTUATOR:{", "Opening brace recognized");
        tf.assert_contains(tokens[5], "KEYWORD:return", "return keyword recognized");
        tf.assert_contains(tokens[6], "NUMBER:0", "Return value recognized");
        tf.assert_contains(tokens[7], "PUNCTUATOR:;", "Semicolon recognized");
        tf.assert_contains(tokens[8], "PUNCTUATOR:}", "Closing brace recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "C-style function parsed");
    }
}

void test_stl_integration()
{
    TestFramework tf("STL Integration");

    // Test STL container declaration
    {
        std::string code = "std::vector<int> numbers = {1, 2, 3};";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_equal(tokens[0], "std", "std namespace recognized");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator recognized");
        tf.assert_contains(tokens[2], "STL_CONTAINER:vector", "vector container recognized");
        tf.assert_contains(tokens[3], "PUNCTUATOR:<", "Template opening recognized");
        tf.assert_contains(tokens[4], "KEYWORD:int", "int keyword recognized");
        tf.assert_contains(tokens[5], "PUNCTUATOR:>", "Template closing recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "STL container declaration parsed");
    }

    // Test STL algorithm call
    {
        std::string code = "std::sort(numbers.begin(), numbers.end());";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_equal(tokens[0], "std", "std namespace recognized");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator recognized");
        tf.assert_contains(tokens[2], "STL_ALGORITHM:sort", "sort algorithm recognized");
        tf.assert_contains(tokens[3], "PUNCTUATOR:(", "Function call opening recognized");
        tf.assert_equal(tokens[4], "numbers", "Container name recognized");
        tf.assert_contains(tokens[5], "PUNCTUATOR:.", "Member access operator recognized");
        tf.assert_contains(tokens[6], "STL_ITERATOR:begin", "begin iterator recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "STL algorithm call parsed");
    }
}

void test_complex_expressions_integration()
{
    TestFramework tf("Complex Expressions Integration");

    // Test complex arithmetic with parentheses
    {
        std::string code = "(a + b) * (c - d) / e";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_contains(tokens[0], "PUNCTUATOR:(", "Opening parenthesis recognized");
        tf.assert_equal(tokens[1], "a", "Variable a recognized");
        tf.assert_contains(tokens[2], "PUNCTUATOR:+", "Plus operator recognized");
        tf.assert_equal(tokens[3], "b", "Variable b recognized");
        tf.assert_contains(tokens[4], "PUNCTUATOR:)", "Closing parenthesis recognized");
        tf.assert_contains(tokens[5], "PUNCTUATOR:*", "Multiply operator recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Complex arithmetic expression parsed");

        if (ast)
        {
            std::cout << "AST for complex expression: ";
            ast->print();
            std::cout << std::endl;
        }
    }

    // Test nested function calls
    {
        std::string code = "outer(inner(x), y)";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_equal(tokens[0], "outer", "Outer function name recognized");
        tf.assert_contains(tokens[1], "PUNCTUATOR:(", "Function call opening recognized");
        tf.assert_equal(tokens[2], "inner", "Inner function name recognized");
        tf.assert_contains(tokens[3], "PUNCTUATOR:(", "Nested function call opening recognized");
        tf.assert_equal(tokens[4], "x", "First argument recognized");
        tf.assert_contains(tokens[5], "PUNCTUATOR:)", "Nested function call closing recognized");
        tf.assert_contains(tokens[6], "PUNCTUATOR:,", "Comma separator recognized");
        tf.assert_equal(tokens[7], "y", "Second argument recognized");
        tf.assert_contains(tokens[8], "PUNCTUATOR:)", "Function call closing recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Nested function calls parsed");
    }
}

void test_error_recovery_integration()
{
    TestFramework tf("Error Recovery Integration");

    // Test with invalid syntax but continue parsing
    {
        std::string code = "1 + 2; 3 * 4;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);

        // Parse first expression
        auto ast1 = parser.Parse();
        tf.assert_true(ast1 != nullptr, "First expression parsed despite semicolon");

        // Parse second expression
        auto ast2 = parser.Parse();
        tf.assert_true(ast2 != nullptr, "Second expression parsed");

        if (ast1)
        {
            std::cout << "First AST: ";
            ast1->print();
            std::cout << std::endl;
        }
        if (ast2)
        {
            std::cout << "Second AST: ";
            ast2->print();
            std::cout << std::endl;
        }
    }
}

void test_comments_integration()
{
    TestFramework tf("Comments Integration");

    // Test with single-line comments
    {
        std::string code = "// This is a comment\nint x = 5;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after comment recognized");
        tf.assert_equal(tokens[1], "x", "Variable name after comment recognized");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after comment recognized");
        tf.assert_contains(tokens[3], "NUMBER:5", "Number after comment recognized");
        tf.assert_contains(tokens[4], "PUNCTUATOR:;", "Semicolon after comment recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Code with comments parsed successfully");
    }

    // Test with multi-line comments
    {
        std::string code = "/* Multi-line\n   comment */\ndouble y = 3.14;";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_contains(tokens[0], "KEYWORD:double", "Keyword after multi-line comment recognized");
        tf.assert_equal(tokens[1], "y", "Variable name after multi-line comment recognized");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after multi-line comment recognized");
        tf.assert_contains(tokens[3], "NUMBER:3.14", "Number after multi-line comment recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "Code with multi-line comments parsed successfully");
    }
}

void test_string_literals_integration()
{
    TestFramework tf("String Literals Integration");

    // Test string literals in expressions
    {
        std::string code = "std::cout << \"Hello World\";";
        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_equal(tokens[0], "std", "std namespace recognized");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator recognized");
        tf.assert_contains(tokens[2], "STL_IO:cout", "cout recognized");
        tf.assert_contains(tokens[3], "OPERATOR:<<", "Output operator recognized");
        tf.assert_equal(tokens[4], "\"Hello World\"", "String literal recognized");
        tf.assert_contains(tokens[5], "PUNCTUATOR:;", "Semicolon recognized");

        Parser parser(tokens);
        auto ast = parser.Parse();
        tf.assert_true(ast != nullptr, "String literal expression parsed");
    }
}

void test_complete_program_integration()
{
    TestFramework tf("Complete Program Integration");

    // Test a complete C++ program snippet
    {
        std::string code = R"(
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Sum: " << std::accumulate(numbers.begin(), numbers.end(), 0) << std::endl;
    return 0;
}
)";

        Lexer lexer(code);
        auto tokens = lexer.tokenize();

        tf.assert_true(tokens.size() > 0, "Complete program tokenized successfully");

        // Check for key tokens
        bool has_include = false, has_int = false, has_main = false, has_vector = false, has_cout = false;
        for (const auto &token : tokens)
        {
            if (token.find("#include") != std::string::npos)
                has_include = true;
            if (token.find("KEYWORD:int") != std::string::npos)
                has_int = true;
            if (token == "main")
                has_main = true;
            if (token.find("STL_CONTAINER:vector") != std::string::npos)
                has_vector = true;
            if (token.find("STL_IO:cout") != std::string::npos)
                has_cout = true;
        }

        tf.assert_true(has_include, "Include directive recognized");
        tf.assert_true(has_int, "int keyword recognized");
        tf.assert_true(has_main, "main function name recognized");
        tf.assert_true(has_vector, "vector container recognized");
        tf.assert_true(has_cout, "cout recognized");

        Parser parser(tokens);

        // Try to parse as much as possible
        int parsed_count = 0;
        while (auto ast = parser.Parse())
        {
            parsed_count++;
            if (parsed_count <= 3)
            { // Limit output
                std::cout << "Parsed statement " << parsed_count << ": ";
                ast->print();
                std::cout << std::endl;
            }
        }

        tf.assert_true(parsed_count > 0, "At least some statements parsed successfully");
    }
}

int main()
{
    std::cout << "🚀 Starting Integration Tests\n";
    std::cout << "=============================\n";

    RUN_TEST(test_basic_kaleidoscope_integration);
    RUN_TEST(test_c_language_integration);
    RUN_TEST(test_stl_integration);
    RUN_TEST(test_complex_expressions_integration);
    RUN_TEST(test_error_recovery_integration);
    RUN_TEST(test_comments_integration);
    RUN_TEST(test_string_literals_integration);
    RUN_TEST(test_complete_program_integration);

    std::cout << "\n🎉 All integration tests completed!\n";
    return 0;
}