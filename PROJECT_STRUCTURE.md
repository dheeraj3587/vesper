# Vesper Compiler Project Structure

```
vesper/
├── README.md              # Main project documentation
├── Makefile              # Build configuration
├── run_vesper.sh         # Convenient script to compile and run Vesper programs
├── .gitignore            # Git ignore patterns
│
├── src/                  # Source code
│   ├── main.cpp         # Compiler entry point
│   ├── Lexer.cpp        # Tokenization implementation
│   ├── Parser.cpp       # Parsing implementation
│   └── CodeGen.cpp      # Code generation implementation
│
├── include/              # Header files
│   ├── AST.h            # Abstract Syntax Tree definitions
│   ├── Lexer.h          # Lexer interface
│   ├── Parser.h         # Parser interface
│   └── CodeGen.h        # Code generator interface
│
├── examples/             # Example Vesper programs
│   ├── README.md        # Examples documentation
│   ├── hello_world.vsp  # Simple print example
│   ├── calculator.vsp   # Arithmetic operations demo
│   ├── fibonacci.vsp    # Fibonacci sequence generator
│   └── control_flow.vsp # Control structures demo
│
├── tests/                # Test suite
│   ├── unit/            # Unit tests
│   │   ├── test_lexer.cpp
│   │   ├── test_parser.cpp
│   │   └── test_ast.cpp
│   ├── integration/     # Integration tests
│   ├── examples/        # Test example programs
│   └── manual/          # Manual test files
│
├── scripts/              # Utility scripts
│   ├── setup/           # Setup and configuration scripts
│   │   ├── setup.sh
│   │   ├── linux_quickstart.sh
│   │   ├── linux_setup_instructions.md
│   │   └── linux_codegen_patch.cpp
│   └── testing/         # Testing scripts
│       ├── test_compiler.sh
│       ├── test_linux.sh
│       └── quick_test.sh
│
├── docs/                 # Documentation
│   ├── explanations/    # Detailed code explanations
│   └── summaries/       # Project summaries
│
└── build/               # Build artifacts (generated)
    ├── vesper          # Compiled compiler executable
    └── obj/            # Object files
```

## Directory Descriptions

### `/src` and `/include`

Core compiler implementation with clean separation between headers and implementation files.

### `/examples`

Ready-to-run example programs demonstrating Vesper language features. Each example is documented and can be run using `./run_vesper.sh examples/<filename>.vsp`.

### `/tests`

Comprehensive test suite including unit tests for individual components and integration tests for the full compiler pipeline.

### `/scripts`

Organized utility scripts:

- `setup/`: Platform-specific setup and configuration
- `testing/`: Automated testing scripts

### `/docs`

Project documentation including detailed explanations of the codebase and high-level summaries.

### `/build`

Generated during compilation. Contains the compiler executable and intermediate object files.
