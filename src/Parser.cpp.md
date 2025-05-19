# Parser.cpp Implementation Explanation

This document provides a detailed line-by-line explanation of the Parser implementation for the Vesper compiler.

## File Structure and Dependencies

```cpp
#include "Parser.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <map>

using namespace std;
```

- Includes necessary headers for the parser implementation
- Uses standard C++ libraries for I/O, character classification, and string conversion
- Includes map for operator precedence management

## Operator Precedence

```cpp
static map<char, int> BinopPrecedence;
```

- Static map that stores operator precedence levels
- Used to determine the order of operations in expressions

## Constructor Implementation

```cpp
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
```

- Constructor takes a vector of tokens as input
- Initializes operator precedence levels:
  - `<` has lowest precedence (10)
  - `+` and `-` have medium precedence (20)
  - `*` and `/` have highest precedence (40)
- Calls getNextToken() to initialize the first token

## Token Precedence Helper

```cpp
int Parser::GetTokPrecedence()
{
    if (!isascii(CurrentToken))
        return -1;

    int TokPrec = BinopPrecedence[CurrentToken];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}
```

- Returns the precedence of the current binary operator
- Returns -1 if the token is not a valid binary operator
- Used in expression parsing to maintain correct operator precedence

## Token Stream Management

```cpp
int Parser::getNextToken()
{
    if (CurrentPos >= Tokens.size())
    {
        this->CurrentToken = tok_eof;
        return this->CurrentToken;
    }

    string token_str = Tokens[CurrentPos++];
    int determined_tok_type;
```

- Advances the token stream
- Returns EOF if all tokens have been consumed
- Gets the next token string and prepares to determine its type

### Token Type Determination

```cpp
    if (token_str == "def")
        determined_tok_type = tok_def;
    else if (token_str == "extern")
        determined_tok_type = tok_extern;
    // ... more keyword checks ...
    else if (isdigit(token_str[0]) || token_str[0] == '.')
    {
        NumVal = strtod(token_str.c_str(), nullptr);
        IdentifierStr = "";
        determined_tok_type = tok_number;
    }
    else if (isalpha(token_str[0]))
    {
        IdentifierStr = token_str;
        determined_tok_type = tok_identifier;
    }
```

- Determines token type based on the token string
- Handles keywords, operators, numbers, and identifiers
- Sets appropriate semantic values (NumVal, IdentifierStr)

## Expression Parsing

### Number Expression

```cpp
unique_ptr<ExprAST> Parser::ParseNumberExpr()
{
    auto Result = make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
}
```

- Creates a NumberExprAST node for numeric literals
- Consumes the number token
- Returns the created AST node

### Parenthesized Expression

```cpp
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
```

- Handles expressions enclosed in parentheses
- Parses the inner expression
- Verifies proper closing parenthesis
- Returns the parsed expression

### Identifier Expression

```cpp
unique_ptr<ExprAST> Parser::ParseIdentifierExpr()
{
    string IdName = IdentifierStr;
    getNextToken(); // eat identifier.

    if (CurrentToken != '(') // Simple variable ref.
        return make_unique<VariableExprAST>(IdName);

    // Call.
    getNextToken(); // eat (
    vector<unique_ptr<ExprAST>> Args;
    // ... argument parsing ...
}
```

- Handles variable references and function calls
- Creates VariableExprAST for simple variables
- Creates CallExprAST for function calls with arguments

### Primary Expression

```cpp
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
```

- Entry point for parsing basic expressions
- Handles identifiers, numbers, and parenthesized expressions
- Returns nullptr for invalid expressions

### Binary Operator Expression

```cpp
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

        // ... precedence handling ...
        LHS = make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}
```

- Implements operator precedence parsing
- Handles binary operator expressions
- Creates BinaryExprAST nodes
- Maintains correct operator precedence

### General Expression

```cpp
unique_ptr<ExprAST> Parser::ParseExpression()
{
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}
```

- Main entry point for expression parsing
- Parses the left-hand side
- Handles binary operators with proper precedence

## Function Parsing

### Function Prototype

```cpp
unique_ptr<PrototypeAST> Parser::ParsePrototype()
{
    string FnName;
    unsigned Kind = 0; // 0 = identifier, 1 = unary, 2 = binary.
    unsigned BinaryPrecedence = 30;

    // ... prototype parsing ...
}
```

- Parses function declarations
- Handles regular functions, unary operators, and binary operators
- Creates PrototypeAST nodes

## Error Handling

The parser implements error handling through:

- Nullptr returns for invalid expressions
- Error messages for unexpected tokens
- Proper token consumption to maintain parsing state

## Usage Example

```cpp
// Example of parsing a simple expression:
// a + b * 2
Parser parser(tokens);
auto ast = parser.ParseExpression();
```

The parser follows a recursive descent approach, maintaining proper operator precedence and handling various expression types in the Kaleidoscope language.
