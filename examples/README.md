# Vesper Examples

This directory contains example programs written in the Vesper programming language.

## Running Examples

To run any example, use the provided `run_vesper.sh` script from the project root:

```bash
./run_vesper.sh examples/hello_world.vsp
```

## Available Examples

### 1. hello_world.vsp

The simplest Vesper program - prints a number to demonstrate basic output.

### 2. calculator.vsp

Demonstrates arithmetic operations including addition, subtraction, multiplication, and division.

### 3. fibonacci.vsp

Generates and prints the first 10 numbers in the Fibonacci sequence using loops and variables.

### 4. control_flow.vsp

Comprehensive demonstration of control flow structures:

- If-else statements
- While loops
- For loops
- Nested loops

## Language Features Demonstrated

- **Variable Declaration**: `int x = 10;`
- **Arithmetic**: `+`, `-`, `*`, `/`
- **Comparison**: `>`, `<`, `==`, `!=`, `>=`, `<=`
- **Control Flow**: `if`, `else`, `while`, `for`
- **Output**: `print(value);`

## Writing Your Own Programs

Create a new `.vsp` file and use the language features shown in these examples. The Vesper language currently supports:

- Integer variables
- Basic arithmetic operations
- Control flow statements
- Print function for output

Example structure:

```c
int x = 5;
int y = 10;

if (x < y) {
    print(x + y);
}
```
