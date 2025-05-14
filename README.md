# Kaleidoscope Compiler

This project is a compiler for the Kaleidoscope language, a simple procedural language often used as a tutorial example for compiler construction (famously in the LLVM tutorial).

## Features

*   **Lexer**: Tokenizes the Kaleidoscope source code.
*   **Parser**: Parses the token stream into an Abstract Syntax Tree (AST).
*   **AST**: Defines the structure of the Kaleidoscope language, including expressions, function definitions, and prototypes.

## Language Constructs Supported

Currently, the parser and AST support:

*   Function Definitions (`def`)
*   External Function Declarations (`extern`)
*   Primary Expressions:
    *   Numeric Literals (e.g., `1.0`, `42`)
    *   Variable References (e.g., `x`, `myVar`)
    *   Parenthesized Expressions (e.g., `(a + b)`)
*   Binary Expressions with operator precedence (e.g., `a + b * c`)
*   Function Calls (e.g., `foo(a, b)`)

## Components

*   `src/Lexer.h`, `src/Lexer.cpp`: The lexical analyzer.
*   `src/Parser.h`, `src/Parser.cpp`: The parser that builds the AST.
*   `src/AST.h`: The definition of the Abstract Syntax Tree nodes.

## Getting Started

This project is currently under development. The next steps involve:

1.  **Implementing a `main.cpp`**: To tie the lexer and parser together and provide a driver for the compiler.
2.  **Code Generation**: Implementing a visitor pattern or similar mechanism to traverse the AST and generate code (e.g., LLVM IR or another target).
3.  **Error Handling**: Enhancing error reporting throughout the lexing and parsing stages.
4.  **Expanding Language Features**: Adding more features to Kaleidoscope as needed (e.g., if/then/else, for loops).

## How to Build (Placeholder)

Instructions on how to build the compiler will be added once the project is in a more complete state (e.g., using CMake or a simple Makefile).

```bash
# Example build commands (to be updated)
# mkdir build
# cd build
# cmake ..
# make
```

## How to Use (Placeholder)

Instructions on how to run the compiler with an example Kaleidoscope file.

```bash
# Example usage (to be updated)
# ./kaleidoscope_compiler my_program.k
```
