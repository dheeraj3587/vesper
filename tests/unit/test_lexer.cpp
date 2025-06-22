#include "test_framework.h"
#include "Lexer.h"
#include <iostream>
#include <vector>

void test_basic_tokens()
{
    TestFramework tf("Basic Tokens");

    // Test numbers
    {
        Lexer lexer("42 3.14 -5.2 1e-3");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of tokens");
        tf.assert_contains(tokens[0], "NUMBER:42", "Integer token");
        tf.assert_contains(tokens[1], "NUMBER:3.14", "Float token");
        tf.assert_contains(tokens[2], "NUMBER:-5.2", "Negative float token");
        tf.assert_contains(tokens[3], "NUMBER:1e-3", "Scientific notation token");
    }

    // Test identifiers
    {
        Lexer lexer("hello world _variable123");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(3), "Number of identifier tokens");
        tf.assert_equal(tokens[0], "hello", "Simple identifier");
        tf.assert_equal(tokens[1], "world", "Simple identifier");
        tf.assert_equal(tokens[2], "_variable123", "Identifier with underscore and numbers");
    }

    // Test operators
    {
        Lexer lexer("+ - * / = < > <= >= == != && || ++ --");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(15), "Number of operator tokens");
        tf.assert_contains(tokens[0], "PUNCTUATOR:+", "Plus operator");
        tf.assert_contains(tokens[1], "PUNCTUATOR:-", "Minus operator");
        tf.assert_contains(tokens[2], "PUNCTUATOR:*", "Multiply operator");
        tf.assert_contains(tokens[3], "PUNCTUATOR:/", "Divide operator");
        tf.assert_contains(tokens[4], "PUNCTUATOR:=", "Assignment operator");
        tf.assert_contains(tokens[5], "PUNCTUATOR:<", "Less than operator");
        tf.assert_contains(tokens[6], "PUNCTUATOR:>", "Greater than operator");
        tf.assert_contains(tokens[7], "OPERATOR:<=", "Less equal operator");
        tf.assert_contains(tokens[8], "OPERATOR:>=", "Greater equal operator");
        tf.assert_contains(tokens[9], "OPERATOR:==", "Equal operator");
        tf.assert_contains(tokens[10], "OPERATOR:!=", "Not equal operator");
        tf.assert_contains(tokens[11], "OPERATOR:&&", "Logical AND operator");
        tf.assert_contains(tokens[12], "OPERATOR:||", "Logical OR operator");
        tf.assert_contains(tokens[13], "OPERATOR:++", "Increment operator");
        tf.assert_contains(tokens[14], "OPERATOR:--", "Decrement operator");
    }
}

void test_c_keywords()
{
    TestFramework tf("C Keywords");

    // Test data type keywords
    {
        Lexer lexer("int char float double long short unsigned signed void");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(10), "Number of data type keywords");
        tf.assert_contains(tokens[0], "KEYWORD:int", "int keyword");
        tf.assert_contains(tokens[1], "KEYWORD:char", "char keyword");
        tf.assert_contains(tokens[2], "KEYWORD:float", "float keyword");
        tf.assert_contains(tokens[3], "KEYWORD:double", "double keyword");
        tf.assert_contains(tokens[4], "KEYWORD:long", "long keyword");
        tf.assert_contains(tokens[5], "KEYWORD:short", "short keyword");
        tf.assert_contains(tokens[6], "KEYWORD:unsigned", "unsigned keyword");
        tf.assert_contains(tokens[7], "KEYWORD:signed", "signed keyword");
        tf.assert_contains(tokens[8], "KEYWORD:void", "void keyword");
    }

    // Test control flow keywords
    {
        Lexer lexer("if else for while do switch case default break continue return");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(12), "Number of control flow keywords");
        tf.assert_contains(tokens[0], "KEYWORD:if", "if keyword");
        tf.assert_contains(tokens[1], "KEYWORD:else", "else keyword");
        tf.assert_contains(tokens[2], "KEYWORD:for", "for keyword");
        tf.assert_contains(tokens[3], "KEYWORD:while", "while keyword");
        tf.assert_contains(tokens[4], "KEYWORD:do", "do keyword");
        tf.assert_contains(tokens[5], "KEYWORD:switch", "switch keyword");
        tf.assert_contains(tokens[6], "KEYWORD:case", "case keyword");
        tf.assert_contains(tokens[7], "KEYWORD:default", "default keyword");
        tf.assert_contains(tokens[8], "KEYWORD:break", "break keyword");
        tf.assert_contains(tokens[9], "KEYWORD:continue", "continue keyword");
        tf.assert_contains(tokens[10], "KEYWORD:return", "return keyword");
    }

    // Test other keywords
    {
        Lexer lexer("const static extern auto register volatile struct union enum typedef");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(11), "Number of other keywords");
        tf.assert_contains(tokens[0], "KEYWORD:const", "const keyword");
        tf.assert_contains(tokens[1], "KEYWORD:static", "static keyword");
        tf.assert_contains(tokens[2], "KEYWORD:extern", "extern keyword");
        tf.assert_contains(tokens[3], "KEYWORD:auto", "auto keyword");
        tf.assert_contains(tokens[4], "KEYWORD:register", "register keyword");
        tf.assert_contains(tokens[5], "KEYWORD:volatile", "volatile keyword");
        tf.assert_contains(tokens[6], "KEYWORD:struct", "struct keyword");
        tf.assert_contains(tokens[7], "KEYWORD:union", "union keyword");
        tf.assert_contains(tokens[8], "KEYWORD:enum", "enum keyword");
        tf.assert_contains(tokens[9], "KEYWORD:typedef", "typedef keyword");
    }
}

void test_stl_components()
{
    TestFramework tf("STL Components");

    // Test STL containers
    {
        Lexer lexer("vector list map set unordered_map array deque stack queue");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(10), "Number of STL container tokens");
        tf.assert_contains(tokens[0], "STL_CONTAINER:vector", "vector container");
        tf.assert_contains(tokens[1], "STL_CONTAINER:list", "list container");
        tf.assert_contains(tokens[2], "STL_CONTAINER:map", "map container");
        tf.assert_contains(tokens[3], "STL_CONTAINER:set", "set container");
        tf.assert_contains(tokens[4], "STL_CONTAINER:unordered_map", "unordered_map container");
        tf.assert_contains(tokens[5], "STL_CONTAINER:array", "array container");
        tf.assert_contains(tokens[6], "STL_CONTAINER:deque", "deque container");
        tf.assert_contains(tokens[7], "STL_CONTAINER:stack", "stack container");
        tf.assert_contains(tokens[8], "STL_CONTAINER:queue", "queue container");
    }

    // Test STL algorithms
    {
        Lexer lexer("sort find transform accumulate copy move swap");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(7), "Number of STL algorithm tokens");
        tf.assert_contains(tokens[0], "STL_ALGORITHM:sort", "sort algorithm");
        tf.assert_contains(tokens[1], "STL_ALGORITHM:find", "find algorithm");
        tf.assert_contains(tokens[2], "STL_ALGORITHM:transform", "transform algorithm");
        tf.assert_contains(tokens[3], "STL_ALGORITHM:accumulate", "accumulate algorithm");
        tf.assert_contains(tokens[4], "STL_ALGORITHM:copy", "copy algorithm");
        tf.assert_contains(tokens[5], "STL_ALGORITHM:move", "move algorithm");
        tf.assert_contains(tokens[6], "STL_ALGORITHM:swap", "swap algorithm");
    }

    // Test STL utilities
    {
        Lexer lexer("make_pair make_unique make_shared move forward swap");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(6), "Number of STL utility tokens");
        tf.assert_contains(tokens[0], "STL_UTILITY:make_pair", "make_pair utility");
        tf.assert_contains(tokens[1], "STL_UTILITY:make_unique", "make_unique utility");
        tf.assert_contains(tokens[2], "STL_UTILITY:make_shared", "make_shared utility");
        tf.assert_contains(tokens[3], "STL_UTILITY:move", "move utility");
        tf.assert_contains(tokens[4], "STL_UTILITY:forward", "forward utility");
        tf.assert_contains(tokens[5], "STL_UTILITY:swap", "swap utility");
    }

    // Test STL I/O
    {
        Lexer lexer("cout cin cerr endl");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of STL I/O tokens");
        tf.assert_contains(tokens[0], "STL_IO:cout", "cout I/O");
        tf.assert_contains(tokens[1], "STL_IO:cin", "cin I/O");
        tf.assert_contains(tokens[2], "STL_IO:cerr", "cerr I/O");
        tf.assert_contains(tokens[3], "STL_IO:endl", "endl I/O");
    }
}

void test_string_literals()
{
    TestFramework tf("String Literals");

    // Test basic string literals
    {
        Lexer lexer("\"Hello World\" \"Test\\nString\" \"\"");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(3), "Number of string literal tokens");
        tf.assert_equal(tokens[0], "\"Hello World\"", "Basic string literal");
        tf.assert_equal(tokens[1], "\"Test\\nString\"", "String with escape sequence");
        tf.assert_equal(tokens[2], "\"\"", "Empty string literal");
    }

    // Test character literals
    {
        Lexer lexer("'a' '\\n' '\\t' '\\0'");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of character literal tokens");
        tf.assert_equal(tokens[0], "'a'", "Basic character literal");
        tf.assert_equal(tokens[1], "'\\n'", "Character with newline escape");
        tf.assert_equal(tokens[2], "'\\t'", "Character with tab escape");
        tf.assert_equal(tokens[3], "'\\0'", "Character with null escape");
    }
}

void test_comments()
{
    TestFramework tf("Comments");

    // Test single-line comments - comments should be skipped
    {
        Lexer lexer("// This is a comment\nint x = 5;");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of tokens after comment");
        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after comment");
        tf.assert_equal(tokens[1], "x", "Variable name after comment");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after comment");
        tf.assert_contains(tokens[3], "NUMBER:5", "Number after comment");
    }

    // Test hash comments - comments should be skipped
    {
        Lexer lexer("# This is a hash comment\nfloat y = 3.14;");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of tokens after hash comment");
        tf.assert_contains(tokens[0], "KEYWORD:float", "Keyword after hash comment");
        tf.assert_equal(tokens[1], "y", "Variable name after hash comment");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after hash comment");
        tf.assert_contains(tokens[3], "NUMBER:3.14", "Number after hash comment");
    }

    // Test multi-line comments - comments should be skipped
    {
        Lexer lexer("/* This is a\n   multi-line comment */\ndouble z = 2.718;");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of tokens after multi-line comment");
        tf.assert_contains(tokens[0], "KEYWORD:double", "Keyword after multi-line comment");
        tf.assert_equal(tokens[1], "z", "Variable name after multi-line comment");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after multi-line comment");
        tf.assert_contains(tokens[3], "NUMBER:2.718", "Number after multi-line comment");
    }
}

void test_preprocessor()
{
    TestFramework tf("Preprocessor Directives");

    // Test include directive - preprocessor directives should be skipped
    {
        Lexer lexer("#include <iostream>");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(0), "Number of preprocessor tokens (should be 0 as they are skipped)");
    }

    // Test define directive - preprocessor directives should be skipped
    {
        Lexer lexer("#define MAX_SIZE 100");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(0), "Number of define tokens (should be 0 as they are skipped)");
    }

    // Test preprocessor directive followed by code
    {
        Lexer lexer("#include <iostream>\nint main() { return 0; }");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(8), "Number of tokens after preprocessor directive");
        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after preprocessor directive");
        tf.assert_equal(tokens[1], "main", "Function name after preprocessor directive");
    }
}

void test_error_handling()
{
    TestFramework tf("Error Handling");

    // Test unknown character
    {
        Lexer lexer("int x = 5; @");
        tf.assert_throws([&lexer]()
                         { lexer.tokenize(); }, "Unknown character throws exception");
    }

    // Test unterminated string
    {
        Lexer lexer("\"unterminated string");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(1), "Unterminated string handled gracefully");
    }
}

void test_complex_expressions()
{
    TestFramework tf("Complex Expressions");

    // Test C++ style code
    {
        Lexer lexer("std::vector<int> numbers = {1, 2, 3};");
        auto tokens = lexer.tokenize();
        tf.assert_contains(tokens[0], "std", "std namespace");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator");
        tf.assert_contains(tokens[2], "STL_CONTAINER:vector", "vector container");
        tf.assert_contains(tokens[3], "PUNCTUATOR:<", "Template opening");
        tf.assert_contains(tokens[4], "KEYWORD:int", "int keyword");
        tf.assert_contains(tokens[5], "PUNCTUATOR:>", "Template closing");
    }

    // Test function call with STL
    {
        Lexer lexer("std::sort(vec.begin(), vec.end());");
        auto tokens = lexer.tokenize();
        tf.assert_contains(tokens[0], "std", "std namespace");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator");
        tf.assert_contains(tokens[2], "STL_ALGORITHM:sort", "sort algorithm");
        tf.assert_contains(tokens[3], "PUNCTUATOR:(", "Function call opening");
        tf.assert_contains(tokens[4], "vec", "Variable name");
        tf.assert_contains(tokens[5], "PUNCTUATOR:.", "Member access");
        tf.assert_contains(tokens[6], "STL_ITERATOR:begin", "begin iterator");
    }
}

int main()
{
    std::cout << "🚀 Starting Lexer Unit Tests\n";
    std::cout << "============================\n";

    RUN_TEST(test_basic_tokens);
    RUN_TEST(test_c_keywords);
    RUN_TEST(test_stl_components);
    RUN_TEST(test_string_literals);
    RUN_TEST(test_comments);
    RUN_TEST(test_preprocessor);
    RUN_TEST(test_error_handling);
    RUN_TEST(test_complex_expressions);

    std::cout << "\n🎉 All Lexer unit tests completed!\n";
    return 0;
}