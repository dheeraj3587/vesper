#include "CodeGen.h"
#include "AST.h"
#include <fstream>
#include <unordered_map>
#include <sstream>

// Forward declarations for AST codegen
class NumberExprAST;
class VariableExprAST;
class BinaryExprAST;
class AssignmentExprAST;
class VarDeclStmtAST;
class ExprStmtAST;
class CompoundStmtAST;
class ProgramAST;

// Symbol table for variable stack offsets
static std::unordered_map<std::string, int> symbolTable;
static int stackOffset = 0;

CodeGen::CodeGen() {}

// Helper to emit assembly
void CodeGen::emit(const std::string &line)
{
    assemblyLines.push_back(line);
}

// Minimal codegen for NumberExprAST
void NumberExprAST::codegen(CodeGen &gen) const
{
    // Move immediate value into rax
    std::ostringstream oss;
    oss << "    mov rax, " << static_cast<int>(Val);
    gen.emit(oss.str());
}

// Minimal codegen for VariableExprAST
void VariableExprAST::codegen(CodeGen &gen) const
{
    // Load variable from stack
    if (symbolTable.find(Name) != symbolTable.end())
    {
        int offset = symbolTable[Name];
        std::ostringstream oss;
        oss << "    mov rax, [rbp-" << offset << "]";
        gen.emit(oss.str());
    }
    else
    {
        gen.emit("    ; ERROR: Unknown variable " + Name);
    }
}

// Minimal codegen for BinaryExprAST (only +, -, *, /)
void BinaryExprAST::codegen(CodeGen &gen) const
{
    // Evaluate RHS first (will be overwritten by LHS)
    RHS->codegen(gen);
    gen.emit("    push rax");
    LHS->codegen(gen);
    gen.emit("    pop rcx");
    if (Op == "+")
        gen.emit("    add rax, rcx");
    else if (Op == "-")
        gen.emit("    sub rax, rcx");
    else if (Op == "*")
        gen.emit("    imul rax, rcx");
    else if (Op == "/")
    {
        gen.emit("    cqo");
        gen.emit("    idiv rcx");
    }
    else
    {
        gen.emit("    ; ERROR: Unsupported binary op " + Op);
    }
}

// Minimal codegen for AssignmentExprAST
void AssignmentExprAST::codegen(CodeGen &gen) const
{
    RHS->codegen(gen);
    VariableExprAST *var = dynamic_cast<VariableExprAST *>(LHS.get());
    if (var && symbolTable.find(var->getName()) != symbolTable.end())
    {
        int offset = symbolTable[var->getName()];
        std::ostringstream oss;
        oss << "    mov [rbp-" << offset << "], rax";
        gen.emit(oss.str());
    }
    else
    {
        gen.emit("    ; ERROR: Assignment to unknown variable");
    }
}

// Minimal codegen for VarDeclStmtAST (int only)
void VarDeclStmtAST::codegen(CodeGen &gen) const
{
    for (const auto &var : Vars)
    {
        stackOffset += 8; // 8 bytes for int
        symbolTable[var.first] = stackOffset;
        if (var.second)
        {
            var.second->codegen(gen);
            std::ostringstream oss;
            oss << "    mov [rbp-" << stackOffset << "], rax";
            gen.emit(oss.str());
        }
    }
}

// Minimal codegen for ExprStmtAST
void ExprStmtAST::codegen(CodeGen &gen) const
{
    Expr->codegen(gen);
}

// Minimal codegen for CompoundStmtAST
void CompoundStmtAST::codegen(CodeGen &gen) const
{
    for (const auto &stmt : Statements)
    {
        stmt->codegen(gen);
    }
}

// Minimal codegen for ProgramAST
void ProgramAST::codegen(CodeGen &gen) const
{
    gen.emit("section .text");
    gen.emit("global _start");
    gen.emit("_start:");
    gen.emit("    push rbp");
    gen.emit("    mov rbp, rsp");
    for (const auto &stmt : Statements)
    {
        stmt->codegen(gen);
    }
    gen.emit("    mov rax, 60"); // exit syscall
    gen.emit("    xor rdi, rdi");
    gen.emit("    syscall");
}

// Stub codegen for all unimplemented AST node types
void BoolExprAST::codegen(CodeGen &gen) const { gen.emit("    ; BoolExprAST codegen not implemented"); }
void CharExprAST::codegen(CodeGen &gen) const { gen.emit("    ; CharExprAST codegen not implemented"); }
void StringExprAST::codegen(CodeGen &gen) const { gen.emit("    ; StringExprAST codegen not implemented"); }
void UnaryExprAST::codegen(CodeGen &gen) const { gen.emit("    ; UnaryExprAST codegen not implemented"); }
void CallExprAST::codegen(CodeGen &gen) const { gen.emit("    ; CallExprAST codegen not implemented"); }
void ArrayExprAST::codegen(CodeGen &gen) const { gen.emit("    ; ArrayExprAST codegen not implemented"); }
void IfStmtAST::codegen(CodeGen &gen) const { gen.emit("    ; IfStmtAST codegen not implemented"); }
void WhileStmtAST::codegen(CodeGen &gen) const { gen.emit("    ; WhileStmtAST codegen not implemented"); }
void ForStmtAST::codegen(CodeGen &gen) const { gen.emit("    ; ForStmtAST codegen not implemented"); }
void ReturnStmtAST::codegen(CodeGen &gen) const { gen.emit("    ; ReturnStmtAST codegen not implemented"); }
void BreakStmtAST::codegen(CodeGen &gen) const { gen.emit("    ; BreakStmtAST codegen not implemented"); }
void ContinueStmtAST::codegen(CodeGen &gen) const { gen.emit("    ; ContinueStmtAST codegen not implemented"); }
void PrototypeAST::codegen(CodeGen &gen) const { gen.emit("    ; PrototypeAST codegen not implemented"); }
void FunctionAST::codegen(CodeGen &gen) const { gen.emit("    ; FunctionAST codegen not implemented"); }
void ScopeExprAST::codegen(CodeGen &gen) const { gen.emit("    ; ScopeExprAST codegen not implemented"); }

void CodeGen::generateAssembly(ProgramAST *root)
{
    if (root)
    {
        root->codegen(*this);
    }
    else
    {
        emit("; ERROR: Root is not a ProgramAST");
    }
}

void CodeGen::writeToFile(const std::string &filename) const
{
    std::ofstream out(filename);
    for (const auto &line : assemblyLines)
    {
        out << line << "\n";
    }
}

std::string CodeGen::getAssembly() const
{
    std::string result;
    for (const auto &line : assemblyLines)
    {
        result += line + "\n";
    }
    return result;
}