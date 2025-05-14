#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<std::string> tokenize();

private:
    std::string source_;
    size_t current_pos_;
    char current_char_;

    void advance();
    void skipWhitespace();
    void skipComment();
    std::string getIdentifier();
    std::string getNumber();
};

#endif // LEXER_H 