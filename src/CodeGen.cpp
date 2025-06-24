#include "CodeGen.h"
#include "AST.h"
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cstdio>

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
    code << line << std::endl;
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
        return 4; // default to 4 bytes for int
    }
}

// NumberExprAST codegen
void NumberExprAST::codegen(CodeGen &gen) const
{
    std::ostringstream oss;
    oss << "    mov rax, " << static_cast<int>(Val);
    gen.emit(oss.str());
}

// VariableExprAST codegen - Load variable from stack
void VariableExprAST::codegen(CodeGen &gen) const
{
    if (symbolTable.find(Name) != symbolTable.end())
    {
        const VariableInfo &varInfo = symbolTable[Name];
        std::ostringstream oss;

        // Load as 32-bit integer and sign-extend to 64-bit
        oss << "    mov eax, dword [rbp-" << varInfo.stackOffset << "]";
        gen.emit(oss.str());
        gen.emit("    movsx rax, eax"); // sign extend to 64-bit
    }
    else
    {
        gen.emit("    ; ERROR: Unknown variable " + Name);
        gen.emit("    mov rax, 0"); // Set to 0 for safety
    }
}

// BinaryExprAST codegen - Fixed to handle operations correctly
void BinaryExprAST::codegen(CodeGen &gen) const
{
    // Evaluate left side first
    LHS->codegen(gen);
    gen.emit("    push rax"); // Save left side

    // Evaluate right side
    RHS->codegen(gen);
    gen.emit("    mov rcx, rax"); // Right side in rcx
    gen.emit("    pop rax");      // Left side back in rax

    if (Op == "+")
        gen.emit("    add rax, rcx");
    else if (Op == "-")
        gen.emit("    sub rax, rcx");
    else if (Op == "*")
        gen.emit("    imul rax, rcx");
    else if (Op == "/")
    {
        gen.emit("    cqo");      // Sign extend rax to rdx:rax
        gen.emit("    idiv rcx"); // Divide rdx:rax by rcx
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
}

// AssignmentExprAST codegen - Store value to variable
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

        // Store as 32-bit integer
        oss << "    mov dword [rbp-" << varInfo.stackOffset << "], eax";
        gen.emit(oss.str());
    }
    else
    {
        gen.emit("    ; ERROR: Assignment to unknown variable");
    }
}

// VarDeclStmtAST codegen - Declare variables and initialize
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
            oss << "    mov dword [rbp-" << stackOffset << "], eax";
            gen.emit(oss.str());
        }
        else
        {
            // Initialize to zero if no initializer
            std::ostringstream oss;
            oss << "    mov dword [rbp-" << stackOffset << "], 0";
            gen.emit(oss.str());
        }
    }
}

// ExprStmtAST codegen
void ExprStmtAST::codegen(CodeGen &gen) const
{
    Expr->codegen(gen);
}

// CompoundStmtAST codegen
void CompoundStmtAST::codegen(CodeGen &gen) const
{
    for (const auto &stmt : Statements)
    {
        stmt->codegen(gen);
    }
}

// ProgramAST codegen - Main program entry point
void ProgramAST::codegen(CodeGen &gen) const
{
    // Linux ELF64 assembly header
    gen.emit("section .data");
    gen.emit("    buffer times 32 db 0");
    gen.emit("");
    gen.emit("section .text");
    gen.emit("global _start");
    gen.emit("");

    // Simple print function for integers - Linux specific
    gen.emit("print_int:");
    gen.emit("    ; Convert integer in rdi to string and print");
    gen.emit("    push rbp");
    gen.emit("    mov rbp, rsp");
    gen.emit("    push rbx");
    gen.emit("    push rcx");
    gen.emit("    push rdx");
    gen.emit("    push rsi");
    gen.emit("");
    gen.emit("    mov rax, rdi         ; number to convert");
    gen.emit("    mov rsi, buffer + 31 ; point to end of buffer");
    gen.emit("    mov byte [rsi], 0    ; null terminator");
    gen.emit("    dec rsi");
    gen.emit("    mov byte [rsi], 10   ; newline");
    gen.emit("    dec rsi");
    gen.emit("");
    gen.emit("    ; Handle negative numbers");
    gen.emit("    test rax, rax");
    gen.emit("    jns .positive");
    gen.emit("    neg rax");
    gen.emit("    mov bl, 1            ; remember negative");
    gen.emit("    jmp .convert");
    gen.emit(".positive:");
    gen.emit("    mov bl, 0            ; not negative");
    gen.emit("");
    gen.emit(".convert:");
    gen.emit("    mov rcx, 10");
    gen.emit("    xor rdx, rdx");
    gen.emit("    div rcx              ; rax = quotient, rdx = remainder");
    gen.emit("    add dl, '0'          ; convert to ASCII");
    gen.emit("    mov [rsi], dl");
    gen.emit("    dec rsi");
    gen.emit("    test rax, rax");
    gen.emit("    jnz .convert");
    gen.emit("");
    gen.emit("    ; Add minus sign if negative");
    gen.emit("    test bl, bl");
    gen.emit("    jz .print");
    gen.emit("    mov byte [rsi], '-'");
    gen.emit("    dec rsi");
    gen.emit("");
    gen.emit(".print:");
    gen.emit("    inc rsi              ; point to first character");
    gen.emit("    ; Calculate string length");
    gen.emit("    mov rdx, buffer + 32");
    gen.emit("    sub rdx, rsi         ; length including newline");
    gen.emit("    ; Linux sys_write system call");
    gen.emit("    mov rax, 1           ; sys_write");
    gen.emit("    mov rdi, 1           ; stdout");
    gen.emit("    syscall");
    gen.emit("");
    gen.emit("    pop rsi");
    gen.emit("    pop rdx");
    gen.emit("    pop rcx");
    gen.emit("    pop rbx");
    gen.emit("    pop rbp");
    gen.emit("    ret");
    gen.emit("");

    gen.emit("_start:");
    gen.emit("    push rbp");
    gen.emit("    mov rbp, rsp");

    // Calculate total stack space needed
    int totalStackNeeded = 0;
    for (const auto &stmt : Statements)
    {
        const VarDeclStmtAST *varDecl = dynamic_cast<const VarDeclStmtAST *>(stmt.get());
        if (varDecl)
        {
            for (const auto &var : varDecl->getVars())
            {
                totalStackNeeded += getTypeSize(varDecl->getVarType());
            }
        }
    }

    // Reserve stack space if needed
    if (totalStackNeeded > 0)
    {
        // Align to 16-byte boundary
        int alignedStack = ((totalStackNeeded + 15) / 16) * 16;
        std::ostringstream oss;
        oss << "    sub rsp, " << alignedStack;
        gen.emit(oss.str());
    }

    // Generate code for all statements
    for (const auto &stmt : Statements)
    {
        stmt->codegen(gen);
    }

    // Program exit - Linux specific
    gen.emit("    ; Exit program");
    gen.emit("    mov rax, 60         ; sys_exit");
    gen.emit("    mov rdi, 0          ; exit status");
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

// String expression codegen
void StringExprAST::codegen(CodeGen &gen) const
{
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
}

// Function call codegen
void CallExprAST::codegen(CodeGen &gen) const
{
    gen.emit("    ; Function call: " + Callee);
    // For now, just placeholder
}

// Array access codegen
void ArrayExprAST::codegen(CodeGen &gen) const
{
    gen.emit("    ; Array access - placeholder");
}

// If statement codegen - Fixed label generation
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
    else
    {
        // No else clause, false label is the end
        gen.emit(endLabel + ":");
    }
}

// While loop codegen - Fixed
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

// For loop codegen - Fixed to handle increment properly
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

    // Jump back to condition check
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
        gen.emit("    mov rax, 0"); // Return 0 if no value
    }

    gen.emit("    mov rsp, rbp");
    gen.emit("    pop rbp");
    gen.emit("    ret");
}

// Break and continue statements - simplified
void BreakStmtAST::codegen(CodeGen &gen) const
{
    gen.emit("    ; break statement - placeholder");
}

void ContinueStmtAST::codegen(CodeGen &gen) const
{
    gen.emit("    ; continue statement - placeholder");
}

// Function definition codegen
void PrototypeAST::codegen(CodeGen &gen) const
{
    gen.emit(Name + ":");
    gen.emit("    push rbp");
    gen.emit("    mov rbp, rsp");
}

void FunctionAST::codegen(CodeGen &gen) const
{
    Proto->codegen(gen);
    Body->codegen(gen);
    gen.emit("    mov rax, 0");
    gen.emit("    mov rsp, rbp");
    gen.emit("    pop rbp");
    gen.emit("    ret");
}

// Scope expression codegen
void ScopeExprAST::codegen(CodeGen &gen) const
{
    gen.emit("    ; Scope resolution: " + Member);
    Base->codegen(gen);
}

// Print statement codegen - Fixed for Linux
void PrintStmtAST::codegen(CodeGen &gen) const
{
    // Generate code to evaluate the expression
    Value->codegen(gen);

    // Call our print function
    gen.emit("    mov rdi, rax        ; argument for print_int");
    gen.emit("    call print_int      ; call our print function");
}

// Generate assembly from AST
void CodeGen::generateAssembly(ProgramAST *root)
{
    if (root)
    {
        root->codegen(*this);
    }
}

// Write assembly to file
void CodeGen::writeToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return;
    }
    file << code.str();
    file.close();
}

// Get assembly as string
std::string CodeGen::getAssembly() const
{
    return code.str();
}

void CodeGen::generateAssembly(const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return;
    }
    file << code.str();
    file.close();
    std::cout << "📄 Assembly written to " << filename << std::endl;
}

// Linux-specific binary generation
bool CodeGen::assembleToBinary(const std::string &asmFile, const std::string &outputBinary)
{
    std::string objFile = outputBinary + ".o";

    // Step 1: Assemble to object file (Linux ELF64)
    std::string nasmCmd = "nasm -f elf64 " + asmFile + " -o " + objFile;
    std::cout << "Assembling: " << nasmCmd << std::endl;

    int nasmResult = std::system(nasmCmd.c_str());
    if (nasmResult != 0)
    {
        std::cerr << "Error: Assembly failed with nasm" << std::endl;
        return false;
    }

    // Step 2: Link to executable (Linux specific)
    std::string linkCmd = "ld -o " + outputBinary + " " + objFile + " -e _start";
    std::cout << "Linking: " << linkCmd << std::endl;

    int linkResult = std::system(linkCmd.c_str());
    if (linkResult != 0)
    {
        std::cerr << "Error: Linking failed" << std::endl;
        std::remove(objFile.c_str());
        return false;
    }

    // Clean up object file
    std::remove(objFile.c_str());

    std::cout << "✅ Binary generated successfully: " << outputBinary << std::endl;
    return true;
}

bool CodeGen::generateBinary(const std::string &asmFile, const std::string &outputBinary)
{
    generateAssembly(asmFile);
    return assembleToBinary(asmFile, outputBinary);
}