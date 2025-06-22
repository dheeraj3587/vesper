CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude
TARGET = build/vesper
SOURCES = src/main.cpp src/Lexer.cpp src/Parser.cpp
OBJECTS = $(SOURCES:src/%.cpp=build/obj/%.o)
HEADERS = include/Lexer.h include/Parser.h include/AST.h

# Test files
TEST_UNIT_SOURCES = tests/unit/run_all_tests.cpp tests/unit/test_lexer.cpp tests/unit/test_parser.cpp tests/unit/test_ast.cpp
TEST_INTEGRATION_SOURCES = tests/integration/test_integration.cpp
TEST_UNIT_OBJECTS = $(TEST_UNIT_SOURCES:tests/unit/%.cpp=build/obj/test_unit_%.o)
TEST_INTEGRATION_OBJECTS = $(TEST_INTEGRATION_SOURCES:tests/integration/%.cpp=build/obj/test_integration_%.o)

# Test executables
TEST_UNIT_TARGET = build/test_unit
TEST_INTEGRATION_TARGET = build/test_integration

.PHONY: all clean test install uninstall docs test-unit test-integration test-all test-lexer test-parser test-ast

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p build
	$(CXX) $(OBJECTS) -o $(TARGET)

build/obj/%.o: src/%.cpp $(HEADERS)
	@mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test targets
test: test-unit test-integration test-files

test-unit: $(TEST_UNIT_TARGET)
	@echo "🧪 Running Unit Tests..."
	./$(TEST_UNIT_TARGET)

test-integration: $(TEST_INTEGRATION_TARGET)
	@echo "🔗 Running Integration Tests..."
	./$(TEST_INTEGRATION_TARGET)

test-all: test-unit test-integration test-files
	@echo "🎉 All tests completed!"

# Individual component tests
test-lexer: build/obj/test_unit_test_lexer.o $(filter-out build/obj/main.o, $(OBJECTS))
	@mkdir -p build
	$(CXX) build/obj/test_unit_test_lexer.o $(filter-out build/obj/main.o, $(OBJECTS)) -o build/test_lexer
	@echo "🔍 Testing Lexer..."
	./build/test_lexer

test-parser: build/obj/test_unit_test_parser.o $(filter-out build/obj/main.o, $(OBJECTS))
	@mkdir -p build
	$(CXX) build/obj/test_unit_test_parser.o $(filter-out build/obj/main.o, $(OBJECTS)) -o build/test_parser
	@echo "🔍 Testing Parser..."
	./build/test_parser

test-ast: build/obj/test_unit_test_ast.o $(filter-out build/obj/main.o, $(OBJECTS))
	@mkdir -p build
	$(CXX) build/obj/test_unit_test_ast.o $(filter-out build/obj/main.o, $(OBJECTS)) -o build/test_ast
	@echo "🔍 Testing AST..."
	./build/test_ast

# Test with sample files
test-files: $(TARGET)
	@echo "📄 Testing with sample files:"
	@echo "Testing with basic Kaleidoscope code:"
	./$(TARGET) tests/test.vsp
	@echo -e "\nTesting with C/STL keywords:"
	./$(TARGET) tests/test_c_stl.vsp

# Unit test executable
$(TEST_UNIT_TARGET): $(TEST_UNIT_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS))
	@mkdir -p build
	$(CXX) $(TEST_UNIT_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS)) -o $(TEST_UNIT_TARGET)

# Integration test executable
$(TEST_INTEGRATION_TARGET): $(TEST_INTEGRATION_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS))
	@mkdir -p build
	$(CXX) $(TEST_INTEGRATION_OBJECTS) $(filter-out build/obj/main.o, $(OBJECTS)) -o $(TEST_INTEGRATION_TARGET)

# Compile test files
build/obj/test_unit_%.o: tests/unit/%.cpp $(HEADERS)
	@mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/obj/test_integration_%.o: tests/integration/%.cpp $(HEADERS)
	@mkdir -p build/obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/obj/*.o build/vesper build/kaleidoscope_compiler build/test_*

clean-all:
	rm -rf build/ docs/explanations/*.md docs/summaries/*.md

clean-tests:
	rm -f build/test_* build/obj/test_*.o

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/vesper

docs:
	@echo "Documentation files are organized in:"
	@echo "  - docs/explanations/ : Code explanations"
	@echo "  - docs/summaries/    : Project summaries"
	@echo "  - tests/             : Test files"
	@echo "  - examples/          : Example programs"

help:
	@echo "Available targets:"
	@echo "  all              - Build the compiler"
	@echo "  test             - Run all tests (unit + integration + files)"
	@echo "  test-unit        - Run unit tests only"
	@echo "  test-integration - Run integration tests only"
	@echo "  test-all         - Run all tests with summary"
	@echo "  test-lexer       - Run lexer tests only"
	@echo "  test-parser      - Run parser tests only"
	@echo "  test-ast         - Run AST tests only"
	@echo "  test-files       - Test with sample files"
	@echo "  clean            - Remove object files and executables"
	@echo "  clean-all        - Remove all generated files"
	@echo "  clean-tests      - Remove only test artifacts"
	@echo "  install          - Install to system"
	@echo "  uninstall        - Remove from system"
	@echo "  docs             - Show documentation structure"
	@echo "  help             - Show this help"
	@echo ""
	@echo "Test Examples:"
	@echo "  make test        - Run comprehensive test suite"
	@echo "  make test-lexer  - Test only the lexer component"
	@echo "  make test-files  - Test with sample .vsp files" 