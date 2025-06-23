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
        tf.assert_equal(tokens[0], "IDENTIFIER:hello", "Simple identifier");
        tf.assert_equal(tokens[1], "IDENTIFIER:world", "Simple identifier");
        tf.assert_equal(tokens[2], "IDENTIFIER:_variable123", "Identifier with underscore and numbers");
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
        tf.assert_equal(tokens.size(), size_t(9), "Number of data type keywords");
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
        tf.assert_equal(tokens.size(), size_t(11), "Number of control flow keywords");
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
        tf.assert_equal(tokens.size(), size_t(10), "Number of other keywords");
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
        tf.assert_equal(tokens.size(), size_t(9), "Number of STL container tokens");
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
        tf.assert_equal(tokens[0], "STRING_LITERAL:\"Hello World\"", "Basic string literal");
        tf.assert_equal(tokens[1], "STRING_LITERAL:\"Test\\nString\"", "String with escape sequence");
        tf.assert_equal(tokens[2], "STRING_LITERAL:\"\"", "Empty string literal");
    }

    // Test character literals
    {
        Lexer lexer("'a' '\\n' '\\t' '\\0'");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(4), "Number of character literal tokens");
        tf.assert_equal(tokens[0], "CHAR_LITERAL:'a'", "Basic character literal");
        tf.assert_equal(tokens[1], "CHAR_LITERAL:'\\n'", "Character with newline escape");
        tf.assert_equal(tokens[2], "CHAR_LITERAL:'\\t'", "Character with tab escape");
        tf.assert_equal(tokens[3], "CHAR_LITERAL:'\\0'", "Character with null escape");
    }
}

void test_comments()
{
    TestFramework tf("Comments");

    // Test single-line comments - comments should be skipped
    {
        Lexer lexer("int x = 5; // This is a comment");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(5), "Number of tokens after comment");
        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after comment");
        tf.assert_equal(tokens[1], "IDENTIFIER:x", "Variable name after comment");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after comment");
        tf.assert_contains(tokens[3], "NUMBER:5", "Number after comment");
        tf.assert_contains(tokens[4], "PUNCTUATOR:;", "Semicolon after comment");
    }

    // Test hash comments
    {
        Lexer lexer("int y = 10; # This is a hash comment");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(5), "Number of tokens after hash comment");
        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after hash comment");
        tf.assert_equal(tokens[1], "IDENTIFIER:y", "Variable name after hash comment");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after hash comment");
        tf.assert_contains(tokens[3], "NUMBER:10", "Number after hash comment");
        tf.assert_contains(tokens[4], "PUNCTUATOR:;", "Semicolon after hash comment");
    }

    // Test multi-line comments
    {
        Lexer lexer("int z = 15; /* This is a\nmulti-line comment */");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(5), "Number of tokens after multi-line comment");
        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after multi-line comment");
        tf.assert_equal(tokens[1], "IDENTIFIER:z", "Variable name after multi-line comment");
        tf.assert_contains(tokens[2], "PUNCTUATOR:=", "Assignment operator after multi-line comment");
        tf.assert_contains(tokens[3], "NUMBER:15", "Number after multi-line comment");
        tf.assert_contains(tokens[4], "PUNCTUATOR:;", "Semicolon after multi-line comment");
    }
}

void test_preprocessor()
{
    TestFramework tf("Preprocessor Directives");

    // Test preprocessor directives - should be skipped
    {
        Lexer lexer("#include <iostream>\nint main() { return 0; }");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(0), "Number of preprocessor tokens (should be 0 as they are skipped)");
    }

    // Test define directives
    {
        Lexer lexer("#define MAX_SIZE 100\nint x = MAX_SIZE;");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(0), "Number of define tokens (should be 0 as they are skipped)");
    }

    // Test mixed code with preprocessor
    {
        Lexer lexer("#include <iostream>\nint main() {\n    int x = 42;\n    return x;\n}");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens.size(), size_t(9), "Number of tokens after preprocessor directive");
        tf.assert_contains(tokens[0], "KEYWORD:int", "Keyword after preprocessor directive");
        tf.assert_equal(tokens[1], "IDENTIFIER:main", "Function name after preprocessor directive");
        tf.assert_contains(tokens[2], "PUNCTUATOR:(", "Opening parenthesis after preprocessor directive");
        tf.assert_contains(tokens[3], "PUNCTUATOR:)", "Closing parenthesis after preprocessor directive");
        tf.assert_contains(tokens[4], "PUNCTUATOR:{", "Opening brace after preprocessor directive");
        tf.assert_contains(tokens[5], "KEYWORD:int", "int keyword after preprocessor directive");
        tf.assert_equal(tokens[6], "IDENTIFIER:x", "Variable name after preprocessor directive");
        tf.assert_contains(tokens[7], "PUNCTUATOR:=", "Assignment operator after preprocessor directive");
        tf.assert_contains(tokens[8], "NUMBER:42", "Number after preprocessor directive");
    }
}

void test_error_handling()
{
    TestFramework tf("Error Handling");

    // Test unknown character
    {
        Lexer lexer("int x = 5; @");
        try
        {
            auto tokens = lexer.tokenize();
            tf.assert_true(false, "Unknown character throws exception");
        }
        catch (const std::runtime_error &e)
        {
            tf.assert_true(true, "Unknown character throws exception");
        }
    }

    // Test unterminated string
    {
        Lexer lexer("int x = 5; \"unterminated string");
        try
        {
            auto tokens = lexer.tokenize();
            tf.assert_true(true, "Unterminated string handled gracefully");
        }
        catch (const std::runtime_error &e)
        {
            tf.assert_true(false, "Unterminated string should be handled gracefully");
        }
    }
}

void test_complex_expressions()
{
    TestFramework tf("Complex Expressions");

    // Test STL template expression
    {
        Lexer lexer("std::vector<int>");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens[0], "IDENTIFIER:std", "std namespace");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator");
        tf.assert_contains(tokens[2], "STL_CONTAINER:vector", "vector container");
        tf.assert_contains(tokens[3], "PUNCTUATOR:<", "Template opening");
        tf.assert_contains(tokens[4], "KEYWORD:int", "int keyword");
        tf.assert_contains(tokens[5], "PUNCTUATOR:>", "Template closing");
    }

    // Test STL algorithm call
    {
        Lexer lexer("std::sort(numbers.begin(), numbers.end())");
        auto tokens = lexer.tokenize();
        tf.assert_equal(tokens[0], "IDENTIFIER:std", "std namespace");
        tf.assert_contains(tokens[1], "OPERATOR:::", "Scope resolution operator");
        tf.assert_contains(tokens[2], "STL_ALGORITHM:sort", "sort algorithm");
        tf.assert_contains(tokens[3], "PUNCTUATOR:(", "Function call opening");
        tf.assert_equal(tokens[4], "IDENTIFIER:numbers", "Variable name");
        tf.assert_contains(tokens[5], "PUNCTUATOR:.", "Member access");
        tf.assert_contains(tokens[6], "STL_ITERATOR:begin", "begin iterator");
    }
}