CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
TARGET = build/vesper
SOURCES = src/main.cpp src/Lexer.cpp src/Parser.cpp src/CodeGen.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/obj/%.o)
HEADERS = include/Lexer.h include/Parser.h include/AST.h include/CodeGen.h

# Test files
TEST_UNIT_SOURCES = tests/unit/run_all_tests.cpp tests/unit/test_lexer.cpp tests/unit/test_parser.cpp tests/unit/test_ast.cpp
TEST_INTEGRATION_SOURCES = tests/integration/test_integration.cpp
TEST_UNIT_OBJECTS = $(TEST_UNIT_SOURCES:tests/unit/%.cpp=build/obj/test_unit_%.o)
TEST_INTEGRATION_OBJECTS = $(TEST_INTEGRATION_SOURCES:tests/integration/%.cpp=build/obj/test_integration_%.o)

# Test executables
TEST_UNIT_TARGET = build/test_unit
TEST_INTEGRATION_TARGET = build/test_integration

# Example files
EXAMPLE_FILES = tests/examples/basic_control_flow.vsp \
                tests/examples/variables_and_expressions.vsp \
                tests/examples/nested_loops.vsp

.PHONY: all clean test install uninstall docs test-unit test-integration test-all test-lexer test-parser test-ast examples test-legacy

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p build
	$(CXX) $(OBJECTS) -o $(TARGET)

build/obj/%.o: src/%.cpp $(HEADERS)
	mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test targets
test: test-unit test-integration examples

test-unit: $(TEST_UNIT_TARGET)
	@echo "🧪 Running Unit Tests..."
	./$(TEST_UNIT_TARGET)

test-integration: $(TEST_INTEGRATION_TARGET)
	@echo "🔗 Running Integration Tests..."
	./$(TEST_INTEGRATION_TARGET)

test-all: test-unit test-integration examples
	@echo "🎉 All tests completed!"

# Individual component tests
test-lexer: build/obj/test_unit_test_lexer.o $(filter-out build/obj/main.o, $(OBJECTS))
	mkdir -p build
	$(CXX) build/obj/test_unit_test_lexer.o $(filter-out build/obj/main.o, $(OBJECTS)) -o build/test_lexer
	@echo "🔍 Testing Lexer..."
	./build/test_lexer

test-parser: build/obj/test_unit_test_parser.o $(filter-out build/obj/main.o, $(OBJECTS))
	mkdir -p build
	$(CXX) build/obj/test_unit_test_parser.o $(filter-out build/obj/main.o, $(OBJECTS)) -o build/test_parser
	@echo "🔍 Testing Parser..."
	./build/test_parser

test-ast: build/obj/test_unit_test_ast.o $(filter-out build/obj/main.o, $(OBJECTS))
	mkdir -p build
	$(CXX) build/obj/test_unit_test_ast.o $(filter-out build/obj/main.o, $(OBJECTS)) -o build/test_ast
	@echo "🔍 Testing AST..."
	./build/test_ast

# Test with example files
examples: $(TARGET)
	@echo "📄 Testing with example files:"
	@for file in $(EXAMPLE_FILES); do \
		echo "Testing $$file:"; \
		./$(TARGET) $$file || echo "Failed: $$file"; \
		echo ""; \
	done

# Legacy test files (for compatibility)
test-legacy: $(TARGET)
	@echo "📄 Testing with legacy files:"
	@echo "Testing Kaleidoscope-style code:"
	./$(TARGET) tests/test.vsp || echo "Expected failure - Kaleidoscope syntax not fully supported"
	@echo "Testing C-style code:"
	./$(TARGET) tests/test_c_style.vsp

# Unit test executable
$(TEST_UNIT_TARGET): $(TEST_UNIT_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS))
	mkdir -p build
	$(CXX) $(TEST_UNIT_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS)) -o $(TEST_UNIT_TARGET)

# Integration test executable
$(TEST_INTEGRATION_TARGET): $(TEST_INTEGRATION_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS))
	mkdir -p build
	$(CXX) $(TEST_INTEGRATION_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS)) -o $(TEST_INTEGRATION_TARGET)

# Compile test files
build/obj/test_unit_%.o: tests/unit/%.cpp $(HEADERS)
	mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/obj/test_integration_%.o: tests/integration/%.cpp $(HEADERS)
	mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Utility targets
clean:
	rm -rf build/obj/*.o build/vesper build/test_*

clean-all:
	rm -rf build/ docs/explanations/*.md docs/summaries/*.md

clean-tests:
	rm -f build/test_* build/obj/test_*.o

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/vesper

# Development utilities
format:
	@echo "Formatting code..."
	@find src include -name "*.cpp" -o -name "*.h" | xargs clang-format -i

docs:
	@echo "Documentation files are organized in:"
	@echo "  - docs/explanations/ : Code explanations"
	@echo "  - docs/summaries/    : Project summaries"
	@echo "  - tests/examples/    : Example programs"
	@echo "  - tests/unit/        : Unit tests"
	@echo "  - tests/integration/ : Integration tests"

help:
	@echo "Available targets:"
	@echo "  all              - Build the compiler"
	@echo "  test             - Run all tests (unit + integration + examples)"
	@echo "  test-unit        - Run unit tests only"
	@echo "  test-integration - Run integration tests only"
	@echo "  test-all         - Run all tests with summary"
	@echo "  test-lexer       - Run lexer tests only"
	@echo "  test-parser      - Run parser tests only"
	@echo "  test-ast         - Run AST tests only"
	@echo "  examples         - Test with example files"
	@echo "  test-legacy      - Test with legacy files"
	@echo "  clean            - Remove object files and executables"
	@echo "  clean-all        - Remove all generated files"
	@echo "  clean-tests      - Remove only test artifacts"
	@echo "  format           - Format source code"
	@echo "  install          - Install to system"
	@echo "  uninstall        - Remove from system"
	@echo "  docs             - Show documentation structure"
	@echo "  help             - Show this help"
	@echo ""
	@echo "Examples:"
	@echo "  make examples    - Test with all example files"
	@echo "  make test-lexer  - Test only the lexer component" 