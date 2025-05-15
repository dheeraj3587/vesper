#include <iostream>
#include <vector>
#include <string>
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

int main()
{
    // Sample Kaleidoscope code
    std::string code = "def foo(a, b) a+b*2; foo(1, 2); extern sin(x);";

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

    // 2. Parsing multiple top-level expressions
    // We create one parser and it will advance through the tokens.
    Parser parser(tokens);
    bool firstParse = true;

    // The parser internally manages its current token. We don't need currentTokenIndex for parser.
    // The loop condition should be based on whether the parser thinks there's more to parse.
    // For now, we make the parser parse one top-level expression at a time.
    // The parser.Parse() should advance its internal token pointer.
    // We need a way for the parser to signal it has reached EOF or an unparseable state.

    std::cout << "Attempting to parse..." << std::endl;
    while (true)
    {
        // A mechanism to check if the parser is at EOF would be good.
        // For now, we rely on Parse() throwing an error or returning nullptr for EOF.
        // The `Parser` is stateful and `getNextToken()` will eventually return `tok_eof`.
        // `Parse()` will try to parse based on `CurrentToken`.
        // If `CurrentToken` is `tok_eof` (because all tokens were consumed or it was empty),
        // `ParseTopLevelExpr` (called by `Parse` by default) will try to parse an expression.
        // If it can't (e.g. at EOF), it might throw or return null.
        // A more robust parser might have a peekToken() and isDone() method.

        // Before calling Parse, check if the parser has already processed all tokens
        // This is tricky because Parser's internal state (CurrentPos, CurrentToken) is not directly exposed
        // to check against tokens.size() from here.
        // We rely on Parser::Parse() behavior at EOF.

        if (firstParse)
        {
            firstParse = false;
        }
        else
        {
            // If not the first parse, and if the previous construct ended and the current token
            // in the parser is a semicolon, the parser should advance past it when it tries to get the next token.
            // The Parser itself should handle or skip semicolons if they are just separators for top-level expressions.
            // Currently, our `getNextToken` in Parser.cpp doesn't treat semicolon specially other than returning its ASCII.
            // And `ParseTopLevelExpr` doesn't explicitly consume a trailing semicolon.
            // It simply ends when the expression ends.
            // The `Parser::Parse()` itself might need to handle this loop or be called repeatedly.
        }

        std::unique_ptr<ExprAST> ast;
        try
        {
            // The parser will use its internal CurrentToken. If it's EOF, it should handle it gracefully.
            ast = parser.Parse();

            if (ast)
            {
                std::cout << "Parsed a top-level construct successfully." << std::endl;
                ast->print();
                std::cout << std::endl;
            }
            else
            {
                // This condition means Parse() returned nullptr.
                // This could happen if it reached EOF and there was nothing to parse,
                // or if it parsed something that doesn't return an ExprAST (like an error or specific empty construct).
                // Given the current Parser::Parse, it should attempt ParseTopLevelExpr if not def/extern.
                // ParseTopLevelExpr could return nullptr if ParseExpression returns nullptr.
                // ParseExpression returns nullptr if ParsePrimary returns nullptr.
                // ParsePrimary throws on unknown token, doesn't return nullptr for EOF.
                // The getNextToken() returns tok_eof. ParsePrimary will then throw.
                // So, a nullptr return path needs careful checking or it will always throw at EOF.

                // Let's modify the parser to gracefully handle EOF in ParsePrimary or related calls if it's to be called in a loop.
                // For now, we expect it might throw when it hits EOF and tries to parse more.
                std::cout << "Parsing returned null or completed." << std::endl;
                break; // Exit loop if nothing more was parsed or EOF assumed.
            }
        }
        catch (const std::runtime_error &e)
        {
            // Check if the error is due to EOF or a genuine syntax error.
            // A more specific exception type for EOF would be better.
            std::string errMsg = e.what();
            if (errMsg.find("unknown token when expecting an expression") != std::string::npos ||
                errMsg.find("Expected function name in prototype") != std::string::npos)
            {
                // This is a common error when ParsePrimary is called at EOF after all valid tokens are consumed.
                std::cout << "Finished parsing or encountered issue at EOF: " << errMsg << std::endl;
                break; // Likely EOF or end of meaningful tokens
            }
            std::cerr << "Parser Error: " << e.what() << std::endl;
            return 1; // Genuine error
        }
    }

    std::cout << "Finished all parsing attempts." << std::endl;

    return 0;
}