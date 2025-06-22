# Vesper Compiler

A comprehensive compiler for the Kaleidoscope language with extended C language keywords and STL library support.

## 📁 Project Structure

```
vesper/
├── src/                    # Source code files
│   ├── main.cpp           # Main driver program
│   ├── Lexer.cpp          # Lexical analyzer implementation
│   └── Parser.cpp         # Parser implementation
├── include/               # Header files
│   ├── Lexer.h           # Lexer interface
│   ├── Parser.h          # Parser interface
│   └── AST.h             # Abstract Syntax Tree definitions
├── tests/                 # Test files
│   ├── test.vsp          # Basic Kaleidoscope test
│   └── test_c_stl.vsp    # C/STL comprehensive test
├── docs/                  # Documentation
│   ├── explanations/     # Code explanations (Hinglish)
│   └── summaries/        # Project summaries
├── examples/              # Example programs (future)
├── build/                 # Build artifacts (generated)
│   ├── obj/              # Object files
│   └── vesper            # Executable
├── Makefile              # Build configuration
└── README.md             # This file
```

## 🚀 Features

### Core Compiler Components

- **Lexer**: Advanced tokenizer with C language keywords and STL library support
- **Parser**: Recursive descent parser with operator precedence handling
- **AST**: Abstract Syntax Tree with comprehensive node types

### Language Support

- **C Language Keywords**: All standard C/C++ keywords including C99 and C11
- **STL Library**: Complete Standard Template Library support
  - Containers: `vector`, `list`, `map`, `set`, `unordered_map`, etc.
  - Algorithms: `sort`, `find`, `accumulate`, `transform`, etc.
  - Utilities: `make_pair`, `make_unique`, `make_shared`, etc.
  - I/O: `cout`, `cin`, `endl`, etc.
  - Memory Management: `unique_ptr`, `shared_ptr`, `allocator`, etc.
- **Multi-character Operators**: `++`, `--`, `->`, `::`, `<=`, `>=`, `==`, `!=`, `&&`, `||`, etc.
- **String and Character Literals**: Full support with escape sequences
- **Comments**: Both `#` and `//` style comments
- **Preprocessor Directives**: `#include`, `#define`, etc.

## 🛠️ Building

### Prerequisites

- GCC or Clang with C++17 support
- Make

### Build Commands

```bash
# Build the compiler
make

# Clean build artifacts
make clean

# Run tests
make test

# Show help
make help
```

## 📖 Usage

### Basic Usage

```bash
# Compile a Vesper file
./build/vesper my_program.vsp

# Run tests
make test
```

### Example Programs

#### Basic Kaleidoscope (`tests/test.vsp`)

```kaleidoscope
def average(x, y)
    (x + y) / 2.0;

average(10.0, 20.0);
```

#### C/STL Extended (`tests/test_c_stl.vsp`)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::sort(numbers.begin(), numbers.end());

    for (auto n : numbers) {
        std::cout << n << " ";
    }
    return 0;
}
```

## 📚 Documentation

### Code Explanations

Detailed line-by-line explanations of the source code in Hinglish:

- `docs/explanations/Lexer.h.md` - Lexer interface explanation
- `docs/explanations/Lexer.cpp.md` - Lexer implementation explanation
- `docs/explanations/Parser.h.md` - Parser interface explanation
- `docs/explanations/Parser.cpp.md` - Parser implementation explanation
- `docs/explanations/AST.h.md` - AST structure explanation

### Project Summaries

- `docs/summaries/PROJECT_SUMMARY.md` - Comprehensive project overview
- `docs/summaries/CODE_EXPLANATION.md` - General code explanation

## 🔧 Development

### Adding New Features

1. **Lexer Extensions**: Add keywords to the appropriate sets in `src/Lexer.cpp`
2. **Parser Extensions**: Add parsing rules in `src/Parser.cpp`
3. **AST Extensions**: Add new node types in `include/AST.h`

### Testing

```bash
# Run all tests
make test

# Test specific file
./build/vesper tests/test_c_stl.vsp
```

### Build System

The project uses a simple Makefile-based build system:

- Object files are placed in `build/obj/`
- Final executable is `build/vesper`
- Headers are in `include/` directory

## 🎯 Current Status

### ✅ Completed

- [x] Lexer with C keywords and STL support
- [x] Parser with operator precedence
- [x] AST structure
- [x] Multi-character operators
- [x] String and character literals
- [x] Comments and preprocessor directives
- [x] Organized project structure
- [x] Comprehensive documentation

### 🚧 In Progress

- [ ] Code generation (LLVM IR)
- [ ] Semantic analysis
- [ ] Error recovery mechanisms

### 📋 Planned

- [ ] Control flow constructs (if/then/else, loops)
- [ ] Variable declarations
- [ ] Type checking
- [ ] Optimization passes
- [ ] More comprehensive test suite

## 🤝 Contributing

1. Follow the existing code structure
2. Add tests for new features
3. Update documentation
4. Use the organized directory structure

## 📄 License

This project is part of a compiler construction course and is for educational purposes.

---

**Note**: This compiler currently focuses on lexical analysis and parsing. Code generation and semantic analysis are planned for future development.
