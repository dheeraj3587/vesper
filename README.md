# Vesper Programming Language Compiler 🚀

A modern, feature-complete compiler for the **Vesper** programming language, implementing C-style syntax with comprehensive control flow support and code generation for x86-64 architecture.

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![Language](https://img.shields.io/badge/language-C++-blue.svg)]()
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey.svg)]()

## ✨ Features

### 🎯 **Complete Language Support**

- ✅ Variable declarations with type inference (`int x = 10;`)
- ✅ All arithmetic operations (`+`, `-`, `*`, `/`)
- ✅ Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)
- ✅ Control flow statements (`if`, `else`, `while`, `for`)
- ✅ Compound statements and nested structures
- ✅ Assignment expressions and complex expressions
- ✅ Print function for output (`print(value);`)

### 🔧 **Professional Code Generation**

- ✅ x86-64 assembly output
- ✅ Proper stack management
- ✅ Type-aware variable storage
- ✅ Optimized register usage
- ✅ Label generation for control flow
- ✅ Cross-platform support (macOS & Linux)

### 🏗️ **Robust Architecture**

- ✅ Modular lexer, parser, and code generator
- ✅ Comprehensive AST representation
- ✅ Extensive test suite with examples
- ✅ Clean separation of concerns
- ✅ Professional project structure

## 🚀 Quick Start

### Prerequisites

- **C++ Compiler**: GCC or Clang with C++17 support
- **NASM**: Netwide Assembler for assembly compilation
- **Make**: Build system
- **Operating System**: macOS or Linux

### Installation

```bash
# Clone the repository
git clone https://github.com/your-username/vesper.git
cd vesper

# Build the compiler
make

# Test with examples
./run_vesper.sh examples/hello_world.vsp
```

### Hello World

Create a file `hello.vsp`:

```c
// Hello World in Vesper
print(42);
```

Compile and run:

```bash
./run_vesper.sh hello.vsp
```

Output:

```
42
```

## 📚 Examples

The `examples/` directory contains comprehensive example programs:

### 🔥 **Featured Examples**

| Example                                         | Description           | Features Demonstrated             |
| ----------------------------------------------- | --------------------- | --------------------------------- |
| [`hello_world.vsp`](examples/hello_world.vsp)   | Simple output         | Basic print functionality         |
| [`calculator.vsp`](examples/calculator.vsp)     | Arithmetic operations | Variables, math, expressions      |
| [`fibonacci.vsp`](examples/fibonacci.vsp)       | Fibonacci sequence    | Loops, variables, calculations    |
| [`control_flow.vsp`](examples/control_flow.vsp) | Control structures    | If/else, while, for, nested loops |

### Running Examples

```bash
# Run any example
./run_vesper.sh examples/fibonacci.vsp

# Expected output: 0 1 1 2 3 5 8 13 21 34
```

## 🛠️ Language Reference

### Data Types

```c
int x = 10;        // Integer variables
```

### Operators

```c
// Arithmetic
int sum = a + b;   // Addition
int diff = a - b;  // Subtraction
int prod = a * b;  // Multiplication
int quot = a / b;  // Division

// Comparison
if (x > 5) { ... }     // Greater than
if (x < 10) { ... }    // Less than
if (x == 5) { ... }    // Equal to
if (x != 0) { ... }    // Not equal to
```

### Control Flow

```c
// If statements
if (condition) {
    // code
} else {
    // code
}

// While loops
while (condition) {
    // code
}

// For loops
for (int i = 0; i < 10; i = i + 1) {
    // code
}
```

### Output

```c
print(42);         // Print integer
print(x + y);      // Print expression result
```

## 🧪 Testing

### Run All Tests

```bash
# Complete test suite
make test

# Quick project validation
./scripts/testing/quick_test.sh

# Comprehensive compiler tests
./scripts/testing/test_compiler.sh
```

### Create Your Own Tests

```c
// test_program.vsp
int a = 5;
int b = 10;

print(a + b);  // Should output: 15

if (a < b) {
    print(1);  // Should output: 1
}
```

Run your test:

```bash
./run_vesper.sh test_program.vsp
```

## 📁 Project Structure

```
vesper/
├── README.md              # This file
├── Makefile              # Build configuration
├── run_vesper.sh         # Convenient compilation script
│
├── src/                  # Source code
│   ├── main.cpp         # Compiler entry point
│   ├── Lexer.cpp        # Tokenization
│   ├── Parser.cpp       # Syntax analysis
│   └── CodeGen.cpp      # Code generation
│
├── include/              # Header files
│   ├── AST.h            # Abstract Syntax Tree
│   ├── Lexer.h          # Lexer interface
│   ├── Parser.h         # Parser interface
│   └── CodeGen.h        # Code generator interface
│
├── examples/             # Example programs
│   ├── hello_world.vsp  # Simple hello world
│   ├── calculator.vsp   # Arithmetic demo
│   ├── fibonacci.vsp    # Fibonacci sequence
│   └── control_flow.vsp # Control structures
│
├── tests/                # Test suite
│   ├── unit/            # Unit tests
│   ├── integration/     # Integration tests
│   └── examples/        # Test examples
│
├── scripts/              # Utility scripts
│   ├── setup/           # Setup scripts
│   └── testing/         # Testing scripts
│
└── docs/                 # Documentation
```

## 🔧 Development

### Building from Source

```bash
# Clean build
make clean
make

# Debug build
make debug

# Release build
make release
```

### Code Architecture

#### Compilation Pipeline

1. **Lexical Analysis** → Tokenize source code
2. **Syntax Analysis** → Build Abstract Syntax Tree (AST)
3. **Code Generation** → Generate x86-64 assembly
4. **Assembly & Linking** → Create executable binary

#### Key Components

- **Lexer**: Converts source code into tokens
- **Parser**: Builds AST from tokens using recursive descent
- **CodeGen**: Traverses AST to generate assembly code
- **AST**: Comprehensive node types for all language constructs

## 🌐 Platform Support

| Platform    | Status             | Notes                       |
| ----------- | ------------------ | --------------------------- |
| **macOS**   | ✅ Fully Supported | Native development platform |
| **Linux**   | ✅ Fully Supported | Tested on Ubuntu/Debian     |
| **Windows** | 🔄 In Progress     | WSL recommended             |

## 🤝 Contributing

We welcome contributions! Here's how to get started:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Development Guidelines

- Follow existing code style
- Add tests for new features
- Update documentation
- Ensure all tests pass

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Built with modern C++17 features
- Inspired by traditional compiler design principles
- Thanks to the open-source community for tools and inspiration

## 📞 Support

- 📖 **Documentation**: Check the [`docs/`](docs/) directory
- 🐛 **Issues**: Report bugs via GitHub Issues
- 💬 **Discussions**: Use GitHub Discussions for questions
- 📧 **Contact**: [Your email/contact info]

---

**Vesper** - _A modern programming language for the next generation_ 🚀
