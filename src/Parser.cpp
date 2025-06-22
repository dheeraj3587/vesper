#include "Parser.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <map>
#include <stdexcept>

using namespace std;

// Map of operator precedence
static map<char, int> BinopPrecedence;

// Constructor
Parser::Parser(const vector<string> &tokens) : Tokens(tokens), CurrentPos(0)
{
    // Initialize operator precedence
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;
    BinopPrecedence['/'] = 40;
    getNextToken(); // Initialize CurrentToken
}

// Get the precedence of the pending binary operator token.
int Parser::GetTokPrecedence()
{
    if (!isascii(CurrentToken))
        return -1;

    // Make sure it's a declared binop.
    int TokPrec = BinopPrecedence[CurrentToken];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}

// Helper function to advance the token stream
int Parser::getNextToken()
{
    if (CurrentPos >= Tokens.size())
    {
        this->CurrentToken = tok_eof;
        return this->CurrentToken;
    }

    string token_str = Tokens[CurrentPos++];
    int determined_tok_type;

    if (token_str == "def")
        determined_tok_type = tok_def;
    else if (token_str == "extern")
        determined_tok_type = tok_extern;
    else if (token_str == "if")
        determined_tok_type = tok_if;
    else if (token_str == "then")
        determined_tok_type = tok_then;
    else if (token_str == "else")
        determined_tok_type = tok_else;
    else if (token_str == "for")
        determined_tok_type = tok_for;
    else if (token_str == "in")
        determined_tok_type = tok_in;
    else if (token_str == "binary")
        determined_tok_type = tok_binary;
    else if (token_str == "unary")
        determined_tok_type = tok_unary;
    else if (token_str == "var")
        determined_tok_type = tok_var;
    else if (token_str == ";")
        determined_tok_type = ';';
    else if (token_str == "(")
        determined_tok_type = '(';
    else if (token_str == ")")
        determined_tok_type = ')';
    else if (token_str == ",")
        determined_tok_type = ',';
    else if (token_str == "+")
        determined_tok_type = '+';
    else if (token_str == "-")
        determined_tok_type = '-';
    else if (token_str == "*")
        determined_tok_type = '*';
    else if (token_str == "/")
        determined_tok_type = '/';
    else if (token_str == "<")
        determined_tok_type = '<';
    else if (token_str == ">")
        determined_tok_type = '>';
    else if (token_str == "=")
        determined_tok_type = '=';
    else if (isdigit(token_str[0]) || token_str[0] == '.')
    {
        NumVal = strtod(token_str.c_str(), nullptr); // Sets NumVal
        IdentifierStr = "";                          // Clear IdentifierStr
        determined_tok_type = tok_number;
    }
    else if (isalpha(token_str[0]))
    {
        IdentifierStr = token_str; // Sets IdentifierStr
        determined_tok_type = tok_identifier;
    }
    else
    {
        std::cerr << "Parser::getNextToken: Unknown token string '" << token_str << "'" << std::endl;
        determined_tok_type = tok_eof; // Treat unknown as EOF or an error token
    }

    this->CurrentToken = determined_tok_type;
    return this->CurrentToken;
}

// Parse a number expression
unique_ptr<ExprAST> Parser::ParseNumberExpr()
{
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
}

// Parse a parenthesized expression
unique_ptr<ExprAST> Parser::ParseParenExpr()
{
    getNextToken(); // eat (.
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (CurrentToken != ')')
        return nullptr;
    getNextToken(); // eat ).
    return V;
}

// Parse an identifier expression
unique_ptr<ExprAST> Parser::ParseIdentifierExpr()
{
    string IdName = IdentifierStr;

    getNextToken(); // eat identifier.

    if (CurrentToken != '(') // Simple variable ref.
        return make_unique<VariableExprAST>(IdName);

    // Call.
    getNextToken(); // eat (
    vector<unique_ptr<ExprAST>> Args;
    if (CurrentToken != ')')
    {
        while (true)
        {
            if (auto Arg = ParseExpression())
                Args.push_back(std::move(Arg));
            else
                return nullptr;

            if (CurrentToken == ')')
                break;

            if (CurrentToken != ',')
                return nullptr;
            getNextToken();
        }
    }

    // Eat the ')'.
    getNextToken();

    return make_unique<CallExprAST>(IdName, std::move(Args));
}

// Parse a primary expression
unique_ptr<ExprAST> Parser::ParsePrimary()
{
    switch (CurrentToken)
    {
    default:
        return nullptr;
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case '(':
        return ParseParenExpr();
    }
}

// Parse a binary operator expression
unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS)
{
    while (true)
    {
        int TokPrec = GetTokPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        int BinOp = CurrentToken;
        getNextToken(); // eat binop

        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec)
        {
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

// Parse an expression
unique_ptr<ExprAST> Parser::ParseExpression()
{
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

// Parse a function prototype
unique_ptr<PrototypeAST> Parser::ParsePrototype()
{
    std::cerr << "ParsePrototype: CurrentToken = " << CurrentToken << std::endl;
    string FnName;

    unsigned Kind = 0; // 0 = identifier, 1 = unary, 2 = binary.
    unsigned BinaryPrecedence = 30;

    switch (CurrentToken)
    {
    default:
        std::cerr << "ParsePrototype: Unexpected token." << std::endl;
        return nullptr;
    case tok_identifier:
        FnName = IdentifierStr;
        Kind = 0;
        getNextToken();
        break;
    case tok_unary:
        getNextToken();
        if (!isascii(CurrentToken))
        {
            std::cerr << "ParsePrototype: Expected ASCII character after unary." << std::endl;
            return nullptr;
        }
        FnName = "unary";
        FnName += (char)CurrentToken;
        Kind = 1;
        getNextToken();
        break;
    case tok_binary:
        getNextToken();
        if (!isascii(CurrentToken))
        {
            std::cerr << "ParsePrototype: Expected ASCII character after binary." << std::endl;
            return nullptr;
        }
        FnName = "binary";
        FnName += (char)CurrentToken;
        Kind = 2;
        getNextToken();

        if (CurrentToken == tok_number)
        {
            if (NumVal < 1 || NumVal > 100)
            {
                std::cerr << "ParsePrototype: Binary precedence must be 1..100." << std::endl;
                return nullptr;
            }
            BinaryPrecedence = (unsigned)NumVal;
            getNextToken();
        }
        break;
    }

    if (CurrentToken != '(')
    {
        std::cerr << "ParsePrototype: Expected '(' after function name. Got: " << CurrentToken << std::endl;
        return nullptr;
    }
    getNextToken(); // Consume '('. CurrentToken is now the first argument or ')'.

    vector<string> ArgNames;
    if (CurrentToken != ')')
    { // If there are arguments
        if (CurrentToken != tok_identifier)
        {
            std::cerr << "ParsePrototype: Expected identifier in argument list. Got: " << CurrentToken << std::endl;
            return nullptr;
        }
        ArgNames.push_back(IdentifierStr);
        getNextToken(); // Consume argument identifier.

        while (CurrentToken == ',')
        {
            getNextToken(); // Consume ','.
            if (CurrentToken != tok_identifier)
            {
                std::cerr << "ParsePrototype: Expected identifier after ','. Got: " << CurrentToken << std::endl;
                return nullptr;
            }
            ArgNames.push_back(IdentifierStr);
            getNextToken(); // Consume argument identifier.
        }
    }

    if (CurrentToken != ')')
    {
        std::cerr << "ParsePrototype: Expected ')' to end argument list. Got: " << CurrentToken << std::endl;
        return nullptr;
    }
    getNextToken(); // eat ')'.

    if (Kind && ArgNames.size() != Kind)
    {
        std::cerr << "ParsePrototype: Invalid number of operands for operator." << std::endl;
        return nullptr;
    }

    return make_unique<PrototypeAST>(FnName, std::move(ArgNames), Kind != 0,
                                     BinaryPrecedence);
}

// Parse a function definition
unique_ptr<FunctionAST> Parser::ParseDefinition()
{
    // When called, CurrentToken is tok_def.
    // Consume 'def' and advance CurrentToken to the function name.
    getNextToken();
    // std::cerr << "ParseDefinition: After eating def. CurrentToken = " << CurrentToken << " (Identifier: " << IdentifierStr << ")" << std::endl;
    auto Proto = ParsePrototype();
    if (!Proto)
    {
        std::cerr << "ParseDefinition: Failed to parse prototype." << std::endl;
        return nullptr;
    }

    // CurrentToken should be at the start of the body expression now
    if (auto E = ParseExpression())
        return make_unique<FunctionAST>(std::move(Proto), std::move(E));
    std::cerr << "ParseDefinition: Failed to parse function body." << std::endl;
    return nullptr;
}

// Parse an external function declaration
unique_ptr<PrototypeAST> Parser::ParseExtern()
{
    getNextToken(); // eat extern.
    return ParsePrototype();
}

// Parse a top-level expression
unique_ptr<FunctionAST> Parser::ParseTopLevelExpr()
{
    if (auto E = ParseExpression())
    {
        auto Proto = make_unique<PrototypeAST>("__anon_expr",
                                               vector<string>());
        return make_unique<FunctionAST>(std::move(Proto), std::move(E));
    }
    return nullptr;
}

// Main entry point for parsing
unique_ptr<ExprAST> Parser::Parse()
{
    while (true)
    {
        switch (CurrentToken)
        {
        case tok_eof:
            return nullptr;
        case ';': // ignore top-level semicolons.
            getNextToken();
            break;
        case tok_def:
            return ParseDefinition();
        case tok_extern:
            return ParseExtern();
        default:
            return ParseTopLevelExpr();
        }
    }
}
