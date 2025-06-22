#include "Parser.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <map>

using namespace std;

// Map of operator precedence
static map<string, int> BinOpPrecedence;

// Constructor
Parser::Parser(const vector<string> &tokens) : Tokens(tokens), CurrentPos(0)
{
    initializePrecedence();
    getNextToken(); // Initialize CurrentToken
}

void Parser::initializePrecedence()
{
    // Initialize operator precedence (higher number = higher precedence)
    BinOpPrecedence["||"] = 5;
    BinOpPrecedence["&&"] = 10;
    BinOpPrecedence["=="] = 20;
    BinOpPrecedence["!="] = 20;
    BinOpPrecedence["<"] = 30;
    BinOpPrecedence["<="] = 30;
    BinOpPrecedence[">"] = 30;
    BinOpPrecedence[">="] = 30;
    BinOpPrecedence["+"] = 40;
    BinOpPrecedence["-"] = 40;
    BinOpPrecedence["*"] = 50;
    BinOpPrecedence["/"] = 50;
    BinOpPrecedence["%"] = 50;
}

// Get the precedence of the pending binary operator token
int Parser::GetTokPrecedence()
{
    string op = getCurrentTokenString();
    auto it = BinOpPrecedence.find(op);
    if (it != BinOpPrecedence.end())
        return it->second;
    return -1; // Not a binary operator
}

string Parser::getCurrentTokenString()
{
    if (CurrentPos > 0 && CurrentPos <= Tokens.size())
        return stripTag(Tokens[CurrentPos - 1]);
    return "";
}

// Helper function to strip tags from tokens
string Parser::stripTag(const string &token)
{
    size_t colon_pos = token.find(':');
    if (colon_pos != string::npos)
    {
        return token.substr(colon_pos + 1);
    }
    return token;
}

// Helper function to advance the token stream
int Parser::getNextToken()
{
    if (CurrentPos >= Tokens.size())
    {
        CurrentToken = tok_eof;
        return CurrentToken;
    }

    string token_str = Tokens[CurrentPos++];
    string stripped_token = stripTag(token_str);

    // Keywords
    if (stripped_token == "def")
        CurrentToken = tok_def;
    else if (stripped_token == "extern")
        CurrentToken = tok_extern;
    else if (stripped_token == "if")
        CurrentToken = tok_if;
    else if (stripped_token == "else")
        CurrentToken = tok_else;
    else if (stripped_token == "while")
        CurrentToken = tok_while;
    else if (stripped_token == "for")
        CurrentToken = tok_for;
    else if (stripped_token == "return")
        CurrentToken = tok_return;
    else if (stripped_token == "break")
        CurrentToken = tok_break;
    else if (stripped_token == "continue")
        CurrentToken = tok_continue;
    else if (stripped_token == "true")
        CurrentToken = tok_true;
    else if (stripped_token == "false")
        CurrentToken = tok_false;

    // Types
    else if (stripped_token == "int")
        CurrentToken = tok_int;
    else if (stripped_token == "float")
        CurrentToken = tok_float;
    else if (stripped_token == "double")
        CurrentToken = tok_double;
    else if (stripped_token == "char")
        CurrentToken = tok_char;
    else if (stripped_token == "bool")
        CurrentToken = tok_bool;
    else if (stripped_token == "void")
        CurrentToken = tok_void;
    else if (stripped_token == "string")
        CurrentToken = tok_string;
    else if (stripped_token == "auto")
        CurrentToken = tok_auto;

    // Operators
    else if (stripped_token == "=")
        CurrentToken = tok_assign;
    else if (stripped_token == "+=")
        CurrentToken = tok_plus_assign;
    else if (stripped_token == "-=")
        CurrentToken = tok_minus_assign;
    else if (stripped_token == "*=")
        CurrentToken = tok_mult_assign;
    else if (stripped_token == "/=")
        CurrentToken = tok_div_assign;
    else if (stripped_token == "%=")
        CurrentToken = tok_mod_assign;
    else if (stripped_token == "++")
        CurrentToken = tok_increment;
    else if (stripped_token == "--")
        CurrentToken = tok_decrement;
    else if (stripped_token == "==")
        CurrentToken = tok_equal;
    else if (stripped_token == "!=")
        CurrentToken = tok_not_equal;
    else if (stripped_token == "<=")
        CurrentToken = tok_less_equal;
    else if (stripped_token == ">=")
        CurrentToken = tok_greater_equal;
    else if (stripped_token == "&&")
        CurrentToken = tok_logical_and;
    else if (stripped_token == "||")
        CurrentToken = tok_logical_or;
    else if (stripped_token == "!")
        CurrentToken = tok_logical_not;
    else if (stripped_token == "->")
        CurrentToken = tok_arrow;
    else if (stripped_token == "::")
        CurrentToken = tok_scope;

    // Punctuation
    else if (stripped_token == ";")
        CurrentToken = tok_semicolon;
    else if (stripped_token == ",")
        CurrentToken = tok_comma;
    else if (stripped_token == "(")
        CurrentToken = tok_left_paren;
    else if (stripped_token == ")")
        CurrentToken = tok_right_paren;
    else if (stripped_token == "{")
        CurrentToken = tok_left_brace;
    else if (stripped_token == "}")
        CurrentToken = tok_right_brace;
    else if (stripped_token == "[")
        CurrentToken = tok_left_bracket;
    else if (stripped_token == "]")
        CurrentToken = tok_right_bracket;

    // Single character operators
    else if (stripped_token == "+")
        CurrentToken = '+';
    else if (stripped_token == "-")
        CurrentToken = '-';
    else if (stripped_token == "*")
        CurrentToken = '*';
    else if (stripped_token == "/")
        CurrentToken = '/';
    else if (stripped_token == "%")
        CurrentToken = '%';
    else if (stripped_token == "<")
        CurrentToken = '<';
    else if (stripped_token == ">")
        CurrentToken = '>';
    else if (stripped_token == "&")
        CurrentToken = '&';
    else if (stripped_token == "|")
        CurrentToken = '|';
    else if (stripped_token == "^")
        CurrentToken = '^';
    else if (stripped_token == "~")
        CurrentToken = '~';
    else if (stripped_token == "?")
        CurrentToken = '?';
    else if (stripped_token == ":")
        CurrentToken = ':';

    // Literals
    else if (token_str.find("STRING_LITERAL:") == 0)
    {
        StringVal = stripped_token;
        CurrentToken = tok_string_literal;
    }
    else if (token_str.find("CHAR_LITERAL:") == 0)
    {
        CharVal = stripped_token[0];
        CurrentToken = tok_char_literal;
    }
    else if (isdigit(stripped_token[0]) || (stripped_token[0] == '.' && stripped_token.length() > 1))
    {
        NumVal = strtod(stripped_token.c_str(), nullptr);
        CurrentToken = tok_number;
    }
    else if (isalpha(stripped_token[0]) || stripped_token[0] == '_')
    {
        IdentifierStr = stripped_token;
        CurrentToken = tok_identifier;
    }
    else
    {
        cerr << "Parser::getNextToken: Unknown token '" << stripped_token << "'" << endl;
        CurrentToken = tok_eof;
    }

    return CurrentToken;
}

DataType Parser::parseType()
{
    switch (CurrentToken)
    {
    case tok_void:
        return DataType::VOID;
    case tok_int:
        return DataType::INT;
    case tok_float:
        return DataType::FLOAT;
    case tok_double:
        return DataType::DOUBLE;
    case tok_char:
        return DataType::CHAR;
    case tok_bool:
        return DataType::BOOL;
    case tok_string:
        return DataType::STRING;
    case tok_auto:
        return DataType::AUTO;
    default:
        return DataType::UNKNOWN;
    }
}

bool Parser::isType(int token)
{
    return token == tok_void || token == tok_int || token == tok_float ||
           token == tok_double || token == tok_char || token == tok_bool ||
           token == tok_string || token == tok_auto;
}

bool Parser::expectToken(int expectedToken)
{
    if (CurrentToken != expectedToken)
    {
        cerr << "Expected token " << expectedToken << " but got " << CurrentToken << endl;
        return false;
    }
    getNextToken();
    return true;
}

// Parse a number expression
unique_ptr<ExprAST> Parser::ParseNumberExpr()
{
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return move(Result);
}

// Parse a string expression
unique_ptr<ExprAST> Parser::ParseStringExpr()
{
    auto Result = make_unique<StringExprAST>(StringVal);
    getNextToken(); // consume the string
    return move(Result);
}

// Parse a character expression
unique_ptr<ExprAST> Parser::ParseCharExpr()
{
    auto Result = make_unique<CharExprAST>(CharVal);
    getNextToken(); // consume the character
    return move(Result);
}

// Parse a boolean expression
unique_ptr<ExprAST> Parser::ParseBoolExpr()
{
    bool val = (CurrentToken == tok_true);
    auto Result = make_unique<BoolExprAST>(val);
    getNextToken(); // consume true/false
    return move(Result);
}

// Parse a parenthesized expression
unique_ptr<ExprAST> Parser::ParseParenExpr()
{
    getNextToken(); // eat '('
    auto V = ParseExpression();
    if (!V)
        return nullptr;

    if (CurrentToken != tok_right_paren)
    {
        cerr << "Expected ')'" << endl;
        return nullptr;
    }
    getNextToken(); // eat ')'
    return V;
}

// Parse an identifier expression (variable or function call)
unique_ptr<ExprAST> Parser::ParseIdentifierExpr()
{
    string IdName = IdentifierStr;
    getNextToken(); // eat identifier

    if (CurrentToken != tok_left_paren) // Simple variable reference
        return make_unique<VariableExprAST>(IdName);

    // Function call
    getNextToken(); // eat '('
    vector<unique_ptr<ExprAST>> Args;

    if (CurrentToken != tok_right_paren)
    {
        while (true)
        {
            if (auto Arg = ParseExpression())
                Args.push_back(move(Arg));
            else
                return nullptr;

            if (CurrentToken == tok_right_paren)
                break;

            if (CurrentToken != tok_comma)
            {
                cerr << "Expected ',' in argument list" << endl;
                return nullptr;
            }
            getNextToken(); // eat ','
        }
    }

    getNextToken(); // eat ')'
    return make_unique<CallExprAST>(IdName, move(Args));
}

// Parse unary expressions
unique_ptr<ExprAST> Parser::ParseUnaryExpr()
{
    string op = getCurrentTokenString();

    if (op == "!" || op == "-" || op == "+" || op == "~" || op == "++" || op == "--")
    {
        getNextToken(); // consume operator
        if (auto Operand = ParseUnaryExpr())
            return make_unique<UnaryExprAST>(op, move(Operand));
        return nullptr;
    }

    return ParsePrimary();
}

// Parse a primary expression
unique_ptr<ExprAST> Parser::ParsePrimary()
{
    unique_ptr<ExprAST> expr = nullptr;

    switch (CurrentToken)
    {
    case tok_identifier:
        expr = ParseIdentifierExpr();
        break;
    case tok_number:
        expr = ParseNumberExpr();
        break;
    case tok_string_literal:
        expr = ParseStringExpr();
        break;
    case tok_char_literal:
        expr = ParseCharExpr();
        break;
    case tok_true:
    case tok_false:
        expr = ParseBoolExpr();
        break;
    case tok_left_paren:
        expr = ParseParenExpr();
        break;
    default:
        cerr << "Unknown token when expecting an expression" << endl;
        return nullptr;
    }

    // Handle postfix operators (++, --)
    while (CurrentToken == tok_increment || CurrentToken == tok_decrement)
    {
        string op = getCurrentTokenString();
        getNextToken(); // consume the operator
        expr = make_unique<UnaryExprAST>(op, move(expr));
    }

    return expr;
}

// Parse array access
unique_ptr<ExprAST> Parser::ParseArrayAccess(unique_ptr<ExprAST> Array)
{
    getNextToken(); // eat '['
    auto Index = ParseExpression();
    if (!Index)
        return nullptr;

    if (!expectToken(tok_right_bracket))
        return nullptr;

    return make_unique<ArrayExprAST>(move(Array), move(Index));
}

// Parse binary operator RHS
unique_ptr<ExprAST> Parser::ParseBinOpRHS(int ExprPrec, unique_ptr<ExprAST> LHS)
{
    while (true)
    {
        int TokPrec = GetTokPrecedence();

        if (TokPrec < ExprPrec)
            return LHS;

        string BinOp = getCurrentTokenString();
        getNextToken(); // eat binop

        auto RHS = ParseUnaryExpr();
        if (!RHS)
            return nullptr;

        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec)
        {
            RHS = ParseBinOpRHS(TokPrec + 1, move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = make_unique<BinaryExprAST>(BinOp, move(LHS), move(RHS));
    }
}

// Parse expression
unique_ptr<ExprAST> Parser::ParseExpression()
{
    auto LHS = ParseUnaryExpr();
    if (!LHS)
        return nullptr;

    // Handle array access
    if (CurrentToken == tok_left_bracket)
    {
        LHS = ParseArrayAccess(move(LHS));
        if (!LHS)
            return nullptr;
    }

    return ParseBinOpRHS(0, move(LHS));
}

// Parse assignment expression
unique_ptr<ExprAST> Parser::ParseAssignmentExpr()
{
    auto LHS = ParseExpression();
    if (!LHS)
        return nullptr;

    if (CurrentToken == tok_assign)
    {
        getNextToken(); // eat '='
        auto RHS = ParseAssignmentExpr();
        if (!RHS)
            return nullptr;
        return make_unique<AssignmentExprAST>(move(LHS), move(RHS));
    }

    return LHS;
}

// Parse variable declaration
unique_ptr<StmtAST> Parser::ParseVarDeclaration()
{
    DataType type = parseType();
    getNextToken(); // consume type

    if (CurrentToken != tok_identifier)
    {
        cerr << "Expected variable name" << endl;
        return nullptr;
    }

    string varName = IdentifierStr;
    getNextToken(); // consume identifier

    unique_ptr<ExprAST> initializer = nullptr;
    if (CurrentToken == tok_assign)
    {
        getNextToken(); // eat '='
        initializer = ParseExpression();
        if (!initializer)
            return nullptr;
    }

    if (!expectToken(tok_semicolon))
        return nullptr;

    return make_unique<VarDeclStmtAST>(type, varName, move(initializer));
}

// Parse expression statement
unique_ptr<StmtAST> Parser::ParseExpressionStatement()
{
    auto expr = ParseAssignmentExpr();
    if (!expr)
        return nullptr;

    if (!expectToken(tok_semicolon))
        return nullptr;

    return make_unique<ExprStmtAST>(move(expr));
}

// Parse compound statement
unique_ptr<StmtAST> Parser::ParseCompoundStatement()
{
    if (!expectToken(tok_left_brace))
        return nullptr;

    vector<unique_ptr<StmtAST>> statements;

    while (CurrentToken != tok_right_brace && CurrentToken != tok_eof)
    {
        if (auto stmt = ParseStatement())
            statements.push_back(move(stmt));
        else
            return nullptr;
    }

    if (!expectToken(tok_right_brace))
        return nullptr;

    return make_unique<CompoundStmtAST>(move(statements));
}

// Parse if statement
unique_ptr<StmtAST> Parser::ParseIfStatement()
{
    getNextToken(); // eat 'if'

    if (!expectToken(tok_left_paren))
        return nullptr;

    auto condition = ParseExpression();
    if (!condition)
        return nullptr;

    if (!expectToken(tok_right_paren))
        return nullptr;

    auto thenStmt = ParseStatement();
    if (!thenStmt)
        return nullptr;

    unique_ptr<StmtAST> elseStmt = nullptr;
    if (CurrentToken == tok_else)
    {
        getNextToken(); // eat 'else'
        elseStmt = ParseStatement();
        if (!elseStmt)
            return nullptr;
    }

    return make_unique<IfStmtAST>(move(condition), move(thenStmt), move(elseStmt));
}

// Parse while statement
unique_ptr<StmtAST> Parser::ParseWhileStatement()
{
    getNextToken(); // eat 'while'

    if (!expectToken(tok_left_paren))
        return nullptr;

    auto condition = ParseExpression();
    if (!condition)
        return nullptr;

    if (!expectToken(tok_right_paren))
        return nullptr;

    auto body = ParseStatement();
    if (!body)
        return nullptr;

    return make_unique<WhileStmtAST>(move(condition), move(body));
}

// Parse for statement
unique_ptr<StmtAST> Parser::ParseForStatement()
{
    getNextToken(); // eat 'for'

    if (!expectToken(tok_left_paren))
        return nullptr;

    // Parse initialization
    unique_ptr<StmtAST> init = nullptr;
    if (CurrentToken != tok_semicolon)
    {
        if (isType(CurrentToken))
        {
            init = ParseVarDeclaration();
        }
        else
        {
            init = ParseExpressionStatement();
        }
        if (!init)
            return nullptr;
    }
    else
    {
        getNextToken(); // eat ';'
    }

    // Parse condition
    unique_ptr<ExprAST> condition = nullptr;
    if (CurrentToken != tok_semicolon)
    {
        condition = ParseExpression();
        if (!condition)
            return nullptr;
    }
    if (!expectToken(tok_semicolon))
        return nullptr;

    // Parse update
    unique_ptr<ExprAST> update = nullptr;
    if (CurrentToken != tok_right_paren)
    {
        update = ParseExpression();
        if (!update)
            return nullptr;
    }
    if (!expectToken(tok_right_paren))
        return nullptr;

    // Parse body
    auto body = ParseStatement();
    if (!body)
        return nullptr;

    return make_unique<ForStmtAST>(move(init), move(condition), move(update), move(body));
}

// Parse return statement
unique_ptr<StmtAST> Parser::ParseReturnStatement()
{
    getNextToken(); // eat 'return'

    unique_ptr<ExprAST> value = nullptr;
    if (CurrentToken != tok_semicolon)
    {
        value = ParseExpression();
        if (!value)
            return nullptr;
    }

    if (!expectToken(tok_semicolon))
        return nullptr;

    return make_unique<ReturnStmtAST>(move(value));
}

// Parse break statement
unique_ptr<StmtAST> Parser::ParseBreakStatement()
{
    getNextToken(); // eat 'break'
    if (!expectToken(tok_semicolon))
        return nullptr;
    return make_unique<BreakStmtAST>();
}

// Parse continue statement
unique_ptr<StmtAST> Parser::ParseContinueStatement()
{
    getNextToken(); // eat 'continue'
    if (!expectToken(tok_semicolon))
        return nullptr;
    return make_unique<ContinueStmtAST>();
}

// Parse statement
unique_ptr<StmtAST> Parser::ParseStatement()
{
    switch (CurrentToken)
    {
    case tok_left_brace:
        return ParseCompoundStatement();
    case tok_if:
        return ParseIfStatement();
    case tok_while:
        return ParseWhileStatement();
    case tok_for:
        return ParseForStatement();
    case tok_return:
        return ParseReturnStatement();
    case tok_break:
        return ParseBreakStatement();
    case tok_continue:
        return ParseContinueStatement();
    default:
        if (isType(CurrentToken))
        {
            return ParseVarDeclaration();
        }
        else
        {
            return ParseExpressionStatement();
        }
    }
}

// Parse function prototype
unique_ptr<PrototypeAST> Parser::ParsePrototype()
{
    DataType returnType = parseType();
    getNextToken(); // consume return type

    if (CurrentToken != tok_identifier)
    {
        cerr << "Expected function name in prototype" << endl;
        return nullptr;
    }

    string functionName = IdentifierStr;
    getNextToken(); // consume function name

    if (!expectToken(tok_left_paren))
        return nullptr;

    vector<pair<DataType, string>> args;
    while (CurrentToken != tok_right_paren)
    {
        if (!isType(CurrentToken))
        {
            cerr << "Expected parameter type" << endl;
            return nullptr;
        }

        DataType paramType = parseType();
        getNextToken(); // consume type

        if (CurrentToken != tok_identifier)
        {
            cerr << "Expected parameter name" << endl;
            return nullptr;
        }

        string paramName = IdentifierStr;
        getNextToken(); // consume parameter name

        args.push_back({paramType, paramName});

        if (CurrentToken == tok_comma)
        {
            getNextToken(); // consume ','
        }
        else if (CurrentToken != tok_right_paren)
        {
            cerr << "Expected ',' or ')' in parameter list" << endl;
            return nullptr;
        }
    }

    if (!expectToken(tok_right_paren))
        return nullptr;

    return make_unique<PrototypeAST>(returnType, functionName, move(args));
}

// Parse function definition
unique_ptr<FunctionAST> Parser::ParseFunction()
{
    auto proto = ParsePrototype();
    if (!proto)
        return nullptr;

    auto body = ParseCompoundStatement();
    if (!body)
        return nullptr;

    return make_unique<FunctionAST>(move(proto), move(body));
}

// Parse extern declaration
unique_ptr<PrototypeAST> Parser::ParseExtern()
{
    getNextToken(); // eat 'extern'
    return ParsePrototype();
}

// Parse complete program
unique_ptr<ProgramAST> Parser::ParseProgram()
{
    auto program = make_unique<ProgramAST>();

    while (CurrentToken != tok_eof)
    {
        unique_ptr<StmtAST> stmt = nullptr;

        if (CurrentToken == tok_extern)
        {
            auto proto = ParseExtern();
            if (!proto)
                return nullptr;
            if (!expectToken(tok_semicolon))
                return nullptr;
            // Convert prototype to statement (you might want a separate ExternStmt)
            continue;
        }
        else if (isType(CurrentToken))
        {
            // Could be function definition or variable declaration
            // Look ahead to determine which
            size_t savedPos = CurrentPos - 1;
            DataType type = parseType();
            getNextToken(); // consume type

            if (CurrentToken == tok_identifier)
            {
                getNextToken(); // consume identifier
                if (CurrentToken == tok_left_paren)
                {
                    // Function definition
                    CurrentPos = savedPos;
                    getNextToken(); // restore position
                    stmt = ParseFunction();
                }
                else
                {
                    // Variable declaration
                    CurrentPos = savedPos;
                    getNextToken(); // restore position
                    stmt = ParseVarDeclaration();
                }
            }
        }
        else
        {
            stmt = ParseStatement();
        }

        if (stmt)
        {
            program->addStatement(move(stmt));
        }
        else
        {
            cerr << "Failed to parse statement" << endl;
            return nullptr;
        }
    }

    return program;
}

// Parse single statement (for testing)
unique_ptr<StmtAST> Parser::ParseSingleStatement()
{
    return ParseStatement();
}

// Parse single expression (for testing)
unique_ptr<ExprAST> Parser::ParseSingleExpression()
{
    return ParseExpression();
}
