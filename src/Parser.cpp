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
    BinOpPrecedence["<"] = 10;
    BinOpPrecedence[">"] = 10;
    BinOpPrecedence["<="] = 10;
    BinOpPrecedence[">="] = 10;
    BinOpPrecedence["=="] = 10;
    BinOpPrecedence["!="] = 10;
    BinOpPrecedence["<<"] = 15;
    BinOpPrecedence[">>"] = 15;
    BinOpPrecedence["+"] = 20;
    BinOpPrecedence["-"] = 20;
    BinOpPrecedence["*"] = 40;
    BinOpPrecedence["/"] = 40;
    BinOpPrecedence["%"] = 40;
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

    if (token_str.rfind("KEYWORD:", 0) == 0)
    {
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
        else if (stripped_token == "const")
            CurrentToken = tok_const;
        else if (stripped_token == "unsigned")
            CurrentToken = tok_unsigned;
        else if (stripped_token == "volatile")
            CurrentToken = tok_volatile;
        else
        {
            IdentifierStr = stripped_token;
            CurrentToken = tok_identifier;
        }
    }
    else if (token_str.rfind("IDENTIFIER:", 0) == 0)
    {
        IdentifierStr = stripped_token;
        CurrentToken = tok_identifier;
    }
    else if (token_str.rfind("NUMBER:", 0) == 0)
    {
        NumVal = strtod(stripped_token.c_str(), nullptr);
        CurrentToken = tok_number;
    }
    else if (token_str.rfind("OPERATOR:", 0) == 0)
    {
        if (stripped_token == "=")
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
        else if (stripped_token == "<<")
            CurrentToken = tok_left_shift;
        else if (stripped_token == ">>")
            CurrentToken = tok_right_shift;
        else if (stripped_token.length() == 1 && (BinOpPrecedence.count(stripped_token) || stripped_token == "<" || stripped_token == ">"))
            CurrentToken = stripped_token[0];
        else
        {
            cerr << "Unknown operator: " << stripped_token << endl;
            CurrentToken = tok_eof;
        }
    }
    else if (token_str.rfind("PUNCTUATOR:", 0) == 0)
    {
        if (stripped_token == ";")
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
        else if (stripped_token == "=")
            CurrentToken = tok_assign;
        else if (stripped_token.length() == 1)
            CurrentToken = stripped_token[0];
        else
        {
            cerr << "Unknown punctuator: " << stripped_token << endl;
            CurrentToken = tok_eof;
        }
    }
    else if (token_str.rfind("STRING_LITERAL:", 0) == 0)
    {
        StringVal = stripped_token;
        CurrentToken = tok_string_literal;
    }
    else if (token_str.rfind("CHAR_LITERAL:", 0) == 0)
    {
        if (!stripped_token.empty())
            CharVal = stripped_token[0];
        CurrentToken = tok_char_literal;
    }
    else // Fallback for simple, untagged tokens (e.g. from early tests)
    {
        if (stripped_token == "def")
            CurrentToken = tok_def;
        else if (stripped_token == "extern")
            CurrentToken = tok_extern;
        else if (isalpha(stripped_token[0]) || stripped_token[0] == '_')
        {
            IdentifierStr = stripped_token;
            CurrentToken = tok_identifier;
        }
        else if (isdigit(stripped_token[0]) || stripped_token[0] == '.' || stripped_token[0] == '-')
        {
            NumVal = strtod(stripped_token.c_str(), nullptr);
            CurrentToken = tok_number;
        }
        else if (stripped_token.length() == 1)
        {
            CurrentToken = stripped_token[0];
        }
        else
        {
            CurrentToken = tok_eof;
        }
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
           token == tok_string || token == tok_auto || token == tok_const ||
           token == tok_unsigned || token == tok_volatile;
}

bool Parser::expectToken(int expectedToken)
{
    if (CurrentToken != expectedToken)
    {
        cerr << "Expected token " << expectedToken << " but got " << CurrentToken << endl;
        return false;
    }
    getNextToken(); // Consume the expected token
    return true;
}

// Parse a number expression
unique_ptr<ExprAST> Parser::ParseNumberExpr()
{
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
}

// Parse a string expression
unique_ptr<ExprAST> Parser::ParseStringExpr()
{
    auto Result = make_unique<StringExprAST>(StringVal);
    getNextToken(); // consume the string
    return std::move(Result);
}

// Parse a character expression
unique_ptr<ExprAST> Parser::ParseCharExpr()
{
    auto Result = make_unique<CharExprAST>(CharVal);
    getNextToken(); // consume the character
    return std::move(Result);
}

// Parse a boolean expression
unique_ptr<ExprAST> Parser::ParseBoolExpr()
{
    bool val = (CurrentToken == tok_true);
    auto Result = make_unique<BoolExprAST>(val);
    getNextToken(); // consume true/false
    return std::move(Result);
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
                Args.push_back(std::move(Arg));
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
    return make_unique<CallExprAST>(IdName, std::move(Args));
}

// Parse initializer list { expr1, expr2, ... }
unique_ptr<ExprAST> Parser::ParseInitializerList()
{
    getNextToken(); // consume '{'

    vector<unique_ptr<ExprAST>> elements;

    if (CurrentToken != tok_right_brace)
    {
        while (true)
        {
            auto elem = ParseExpression();
            if (!elem)
                return nullptr;
            elements.push_back(std::move(elem));

            if (CurrentToken == tok_right_brace)
                break;

            if (CurrentToken != tok_comma)
            {
                cerr << "Expected ',' or '}' in initializer list" << endl;
                return nullptr;
            }
            getNextToken(); // consume ','
        }
    }

    if (!expectToken(tok_right_brace))
        return nullptr;

    // For now, return the first element or a default value
    // In a full implementation, we'd have a proper InitializerListExprAST
    if (!elements.empty())
        return std::move(elements[0]);
    else
        return make_unique<NumberExprAST>(0);
}

// Parse unary expressions
unique_ptr<ExprAST> Parser::ParseUnaryExpr()
{
    // If the current token is not a unary operator, it must be a primary expression.
    if (CurrentToken != '!' && CurrentToken != '-' && CurrentToken != '+' && CurrentToken != '~' &&
        CurrentToken != tok_increment && CurrentToken != tok_decrement && CurrentToken != '*')
    {
        return ParsePrimary();
    }

    // It is a unary operator.
    string op = getCurrentTokenString();
    getNextToken(); // consume operator

    if (auto Operand = ParseUnaryExpr())
        return make_unique<UnaryExprAST>(op, std::move(Operand));

    return nullptr;
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
    case tok_left_brace:
        // Handle initializer lists
        return ParseInitializerList();
    default:
        cerr << "Unknown token when expecting an expression: " << getCurrentTokenString()
             << " (token: " << CurrentToken << ")" << endl;
        return nullptr;
    }

    // Handle postfix operators (++, --, array access, member access)
    while (true)
    {
        if (CurrentToken == tok_increment || CurrentToken == tok_decrement)
        {
            string op = getCurrentTokenString();
            getNextToken(); // consume the operator
            expr = make_unique<UnaryExprAST>(op, std::move(expr));
        }
        else if (CurrentToken == tok_left_bracket)
        {
            expr = ParseArrayAccess(std::move(expr));
            if (!expr)
                return nullptr;
        }
        else if (CurrentToken == '.')
        {
            getNextToken(); // consume '.'
            if (CurrentToken != tok_identifier)
            {
                cerr << "Expected identifier after '.'" << endl;
                return nullptr;
            }
            string member = IdentifierStr;
            getNextToken(); // consume identifier
            expr = make_unique<BinaryExprAST>(".", std::move(expr),
                                              make_unique<VariableExprAST>(member));
        }
        else if (CurrentToken == tok_scope)
        {
            getNextToken(); // consume '::'
            if (CurrentToken != tok_identifier)
            {
                cerr << "Expected identifier after '::'" << endl;
                return nullptr;
            }
            string member = IdentifierStr;
            getNextToken(); // consume identifier
            expr = make_unique<ScopeExprAST>(std::move(expr), member);
        }
        else
        {
            break;
        }
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

    return make_unique<ArrayExprAST>(std::move(Array), std::move(Index));
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
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        LHS = make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
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
        LHS = ParseArrayAccess(std::move(LHS));
        if (!LHS)
            return nullptr;
    }

    return ParseBinOpRHS(0, std::move(LHS));
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
        return make_unique<AssignmentExprAST>(std::move(LHS), std::move(RHS));
    }

    return LHS;
}

// Parse variable declaration
unique_ptr<StmtAST> Parser::ParseVarDeclaration()
{
    // Handle const modifier
    bool isConst = false;
    if (CurrentToken == tok_const)
    {
        isConst = true;
        getNextToken(); // consume 'const'
    }

    // Handle unsigned modifier
    bool isUnsigned = false;
    if (CurrentToken == tok_unsigned)
    {
        isUnsigned = true;
        getNextToken(); // consume 'unsigned'
    }

    auto type = parseType();
    getNextToken(); // consume type

    std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> vars;

    while (true)
    {
        // Handle pointer declarations
        int pointerLevel = 0;
        while (CurrentToken == '*')
        {
            pointerLevel++;
            getNextToken(); // consume '*'
        }

        if (CurrentToken != tok_identifier)
        {
            cerr << "Expected identifier after type" << endl;
            return nullptr;
        }
        std::string varName = IdentifierStr;
        getNextToken(); // consume identifier

        std::unique_ptr<ExprAST> initializer = nullptr;
        if (CurrentToken == tok_assign)
        {
            getNextToken(); // eat '='
            initializer = ParseExpression();
            if (!initializer)
                return nullptr;
        }
        vars.emplace_back(varName, std::move(initializer));

        if (CurrentToken == tok_comma)
        {
            getNextToken(); // consume ',' and continue to next variable
            continue;
        }
        else if (CurrentToken == tok_semicolon)
        {
            getNextToken(); // consume ';' and finish
            break;
        }
        else
        {
            cerr << "Expected ',' or ';' after variable declaration, got token " << CurrentToken << endl;
            return nullptr;
        }
    }

    return make_unique<VarDeclStmtAST>(type, std::move(vars));
}

// Parse expression statement
unique_ptr<StmtAST> Parser::ParseExpressionStatement()
{
    auto expr = ParseAssignmentExpr();
    if (!expr)
        return nullptr;

    // Make semicolon optional to support both Kaleidoscope and C-style syntax
    if (CurrentToken == tok_semicolon)
    {
        getNextToken(); // consume semicolon
    }

    return make_unique<ExprStmtAST>(std::move(expr));
}

// Parse compound statement
unique_ptr<StmtAST> Parser::ParseCompoundStatement()
{
    if (!expectToken(tok_left_brace))
        return nullptr;

    vector<unique_ptr<StmtAST>> statements;
    while (CurrentToken != tok_right_brace && CurrentToken != tok_eof)
    {
        auto stmt = ParseStatement();
        if (stmt)
            statements.push_back(std::move(stmt));
        else
        {
            // Error recovery: skip token and continue
            cerr << "Skipping token due to error in compound statement." << endl;
            getNextToken();
        }
    }

    if (!expectToken(tok_right_brace))
        return nullptr;

    return make_unique<CompoundStmtAST>(std::move(statements));
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
    return make_unique<IfStmtAST>(std::move(condition), std::move(thenStmt), std::move(elseStmt));
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
    return make_unique<WhileStmtAST>(std::move(condition), std::move(body));
}

// Parse for statement
unique_ptr<StmtAST> Parser::ParseForStatement()
{
    getNextToken(); // eat 'for'
    if (!expectToken(tok_left_paren))
        return nullptr;

    unique_ptr<StmtAST> init = nullptr;
    if (CurrentToken != tok_semicolon)
    {
        init = ParseStatement(); // Can be VarDecl or ExprStmt
    }
    else
    {
        if (!expectToken(tok_semicolon))
            return nullptr;
    }

    unique_ptr<ExprAST> condition = nullptr;
    if (CurrentToken != tok_semicolon)
    {
        condition = ParseExpression();
        if (!condition)
            return nullptr;
    }
    if (!expectToken(tok_semicolon))
        return nullptr;

    unique_ptr<ExprAST> update = nullptr;
    if (CurrentToken != tok_right_paren)
    {
        update = ParseExpression();
        if (!update)
            return nullptr;
    }
    if (!expectToken(tok_right_paren))
        return nullptr;

    auto body = ParseStatement();
    if (!body)
        return nullptr;

    return make_unique<ForStmtAST>(std::move(init), std::move(condition), std::move(update), std::move(body));
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

    return make_unique<ReturnStmtAST>(std::move(value));
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
    case tok_left_brace:
        return ParseCompoundStatement();
    default:
        if (isType(CurrentToken))
        {
            // This could be a variable declaration or a function definition.
            // The main ParseProgram loop should have handled this distinction.
            // Here, we assume it's a VarDecl if we get this far.
            return ParseVarDeclaration();
        }
        return ParseExpressionStatement();
    }
}

// Parse Kaleidoscope-style function prototype (def funcname(arg1, arg2))
unique_ptr<PrototypeAST> Parser::ParseKaleidoscopePrototype()
{
    if (CurrentToken != tok_def)
    {
        cerr << "Expected 'def' in Kaleidoscope prototype" << endl;
        return nullptr;
    }
    getNextToken(); // consume 'def'

    if (CurrentToken != tok_identifier)
    {
        cerr << "Expected function name in Kaleidoscope prototype" << endl;
        return nullptr;
    }

    string functionName = IdentifierStr;
    getNextToken(); // consume function name

    if (!expectToken(tok_left_paren))
        return nullptr;

    vector<pair<DataType, string>> args;
    while (CurrentToken != tok_right_paren)
    {
        if (CurrentToken != tok_identifier)
        {
            cerr << "Expected parameter name in Kaleidoscope prototype" << endl;
            return nullptr;
        }

        string paramName = IdentifierStr;
        getNextToken(); // consume parameter name

        // In Kaleidoscope, parameters are untyped
        args.push_back({DataType::AUTO, paramName});

        if (CurrentToken == tok_comma)
        {
            getNextToken(); // consume ','
        }
        else if (CurrentToken != tok_right_paren)
        {
            cerr << "Expected ',' or ')' in Kaleidoscope parameter list" << endl;
            return nullptr;
        }
    }

    if (!expectToken(tok_right_paren))
        return nullptr;

    return make_unique<PrototypeAST>(DataType::AUTO, functionName, std::move(args));
}

// Parse Kaleidoscope-style function definition
unique_ptr<FunctionAST> Parser::ParseKaleidoscopeFunction()
{
    auto proto = ParseKaleidoscopePrototype();
    if (!proto)
        return nullptr;

    // In Kaleidoscope, the body is just an expression, but FunctionAST expects a StmtAST
    auto bodyExpr = ParseExpression();
    if (!bodyExpr)
        return nullptr;

    // Wrap the expression in an ExprStmtAST
    auto body = make_unique<ExprStmtAST>(std::move(bodyExpr));

    return make_unique<FunctionAST>(std::move(proto), std::move(body));
}

// Parse function prototype
unique_ptr<PrototypeAST> Parser::ParsePrototype()
{
    auto type = parseType();
    getNextToken(); // consume type

    if (CurrentToken != tok_identifier)
    {
        cerr << "Expected function name in prototype" << endl;
        return nullptr;
    }

    string FnName = IdentifierStr;
    getNextToken();

    if (CurrentToken != tok_left_paren)
    {
        cerr << "Expected '(' in prototype" << endl;
        return nullptr;
    }

    getNextToken(); // eat '('.
    vector<pair<DataType, string>> ArgNames;
    while (isType(CurrentToken))
    {
        auto argType = parseType();
        getNextToken(); // consume type
        if (CurrentToken != tok_identifier)
        {
            cerr << "Expected identifier in prototype arguments" << endl;
            return nullptr;
        }
        ArgNames.push_back({argType, IdentifierStr});
        getNextToken(); // consume identifier

        if (CurrentToken == tok_right_paren)
            break;

        if (CurrentToken != tok_comma)
        {
            cerr << "Expected ')' or ',' in argument list" << endl;
            return nullptr;
        }
        getNextToken();
    }

    if (CurrentToken != tok_right_paren)
    {
        cerr << "Expected ')' in prototype" << endl;
        return nullptr;
    }

    getNextToken(); // eat ')'.

    return make_unique<PrototypeAST>(type, FnName, std::move(ArgNames));
}

// Parse function definition
unique_ptr<FunctionAST> Parser::ParseFunction()
{
    auto Proto = ParsePrototype();
    if (!Proto)
        return nullptr;

    if (auto Body = ParseCompoundStatement())
        return make_unique<FunctionAST>(std::move(Proto), std::move(Body));

    cerr << "Expected function body" << endl;
    return nullptr;
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
        if (CurrentToken == tok_def)
        {
            auto func = ParseKaleidoscopeFunction();
            if (!func)
                return nullptr;
            program->addFunction(std::move(func));
        }
        else if (CurrentToken == tok_extern)
        {
            auto ext = ParseExtern();
            if (!ext)
                return nullptr;
            if (!expectToken(tok_semicolon))
                return nullptr;
            program->addExtern(std::move(ext));
        }
        else if (isType(CurrentToken))
        {
            // Look ahead to distinguish function from variable declaration
            size_t savedPos = CurrentPos - 1;
            parseType();
            getNextToken(); // consume type

            bool isFunc = false;
            if (CurrentToken == tok_identifier)
            {
                getNextToken(); // consume identifier
                if (CurrentToken == tok_left_paren)
                {
                    isFunc = true;
                }
            }

            // Restore parser state
            CurrentPos = savedPos;
            getNextToken();

            if (isFunc)
            {
                auto func = ParseFunction();
                if (!func)
                    return nullptr;
                program->addFunction(std::move(func));
            }
            else
            {
                auto varDecl = ParseVarDeclaration();
                if (!varDecl)
                    return nullptr;
                program->addStatement(std::move(varDecl));
            }
        }
        else
        {
            // Could be a top-level expression for Kaleidoscope
            auto stmt = ParseExpressionStatement();
            if (!stmt)
                return nullptr;
            program->addStatement(std::move(stmt));
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
