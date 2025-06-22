#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <vector>
#include "AST.h"

using namespace std;

// Token enum
enum Token
{
    tok_eof = -1,
    tok_def = -2,
    tok_extern = -3,
    tok_identifier = -4,
    tok_number = -5,
    tok_if = -6,
    tok_then = -7,
    tok_else = -8,
    tok_for = -9,
    tok_in = -10,
    tok_binary = -11,
    tok_unary = -12,
    tok_var = -13
};

class Parser
{
private:
    int CurrentToken;
    vector<string> Tokens;
    size_t CurrentPos;

    // Token semantic values
    string IdentifierStr; // Holds the identifier name if the current token is tok_identifier
    double NumVal;        // Holds the number value if the current token is tok_number

    // Helper functions to advance the token stream and parse specific grammar rules.
    int getNextToken();
    int GetTokPrecedence();
    unique_ptr<ExprAST> ParseNumberExpr();
    unique_ptr<ExprAST> ParseParenExpr();
    unique_ptr<ExprAST> ParseIdentifierExpr();
    unique_ptr<ExprAST> ParsePrimary();
    unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS);
    unique_ptr<ExprAST> ParseExpression();
    unique_ptr<PrototypeAST> ParsePrototype();
    unique_ptr<FunctionAST> ParseDefinition();
    unique_ptr<PrototypeAST> ParseExtern();
    unique_ptr<FunctionAST> ParseTopLevelExpr();

public:
    Parser(const vector<string> &tokens);
    // Main entry point for parsing.
    unique_ptr<ExprAST> Parse();
};

#endif // PARSER_H
