#ifndef __AST_H__
#define __AST_H__

// #include <logger/logger.h"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <kaleidoscope/kaleidoscope.h>


class ExprAST {
public:
  virtual ~ExprAST() {}
  virtual llvm::Value *codegen() = 0;
};

// Represents the "prototype" for a function,
// which captures its name, and its argument names
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &name, std::vector<std::string> Args)
      : Name(name), Args(std::move(Args)) {}

  llvm::Function *codegen();
  const std::string &getName() const { return Name; }
};


// Expression class for a binary operator
class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  llvm::Value *codegen() override;
};


// Expression class for function calls
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}
  llvm::Value *codegen() override;
};

// Represents a function definition itself
class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
  llvm::Function *codegen();
};

// Expression class for numeric literals like "1.0"
class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}
  llvm::Value *codegen() override;
};

// Expression class for referencing a variable, like "a"
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
  llvm::Value *codegen() override;
};

#endif