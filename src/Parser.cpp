#include "Parser.h"
#include <cctype>
#include <stdexcept>

// Token definitions used by the lexer and parser.
// Negative values are used for tokens that don't have a direct char representation.
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

// Consumes the current token and returns the next token from the input stream.
int Parser::getNextToken() {
    if (CurrentPos >= Tokens.size())
        return tok_eof;

    std::string token = Tokens[CurrentPos++];
    
    if (token == "def")
        return tok_def;
    if (token == "extern")
        return tok_extern;
    // Check for number before identifier because an identifier can start with a letter
    // but a number can also contain a decimal point which is not a digit.
    if (isdigit(token[0]) || token[0] == '.')
        return tok_number;
    if (isalpha(token[0]))
        return tok_identifier;
    
    // Otherwise, it must be an operator or parenthesis, return its ASCII value.
    return token[0]; // Return the character as its ASCII value
}

// Parses a numeric literal expression.
// numberexpr ::= number
std::unique_ptr<ExprAST> Parser::ParseNumberExpr() {
    double Val = std::stod(Tokens[CurrentPos - 1]);
    auto Result = std::make_unique<NumberExprAST>(Val);
    getNextToken(); // consume the number
    return std::move(Result);
}

// Parses a parenthesized expression.
// parenexpr ::= '(' expression ')'
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

// Parses an identifier expression, which can be a variable reference or a function call.
// identifierexpr
//   ::= identifier
//   ::= identifier '(' expression* ')'
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

// Parses primary expressions, which are the basic building blocks of other expressions.
// primary
//   ::= identifierexpr
//   ::= numberexpr
//   ::= parenexpr
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

// Get the precedence of the pending binary operator token.
// This helps in parsing expressions with correct operator precedence.
int Parser::GetTokPrecedence() {
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

// Parses the right-hand side of a binary operator expression.
// binoprhs ::= (operator primary)*
// This function is called when we have already parsed the LHS of a binary expression
// and need to parse the operator and the RHS.
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

// Parses a full expression.
// expression ::= primary binoprhs
std::unique_ptr<ExprAST> Parser::ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

// Parses a function prototype.
// prototype ::= id '(' id* ')'
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

// Parses a function definition.
// definition ::= 'def' prototype expression
std::unique_ptr<FunctionAST> Parser::ParseDefinition() {
    getNextToken(); // eat def
    auto Proto = ParsePrototype();
    if (!Proto)
        return nullptr;

    if (auto E = ParseExpression())
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    return nullptr;
}

// Parses an external function declaration.
// extern ::= 'extern' prototype
std::unique_ptr<PrototypeAST> Parser::ParseExtern() {
    getNextToken(); // eat extern
    return ParsePrototype();
}

// Parses a top-level expression, which is treated as an anonymous function.
// toplevelexpr ::= expression
std::unique_ptr<FunctionAST> Parser::ParseTopLevelExpr() {
    if (auto E = ParseExpression()) {
        auto Proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

// Main parsing loop. Dispatches to other parsing functions based on the current token.
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