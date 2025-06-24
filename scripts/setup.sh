#!/bin/bash

# Vesper Compiler Project Setup Script
# This script helps organize and test the project structure

echo "🚀 Setting up Vesper Compiler Project..."

# Create necessary directories
echo "📁 Creating directory structure..."
mkdir -p scripts build/obj tests/output docs/generated

# Clean up old build artifacts from root
echo "🧹 Cleaning build artifacts..."
rm -f *.o *.asm output test_*.vsp

# Check if Makefile exists
if [ ! -f "Makefile" ]; then
    echo "❌ Makefile not found!"
    exit 1
fi

# Build the project
echo "🔨 Building compiler..."
echo "Running: make clean && make"

# Try to clean first, but don't fail if clean doesn't work
if make clean 2>/dev/null; then
    echo "✅ Clean successful"
else
    echo "⚠️  Clean failed or not needed, continuing..."
fi

# Now try to build
if make; then
    echo "✅ Build successful!"
else
    echo "❌ Build failed!"
    echo "📝 Trying alternative build approach..."
    
    # Create build directory if it doesn't exist
    mkdir -p build/obj
    
    # Try building manually
    echo "Building manually..."
    if g++ -std=c++17 -Wall -Wextra -g -Iinclude -c src/main.cpp -o build/obj/main.o && \
       g++ -std=c++17 -Wall -Wextra -g -Iinclude -c src/Lexer.cpp -o build/obj/Lexer.o && \
       g++ -std=c++17 -Wall -Wextra -g -Iinclude -c src/Parser.cpp -o build/obj/Parser.o && \
       g++ -std=c++17 -Wall -Wextra -g -Iinclude -c src/CodeGen.cpp -o build/obj/CodeGen.o && \
       g++ build/obj/main.o build/obj/Lexer.o build/obj/Parser.o build/obj/CodeGen.o -o build/vesper; then
        echo "✅ Manual build successful!"
    else
        echo "❌ Manual build also failed!"
        exit 1
    fi
fi

# Check if the executable was created
if [ ! -f "build/vesper" ]; then
    echo "❌ Executable not found!"
    exit 1
fi

echo "✅ Executable created: build/vesper"

# Test with examples if they exist
echo "🧪 Testing with examples..."
if [ -d "tests/examples" ] && [ "$(ls -A tests/examples/*.vsp 2>/dev/null)" ]; then
    echo "Found example files, testing..."
    success_count=0
    total_count=0
    
    for file in tests/examples/*.vsp; do
        if [ -f "$file" ]; then
            echo "Testing $file..."
            total_count=$((total_count + 1))
            if ./build/vesper "$file" >/dev/null 2>&1; then
                echo "  ✅ $file - PASSED"
                success_count=$((success_count + 1))
            else
                echo "  ❌ $file - FAILED"
            fi
        fi
    done
    
    echo "📊 Test Results: $success_count/$total_count passed"
else
    echo "⚠️  No example files found to test"
fi

# Display project status
echo ""
echo "📊 Project Status:"
if [ -d "src" ]; then
    echo "├── Source files: $(find src -name '*.cpp' 2>/dev/null | wc -l | tr -d ' ') files"
else
    echo "├── Source files: 0 files (src directory not found)"
fi

if [ -d "include" ]; then
    echo "├── Header files: $(find include -name '*.h' 2>/dev/null | wc -l | tr -d ' ') files"
else
    echo "├── Header files: 0 files (include directory not found)"
fi

if [ -d "tests/examples" ]; then
    echo "├── Example files: $(find tests/examples -name '*.vsp' 2>/dev/null | wc -l | tr -d ' ') files"
else
    echo "├── Example files: 0 files"
fi

if [ -d "tests/unit" ]; then
    echo "├── Unit tests: $(find tests/unit -name '*.cpp' 2>/dev/null | wc -l | tr -d ' ') files"
else
    echo "├── Unit tests: 0 files"
fi

if [ -d "docs" ]; then
    echo "└── Documentation: $(find docs -name '*.md' 2>/dev/null | wc -l | tr -d ' ') files"
else
    echo "└── Documentation: 0 files"
fi

echo ""
echo "🎉 Vesper Compiler setup complete!"
echo ""
echo "Usage examples:"
echo "  ./build/vesper file.vsp     # Compile a Vesper program"
echo "  make examples              # Test with example files"
echo "  make test                  # Run all tests"
echo "  make help                  # Show all available commands"
echo ""
echo "📁 Project structure:"
echo "  src/           - Source code"
echo "  include/       - Header files"
echo "  tests/examples/- Example programs"
echo "  build/         - Compiled binaries"
echo "  docs/          - Documentation" 