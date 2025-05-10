**Vesper** is a statically-typed, multi-paradigm language powered by LLVM. It blends functional and imperative styles into a clean, Python-inspired syntax while delivering native performance across x86\_64, ARM, and WebAssembly targets.

**Key Highlights**

* **Type Inference & Safety**
  A strong, inference-driven system with optional annotations, immutable-by-default variables, pattern matching, and compile-time checks.
* **Expressive Syntax**
  Lightweight, indentation-friendly design for readability—think concise declarations, `match` expressions, and first-class functions.
* **LLVM Integration**
  Frontend (in C++/Rust) lowers AST into LLVM IR, leveraging O2/LTO optimizations and ORC JIT for REPL support.
* **Concurrency & Macros**
  Built-in async/await tasks with channels, plus a hygienic macro system for extending the language without sacrificing tooling.
* **Interop & Tooling**
  Zero-cost FFI with C (and other LLVM targets), and a simple CLI (`vesper build`, `run`, `test`) that handles compilation, linking, and packaging.

**Getting Started**

1. **Prototype syntax** with simple “Hello, World!” snippets.
2. **Implement lexer/parser** to generate an AST.
3. **Emit LLVM IR** for core constructs and hook into the optimizer.
4. **Build the type system** and refine error messages.
5. **Expand the standard library** to include collections, I/O, and concurrency primitives.

Vesper combines readability, safety, and performance—making it ideal for systems programming, scripting, and rapid prototyping.
