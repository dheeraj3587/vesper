#pragma once
#include "AST.h"
#include <string>
#include <vector>
#include <sstream>

class CodeGen
{
public:
    CodeGen();

    // Generate assembly code from the root AST node
    void generateAssembly(ProgramAST *root);

    // Generate assembly to file
    void generateAssembly(const std::string &filename);

    // Convert assembly to binary
    bool assembleToBinary(const std::string &asmFile, const std::string &outputBinary);

    // Complete pipeline: generate assembly and binary
    bool generateBinary(const std::string &asmFile, const std::string &outputBinary);

    // Write the generated assembly to a file (legacy)
    void writeToFile(const std::string &filename) const;

    // Get the generated assembly as a string (legacy)
    std::string getAssembly() const;

    // Emit a line of assembly code
    void emit(const std::string &line);

private:
    std::ostringstream code;                // Modern approach using stringstream
    std::vector<std::string> assemblyLines; // Legacy support

    // Helper methods for different AST node types can be added here
};