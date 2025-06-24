#!/bin/bash

# Check if a file was provided
if [ $# -eq 0 ]; then
    echo "Usage: ./run_vesper.sh <filename.vsp>"
    exit 1
fi

# Get the input file
INPUT_FILE=$1
BASE_NAME="${INPUT_FILE%.vsp}"

# Check if file exists
if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File '$INPUT_FILE' not found!"
    exit 1
fi

# Compile with Vesper
echo "🔨 Compiling $INPUT_FILE..."
./build/vesper "$INPUT_FILE"

# Check for assembly file (compiler generates program.asm by default)
ASM_FILE="program.asm"
if [ ! -f "$ASM_FILE" ]; then
    echo "❌ Compilation failed - no assembly file generated!"
    exit 1
fi

# Assemble and link for Linux (ELF64)
echo "🔧 Assembling for Linux..."
nasm -f elf64 "$ASM_FILE" -o output.o

if [ $? -ne 0 ]; then
    echo "❌ Assembly failed!"
    rm -f "$ASM_FILE" output.o
    exit 1
fi

echo "🔗 Linking..."
ld -o "$BASE_NAME" output.o -e _start

if [ $? -ne 0 ]; then
    echo "❌ Linking failed!"
    rm -f "$ASM_FILE" output.o
    exit 1
fi

# Clean up intermediate files
rm -f "$ASM_FILE" output.o

echo "✅ Successfully compiled to $BASE_NAME"
echo "🚀 Running program..."
echo "-------------------"

# Run the program
./"$BASE_NAME"
RESULT=$?

echo "-------------------"
echo "Program exited with code: $RESULT" 