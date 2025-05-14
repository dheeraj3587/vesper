#include "Parser.h"
#include <cctype>
#include <stdexcept>

// Token definitions
enum Token {
    tok_eof = -1,
    tok_def = -2,
    tok_extern = -3,
    tok_identifier = -4,
    tok_number = -5
};

Parser::Parser(const std::vector<std::string>& tokens) 
    : Tokens(tokens), CurrentPos(0) {
    CurrentToken = getNextToken();
}

int Parser::getNextToken() {
    if (CurrentPos >= Tokens.size())
        return tok_eof;

    std::string token = Tokens[CurrentPos++];
    
    if (token == "def")
        return tok_def;
    if (token == "extern")
        return tok_extern;
    if (isdigit(token[0]) || token[0] == '.')
        return tok_number;
    if (isalpha(token[0]))
        return tok_identifier;
    
    return token[0]; // Return the character as its ASCII value
}

std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
    double Val = std::stod(Tokens[CurrentPos - 1]);
    auto Result = std::make_unique<NumberExprAST>(Val);
    getNextToken(); // consume the number
    return std::move(Result);
}

std::unique_ptr<ExprAST> Parser::ParseParenExpr() {
    getNextToken(); // eat (
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (CurrentToken != ')')
        throw std::runtime_error("expected ')'");
    getNextToken(); // eat )
    return V;
}

std::unique_ptr<ExprAST> Parser::ParseIdentifierExpr() {
    std::string IdName = Tokens[CurrentPos - 1];
    getNextToken(); // eat identifier

    if (CurrentToken != '(') // Simple variable ref
        return std::make_unique<VariableExprAST>(IdName);

    // Call
    getNextToken(); // eat (
    std::vector<std::unique_ptr<ExprAST>> Args;
    if (CurrentToken != ')') {
        while (true) {
            if (auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else
                return nullptr;

            if (CurrentToken == ')')
                break;

            if (CurrentToken != ',')
                throw std::runtime_error("Expected ')' or ',' in argument list");
            getNextToken();
        }
    }

    getNextToken(); // eat )

    return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

std::unique_ptr<ExprAST> Parser::ParsePrimary() {
    switch (CurrentToken) {
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case '(':
        return ParseParenExpr();
    default:
        throw std::runtime_error("unknown token when expecting an expression");
    }
}

// Get the precedence of the pending binary operator token
int GetTokPrecedence() {
    switch (CurrentToken) {
    case '<':
    case '>':
        return 10;
    case '+':
    case '-':
        return 20;
    case '*':
    case '/':
        return 40;
    default:
        return -1;
    }
}

std::unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    while (true) {
        int TokPrec = GetTokPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        int BinOp = CurrentToken;
        getNextToken(); // eat binop

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

std::unique_ptr<ExprAST> Parser::ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<PrototypeAST> Parser::ParsePrototype() {
    if (CurrentToken != tok_identifier)
        throw std::runtime_error("Expected function name in prototype");

    std::string FnName = Tokens[CurrentPos - 1];
    getNextToken();

    if (CurrentToken != '(')
        throw std::runtime_error("Expected '(' in prototype");

    std::vector<std::string> ArgNames;
    while (getNextToken() == tok_identifier)
        ArgNames.push_back(Tokens[CurrentPos - 1]);

    if (CurrentToken != ')')
        throw std::runtime_error("Expected ')' in prototype");

    getNextToken(); // eat ')'

    return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

std::unique_ptr<FunctionAST> Parser::ParseDefinition() {
    getNextToken(); // eat def
    auto Proto = ParsePrototype();
    if (!Proto)
        return nullptr;

    if (auto E = ParseExpression())
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    return nullptr;
}

std::unique_ptr<PrototypeAST> Parser::ParseExtern() {
    getNextToken(); // eat extern
    return ParsePrototype();
}

std::unique_ptr<FunctionAST> Parser::ParseTopLevelExpr() {
    if (auto E = ParseExpression()) {
        auto Proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

std::unique_ptr<ExprAST> Parser::Parse() {
    switch (CurrentToken) {
    case tok_def:
        return ParseDefinition();
    case tok_extern:
        return ParseExtern();
    default:
        return ParseTopLevelExpr();
    }
} 