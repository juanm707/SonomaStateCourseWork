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

    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
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

private:
    std::vector< std::pair<ExprNode *, Statements *> > _testSuites;
    std::vector< std::string> _labels; //to print the "if", "elif", "else"
};



#endif //EXPRINTER_STATEMENTS_HPP
