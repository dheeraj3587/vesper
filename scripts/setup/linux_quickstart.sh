#!/bin/bash

echo "🚀 Vesper Compiler - Linux Quick Start"
echo "===================================="

# Create a simple test program
cat > test_program.vsp << 'EOF'
// Calculate factorial of 5
int n = 5;
int result = 1;
int i = 1;

while (i <= n) {
    result = result * i;
    i = i + 1;
}

// Result should be 120
EOF

echo "📝 Created test_program.vsp"
echo ""
echo "On your Linux machine, run these commands:"
echo ""
echo "1. Build the compiler:"
echo "   make clean && make"
echo ""
echo "2. Compile the test program:"
echo "   ./build/vesper test_program.vsp -o factorial"
echo ""
echo "3. Run the executable:"
echo "   ./factorial"
echo "   echo \"Exit code: \$?\""
echo ""
echo "The compiler will automatically:"
echo "- Detect Linux platform"
echo "- Generate 'main' instead of '_main'"
echo "- Use 'nasm -f elf64' for Linux"
echo "- Link with 'ld' for Linux ELF binary"
echo ""
echo "The modified CodeGen.cpp already includes all Linux support!" 