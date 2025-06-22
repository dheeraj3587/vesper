#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "AST.h"

// Helper to get current token from parser if possible, or from token list
// This is a bit of a hack; ideally, the parser would expose its current token or position.
std::string getCurrentTokenString(const Parser &p, const std::vector<std::string> &tokens, size_t &currentTokenIndex)
{
    // This is a placeholder as Parser doesn't expose its CurrentPos or CurrentToken directly as a string easily.
    // For a robust solution, Parser would need a method like `isAtEnd()` or `peekCurrentTokenStr()`.
    // We'll advance an independent index for the main loop.
    if (currentTokenIndex < tokens.size())
    {
        return tokens[currentTokenIndex];
    }
    return ""; // Represents EOF or out of bounds
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: vesper <file.vsp>\n";
        return 1;
    }

    // Read the input file
    std::ifstream infile(argv[1]);
    if (!infile)
    {
        std::cerr << "Error: Could not open file '" << argv[1] << "'\n";
        return 1;
    }

    // Read the entire file content
    std::string code((std::istreambuf_iterator<char>(infile)),
                     std::istreambuf_iterator<char>());
    infile.close();

    std::cout << "Source Code:\n"
              << code << std::endl
              << std::endl;

    // 1. Lexing
    Lexer lexer(code);
    std::vector<std::string> tokens;
    try
    {
        tokens = lexer.tokenize();
        std::cout << "Tokens:" << std::endl;
        for (const auto &token : tokens)
        {
            std::cout << "'" << token << "' ";
        }
        std::cout << std::endl
                  << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Lexer Error: " << e.what() << std::endl;
        return 1;
    }

    if (tokens.empty())
    {
        std::cout << "No tokens to parse." << std::endl;
        return 0;
    }

    // 2. Parsing
    Parser parser(tokens);
    std::cout << "Attempting to parse..." << std::endl;

    while (true)
    {
        std::unique_ptr<ExprAST> ast;
        try
        {
            ast = parser.Parse();
            if (ast)
            {
                std::cout << "Parsed a top-level construct successfully." << std::endl;
                ast->print();
                std::cout << std::endl;
            }
            else
            {
                std::cout << "Parsing completed." << std::endl;
                break;
            }
        }
        catch (const std::runtime_error &e)
        {
            std::string errMsg = e.what();
            if (errMsg.find("unknown token when expecting an expression") != std::string::npos ||
                errMsg.find("Expected function name in prototype") != std::string::npos)
            {
                std::cout << "Finished parsing." << std::endl;
                break;
            }
            std::cerr << "Parser Error: " << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}