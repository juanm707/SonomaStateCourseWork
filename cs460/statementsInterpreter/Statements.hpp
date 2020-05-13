//
// Created by Ali A. Kooshesh on 2/5/19.
//

#ifndef EXPRINTER_STATEMENTS_HPP
#define EXPRINTER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ArithExpr.hpp"
#include "SymTab.hpp"
#include "Range.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
    Statement();
    virtual ~Statement();
    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;
    virtual bool isReturn() = 0;

};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements {
public:
    Statements();
    ~Statements();
    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);
    void print();

    std::vector<Statement *> getStatements() { return _statements; }

private:
    std::vector<Statement *> _statements;
};

// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement {
public:
    AssignmentStatement();
    ~AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);
    AssignmentStatement(std::string lhsVar, std::vector<ExprNode *> arrayTestList);
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr, ExprNode *i);

    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn() { return false; }

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
    std::vector<ExprNode *> arrayElements;
    ExprNode *index;
    bool isArray;
};

// PrintStatement displays the value of the variable
class PrintStatement : public Statement {
public:
    PrintStatement();
    ~PrintStatement();
    PrintStatement(std::vector<ExprNode *> rhsExprs);

    ExprNode *&rhs();

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn() { return false; }

private:
    ExprNode *_rhsExpression;
    std::vector<ExprNode *> _rhsStatements;
};

// ForStatement
class ForStatement : public Statement {
public:
    ForStatement();
    ~ForStatement();
    ForStatement(Range *rangeInstance, Statements *bodyStatements, std::string ID);

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn() { return false; }

private:
    AssignmentStatement *_assignStmt;
    ExprNode *_relExpr;
    AssignmentStatement *_updateAssignStmt;

    Statements *_bodyStatements;
    bool init; // for executing the for loop

    std::string idName;
    Range *_rangeInstance;

};

// IfStatement
class IfStatement : public Statement {
public:
    IfStatement();
    ~IfStatement();
    IfStatement(std::vector< std::pair<ExprNode *, Statements *> > testSuites, std::vector< std::string> labels);

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn() { return false; }

private:
    std::vector< std::pair<ExprNode *, Statements *> > _testSuites;
    std::vector< std::string> _labels; //to print the "if", "elif", "else"
};

// Array op statement
class ArrayOperationStatement : public Statement {
public:
    ArrayOperationStatement();
    ~ArrayOperationStatement();
    ArrayOperationStatement(std::string operation, std::string variable, ExprNode * test);

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn() { return false; }

private:
    std::string op;
    std::string var;
    ExprNode * _test;
};

// Return Statement
class ReturnStatement : public Statement {
public:
    ReturnStatement();
    ~ReturnStatement();
    ReturnStatement(ExprNode * expr);

    ExprNode *returnVal() { return returnValue; }

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn();

private:
    ExprNode *returnValue;
};


// Function Statement
class FunctionStatement : public Statement {
public:
    FunctionStatement();
    ~FunctionStatement();
    FunctionStatement(std::string identifier, Statements * stmts, std::vector<std::string> ids);

    virtual void evaluate(SymTab &symTab);
    virtual void print();
    virtual bool isReturn() { return false; }

private:
    std::string id;
    Statements *_bodyStatements;
    std::vector<std::string> parameterList;
    // Symbol table?
};

// Call Statement to call functions
class CallStatement : public Statement {
public:
    CallStatement();
    ~CallStatement();
    CallStatement(std::string identifier, std::vector<ExprNode *> args);
    void setReturn() { _return = true; }
    void unSetReturn() { _return = false; }
    virtual void evaluate(SymTab &symTab);
    virtual void print();
    TypeDescriptor * eval(SymTab &symTab);
    virtual bool isReturn() { return false; }

private:
    std::string id;
    std::vector<ExprNode *> arguments;
    bool _return;

};
#endif //EXPRINTER_STATEMENTS_HPP
