#include <string>
#include <vector>
#include <map>
#include "lexical.h"

class ExprAST {
public:
    virtual ~ExprAST() {}
};

class NumberExprAST : public ExprAST {
    double Val;
public:
    NumberExprAST(double val) : Val(val) {}
};

class VariableExprAST : public ExprAST {
    std::string Name;
public:
    VariableExprAST(const std::string &name) : Name(name) {}
};

class BinaryExprAST : public ExprAST {
    char Op;
    ExprAST *LHS, *RHS;
public:
    BinaryExprAST(char op, ExprAST *lhs, ExprAST *rhs)
        : Op(op), LHS(lhs), RHS(rhs){}
};

class CallExprAST : public ExprAST {
    std::string Callee;
    std::vector<ExprAST*> Args;
public:
    CallExprAST(const std::string &callee, std::vector<ExprAST*> &args)
        : Callee(callee), Args(args) {}
};

class PrototypeAST {
    std::string Name;
    std::vector<std::string> Args;
public:
    PrototypeAST(const std::string &name, const std::vector<std::string> &args)
        : Name(name), Args(args) {}
};

class FunctionAST {
    PrototypeAST* Proto;
    ExprAST* Body;
public:
    FunctionAST(PrototypeAST* proto, ExprAST* body)
        : Proto(proto), Body(body) {}
};

static int CurTok;
static int getNextToken() {
    CurTok = gettok();
    return CurTok;
}
static std::map<char, int> BinopPrecedence = {
    {'<', 10}, {'+', 20}, {'-', 20}, {'*', 40}};

ExprAST *Error(const char *Str) {
    fprintf(stderr, "Error: %s\n", Str);
    return 0;
}

PrototypeAST *ErrorP(const char *Str) {
    Error(Str);
    return 0;
}

FunctionAST *ErrorF(const char *Str) {
    Error(Str);
    return 0;
}

static ExprAST *ParseNumberExpr() {
    ExprAST *Result = new NumberExprAST(NumVal);
    getNextToken();
    return Result;
}

static ExprAST *ParseIdentifierExpr(){
    std::string IdName = IdentifierStr;

    getNextToken();

    if (CurTok != '(')
        return new VariableExprAST(IdName);

    getNextToken();
    std::vector<ExprAST*> Args;
    if (CurTok != ')') {
        while (1) {
            ExprAST *Arg = ParseExpression();
            if (!Arg) return 0;
            Args.push_back(Arg);

            if (CurTok == ')') break;
            if (CurTok != ',') return Error("expected ')' or ',' in argument lsit");
            getNextToken();
        }
    }

}

static ExprAST *ParseExpression() {
    ExprAST *LHS = ParsePrimary();
    if (!LHS) return 0;
    return ParseBinopRHS(0, LHS);

}

static ExprAST *ParseBinopRHS(int ExprPrec, ExprAST *LHS) {
    while (true) {
        int TokPrec = GetTokPrecedence();
        if (TokPrec < ExprPrec) return LHS;
        int BinOp = CurTok;
        getNextToken();

        ExprAST *RHS = ParsePrimary();
        if (!RHS) return 0;
        int NextPrec = GetTokPrecedence();
        if (TokPrec < NextPrec) {
            RHS = ParseBinopRHS(TokPrec+1, RHS);
            if (RHS == 0) return 0;
        }
        LHS = new BinaryExprAST(BinOp, LHS, RHS);
    }
    
}

static PrototypeAST *ParsePrototype() {
    if (CurTok != tok_identifier) return ErrorP("Expected funtion name in prototype");
    std::string FnName = IdentifierStr;
    getNextToken();
    if (CurTok != 'C') return ErrorP("Expected '(' in prototype");

    std::vector<std::string> ArgNames;
    while (getNextToken() == tok_identifier) {
        ArgNames.push_back(IdentifierStr);
    }
    if (CurTok != ')') return ErrorP("Expected ')' in prototype");

    getNextToken();
    return new PrototypeAST(FnName, ArgNames);

}
static FunctionAST *ParseDefinition() {
    getNextToken();
    PrototypeAST *Proto = ParsePrototype();
    if (Proto == 0) return 0;
    if (ExprAST *E = ParseExpression()) return new FunctionAST(Proto, E);
    return 0;
}

static PrototypeAST *ParseExtern() {
    getNextToken();
    return ParsePrototype();
}

static FunctionAST *ParseTopLevelExpr() {
    if (ExprAST *E = ParseExpression()) {
        PrototypeAST *Proto = new PrototypeAST("", std::vector<std::string>());
        return new FunctionAST(Proto, E);
    }
    return 0;
}

static ExprAST *ParseParenExpr() {
    getNextToken();
    ExprAST *V = ParseExpression();
    if (!V) return 0;
    if (CurTok != ')') return Error("expected ')'");
    getNextToken();
    return V;
}

static int GetTokPrecedence() {
    if (!isascii(CurTok)) return -1;
    int TokPrec = BinopPrecedence[CurTok];
    if (TokPrec <= 0) return -1;
    return TokPrec; 
}


static ExprAST *ParsePrimary() {
    switch (CurTok) {
        case tok_identifier:
            return ParseIdentifierExpr();
        case tok_number:
            return ParseNumberExpr();
        case '(':
            return ParseParenExpr();
        default:
            return Error("unknown token when expecting an expression");
    }
}

static void MainLoop() {
    while(1) {
        fprintf(stderr, "ready>  ");
        switch (CurTok) {
            case tok_eof:
                return;
            case ';':
                getNextToken();
                break;
            case tok_def:
                HandleDefinition();
                break;
            case tok_extern:
                HandleExtern();
                break;
            default:
                break;
        }
    }
}