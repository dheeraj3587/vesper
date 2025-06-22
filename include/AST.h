#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Base class for all expression nodes.
class ExprAST
{
public:
    virtual ~ExprAST() = default;
    virtual void print() const = 0;
};

// Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST
{
    double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
    void print() const override { std::cout << Val; }
};

// Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST
{
    string Name;

public:
    VariableExprAST(const string &Name) : Name(Name) {}
    void print() const override { std::cout << Name; }
};

// Expression class for a binary operator.
class BinaryExprAST : public ExprAST
{
    char Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op, unique_ptr<ExprAST> LHS,
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

// This class represents the "prototype" for a function,
// which captures its name, and its argument names (thus implicitly the number
// of arguments the function takes).
class PrototypeAST : public ExprAST
{
    string Name;
    vector<string> Args;
    bool IsOperator;
    unsigned Precedence;

public:
    PrototypeAST(const string &name, vector<string> Args, bool IsOperator = false, unsigned Precedence = 0)
        : Name(name), Args(std::move(Args)), IsOperator(IsOperator), Precedence(Precedence) {}
    void print() const override
    {
        std::cout << "def " << Name << "(";
        for (size_t i = 0; i < Args.size(); ++i)
        {
            std::cout << Args[i];
            if (i < Args.size() - 1)
                std::cout << ", ";
        }
        std::cout << ")";
    }
};

// This class represents a function definition itself.
class FunctionAST : public ExprAST
{
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<ExprAST> Body;

public:
    FunctionAST(unique_ptr<PrototypeAST> Proto,
                unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}
    void print() const override
    {
        Proto->print();
        std::cout << " ";
        Body->print();
    }
};

#endif // AST_H