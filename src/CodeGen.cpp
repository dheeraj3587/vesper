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

// Symbol table for variable stack offsets and types
struct VariableInfo
{
    int stackOffset;
    DataType type;
    int size; // size in bytes
};

static std::unordered_map<std::string, VariableInfo> symbolTable;
static int stackOffset = 0;
static int labelCounter = 0; // For generating unique labels

// Helper to generate unique labels
std::string generateLabel(const std::string &prefix)
{
    return prefix + std::to_string(labelCounter++);
}

CodeGen::CodeGen()
{
    // Reset static variables for each new compilation
    symbolTable.clear();
    stackOffset = 0;
    labelCounter = 0;
}

// Helper to emit assembly
void CodeGen::emit(const std::string &line)
{
    assemblyLines.push_back(line);
}

// Helper to get size of data type
int getTypeSize(DataType type)
{
    switch (type)
    {
    case DataType::INT:
    case DataType::FLOAT:
        return 4;
    case DataType::DOUBLE:
        return 8;
    case DataType::CHAR:
    case DataType::BOOL:
        return 1;
    case DataType::STRING:
        return 8; // pointer size
    default:
        return 8; // default to 8 bytes
    }
}

// Minimal codegen for NumberExprAST
void NumberExprAST::codegen(CodeGen &gen) const
{
    // Move immediate value into rax
    std::ostringstream oss;
    oss << "    mov rax, " << static_cast<int>(Val);
    gen.emit(oss.str());
}

// Improved codegen for VariableExprAST
void VariableExprAST::codegen(CodeGen &gen) const
{
    // Load variable from stack
    if (symbolTable.find(Name) != symbolTable.end())
    {
        const VariableInfo &varInfo = symbolTable[Name];
        std::ostringstream oss;

        // Load based on variable type and size
        if (varInfo.type == DataType::INT || varInfo.type == DataType::FLOAT)
        {
            oss << "    mov eax, [rbp-" << varInfo.stackOffset << "]";
            gen.emit(oss.str());
            gen.emit("    movsx rax, eax"); // sign extend to 64-bit
        }
        else if (varInfo.type == DataType::DOUBLE)
        {
            oss << "    mov rax, [rbp-" << varInfo.stackOffset << "]";
            gen.emit(oss.str());
        }
        else if (varInfo.type == DataType::CHAR || varInfo.type == DataType::BOOL)
        {
            oss << "    movzx eax, byte [rbp-" << varInfo.stackOffset << "]";
            gen.emit(oss.str());
            gen.emit("    movzx rax, eax"); // zero extend to 64-bit
        }
        else
        {
            // Default case (treat as 64-bit)
            oss << "    mov rax, [rbp-" << varInfo.stackOffset << "]";
            gen.emit(oss.str());
        }
    }
    else
    {
        gen.emit("    ; ERROR: Unknown variable " + Name);
        gen.emit("    xor rax, rax"); // Set to 0 for safety
    }
}

// Improved codegen for BinaryExprAST (only +, -, *, /)
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
    else if (Op == "==")
    {
        gen.emit("    cmp rax, rcx");
        gen.emit("    sete al");
        gen.emit("    movzx rax, al");
    }
    else if (Op == "!=")
    {
        gen.emit("    cmp rax, rcx");
        gen.emit("    setne al");
        gen.emit("    movzx rax, al");
    }
    else if (Op == "<")
    {
        gen.emit("    cmp rax, rcx");
        gen.emit("    setl al");
        gen.emit("    movzx rax, al");
    }
    else if (Op == ">")
    {
        gen.emit("    cmp rax, rcx");
        gen.emit("    setg al");
        gen.emit("    movzx rax, al");
    }
    else if (Op == "<=")
    {
        gen.emit("    cmp rax, rcx");
        gen.emit("    setle al");
        gen.emit("    movzx rax, al");
    }
    else if (Op == ">=")
    {
        gen.emit("    cmp rax, rcx");
        gen.emit("    setge al");
        gen.emit("    movzx rax, al");
    }
    else
    {
        gen.emit("    ; ERROR: Unsupported binary op " + Op);
    }
}

// Improved codegen for AssignmentExprAST
void AssignmentExprAST::codegen(CodeGen &gen) const
{
    // Evaluate the right-hand side
    RHS->codegen(gen);

    // Get the variable from the left-hand side
    VariableExprAST *var = dynamic_cast<VariableExprAST *>(LHS.get());
    if (var && symbolTable.find(var->getName()) != symbolTable.end())
    {
        const VariableInfo &varInfo = symbolTable[var->getName()];
        std::ostringstream oss;

        // Store based on variable type and size
        if (varInfo.type == DataType::INT || varInfo.type == DataType::FLOAT)
        {
            oss << "    mov [rbp-" << varInfo.stackOffset << "], eax";
        }
        else if (varInfo.type == DataType::DOUBLE)
        {
            oss << "    mov [rbp-" << varInfo.stackOffset << "], rax";
        }
        else if (varInfo.type == DataType::CHAR || varInfo.type == DataType::BOOL)
        {
            oss << "    mov [rbp-" << varInfo.stackOffset << "], al";
        }
        else
        {
            // Default case (treat as 64-bit)
            oss << "    mov [rbp-" << varInfo.stackOffset << "], rax";
        }
        gen.emit(oss.str());
    }
    else
    {
        gen.emit("    ; ERROR: Assignment to unknown variable");
    }
}

// Improved codegen for VarDeclStmtAST
void VarDeclStmtAST::codegen(CodeGen &gen) const
{
    for (const auto &var : Vars)
    {
        int typeSize = getTypeSize(Type);
        stackOffset += typeSize;

        // Add to symbol table
        VariableInfo varInfo;
        varInfo.stackOffset = stackOffset;
        varInfo.type = Type;
        varInfo.size = typeSize;
        symbolTable[var.first] = varInfo;

        // If there's an initializer, evaluate it and store
        if (var.second)
        {
            var.second->codegen(gen);
            std::ostringstream oss;

            // Store based on variable type and size
            if (Type == DataType::INT || Type == DataType::FLOAT)
            {
                oss << "    mov [rbp-" << stackOffset << "], eax";
            }
            else if (Type == DataType::DOUBLE)
            {
                oss << "    mov [rbp-" << stackOffset << "], rax";
            }
            else if (Type == DataType::CHAR || Type == DataType::BOOL)
            {
                oss << "    mov [rbp-" << stackOffset << "], al";
            }
            else
            {
                // Default case (treat as 64-bit)
                oss << "    mov [rbp-" << stackOffset << "], rax";
            }
            gen.emit(oss.str());
        }
        else
        {
            // Initialize to zero if no initializer
            std::ostringstream oss;
            if (Type == DataType::INT || Type == DataType::FLOAT)
            {
                oss << "    mov dword [rbp-" << stackOffset << "], 0";
            }
            else if (Type == DataType::DOUBLE)
            {
                oss << "    mov qword [rbp-" << stackOffset << "], 0";
            }
            else if (Type == DataType::CHAR || Type == DataType::BOOL)
            {
                oss << "    mov byte [rbp-" << stackOffset << "], 0";
            }
            else
            {
                oss << "    mov qword [rbp-" << stackOffset << "], 0";
            }
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

// Improved codegen for ProgramAST
void ProgramAST::codegen(CodeGen &gen) const
{
    // First pass: calculate total stack space needed by traversing all statements
    // Reset the stack offset for calculation
    int originalStackOffset = stackOffset;
    stackOffset = 0;
    symbolTable.clear();

    // Simulate code generation to calculate stack requirements
    for (const auto &stmt : Statements)
    {
        // We need to traverse variable declarations to calculate stack space
        // This is a simplified approach - in a real compiler you'd want a separate pass
        const VarDeclStmtAST *varDecl = dynamic_cast<const VarDeclStmtAST *>(stmt.get());
        if (varDecl)
        {
            for (const auto &var : varDecl->getVars())
            {
                int typeSize = getTypeSize(varDecl->getVarType());
                stackOffset += typeSize;

                // Add to symbol table
                VariableInfo varInfo;
                varInfo.stackOffset = stackOffset;
                varInfo.type = varDecl->getVarType();
                varInfo.size = typeSize;
                symbolTable[var.first] = varInfo;
            }
        }
    }

    // Now generate the actual code
    gen.emit("section .text");
    gen.emit("global _main");
    gen.emit("_main:");
    gen.emit("    push rbp");
    gen.emit("    mov rbp, rsp");

    // Reserve stack space for all variables
    if (stackOffset > 0)
    {
        std::ostringstream oss;
        // Align stack to 16-byte boundary
        int alignedOffset = ((stackOffset + 15) / 16) * 16;
        oss << "    sub rsp, " << alignedOffset;
        gen.emit(oss.str());
    }

    // Reset stack offset for actual code generation
    int totalStackOffset = stackOffset;
    stackOffset = 0;
    symbolTable.clear();

    // Rebuild symbol table for code generation
    for (const auto &stmt : Statements)
    {
        const VarDeclStmtAST *varDecl = dynamic_cast<const VarDeclStmtAST *>(stmt.get());
        if (varDecl)
        {
            for (const auto &var : varDecl->getVars())
            {
                int typeSize = getTypeSize(varDecl->getVarType());
                stackOffset += typeSize;

                // Add to symbol table
                VariableInfo varInfo;
                varInfo.stackOffset = stackOffset;
                varInfo.type = varDecl->getVarType();
                varInfo.size = typeSize;
                symbolTable[var.first] = varInfo;
            }
        }
    }

    // Generate code for all statements
    for (const auto &stmt : Statements)
    {
        stmt->codegen(gen);
    }

    // Restore stack and exit
    if (totalStackOffset > 0)
    {
        std::ostringstream oss;
        int alignedOffset = ((totalStackOffset + 15) / 16) * 16;
        oss << "    add rsp, " << alignedOffset;
        gen.emit(oss.str());
    }

    gen.emit("    mov rax, 60"); // exit syscall
    gen.emit("    xor rdi, rdi");
    gen.emit("    syscall");
}

// Boolean expression codegen
void BoolExprAST::codegen(CodeGen &gen) const
{
    std::ostringstream oss;
    oss << "    mov rax, " << (Val ? 1 : 0);
    gen.emit(oss.str());
}

// Character expression codegen
void CharExprAST::codegen(CodeGen &gen) const
{
    std::ostringstream oss;
    oss << "    mov rax, " << static_cast<int>(Val);
    gen.emit(oss.str());
}

// String expression codegen (basic implementation)
void StringExprAST::codegen(CodeGen &gen) const
{
    // For now, just return a pointer value (simplified)
    // In a full implementation, we'd need a data section and string storage
    gen.emit("    ; String literal: " + Val);
    gen.emit("    mov rax, 0  ; String pointer placeholder");
}

// Unary expression codegen
void UnaryExprAST::codegen(CodeGen &gen) const
{
    Operand->codegen(gen);

    if (Op == "-")
    {
        gen.emit("    neg rax");
    }
    else if (Op == "!")
    {
        gen.emit("    test rax, rax");
        gen.emit("    setz al");
        gen.emit("    movzx rax, al");
    }
    else if (Op == "~")
    {
        gen.emit("    not rax");
    }
    else
    {
        gen.emit("    ; ERROR: Unsupported unary operator " + Op);
    }
}

// Function call codegen (basic implementation)
void CallExprAST::codegen(CodeGen &gen) const
{
    // For now, implement basic function call without proper ABI
    // This is a simplified version - real implementation would handle calling conventions
    gen.emit("    ; Function call: " + Callee);

    // Push arguments in reverse order (simplified)
    for (int i = Args.size() - 1; i >= 0; i--)
    {
        Args[i]->codegen(gen);
        gen.emit("    push rax");
    }

    // Call function (simplified - assumes function exists)
    gen.emit("    call " + Callee);

    // Clean up stack (assuming no return value handling for now)
    if (!Args.empty())
    {
        std::ostringstream oss;
        oss << "    add rsp, " << (Args.size() * 8);
        gen.emit(oss.str());
    }
}

// Array access codegen (basic implementation)
void ArrayExprAST::codegen(CodeGen &gen) const
{
    // Generate code for array base
    Array->codegen(gen);
    gen.emit("    push rax"); // Save array base

    // Generate code for index
    Index->codegen(gen);

    // Calculate offset (index * element_size)
    gen.emit("    imul rax, 8"); // Assuming 8-byte elements for simplicity

    // Add to base address
    gen.emit("    pop rcx");        // Restore array base
    gen.emit("    add rax, rcx");   // Calculate final address
    gen.emit("    mov rax, [rax]"); // Dereference
}

// If statement codegen
void IfStmtAST::codegen(CodeGen &gen) const
{
    std::string falseLabel = generateLabel("if_false_");
    std::string endLabel = generateLabel("if_end_");

    // Evaluate condition
    Condition->codegen(gen);

    // Test condition and jump if false
    gen.emit("    test rax, rax");
    gen.emit("    jz " + falseLabel);

    // Generate then statement
    ThenStmt->codegen(gen);

    // If there's an else clause, jump over it
    if (ElseStmt)
    {
        gen.emit("    jmp " + endLabel);
    }

    // False label
    gen.emit(falseLabel + ":");

    // Generate else statement if it exists
    if (ElseStmt)
    {
        ElseStmt->codegen(gen);
        gen.emit(endLabel + ":");
    }
}

// While loop codegen
void WhileStmtAST::codegen(CodeGen &gen) const
{
    std::string loopLabel = generateLabel("while_loop_");
    std::string endLabel = generateLabel("while_end_");

    // Loop start
    gen.emit(loopLabel + ":");

    // Evaluate condition
    Condition->codegen(gen);

    // Test condition and jump if false
    gen.emit("    test rax, rax");
    gen.emit("    jz " + endLabel);

    // Generate loop body
    Body->codegen(gen);

    // Jump back to condition
    gen.emit("    jmp " + loopLabel);

    // End label
    gen.emit(endLabel + ":");
}

// For loop codegen
void ForStmtAST::codegen(CodeGen &gen) const
{
    std::string loopLabel = generateLabel("for_loop_");
    std::string endLabel = generateLabel("for_end_");

    // Generate initialization
    if (Init)
    {
        Init->codegen(gen);
    }

    // Loop start
    gen.emit(loopLabel + ":");

    // Evaluate condition
    if (Condition)
    {
        Condition->codegen(gen);
        gen.emit("    test rax, rax");
        gen.emit("    jz " + endLabel);
    }

    // Generate loop body
    Body->codegen(gen);

    // Generate update expression
    if (Update)
    {
        Update->codegen(gen);
    }

    // Jump back to condition
    gen.emit("    jmp " + loopLabel);

    // End label
    gen.emit(endLabel + ":");
}

// Return statement codegen
void ReturnStmtAST::codegen(CodeGen &gen) const
{
    if (Value)
    {
        Value->codegen(gen);
    }
    else
    {
        gen.emit("    xor rax, rax"); // Return 0 if no value
    }

    // For now, just exit (in a real implementation, we'd restore stack frame)
    gen.emit("    mov rsp, rbp");
    gen.emit("    pop rbp");
    gen.emit("    ret");
}

// Break statement codegen (simplified)
void BreakStmtAST::codegen(CodeGen &gen) const
{
    // In a full implementation, we'd need a stack of loop end labels
    gen.emit("    ; break statement - would jump to loop end");
    gen.emit("    jmp loop_end  ; Placeholder - needs proper loop tracking");
}

// Continue statement codegen (simplified)
void ContinueStmtAST::codegen(CodeGen &gen) const
{
    // In a full implementation, we'd need a stack of loop start labels
    gen.emit("    ; continue statement - would jump to loop start");
    gen.emit("    jmp loop_start  ; Placeholder - needs proper loop tracking");
}

// Function prototype codegen
void PrototypeAST::codegen(CodeGen &gen) const
{
    // Generate function label
    gen.emit(Name + ":");
    gen.emit("    push rbp");
    gen.emit("    mov rbp, rsp");

    // For now, just set up basic function prologue
    // In a full implementation, we'd handle parameter setup
}

// Function definition codegen
void FunctionAST::codegen(CodeGen &gen) const
{
    // Generate function prototype
    Proto->codegen(gen);

    // Generate function body
    Body->codegen(gen);

    // Function epilogue (if no explicit return)
    gen.emit("    xor rax, rax"); // Default return value
    gen.emit("    mov rsp, rbp");
    gen.emit("    pop rbp");
    gen.emit("    ret");
}

// Scope expression codegen (for :: operator)
void ScopeExprAST::codegen(CodeGen &gen) const
{
    // For now, just generate the member access
    // In a full implementation, we'd handle namespace resolution
    gen.emit("    ; Scope resolution: " + Member);
    Base->codegen(gen);
}

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