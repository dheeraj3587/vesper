# Vesper Compiler - Linux Setup Instructions

## Prerequisites

Make sure you have these installed on your Linux system:

```bash
sudo apt update
sudo apt install build-essential nasm git
```

## Building the Compiler on Linux

1. Clone or copy your project to the Linux machine
2. Navigate to the project directory
3. Build the compiler:

```bash
make clean
make
```

## Using the Compiler on Linux

The compiler will automatically detect that it's running on Linux and generate Linux-compatible binaries.

### Example 1: Simple Test

```bash
# Compile a .vsp file to executable
./build/vesper simple_test.vsp -o my_program

# Run the generated executable
./my_program
echo "Exit code: $?"
```

### Example 2: Generate Assembly Only

```bash
# Generate assembly without creating binary
./build/vesper simple_test.vsp -S -o my_program

# View the generated assembly
cat my_program.asm
```

### Example 3: Verbose Output

```bash
# See detailed compilation process
./build/vesper simple_test.vsp -o my_program -v
```

## How It Works

When running on Linux, the compiler:

1. Generates assembly with `main` instead of `_main`
2. Uses `nasm -f elf64` for 64-bit Linux object files
3. Links with `ld` using Linux-specific options
4. Creates native Linux ELF executables

## Testing Script

Run the comprehensive test suite:

```bash
chmod +x test_linux.sh
./test_linux.sh
```

## Troubleshooting

### If linking fails:

1. Make sure nasm is installed: `which nasm`
2. Check that you're on a 64-bit system: `uname -m`
3. Try the assembly-only option with `-S` flag

### If the binary doesn't run:

1. Check permissions: `chmod +x your_program`
2. Check the file type: `file your_program`
3. It should show: "ELF 64-bit LSB executable"

## Platform Detection

The compiler automatically detects the platform:

- On Linux: Generates Linux ELF binaries
- On macOS: Generates Mach-O binaries

No code changes needed - just compile and run!
