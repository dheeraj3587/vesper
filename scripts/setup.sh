#!/bin/bash

# Vesper Compiler Project Setup Script
# This script helps organize and test the project structure

echo "🚀 Setting up Vesper Compiler Project..."

# Create necessary directories
echo "📁 Creating directory structure..."
mkdir -p scripts
mkdir -p tests/output
mkdir -p docs/generated

# Clean up old build artifacts
echo "🧹 Cleaning build artifacts..."
rm -f *.o *.asm output

# Build the project
echo "🔨 Building compiler..."
if make clean && make; then
    echo "✅ Build successful!"
else
    echo "❌ Build failed!"
    exit 1
fi

# Test with examples
echo "🧪 Testing with examples..."
if make examples; then
    echo "✅ Example tests passed!"
else
    echo "❌ Example tests failed!"
fi

# Display project status
echo ""
echo "📊 Project Status:"
echo "├── Source files: $(find src -name '*.cpp' | wc -l) files"
echo "├── Header files: $(find include -name '*.h' | wc -l) files"
echo "├── Example files: $(find tests/examples -name '*.vsp' 2>/dev/null | wc -l) files"
echo "├── Unit tests: $(find tests/unit -name '*.cpp' 2>/dev/null | wc -l) files"
echo "└── Documentation: $(find docs -name '*.md' | wc -l) files"

echo ""
echo "🎉 Vesper Compiler is ready to use!"
echo ""
echo "Usage examples:"
echo "  make examples           # Test with example files"
echo "  make test              # Run all tests"
echo "  ./build/vesper file.vsp # Compile a Vesper program"
echo "  make help              # Show all available commands" 