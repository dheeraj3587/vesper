#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include "AST.h"

using namespace std;

// Extended Token enum for C++ constructs
enum Token
{
    tok_eof = -1,

    // Keywords
    tok_def = -2,
    tok_extern = -3,
    tok_if = -4,
    tok_else = -5,
    tok_while = -6,
    tok_for = -7,
    tok_return = -8,
    tok_break = -9,
    tok_continue = -10,
    tok_true = -11,
    tok_false = -12,

    // Types
    tok_int = -20,
    tok_float = -21,
    tok_double = -22,
    tok_char = -23,
    tok_bool = -24,
    tok_void = -25,
    tok_string = -26,
    tok_auto = -27,
    tok_const = -28,
    tok_unsigned = -29,
    tok_volatile = -31,

    // Literals and identifiers
    tok_identifier = -35,
    tok_number = -36,
    tok_string_literal = -37,
    tok_char_literal = -38,

    // Operators
    tok_assign = -40,        // =
    tok_plus_assign = -41,   // +=
    tok_minus_assign = -42,  // -=
    tok_mult_assign = -43,   // *=
    tok_div_assign = -44,    // /=
    tok_mod_assign = -45,    // %=
    tok_increment = -46,     // ++
    tok_decrement = -47,     // --
    tok_equal = -48,         // ==
    tok_not_equal = -49,     // !=
    tok_less_equal = -50,    // <=
    tok_greater_equal = -51, // >=
    tok_logical_and = -52,   // &&
    tok_logical_or = -53,    // ||
    tok_logical_not = -54,   // !
    tok_arrow = -55,         // ->
    tok_scope = -56,         // ::
    tok_left_shift = -57,    // <<
    tok_right_shift = -58,   // >>

    // Punctuation
    tok_semicolon = -60,     // ;
    tok_comma = -61,         // ,
    tok_left_paren = -62,    // (
    tok_right_paren = -63,   // )
    tok_left_brace = -64,    // {
    tok_right_brace = -65,   // }
    tok_left_bracket = -66,  // [
    tok_right_bracket = -67, // ]

    // Single character operators (use ASCII values)
    // '+', '-', '*', '/', '%', '<', '>', '&', '|', '^', '~', '?', ':'
};

class Parser
{
private:
    int CurrentToken;
    vector<string> Tokens;
    size_t CurrentPos;

    // Token semantic values
    string IdentifierStr; // Holds the identifier name
    double NumVal;        // Holds the number value
    string StringVal;     // Holds string literal value
    char CharVal;         // Holds character literal value

    // Operator precedence map
    map<string, int> BinOpPrecedence;

    // Helper functions to advance the token stream and parse specific grammar rules
    int getNextToken();
    int GetTokPrecedence();
    DataType parseType();
    string getCurrentTokenString();

    // Expression parsing
    unique_ptr<ExprAST> ParseNumberExpr();
    unique_ptr<ExprAST> ParseStringExpr();
    unique_ptr<ExprAST> ParseCharExpr();
    unique_ptr<ExprAST> ParseBoolExpr();
    unique_ptr<ExprAST> ParseParenExpr();
    unique_ptr<ExprAST> ParseIdentifierExpr();
    unique_ptr<ExprAST> ParseUnaryExpr();
    unique_ptr<ExprAST> ParsePrimary();
    unique_ptr<ExprAST> ParseInitializerList();
    unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS);
    unique_ptr<ExprAST> ParseExpression();
    unique_ptr<ExprAST> ParseAssignmentExpr();
    unique_ptr<ExprAST> ParseArrayAccess(unique_ptr<ExprAST> Array);

    // Statement parsing
    unique_ptr<StmtAST> ParseStatement();
    unique_ptr<StmtAST> ParseExpressionStatement();
    unique_ptr<StmtAST> ParseVarDeclaration();
    unique_ptr<StmtAST> ParseCompoundStatement();
    unique_ptr<StmtAST> ParseIfStatement();
    unique_ptr<StmtAST> ParseWhileStatement();
    unique_ptr<StmtAST> ParseForStatement();
    unique_ptr<StmtAST> ParseReturnStatement();
    unique_ptr<StmtAST> ParseBreakStatement();
    unique_ptr<StmtAST> ParseContinueStatement();
    unique_ptr<StmtAST> ParsePrintStatement();

    // Function parsing
    unique_ptr<PrototypeAST> ParsePrototype();
    unique_ptr<FunctionAST> ParseFunction();
    unique_ptr<PrototypeAST> ParseExtern();
    unique_ptr<PrototypeAST> ParseKaleidoscopePrototype();
    unique_ptr<FunctionAST> ParseKaleidoscopeFunction();

    // Utility functions
    bool isType(int token);
    bool expectToken(int expectedToken);
    void initializePrecedence();
    string stripTag(const string &token);

public:
    Parser(const vector<string> &tokens);

    // Main entry point for parsing a complete program
    unique_ptr<ProgramAST> ParseProgram();

    // Parse single statement/expression (for testing)
    unique_ptr<StmtAST> ParseSingleStatement();
    unique_ptr<ExprAST> ParseSingleExpression();
};

#endif // PARSER_H
