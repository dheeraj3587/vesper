# Vesper Compiler Codebase Explanation

This document provides a detailed explanation of the Vesper compiler implementation, which is based on the Kaleidoscope language tutorial. The compiler is implemented in C++ and follows a traditional compiler pipeline structure.

## Project Structure

The project consists of several key components:

1. `main.cpp` - The entry point and driver program
2. `Lexer.h/cpp` - Tokenization of source code
3. `Parser.h/cpp` - Syntax analysis and AST construction
4. `AST.h` - Abstract Syntax Tree definitions

## Detailed Component Explanation

### 1. main.cpp

The main driver program that demonstrates the compiler pipeline:

```cpp
// Key components:
- Sample Kaleidoscope code input
- Lexer initialization and tokenization
- Parser initialization and AST construction
- Error handling for both lexing and parsing phases
```

Key functions:

- `getCurrentTokenString()`: Helper function to get the current token from either parser or token list
- `main()`: Orchestrates the compilation process:
  1. Takes sample Kaleidoscope code
  2. Performs lexical analysis
  3. Performs syntax analysis
  4. Handles errors at each stage
  5. Prints the resulting AST

### 2. Lexer (Lexer.h)

The lexical analyzer that converts source code into tokens:

```cpp
class Lexer {
    // Private members:
    - source_: The input source code
    - current_pos_: Current position in source
    - current_char_: Current character being processed

    // Public interface:
    - Lexer(): Constructor taking source code
    - tokenize(): Main method to convert source to tokens

    // Private helper methods:
    - advance(): Move to next character
    - skipWhitespace(): Skip whitespace characters
    - skipComment(): Skip comment sections
    - getIdentifier(): Extract identifier tokens
    - getNumber(): Extract number tokens
}
```

### 3. Parser (Parser.h)

The syntax analyzer that converts tokens into an Abstract Syntax Tree:

```cpp
// Token definitions:
enum Token {
    tok_eof = -1,
    tok_def = -2,
    tok_extern = -3,
    tok_identifier = -4,
    tok_number = -5,
    // ... other tokens
}

class Parser {
    // Private members:
    - CurrentToken: Current token being processed
    - Tokens: Vector of input tokens
    - CurrentPos: Current position in token stream
    - IdentifierStr: Current identifier name
    - NumVal: Current number value

    // Public interface:
    - Parser(): Constructor taking token vector
    - Parse(): Main parsing entry point

    // Private parsing methods:
    - ParseNumberExpr(): Parse numeric literals
    - ParseParenExpr(): Parse parenthesized expressions
    - ParseIdentifierExpr(): Parse variable references
    - ParsePrimary(): Parse primary expressions
    - ParseBinOpRHS(): Parse binary operator expressions
    - ParseExpression(): Parse general expressions
    - ParsePrototype(): Parse function prototypes
    - ParseDefinition(): Parse function definitions
    - ParseExtern(): Parse external declarations
    - ParseTopLevelExpr(): Parse top-level expressions
}
```

### 4. Abstract Syntax Tree (AST.h)

Defines the structure of the Abstract Syntax Tree:

```cpp
// Base class for all expressions
class ExprAST {
    virtual ~ExprAST() = default;
    virtual void print() const = 0;
}

// Concrete AST node types:
1. NumberExprAST: Represents numeric literals
   - Stores: double Val

2. VariableExprAST: Represents variable references
   - Stores: string Name

3. BinaryExprAST: Represents binary operations
   - Stores:
     - char Op (operator)
     - unique_ptr<ExprAST> LHS (left operand)
     - unique_ptr<ExprAST> RHS (right operand)

4. CallExprAST: Represents function calls
   - Stores:
     - string Callee (function name)
     - vector<unique_ptr<ExprAST>> Args (arguments)

5. PrototypeAST: Represents function prototypes
   - Stores:
     - string Name (function name)
     - vector<string> Args (parameter names)
     - bool IsOperator
     - unsigned Precedence

6. FunctionAST: Represents function definitions
   - Stores:
     - unique_ptr<PrototypeAST> Proto (function prototype)
     - unique_ptr<ExprAST> Body (function body)
```

## Compilation Pipeline

1. **Lexical Analysis**:

   - Source code is converted into tokens
   - Handles whitespace, comments, identifiers, and numbers
   - Implemented in Lexer class

2. **Syntax Analysis**:

   - Tokens are converted into an Abstract Syntax Tree
   - Implements recursive descent parsing
   - Handles expressions, function definitions, and external declarations
   - Implemented in Parser class

3. **AST Construction**:
   - Represents the program structure
   - Supports various expression types
   - Enables code generation and optimization
   - Implemented through AST node classes

## Error Handling

The compiler implements error handling at multiple levels:

- Lexical errors (invalid tokens)
- Syntax errors (invalid expressions)
- Semantic errors (type mismatches, undefined variables)

## Usage

The compiler can process Kaleidoscope code with features like:

- Function definitions
- External declarations
- Binary operations
- Function calls
- Variable references
- Numeric literals

Example input:

```kaleidoscope
def foo(a, b, c) a+b*2+c;
foo(1, 2);
extern sin(x);
```
