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

if [ ! -f "output.asm" ]; then
    echo "❌ Compilation failed!"
    exit 1
fi

# Detect OS and assemble/link accordingly
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    echo "🔧 Assembling for macOS..."
    nasm -f macho64 output.asm -o output.o
    
    echo "🔗 Linking..."
    ld -o "$BASE_NAME" output.o -lSystem -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib
else
    # Linux
    echo "🔧 Assembling for Linux..."
    nasm -f elf64 output.asm -o output.o
    
    echo "🔗 Linking..."
    ld -o "$BASE_NAME" output.o -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2 -e _start
fi

# Check if linking succeeded
if [ ! -f "$BASE_NAME" ]; then
    echo "❌ Linking failed!"
    rm -f output.asm output.o
    exit 1
fi

# Clean up intermediate files
rm -f output.asm output.o

echo "✅ Successfully compiled to $BASE_NAME"
echo "🚀 Running program..."
echo "-------------------"

# Run the program
./"$BASE_NAME"
RESULT=$?

echo "-------------------"
echo "Program exited with code: $RESULT" 