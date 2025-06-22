#include "Lexer.h"
#include <cctype>
#include <stdexcept>
#include <iostream>

// Static member initialization
std::unordered_set<std::string> Lexer::c_keywords;
std::unordered_set<std::string> Lexer::stl_containers;
std::unordered_set<std::string> Lexer::stl_algorithms;
std::unordered_set<std::string> Lexer::stl_iterators;
std::unordered_set<std::string> Lexer::stl_utilities;
std::unordered_set<std::string> Lexer::stl_string_operations;
std::unordered_set<std::string> Lexer::stl_io_operations;
std::unordered_set<std::string> Lexer::stl_memory_management;
std::unordered_set<std::string> Lexer::multi_char_operators;
bool Lexer::keywords_initialized = false;

Lexer::Lexer(const std::string &source)
    : source_(source), current_pos_(0), current_char_(source.empty() ? '\0' : source_[0])
{
    initializeKeywords();
}

void Lexer::initializeKeywords()
{
    if (keywords_initialized)
        return;

    // C Language Keywords
    c_keywords = {
        // Data types
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",

        // C99 keywords
        "inline", "restrict", "_Bool", "_Complex", "_Imaginary",

        // C11 keywords
        "_Alignas", "_Alignof", "_Atomic", "_Generic", "_Noreturn", "_Static_assert", "_Thread_local",

        // Additional C keywords
        "true", "false", "NULL", "nullptr"};

    // STL Containers
    stl_containers = {
        "vector", "list", "deque", "array", "forward_list", "stack", "queue", "priority_queue",
        "set", "multiset", "map", "multimap", "unordered_set", "unordered_multiset",
        "unordered_map", "unordered_multimap", "bitset", "valarray", "tuple", "pair"};

    // STL Algorithms
    stl_algorithms = {
        "sort", "stable_sort", "partial_sort", "nth_element", "is_sorted", "is_sorted_until",
        "find", "find_if", "find_if_not", "find_end", "find_first_of", "adjacent_find",
        "count", "count_if", "mismatch", "equal", "is_permutation", "search", "search_n",
        "copy", "copy_if", "copy_n", "copy_backward", "move", "move_backward", "swap",
        "swap_ranges", "iter_swap", "transform", "replace", "replace_if", "replace_copy",
        "replace_copy_if", "fill", "fill_n", "generate", "generate_n", "remove", "remove_if",
        "remove_copy", "remove_copy_if", "unique", "unique_copy", "reverse", "reverse_copy",
        "rotate", "rotate_copy", "random_shuffle", "shuffle", "is_partitioned", "partition",
        "stable_partition", "partition_copy", "partition_point", "merge", "inplace_merge",
        "includes", "set_union", "set_intersection", "set_difference", "set_symmetric_difference",
        "push_heap", "pop_heap", "make_heap", "sort_heap", "is_heap", "is_heap_until",
        "min", "max", "minmax", "min_element", "max_element", "minmax_element", "lexicographical_compare",
        "next_permutation", "prev_permutation", "accumulate", "inner_product", "adjacent_difference",
        "partial_sum", "iota", "all_of", "any_of", "none_of", "for_each", "for_each_n"};

    // STL Iterators
    stl_iterators = {
        "begin", "end", "cbegin", "cend", "rbegin", "rend", "crbegin", "crend",
        "advance", "distance", "next", "prev", "back_inserter", "front_inserter", "inserter"};

    // STL Utilities
    stl_utilities = {
        "make_pair", "make_tuple", "tie", "forward_as_tuple", "tuple_cat", "get", "tuple_size",
        "tuple_element", "piecewise_construct", "piecewise_construct_t", "ignore",
        "declval", "decltype", "move", "forward", "swap", "exchange", "make_unique",
        "make_shared", "allocate_shared", "static_pointer_cast", "dynamic_pointer_cast",
        "const_pointer_cast", "reinterpret_pointer_cast", "get_deleter", "owner_less",
        "enable_shared_from_this", "bad_weak_ptr", "hash", "equal_to", "not_equal_to",
        "greater", "less", "greater_equal", "less_equal", "logical_and", "logical_or",
        "logical_not", "bit_and", "bit_or", "bit_xor", "bit_not", "plus", "minus",
        "multiplies", "divides", "modulus", "negate"};

    // STL String Operations
    stl_string_operations = {
        "append", "assign", "at", "back", "begin", "capacity", "cbegin", "cend", "clear",
        "compare", "copy", "crbegin", "crend", "data", "empty", "end", "erase", "find",
        "find_first_not_of", "find_first_of", "find_last_not_of", "find_last_of", "front",
        "get_allocator", "insert", "length", "max_size", "pop_back", "push_back", "rbegin",
        "rend", "replace", "reserve", "resize", "rfind", "shrink_to_fit", "size", "substr",
        "swap", "to_string", "stoi", "stol", "stoul", "stoll", "stoull", "stof", "stod",
        "stold", "to_wstring"};

    // STL I/O Operations
    stl_io_operations = {
        "cin", "cout", "cerr", "clog", "wcin", "wcout", "wcerr", "wclog", "endl", "ends", "flush",
        "getline", "get", "put", "putback", "peek", "ignore", "read", "readsome", "write",
        "tellg", "tellp", "seekg", "seekp", "sync", "sync_with_stdio", "tie", "rdbuf",
        "setstate", "clear", "good", "eof", "fail", "bad", "exceptions", "setf", "unsetf",
        "flags", "setiosflags", "resetiosflags", "setbase", "setfill", "setprecision", "setw",
        "hex", "dec", "oct", "fixed", "scientific", "left", "right", "internal", "showbase",
        "noshowbase", "showpoint", "noshowpoint", "showpos", "noshowpos", "skipws", "noskipws",
        "uppercase", "nouppercase", "unitbuf", "nounitbuf", "boolalpha", "noboolalpha"};

    // STL Memory Management
    stl_memory_management = {
        "allocator", "allocator_traits", "default_delete", "unique_ptr", "shared_ptr",
        "weak_ptr", "auto_ptr", "enable_shared_from_this", "bad_weak_ptr", "owner_less",
        "make_unique", "make_shared", "allocate_shared", "static_pointer_cast",
        "dynamic_pointer_cast", "const_pointer_cast", "reinterpret_pointer_cast",
        "get_deleter", "pointer_traits", "addressof", "align", "aligned_storage",
        "aligned_union", "uses_allocator", "scoped_allocator_adaptor", "allocator_arg",
        "allocator_arg_t", "uses_allocator_v"};

    // Multi-character operators
    multi_char_operators = {
        "++", "--", "->", "->*", ".*", "::", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||",
        "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", "<=>"};

    keywords_initialized = true;
}

void Lexer::advance()
{
    current_pos_++;
    if (current_pos_ >= source_.length())
    {
        current_char_ = '\0'; // EOF
    }
    else
    {
        current_char_ = source_[current_pos_];
    }
}

void Lexer::skipWhitespace()
{
    while (current_char_ != '\0' && std::isspace(current_char_))
    {
        advance();
    }
}

void Lexer::skipComment()
{
    if (current_char_ == '#')
    {
        while (current_char_ != '\0' && current_char_ != '\n' && current_char_ != '\r')
        {
            advance();
        }
        // Also consume the newline character(s) after the comment
        if (current_char_ == '\r' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '\n')
        {
            advance(); // Consume \r
            advance(); // Consume \n
        }
        else if (current_char_ == '\n' || current_char_ == '\r')
        {
            advance(); // Consume single newline/carriage return
        }
    }
    else if (current_char_ == '/' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '/')
    {
        // C++ style single line comment
        while (current_char_ != '\0' && current_char_ != '\n' && current_char_ != '\r')
        {
            advance();
        }
        if (current_char_ == '\r' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '\n')
        {
            advance(); // Consume \r
            advance(); // Consume \n
        }
        else if (current_char_ == '\n' || current_char_ == '\r')
        {
            advance(); // Consume single newline/carriage return
        }
    }
}

void Lexer::skipMultiLineComment()
{
    if (current_char_ == '/' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '*')
    {
        advance(); // Consume /
        advance(); // Consume *

        while (current_char_ != '\0')
        {
            if (current_char_ == '*' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '/')
            {
                advance(); // Consume *
                advance(); // Consume /
                break;
            }
            advance();
        }
    }
}

std::string Lexer::getIdentifier()
{
    std::string result = "";
    while (current_char_ != '\0' && (std::isalnum(current_char_) || current_char_ == '_'))
    {
        result += current_char_;
        advance();
    }
    return result;
}

std::string Lexer::getNumber()
{
    std::string result = "";
    bool has_decimal = false;
    bool has_exponent = false;

    while (current_char_ != '\0' && (std::isdigit(current_char_) || current_char_ == '.' ||
                                     current_char_ == 'e' || current_char_ == 'E' || current_char_ == '+' || current_char_ == '-'))
    {
        if (current_char_ == '.')
        {
            if (has_decimal || has_exponent)
                break; // Cannot have more than one decimal point or decimal after exponent
            has_decimal = true;
        }
        else if (current_char_ == 'e' || current_char_ == 'E')
        {
            if (has_exponent)
                break; // Cannot have more than one exponent
            has_exponent = true;
        }
        else if ((current_char_ == '+' || current_char_ == '-') && !has_exponent)
        {
            // Allow leading + or - for numbers
            if (result.empty())
            {
                // This is a leading sign
            }
            else
            {
                break; // Not a valid number
            }
        }

        result += current_char_;
        advance();
    }
    return result;
}

std::string Lexer::getStringLiteral()
{
    std::string result = "\"";
    advance(); // Consume opening quote

    while (current_char_ != '\0' && current_char_ != '"')
    {
        if (current_char_ == '\\' && current_pos_ + 1 < source_.length())
        {
            // Handle escape sequences
            result += current_char_;
            advance();
            result += current_char_;
            advance();
        }
        else
        {
            result += current_char_;
            advance();
        }
    }

    if (current_char_ == '"')
    {
        result += current_char_;
        advance(); // Consume closing quote
    }

    return result;
}

std::string Lexer::getCharLiteral()
{
    std::string result = "'";
    advance(); // Consume opening quote

    while (current_char_ != '\0' && current_char_ != '\'')
    {
        if (current_char_ == '\\' && current_pos_ + 1 < source_.length())
        {
            // Handle escape sequences
            result += current_char_;
            advance();
            result += current_char_;
            advance();
        }
        else
        {
            result += current_char_;
            advance();
        }
    }

    if (current_char_ == '\'')
    {
        result += current_char_;
        advance(); // Consume closing quote
    }

    return result;
}

std::string Lexer::getPreprocessorDirective()
{
    std::string result = "#";
    advance(); // Consume #

    // Skip whitespace after #
    while (current_char_ != '\0' && std::isspace(current_char_))
    {
        advance();
    }

    // Get the directive name
    while (current_char_ != '\0' && (std::isalnum(current_char_) || current_char_ == '_'))
    {
        result += current_char_;
        advance();
    }

    // Get the rest of the line
    while (current_char_ != '\0' && current_char_ != '\n' && current_char_ != '\r')
    {
        result += current_char_;
        advance();
    }

    return result;
}

std::string Lexer::getMultiCharOperator()
{
    std::string result = "";

    // Try to match the longest possible operator
    for (const auto &op : multi_char_operators)
    {
        if (current_pos_ + op.length() <= source_.length())
        {
            std::string candidate = source_.substr(current_pos_, op.length());
            if (candidate == op)
            {
                result = candidate;
                for (size_t i = 0; i < op.length(); ++i)
                {
                    advance();
                }
                break;
            }
        }
    }

    return result;
}

// Keyword recognition methods
bool Lexer::isCKeyword(const std::string &identifier)
{
    return c_keywords.find(identifier) != c_keywords.end();
}

bool Lexer::isSTLContainer(const std::string &identifier)
{
    return stl_containers.find(identifier) != stl_containers.end();
}

bool Lexer::isSTLAlgorithm(const std::string &identifier)
{
    return stl_algorithms.find(identifier) != stl_algorithms.end();
}

bool Lexer::isSTLIterator(const std::string &identifier)
{
    return stl_iterators.find(identifier) != stl_iterators.end();
}

bool Lexer::isSTLUtility(const std::string &identifier)
{
    return stl_utilities.find(identifier) != stl_utilities.end();
}

bool Lexer::isSTLIO(const std::string &identifier)
{
    return stl_io_operations.find(identifier) != stl_io_operations.end();
}

bool Lexer::isSTLMemory(const std::string &identifier)
{
    return stl_memory_management.find(identifier) != stl_memory_management.end();
}

bool Lexer::isSTLString(const std::string &identifier)
{
    return stl_string_operations.find(identifier) != stl_string_operations.end();
}

bool Lexer::isMultiCharOperator(const std::string &op)
{
    return multi_char_operators.find(op) != multi_char_operators.end();
}

std::vector<std::string> Lexer::tokenize()
{
    std::vector<std::string> tokens;
    bool last_token_was_operator = true; // To allow negative numbers at start or after operator

    while (current_char_ != '\0')
    {
        if (std::isspace(current_char_))
        {
            skipWhitespace();
            continue;
        }

        // Handle comments
        if (current_char_ == '#' || (current_char_ == '/' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '/'))
        {
            skipComment();
            continue;
        }

        // Handle multi-line comments
        if (current_char_ == '/' && current_pos_ + 1 < source_.length() && source_[current_pos_ + 1] == '*')
        {
            skipMultiLineComment();
            continue;
        }

        // Handle preprocessor directives (skip them entirely)
        if (current_char_ == '#')
        {
            skipComment();
            continue;
        }

        // Handle string literals
        if (current_char_ == '"')
        {
            tokens.push_back("STRING_LITERAL:" + getStringLiteral());
            last_token_was_operator = false;
            continue;
        }

        // Handle character literals
        if (current_char_ == '\'')
        {
            tokens.push_back("CHAR_LITERAL:" + getCharLiteral());
            last_token_was_operator = false;
            continue;
        }

        // Handle numbers (including negative and scientific notation)
        if (std::isdigit(current_char_) || (current_char_ == '-' && last_token_was_operator) || current_char_ == '.')
        {
            // Check if it's just a dot (operator) or start of a number
            if (current_char_ == '.' && (current_pos_ + 1 >= source_.length() || !std::isdigit(source_[current_pos_ + 1])))
            {
                // It's just a dot, treat as an operator/punctuation
            }
            else
            {
                tokens.push_back("NUMBER:" + getNumber());
                last_token_was_operator = false;
                continue;
            }
        }

        // Handle identifiers and keywords
        if (std::isalpha(current_char_) || current_char_ == '_')
        {
            std::string identifier = getIdentifier();

            // Tag the identifier based on its type
            if (isCKeyword(identifier))
            {
                tokens.push_back("KEYWORD:" + identifier);
            }
            else if (isSTLContainer(identifier))
            {
                tokens.push_back("STL_CONTAINER:" + identifier);
            }
            else if (isSTLAlgorithm(identifier))
            {
                tokens.push_back("STL_ALGORITHM:" + identifier);
            }
            else if (isSTLIterator(identifier))
            {
                tokens.push_back("STL_ITERATOR:" + identifier);
            }
            else if (isSTLUtility(identifier))
            {
                tokens.push_back("STL_UTILITY:" + identifier);
            }
            else if (isSTLIO(identifier))
            {
                tokens.push_back("STL_IO:" + identifier);
            }
            else if (isSTLMemory(identifier))
            {
                tokens.push_back("STL_MEMORY:" + identifier);
            }
            else if (isSTLString(identifier))
            {
                tokens.push_back("STL_STRING:" + identifier);
            }
            else
            {
                tokens.push_back("IDENTIFIER:" + identifier);
            }
            last_token_was_operator = false;
            continue;
        }

        // Handle multi-character operators
        std::string multi_op = getMultiCharOperator();
        if (!multi_op.empty())
        {
            tokens.push_back("OPERATOR:" + multi_op);
            last_token_was_operator = true;
            continue;
        }

        // Handle single character operators and punctuators
        if (current_char_ == '(' || current_char_ == ')' ||
            current_char_ == '[' || current_char_ == ']' ||
            current_char_ == '{' || current_char_ == '}' ||
            current_char_ == '+' || current_char_ == '-' ||
            current_char_ == '*' || current_char_ == '/' ||
            current_char_ == '%' || current_char_ == '^' ||
            current_char_ == '&' || current_char_ == '|' ||
            current_char_ == '~' || current_char_ == '!' ||
            current_char_ == '<' || current_char_ == '>' ||
            current_char_ == '=' || current_char_ == ',' ||
            current_char_ == ';' || current_char_ == ':' ||
            current_char_ == '?' || current_char_ == '.' ||
            current_char_ == '#' || current_char_ == '@' ||
            current_char_ == '$' || current_char_ == '`' ||
            current_char_ == '\\')
        {
            tokens.push_back("PUNCTUATOR:" + std::string(1, current_char_));
            last_token_was_operator = true;
            advance();
            continue;
        }

        // If we reach here, it's an unknown character
        throw std::runtime_error(std::string("Unknown character: ") + current_char_ + " at position " + std::to_string(current_pos_));
    }

    return tokens;
}