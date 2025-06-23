#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Forward declarations
class ExprAST;
class StmtAST;

// Type system
enum class DataType
{
    VOID,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    BOOL,
    STRING,
    AUTO,
    UNKNOWN
};

// Base class for all expression nodes.
class ExprAST
{
public:
    virtual ~ExprAST() = default;
    virtual void print() const = 0;
};

// Base class for all statement nodes
class StmtAST
{
public:
    virtual ~StmtAST() = default;
    virtual void print() const = 0;
};

// Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST
{
    double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
    void print() const override { std::cout << Val; }
    double getValue() const { return Val; }
};

// Expression class for string literals
class StringExprAST : public ExprAST
{
    string Val;

public:
    StringExprAST(const string &Val) : Val(Val) {}
    void print() const override { std::cout << "\"" << Val << "\""; }
    const string &getValue() const { return Val; }
};

// Expression class for character literals
class CharExprAST : public ExprAST
{
    char Val;

public:
    CharExprAST(char Val) : Val(Val) {}
    void print() const override { std::cout << "'" << Val << "'"; }
    char getValue() const { return Val; }
};

// Expression class for boolean literals
class BoolExprAST : public ExprAST
{
    bool Val;

public:
    BoolExprAST(bool Val) : Val(Val) {}
    void print() const override { std::cout << (Val ? "true" : "false"); }
    bool getValue() const { return Val; }
};

// Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST
{
    string Name;

public:
    VariableExprAST(const string &Name) : Name(Name) {}
    void print() const override { std::cout << Name; }
    const string &getName() const { return Name; }
};

// Expression class for a binary operator.
class BinaryExprAST : public ExprAST
{
    string Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(const string &op, unique_ptr<ExprAST> LHS,
                  unique_ptr<ExprAST> RHS)
        : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    void print() const override
    {
        std::cout << "(";
        LHS->print();
        std::cout << " " << Op << " ";
        RHS->print();
        std::cout << ")";
    }
    const string &getOp() const { return Op; }
};

// Expression class for unary operators
class UnaryExprAST : public ExprAST
{
    string Op;
    unique_ptr<ExprAST> Operand;

public:
    UnaryExprAST(const string &op, unique_ptr<ExprAST> Operand)
        : Op(op), Operand(std::move(Operand)) {}
    void print() const override
    {
        std::cout << Op;
        Operand->print();
    }
};

// Expression class for function calls.
class CallExprAST : public ExprAST
{
    string Callee;
    vector<unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const string &Callee,
                vector<unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}
    void print() const override
    {
        std::cout << Callee << "(";
        for (size_t i = 0; i < Args.size(); ++i)
        {
            Args[i]->print();
            if (i < Args.size() - 1)
                std::cout << ", ";
        }
        std::cout << ")";
    }
};

// Expression class for array access
class ArrayExprAST : public ExprAST
{
    unique_ptr<ExprAST> Array;
    unique_ptr<ExprAST> Index;

public:
    ArrayExprAST(unique_ptr<ExprAST> Array, unique_ptr<ExprAST> Index)
        : Array(std::move(Array)), Index(std::move(Index)) {}
    void print() const override
    {
        Array->print();
        std::cout << "[";
        Index->print();
        std::cout << "]";
    }
};

// Expression class for assignment
class AssignmentExprAST : public ExprAST
{
    unique_ptr<ExprAST> LHS;
    unique_ptr<ExprAST> RHS;

public:
    AssignmentExprAST(unique_ptr<ExprAST> LHS, unique_ptr<ExprAST> RHS)
        : LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    void print() const override
    {
        LHS->print();
        std::cout << " = ";
        RHS->print();
    }
};

// Variable declaration statement
class VarDeclStmtAST : public StmtAST
{
    DataType Type;
    std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> Vars;

public:
    VarDeclStmtAST(DataType Type, std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> Vars)
        : Type(Type), Vars(std::move(Vars)) {}
    void print() const override
    {
        std::cout << "var ";
        for (size_t i = 0; i < Vars.size(); ++i)
        {
            std::cout << Vars[i].first;
            if (Vars[i].second)
            {
                std::cout << " = ";
                Vars[i].second->print();
            }
            if (i + 1 < Vars.size())
                std::cout << ", ";
        }
        std::cout << ";";
    }
    DataType getVarType() const { return Type; }
    const std::vector<std::pair<std::string, std::unique_ptr<ExprAST>>> &getVars() const { return Vars; }
};

// Expression statement (expression followed by semicolon)
class ExprStmtAST : public StmtAST
{
    unique_ptr<ExprAST> Expr;

public:
    ExprStmtAST(unique_ptr<ExprAST> Expr) : Expr(std::move(Expr)) {}
    void print() const override
    {
        Expr->print();
        std::cout << ";";
    }
};

// Compound statement (block of statements)
class CompoundStmtAST : public StmtAST
{
    vector<unique_ptr<StmtAST>> Statements;

public:
    CompoundStmtAST(vector<unique_ptr<StmtAST>> Statements)
        : Statements(std::move(Statements)) {}
    void print() const override
    {
        std::cout << "{" << std::endl;
        for (const auto &stmt : Statements)
        {
            std::cout << "  ";
            stmt->print();
            std::cout << std::endl;
        }
        std::cout << "}";
    }
    void addStatement(unique_ptr<StmtAST> stmt) { Statements.push_back(std::move(stmt)); }
};

// If statement
class IfStmtAST : public StmtAST
{
    unique_ptr<ExprAST> Condition;
    unique_ptr<StmtAST> ThenStmt;
    unique_ptr<StmtAST> ElseStmt;

public:
    IfStmtAST(unique_ptr<ExprAST> Condition, unique_ptr<StmtAST> ThenStmt, unique_ptr<StmtAST> ElseStmt = nullptr)
        : Condition(std::move(Condition)), ThenStmt(std::move(ThenStmt)), ElseStmt(std::move(ElseStmt)) {}
    void print() const override
    {
        std::cout << "if (";
        Condition->print();
        std::cout << ") ";
        ThenStmt->print();
        if (ElseStmt)
        {
            std::cout << " else ";
            ElseStmt->print();
        }
    }
};

// While loop statement
class WhileStmtAST : public StmtAST
{
    unique_ptr<ExprAST> Condition;
    unique_ptr<StmtAST> Body;

public:
    WhileStmtAST(unique_ptr<ExprAST> Condition, unique_ptr<StmtAST> Body)
        : Condition(std::move(Condition)), Body(std::move(Body)) {}
    void print() const override
    {
        std::cout << "while (";
        Condition->print();
        std::cout << ") ";
        Body->print();
    }
};

// For loop statement
class ForStmtAST : public StmtAST
{
    unique_ptr<StmtAST> Init;
    unique_ptr<ExprAST> Condition;
    unique_ptr<ExprAST> Update;
    unique_ptr<StmtAST> Body;

public:
    ForStmtAST(unique_ptr<StmtAST> Init, unique_ptr<ExprAST> Condition,
               unique_ptr<ExprAST> Update, unique_ptr<StmtAST> Body)
        : Init(std::move(Init)), Condition(std::move(Condition)),
          Update(std::move(Update)), Body(std::move(Body)) {}
    void print() const override
    {
        std::cout << "for (";
        if (Init)
            Init->print();
        std::cout << "; ";
        if (Condition)
            Condition->print();
        std::cout << "; ";
        if (Update)
            Update->print();
        std::cout << ") ";
        Body->print();
    }
};

// Return statement
class ReturnStmtAST : public StmtAST
{
    unique_ptr<ExprAST> Value;

public:
    ReturnStmtAST(unique_ptr<ExprAST> Value = nullptr) : Value(std::move(Value)) {}
    void print() const override
    {
        std::cout << "return";
        if (Value)
        {
            std::cout << " ";
            Value->print();
        }
    }
};

// Break statement
class BreakStmtAST : public StmtAST
{
public:
    void print() const override { std::cout << "break"; }
};

// Continue statement
class ContinueStmtAST : public StmtAST
{
public:
    void print() const override { std::cout << "continue"; }
};

// This class represents the "prototype" for a function,
// which captures its name, and its argument names (thus implicitly the number
// of arguments the function takes).
class PrototypeAST : public ExprAST
{
    DataType ReturnType;
    string Name;
    vector<pair<DataType, string>> Args;
    bool IsOperator;
    unsigned Precedence;

public:
    PrototypeAST(DataType ReturnType, const string &name, vector<pair<DataType, string>> Args,
                 bool IsOperator = false, unsigned Precedence = 0)
        : ReturnType(ReturnType), Name(name), Args(std::move(Args)), IsOperator(IsOperator), Precedence(Precedence) {}
    void print() const override
    {
        std::cout << "def " << Name << "(";
        for (size_t i = 0; i < Args.size(); ++i)
        {
            std::cout << Args[i].second;
            if (i < Args.size() - 1)
                std::cout << ", ";
        }
        std::cout << ")";
    }
    DataType getReturnType() const { return ReturnType; }
    const string &getName() const { return Name; }
    const vector<pair<DataType, string>> &getArgs() const { return Args; }
    bool isOperator() const { return IsOperator; }
    unsigned getPrecedence() const { return Precedence; }
};

// This class represents a function definition itself.
class FunctionAST : public StmtAST
{
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<StmtAST> Body;

public:
    FunctionAST(unique_ptr<PrototypeAST> Proto, unique_ptr<StmtAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}
    void print() const override
    {
        Proto->print();
        std::cout << " ";
        Body->print();
    }
};

// Program AST - top level container
class ProgramAST
{
    vector<unique_ptr<StmtAST>> Statements;
    vector<unique_ptr<FunctionAST>> Functions;
    vector<unique_ptr<PrototypeAST>> Externs;

public:
    ProgramAST() = default;

    void addStatement(unique_ptr<StmtAST> stmt) { Statements.push_back(std::move(stmt)); }
    void addFunction(unique_ptr<FunctionAST> func) { Functions.push_back(std::move(func)); }
    void addExtern(unique_ptr<PrototypeAST> ext) { Externs.push_back(std::move(ext)); }

    void print() const
    {
        for (const auto &ext : Externs)
        {
            ext->print();
            std::cout << ";" << std::endl;
        }
        for (const auto &func : Functions)
        {
            func->print();
            std::cout << std::endl;
        }
        for (const auto &stmt : Statements)
        {
            stmt->print();
            std::cout << std::endl;
        }
    }
};

/// ScopeExprAST - Expression class for scope resolution, e.g. `std::vector`
class ScopeExprAST : public ExprAST
{
    std::unique_ptr<ExprAST> Base;
    std::string Member;

public:
    ScopeExprAST(std::unique_ptr<ExprAST> Base, const std::string &Member)
        : Base(std::move(Base)), Member(Member) {}

    void print() const override
    {
        Base->print();
        std::cout << "::" << Member;
    }
};

#endif // AST_H