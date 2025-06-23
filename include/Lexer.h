#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

class Lexer
{
public:
    Lexer(const std::string &source);
    std::vector<std::string> tokenize();

private:
    std::string source_;
    size_t current_pos_;
    char current_char_;

    // Keyword sets
    static std::unordered_set<std::string> c_keywords;
    static std::unordered_set<std::string> stl_containers;
    static std::unordered_set<std::string> stl_algorithms;
    static std::unordered_set<std::string> stl_iterators;
    static std::unordered_set<std::string> stl_utilities;
    static std::unordered_set<std::string> stl_string_operations;
    static std::unordered_set<std::string> stl_io_operations;
    static std::unordered_set<std::string> stl_memory_management;

    // Multi-character operators
    static std::vector<std::string> multi_char_operators;

    // Token types
    enum class TokenType
    {
        KEYWORD,
        IDENTIFIER,
        NUMBER,
        STRING_LITERAL,
        CHAR_LITERAL,
        OPERATOR,
        PUNCTUATOR,
        COMMENT,
        WHITESPACE,
        PREPROCESSOR,
        STL_FUNCTION,
        STL_CONTAINER,
        STL_ALGORITHM,
        STL_ITERATOR,
        STL_UTILITY,
        STL_IO,
        STL_MEMORY,
        STL_STRING,
        UNKNOWN
    };

    void advance();
    void skipWhitespace();
    void skipComment();
    void skipMultiLineComment();
    std::string getIdentifier();
    std::string getNumber();
    std::string getStringLiteral();
    std::string getCharLiteral();
    std::string getPreprocessorDirective();
    std::string getMultiCharOperator();

    // Keyword recognition methods
    bool isCKeyword(const std::string &identifier);
    bool isSTLContainer(const std::string &identifier);
    bool isSTLAlgorithm(const std::string &identifier);
    bool isSTLIterator(const std::string &identifier);
    bool isSTLUtility(const std::string &identifier);
    bool isSTLIO(const std::string &identifier);
    bool isSTLMemory(const std::string &identifier);
    bool isSTLString(const std::string &identifier);
    bool isMultiCharOperator(const std::string &op);

    // Initialize keyword sets
    static void initializeKeywords();
    static bool keywords_initialized;
};

#endif // LEXER_H