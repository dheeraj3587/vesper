#pragma once
#include "AST.h"
#include <string>
#include <vector>

class CodeGen
{
public:
    CodeGen();
    // Generate assembly code from the root AST node
    void generateAssembly(ProgramAST *root);
    // Write the generated assembly to a file
    void writeToFile(const std::string &filename) const;
    // Get the generated assembly as a string
    std::string getAssembly() const;
    void emit(const std::string &line);

private:
    std::vector<std::string> assemblyLines;
    // Helper methods for different AST node types can be added here
};