#include "Lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string &source)
    : source_(source), current_pos_(0), current_char_(source.empty() ? '\0' : source_[0]) {}

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
    while (current_char_ != '\0' && (std::isdigit(current_char_) || current_char_ == '.'))
    {
        if (current_char_ == '.')
        {
            if (has_decimal)
                break; // Cannot have more than one decimal point
            has_decimal = true;
        }
        result += current_char_;
        advance();
    }
    return result;
}

std::vector<std::string> Lexer::tokenize()
{
    std::vector<std::string> tokens;

    while (current_char_ != '\0')
    {
        if (std::isspace(current_char_))
        {
            skipWhitespace();
            continue;
        }

        if (current_char_ == '#')
        {
            skipComment();
            continue;
        }

        if (std::isalpha(current_char_) || current_char_ == '_')
        {
            tokens.push_back(getIdentifier());
            continue;
        }

        if (std::isdigit(current_char_) || current_char_ == '.')
        {
            // Check if it's just a dot (operator) or start of a number
            if (current_char_ == '.' && (current_pos_ + 1 >= source_.length() || !std::isdigit(source_[current_pos_ + 1])))
            {
                // It's just a dot, treat as an operator/punctuation
            }
            else
            {
                tokens.push_back(getNumber());
                continue;
            }
        }

        // Handle operators and parentheses
        // For Kaleidoscope, these are single characters
        if (current_char_ == '(' || current_char_ == ')' ||
            current_char_ == '+' || current_char_ == '-' ||
            current_char_ == '*' || current_char_ == '/' ||
            current_char_ == '<' || current_char_ == '>' ||
            current_char_ == ',' || current_char_ == ';')
        {
            tokens.push_back(std::string(1, current_char_));
            advance();
            continue;
        }

        // If we reach here, it's an unknown character
        throw std::runtime_error(std::string("Unknown character: ") + current_char_ + " at position " + std::to_string(current_pos_));
    }

    return tokens;
}
