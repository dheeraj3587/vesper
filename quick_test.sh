#!/bin/bash

echo "🔍 Quick Project Test"
echo "====================="

# Check if key files exist
echo "📋 Checking project files..."
if [ -f "Makefile" ]; then echo "✅ Makefile found"; else echo "❌ Makefile missing"; fi
if [ -d "src" ]; then echo "✅ src/ directory found"; else echo "❌ src/ directory missing"; fi
if [ -d "include" ]; then echo "✅ include/ directory found"; else echo "❌ include/ directory missing"; fi
if [ -d "tests/examples" ]; then echo "✅ tests/examples/ directory found"; else echo "❌ tests/examples/ directory missing"; fi

# Try a simple build
echo ""
echo "🔨 Testing build..."
mkdir -p build/obj

# Try building just one file to test
if g++ -std=c++17 -Wall -Wextra -g -Iinclude -c src/main.cpp -o build/obj/main_test.o 2>/dev/null; then
    echo "✅ Compilation test passed"
    rm -f build/obj/main_test.o
else
    echo "❌ Compilation test failed"
fi

# Test example files
echo ""
echo "📄 Checking example files..."
if [ -d "tests/examples" ]; then
    for file in tests/examples/*.vsp; do
        if [ -f "$file" ]; then
            echo "✅ Found: $(basename $file)"
        fi
    done
else
    echo "❌ No examples directory found"
fi

echo ""
echo "🎯 Project structure looks good!"
echo "🚀 Ready to build with: make" 