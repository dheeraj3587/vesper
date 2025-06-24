#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "🚀 Vesper Compiler Test Suite"
echo "============================"

# Function to test a single file
test_file() {
    local test_file=$1
    local expected_result=$2
    local description=$3
    
    echo -n "Testing $description... "
    
    # Compile the Vesper code
    ./build/vesper "$test_file" 2>/dev/null
    
    if [ ! -f "output.asm" ]; then
        echo -e "${RED}✗ Failed to generate assembly${NC}"
        return 1
    fi
    
    # Assemble and link
    nasm -f macho64 output.asm -o output.o 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Assembly failed${NC}"
        rm -f output.asm output.o
        return 1
    fi
    
    ld -o output output.o -lSystem -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib 2>/dev/null
    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ Linking failed${NC}"
        rm -f output.asm output.o
        return 1
    fi
    
    # Run and check result
    ./output
    result=$?
    
    if [ "$result" -eq "$expected_result" ]; then
        echo -e "${GREEN}✓ Passed (returned $result)${NC}"
        rm -f output output.asm output.o
        return 0
    else
        echo -e "${RED}✗ Failed (expected $expected_result, got $result)${NC}"
        rm -f output output.asm output.o
        return 1
    fi
}

# Build the compiler
echo "Building compiler..."
make clean >/dev/null 2>&1
make all >/dev/null 2>&1

if [ ! -f "build/vesper" ]; then
    echo -e "${RED}Failed to build compiler!${NC}"
    exit 1
fi

echo -e "${GREEN}Compiler built successfully!${NC}"
echo ""

# Run tests
echo "Running Feature Tests:"
echo "---------------------"

# Test variables and arithmetic
test_file "tests/examples/test_variables.vsp" 25 "Variables and arithmetic"

# Test if statements
test_file "tests/examples/test_simple_if.vsp" 5 "Simple if statement"

# Test while loops
test_file "tests/examples/test_simple_while.vsp" 0 "Simple while loop"

# Test for loops
test_file "tests/examples/test_simple_for.vsp" 10 "Simple for loop"

# Test complex control flow
test_file "tests/examples/basic_control_flow.vsp" 2 "Basic control flow"

# Test nested structures
test_file "tests/examples/nested_loops.vsp" 30 "Nested loops"

echo ""
echo "Running Unit Tests:"
echo "------------------"
make test-unit 2>/dev/null

echo ""
echo "Test Summary Complete!"
echo "===================="

# Cleanup
rm -f output output.asm output.o 