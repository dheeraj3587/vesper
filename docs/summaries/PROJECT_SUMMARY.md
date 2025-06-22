# Kaleidoscope Compiler Project Summary and Viva Questions

## Project Overview

This project focuses on building a compiler for the Kaleidoscope language, a simple procedural language. The development process has been iterative, involving the implementation of core compiler components, testing, and debugging.

## Key Components Implemented

### 1. Lexer (`src/Lexer.h`, `src/Lexer.cpp`)

- **Purpose:** To break down the raw Kaleidoscope source code (a string) into a stream of tokens.
- **Functionality:**
  - The `Lexer` class constructor takes the source code string.
  - The primary public method `tokenize()` processes the source and returns a `std::vector<std::string>` where each string represents a token.
  - **Token Types Handled:**
    - **Keywords:** `def` (function definition), `extern` (external function declaration), `if`, `then`, `else`, `for`, `in`, `binary` (custom binary operator), `unary` (custom unary operator), `var` (variable declaration - though full var implementation is pending).
    - **Identifiers:** Variable names, function names (e.g., `myVar`, `foo`).
    - **Numbers:** Floating-point numbers (e.g., `1.23`, `42.0`, `.5`).
    - **Operators:** `+`, `-`, `*`, `/`, `<`, `>`, `=`, `(`, `)`, `,`, `;`.
    - **Comments:** Lines starting with `#` are ignored.
    - **End-of-File (EOF):** Implicitly handled when the source is exhausted.
  - **Implementation Details:**
    - Uses helper methods like `advance()`, `skipWhitespace()`, `skipComment()`, `getIdentifier()`, and `getNumber()`.
    - `current_char_` and `current_pos_` track the current position in the source.
  - **Error Handling:** Throws a `std::runtime_error` for unknown characters encountered during tokenization.

### 2. Abstract Syntax Tree (AST) (`src/AST.h`)

- **Purpose:** To represent the grammatical structure of the parsed code in a tree format.
- **Core Structure:**
  - An abstract base class `ExprAST` with a pure virtual destructor and a pure virtual `print()` method for debugging and displaying the AST.
- **Node Types (derived from `ExprAST`):**
  - `NumberExprAST`: Represents numeric literals (e.g., `42.0`). Stores a `double` value.
  - `VariableExprAST`: Represents variable references (e.g., `x`). Stores the variable name as a `std::string`.
  - `BinaryExprAST`: Represents binary operations (e.g., `a + b`). Stores the operator (`char`), and `std::unique_ptr`s to the left-hand side (LHS) and right-hand side (RHS) `ExprAST` nodes.
  - `CallExprAST`: Represents function calls (e.g., `foo(a, b)`). Stores the callee name (`std::string`) and a `std::vector` of `std::unique_ptr<ExprAST>` for arguments.
  - `PrototypeAST`: Represents the "signature" of a function, including its name, argument names, and whether it's a custom operator (and its precedence). It also inherits from `ExprAST` to allow `extern` declarations (which are just prototypes) to be handled as top-level parsed elements.
  - `FunctionAST`: Represents a full function definition, containing a `std::unique_ptr<PrototypeAST>` (for the function's signature) and a `std::unique_ptr<ExprAST>` (for the function's body). It inherits from `ExprAST` to be a top-level parsed element.
- **Memory Management:** Uses `std::unique_ptr` extensively to manage the memory of AST nodes, ensuring automatic cleanup (RAII).
- **Debugging:** Each node implements the `print()` method to output a string representation of that part of the AST.

### 3. Parser (`src/Parser.h`, `src/Parser.cpp`)

- **Purpose:** To take the stream of tokens from the Lexer and build an Abstract Syntax Tree (AST) based on the Kaleidoscope grammar.
- **Key Features & Implementation:**
  - **`Token` Enum:** Defines various token types (e.g., `tok_eof`, `tok_def`, `tok_identifier`, `tok_number`, as well as single characters for operators).
  - **Operator Precedence:**
    - A `static std::map<char, int> BinopPrecedence` stores the precedence levels for binary operators (e.g., `*` has higher precedence than `+`).
    - `GetTokPrecedence()`: Returns the precedence of the current token if it's a known binary operator.
  - **Parser State:**
    - `CurrentToken`: Stores the integer value of the current token being processed.
    - `IdentifierStr`: Stores the string value if `CurrentToken` is `tok_identifier`.
    - `NumVal`: Stores the double value if `CurrentToken` is `tok_number`.
  - **Token Consumption:**
    - `getNextToken()`: This function is crucial. It obtains the next token string from the input `Tokens` vector (passed during Parser construction), determines its type, updates `CurrentToken`, `IdentifierStr`, and `NumVal`, and returns the type. The initial design of the parser relied on a vector of tokens; this was later adapted, though the constructor signature remained.
  - **Recursive Descent Parsing Methods:** The parser uses a set of mutually recursive functions to parse different parts of the grammar:
    - `ParseNumberExpr()`: Parses numeric literals into `NumberExprAST`.
    - `ParseParenExpr()`: Parses expressions enclosed in parentheses.
    - `ParseIdentifierExpr()`: Parses identifiers. It differentiates between variable references (creating `VariableExprAST`) and function calls (creating `CallExprAST` by checking for an opening parenthesis `(`).
    - `ParsePrimary()`: Parses the most basic expressions (numbers, identifiers, parenthesized expressions). This often acts as a dispatcher.
    - `ParseBinOpRHS()`: Implements the operator-precedence climbing algorithm to correctly parse binary expressions according to operator precedence and associativity.
    - `ParseExpression()`: Parses a full expression, which might include a primary expression possibly followed by a sequence of binary operators.
    - `ParsePrototype()`: Parses function prototypes (e.g., `def foo(a b)`). It handles regular function prototypes as well as custom unary (`unary op (arg)`) and binary (`binary op prec (lhs rhs)`) operator definitions.
    - `ParseDefinition()`: Parses a full function definition (`def` keyword followed by a prototype and an expression body).
    - `ParseExtern()`: Parses external function declarations (`extern` keyword followed by a prototype).
    - `ParseTopLevelExpr()`: Parses expressions entered at the top level (e.g., in a REPL). These are wrapped in an anonymous function (`__anon_expr`) for consistency.
  - **Main Parsing Loop (`Parse()`):**
    - This is the entry point called by `main.cpp`.
    - It repeatedly attempts to parse top-level constructs (`def`, `extern`, or other expressions).
    - It skips top-level semicolons `;`.
    - It returns `nullptr` upon reaching `tok_eof` or if a parsing error occurs that can't be recovered at that level.
- **Error Handling:** Parsing functions typically return `nullptr` if they encounter an unexpected token or a grammatical error. Debug messages are printed to `std::cerr` in many error cases.

### 4. Main Program (`src/main.cpp`)

- **Purpose:** To drive the lexer and parser, and to demonstrate their functionality.
- **Functionality:**
  1.  Defines a sample Kaleidoscope code string.
  2.  Creates a `Lexer` object with the source code.
  3.  Calls `lexer.tokenize()` to get a vector of token strings.
  4.  Creates a `Parser` object, passing the token vector.
  5.  Enters a loop:
      - Calls `parser.Parse()` to get the AST for one top-level statement.
      - If a valid `ExprAST` is returned, its `print()` method is called to display the structure.
      - The loop continues until `parser.Parse()` returns `nullptr` (signifying EOF or an unrecoverable parsing error for top-level constructs).
  6.  Prints messages indicating the parsing status.

### 5. Iterative Development and Debugging

The project was developed iteratively, with several bugs and issues addressed along the way:

- **AST Inheritance:** Ensured `PrototypeAST` and `FunctionAST` correctly inherit from `ExprAST` to resolve `std::unique_ptr` conversion errors.
- **Lexer Semicolon:** Added `;` as a recognized token in the Lexer.
- **Parser Semicolon Handling:** Modified the main `Parse()` loop to skip top-level semicolons.
- **`CurrentToken` Management:** A significant debugging effort involved ensuring `getNextToken()` correctly and consistently updated the parser's `CurrentToken` state, which was critical for the parsing logic in functions like `ParseDefinition` and `ParsePrototype`.
- **Argument Parsing:** Corrected the argument parsing loop in `ParsePrototype` to properly handle comma-separated identifiers.
- **C++ Issues:** Addressed `Token` enum redefinitions, `PrototypeAST` constructor mismatches (for operator overloading), and qualified `std::move` calls.
- **Error Messages:** Added `std::cerr` outputs in parser functions to aid debugging.

### 6. Documentation

- **`README.md`:** Updated to reflect the Kaleidoscope compiler project, outlining features, components, and potential next steps.
- **Hinglish Explanations:** Created separate markdown files (`AST.h.md`, `Lexer.h.md`, `Lexer.cpp.md`, `Parser.h.md`, `Parser.cpp.md`) providing line-by-line explanations of the C++ source files in Hinglish.

---

## Potential Viva Questions

### I. General Compiler Concepts

1.  **Phases of a Compiler:** What are the main phases of a compiler? (Lexical Analysis, Syntax Analysis/Parsing, Semantic Analysis, Intermediate Code Generation, Optimization, Target Code Generation). Which phases have we implemented so far?
2.  **Lexical Analysis:**
    - What is the role of a lexer (scanner)?
    - What is a "token"? Give examples from our Kaleidoscope lexer.
    - What are "lexemes"?
3.  **Syntax Analysis (Parsing):**
    - What is the role of a parser?
    - What is an Abstract Syntax Tree (AST)? How does it differ from a parse tree?
    - What is "operator precedence"? How is it handled in our parser? (Operator-precedence climbing).
    - What is "operator associativity"? (Though not explicitly handled with different associativities for the same precedence level in our current parser, it's a related concept).
    - What is recursive descent parsing? Is our parser an example of this?
4.  **Error Handling:** What are common types of errors a compiler can detect? (Lexical, Syntax, Semantic). How does our current compiler report errors?

### II. Kaleidoscope Language & Our Implementation Specifics

1.  **Lexer (`Lexer.cpp`, `Lexer.h`):**
    - Explain the `tokenize()` method in `Lexer.cpp`. How does it iterate through the source code?
    - How does the lexer differentiate between keywords, identifiers, and numbers?
    - How are comments (`#`) handled?
    - How are multi-character operators handled (if any, or how would they be)? (Currently, we only have single-character operators from the token string list).
    - What happens if an unrecognized character is found?
2.  **AST (`AST.h`):**
    - Why is `ExprAST` an abstract base class? What is a "pure virtual function"?
    - Explain the structure of `BinaryExprAST`. Why does it store `unique_ptr`s to its children?
    - How does `CallExprAST` represent function arguments?
    - What is the purpose of `PrototypeAST`? Why does it also inherit from `ExprAST`?
    - How does `FunctionAST` combine a prototype and a body?
3.  **Parser (`Parser.cpp`, `Parser.h`):**
    - What is the role of the `Token` enum in `Parser.h`?
    - Explain the `BinopPrecedence` map. How is it initialized and used?
    - Describe the functionality of `Parser::getNextToken()`. What were some of the challenges in getting this right?
    - How does `ParseIdentifierExpr()` distinguish between a variable access and a function call?
    - Explain the logic of `ParseBinOpRHS()`. How does it use `ExprPrec` and `TokPrec`?
    - How does `ParsePrototype()` handle different kinds of prototypes (normal functions vs. custom operators)?
    - How are top-level expressions (e.g., `1+2;`) handled by the parser? (Wrapped in `__anon_expr`).
    - What is the role of the main `Parse()` method in `Parser.cpp`? How does it handle different top-level constructs?
4.  **Language Features:**
    - How are function definitions (`def ...`) parsed?
    - How are external function declarations (`extern ...`) parsed?
    - How would you extend the parser to support `if/then/else` expressions fully (if not already)? (It's in the `Token` enum and `getNextToken` handles it, but `ParsePrimary` doesn't dispatch to a specific `ParseIfExpr`).
    - How are custom binary and unary operators defined in Kaleidoscope (based on our parser)?

### III. C++ Specifics

1.  **Smart Pointers:**
    - Why are `std::unique_ptr`s used for managing AST nodes? What benefits do they provide over raw pointers? (RAII, clear ownership, prevention of memory leaks).
    - What is `std::move`? Why is it frequently used with `std::unique_ptr` in our code (e.g., in constructors, `push_back`)?
2.  **Classes and Inheritance:**
    - Explain the concept of inheritance as used in `AST.h` (e.g., `NumberExprAST : public ExprAST`).
    - What is a virtual destructor, and why is it important in a base class like `ExprAST`?
3.  **Standard Library:**
    - What is the purpose of `<vector>`, `<string>`, `<map>`, `<memory>`, `<iostream>`, `<cctype>`?
    - What does `using namespace std;` do? What are potential issues with using it in header files? (Pollutes global namespace for all includers).
4.  **File Structure & Compilation:**
    - What is the purpose of include guards (`#ifndef FOO_H ... #endif`)?
    - What is the difference between `#include "file.h"` and `#include <file.h>`?
    - What does a `static` global variable like `BinopPrecedence` mean in `Parser.cpp`? (Internal linkage).
5.  **Error Handling in C++:**
    - How is `std::runtime_error` used in the Lexer?
    - How does the parser signal errors to its callers? (Often by returning `nullptr`).

### IV. Project Development & Debugging

1.  **Iterative Process:** This project was built iteratively. What are the advantages of such an approach?
2.  **Debugging:**
    - Describe a specific bug encountered during the development of the parser or lexer. How was it identified and fixed? (e.g., `CurrentToken` update logic, semicolon handling, argument parsing in `ParsePrototype`).
    - How did the `print()` methods in the AST nodes help in debugging?
    - How did `std::cerr` statements aid in debugging the parser?
3.  **Testing:** How was the compiler tested at various stages? (Primarily by running `main.cpp` with sample input and observing AST output or error messages). What further testing strategies could be employed? (Unit tests for lexer and parser components, more comprehensive test cases).
4.  **Design Choices:**
    - Why was the lexer designed to return a `vector<string>` of tokens initially? What are alternative approaches for lexer-parser interaction? (Parser pulls tokens one-by-one from lexer).
    - Discuss the decision to make `PrototypeAST` and `FunctionAST` inherit from `ExprAST`.
5.  **Future Extensions:**
    - What would be the next logical steps to make this a more complete compiler? (Semantic Analysis, LLVM IR Code Generation).
    - What kind of semantic checks would be needed for Kaleidoscope? (e.g., undefined variables, function call argument mismatch).

---
