#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <vector>
#include "AST.h"

class Parser {
private:
    int CurrentToken;
    std::vector<std::string> Tokens;
    size_t CurrentPos;

    // Helper functions
    int getNextToken();
    std::unique_ptr<ExprAST> ParseNumberExpr();
    std::unique_ptr<ExprAST> ParseParenExpr();
    std::unique_ptr<ExprAST> ParseIdentifierExpr();
    std::unique_ptr<ExprAST> ParsePrimary();
    std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);
    std::unique_ptr<ExprAST> ParseExpression();
    std::unique_ptr<PrototypeAST> ParsePrototype();
    std::unique_ptr<FunctionAST> ParseDefinition();
    std::unique_ptr<PrototypeAST> ParseExtern();
    std::unique_ptr<FunctionAST> ParseTopLevelExpr();

public:
    Parser(const std::vector<std::string>& tokens);
    std::unique_ptr<ExprAST> Parse();
};

#endif // PARSER_H 