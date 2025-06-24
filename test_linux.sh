#!/bin/bash

# Test script for Vesper compiler on Linux
# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "🚀 Vesper Compiler Test Suite for Linux"
echo "======================================="

# Check if we're on Linux
if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo -e "${YELLOW}Warning: This script is designed for Linux${NC}"
fi

# Clean and build
echo -e "\n${YELLOW}1. Cleaning and building the compiler...${NC}"
make clean
make

if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}"

# Create test directory
mkdir -p test_outputs

# Test 1: Basic arithmetic
echo -e "\n${YELLOW}2. Testing basic arithmetic...${NC}"
cat > test_outputs/test_arithmetic.vsp << 'EOF'
int a = 10;
int b = 20;
int sum = a + b;
int diff = b - a;
int prod = a * 2;
int div = b / 2;
EOF

./build/vesper test_outputs/test_arithmetic.vsp -o test_outputs/test_arithmetic
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Arithmetic test compiled successfully${NC}"
else
    echo -e "${RED}✗ Arithmetic test failed${NC}"
fi

# Test 2: Control flow
echo -e "\n${YELLOW}3. Testing control flow...${NC}"
cat > test_outputs/test_control.vsp << 'EOF'
int x = 5;
int result = 0;

if (x > 3) {
    result = 100;
}

int counter = 0;
while (counter < 3) {
    result = result + 10;
    counter = counter + 1;
}

for (int i = 0; i < 2; i = i + 1) {
    result = result + 5;
}
EOF

./build/vesper test_outputs/test_control.vsp -o test_outputs/test_control
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Control flow test compiled successfully${NC}"
else
    echo -e "${RED}✗ Control flow test failed${NC}"
fi

# Test 3: Complex expressions
echo -e "\n${YELLOW}4. Testing complex expressions...${NC}"
cat > test_outputs/test_complex.vsp << 'EOF'
int a = 5;
int b = 10;
int c = 15;

int result = (a + b) * c;
result = result / 3;

if (result > 50) {
    result = result - 10;
}

bool flag = result == 65;
if (flag) {
    result = 1000;
}
EOF

./build/vesper test_outputs/test_complex.vsp -o test_outputs/test_complex -v
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Complex expression test compiled successfully${NC}"
else
    echo -e "${RED}✗ Complex expression test failed${NC}"
fi

# Test 4: Nested loops
echo -e "\n${YELLOW}5. Testing nested structures...${NC}"
cat > test_outputs/test_nested.vsp << 'EOF'
int sum = 0;

for (int i = 0; i < 3; i = i + 1) {
    for (int j = 0; j < 2; j = j + 1) {
        sum = sum + i + j;
    }
}

if (sum > 5) {
    if (sum > 10) {
        sum = sum * 2;
    }
}
EOF

./build/vesper test_outputs/test_nested.vsp -o test_outputs/test_nested
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Nested structure test compiled successfully${NC}"
else
    echo -e "${RED}✗ Nested structure test failed${NC}"
fi

# Test 5: Assembly generation only
echo -e "\n${YELLOW}6. Testing assembly generation...${NC}"
./build/vesper test_outputs/test_arithmetic.vsp -S -o test_outputs/test_asm
if [ -f "test_outputs/test_asm.asm" ]; then
    echo -e "${GREEN}✓ Assembly generation successful${NC}"
    echo "Generated assembly preview:"
    head -n 20 test_outputs/test_asm.asm
else
    echo -e "${RED}✗ Assembly generation failed${NC}"
fi

# Summary
echo -e "\n${YELLOW}Test Summary:${NC}"
echo "=================================="
ls -la test_outputs/
echo "=================================="

# Check if binaries can be assembled (Linux-specific)
echo -e "\n${YELLOW}7. Testing binary generation on Linux...${NC}"
if command -v nasm &> /dev/null; then
    echo "NASM found. Attempting to assemble..."
    
    # For Linux, we need to modify the assembly slightly
    sed 's/_main/main/g' test_outputs/test_arithmetic.asm > test_outputs/test_linux.asm
    
    # Try to assemble with nasm
    nasm -f elf64 test_outputs/test_linux.asm -o test_outputs/test_linux.o
    
    if [ $? -eq 0 ]; then
        # Try to link
        ld -o test_outputs/test_linux_binary test_outputs/test_linux.o -e main
        if [ $? -eq 0 ]; then
            echo -e "${GREEN}✓ Linux binary created successfully${NC}"
        else
            echo -e "${YELLOW}Assembly successful but linking failed (this is expected)${NC}"
        fi
    fi
else
    echo -e "${YELLOW}NASM not found. Skipping assembly test.${NC}"
fi

echo -e "\n${GREEN}Test suite completed!${NC}" 