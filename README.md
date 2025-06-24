# Vesper Programming Language Compiler

A modern, feature-complete compiler for the Vesper programming language, implementing C-style syntax with comprehensive control flow support.

## Features

✅ **Complete Language Support:**

- Variable declarations with type inference (`int x = 10;`)
- All arithmetic operations (`+`, `-`, `*`, `/`)
- Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)
- Control flow statements (`if`, `while`, `for`)
- Compound statements and nested structures
- Assignment expressions and complex expressions

✅ **Professional Code Generation:**

- x86-64 assembly output
- Proper stack management
- Type-aware variable storage
- Optimized register usage
- Label generation for control flow

✅ **Robust Architecture:**

- Modular lexer, parser, and code generator
- Comprehensive AST representation
- Extensive test suite
- Clean separation of concerns

## Project Structure

```
vesper/
├── src/                    # Source code
│   ├── main.cpp           # Main compiler driver
│   ├── Lexer.cpp          # Tokenization
│   ├── Parser.cpp         # Syntax analysis
│   └── CodeGen.cpp        # Code generation
├── include/               # Header files
│   ├── AST.h              # Abstract syntax tree
│   ├── Lexer.h            # Lexer interface
│   ├── Parser.h           # Parser interface
│   └── CodeGen.h          # Code generator interface
├── tests/                 # Test suite
│   ├── examples/          # Example programs
│   ├── unit/              # Unit tests
│   └── integration/       # Integration tests
├── docs/                  # Documentation
├── build/                 # Build artifacts (generated)
└── README.md
```

## Quick Start

### Building the Compiler

```bash
# Build the main compiler
make

# Build and run all tests
make test

# Build and test with examples
make examples
```

### Using the Compiler

The easiest way to compile and run a Vesper program:

```bash
# Using the convenient run script
./run_vesper.sh examples/hello_world.vsp

# Or manually compile
./build/vesper program.vsp

# This generates assembly output in output.asm
```

## Example Programs

### Basic Variables and Arithmetic

```c
// File: tests/examples/variables_and_expressions.vsp
int x = 5;
int y = 10;
int result = x + y;
result = result * 2;
```

### Control Flow

```c
// File: tests/examples/basic_control_flow.vsp
int x = 10;

if (x > 5) {
    x = x * 2;
}

while (x > 0) {
    x = x - 1;
}

for (int i = 0; i < 5; i = i + 1) {
    x = x + i;
}
```

### Nested Structures

```c
// File: tests/examples/nested_loops.vsp
for (int row = 0; row < 3; row = row + 1) {
    for (int col = 0; col < 3; col = col + 1) {
        int value = row * col;
        if (value > 2) {
            value = value * 2;
        }
    }
}
```

## Language Reference

### Data Types

- `int` - 32-bit signed integers
- `float` - 32-bit floating point
- `double` - 64-bit floating point
- `char` - 8-bit characters
- `bool` - Boolean values

### Operators

- **Arithmetic:** `+`, `-`, `*`, `/`
- **Comparison:** `==`, `!=`, `<`, `>`, `<=`, `>=`
- **Assignment:** `=`
- **Logical:** `!` (unary not)

### Control Flow

- **Conditional:** `if (condition) { ... }`, `if (condition) { ... } else { ... }`
- **Loops:** `while (condition) { ... }`, `for (init; condition; update) { ... }`

### Variables

```c
int x;                    // Declaration
int y = 10;              // Declaration with initialization
x = 5;                   // Assignment
int result = x + y;      // Expression assignment
```

## Development

### Running Tests

```bash
# Run all tests
make test

# Run specific test categories
make test-unit          # Unit tests only
make test-integration   # Integration tests only
make examples          # Test with example files

# Run individual component tests
make test-lexer        # Test tokenization
make test-parser       # Test parsing
make test-ast          # Test AST generation
```

### Building and Testing

```bash
# Clean build
make clean
make

# Full test suite
make test-all

# Test legacy compatibility
make test-legacy
```

### Code Formatting

```bash
# Format all source code
make format
```

## Architecture

### Compilation Pipeline

1. **Lexical Analysis** (`Lexer.cpp`)

   - Tokenizes source code
   - Handles keywords, operators, literals
   - Supports C-style and STL tokens

2. **Syntax Analysis** (`Parser.cpp`)

   - Builds Abstract Syntax Tree (AST)
   - Implements recursive descent parser
   - Handles operator precedence

3. **Code Generation** (`CodeGen.cpp`)
   - Traverses AST to generate assembly
   - Manages symbol tables and stack frames
   - Produces x86-64 assembly output

### Key Components

- **AST Nodes** (`AST.h`) - Complete representation of language constructs
- **Symbol Management** - Type-aware variable tracking
- **Label Generation** - Unique labels for control flow
- **Stack Management** - Proper stack frame handling

## Testing

The project includes comprehensive testing:

- **Unit Tests** - Test individual components
- **Integration Tests** - Test complete compilation pipeline
- **Example Programs** - Real-world usage scenarios
- **Legacy Compatibility** - Support for older syntax

## Generated Assembly

The compiler produces efficient x86-64 assembly:

```asm
section .text
global _main
_main:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov rax, 10
    mov [rbp-8], eax
    # ... rest of program
```

Features:

- Proper function prologue/epilogue
- Stack-based variable storage
- Type-aware load/store operations
- Conditional jumps for control flow
- Loop constructs with labels

## Contributing

1. Follow the existing code style
2. Add tests for new features
3. Update documentation
4. Ensure all tests pass

## License

[Add your license information here]

## Acknowledgments

Built as a comprehensive compiler implementation demonstrating:

- Lexical and syntax analysis
- Abstract syntax tree construction
- Code generation for x86-64
- Professional software development practices
