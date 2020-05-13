//
// Created by Ali A. Kooshesh on 2/5/19.
//

#ifndef EXPRINTER_ARITHEXPR_HPP
#define EXPRINTER_ARITHEXPR_HPP

#include "Token.hpp"
#include "SymTab.hpp"

// Classes in this file define the internal representation of arithmetic expressions.


// An ExprNode serves as the base class (super class) for arithmetic expression.
// It forces the derived classes (subclasses) to implement two functions, print and
// evaluate.
class ExprNode {
public:
    ExprNode(Token token);
    Token token();

    bool isOppositeValue() { return _isOppositeValue; }
    void setOppositeValue() { _isOppositeValue = true; }
    void unSetOppositeValue() { _isOppositeValue = false; }

    void setNegSignCount(int n) { _negSignCount = n; } //for display purposes
    void printNegativeSigns() const; //for display purposes


    virtual void print() = 0;
    virtual TypeDescriptor * evaluate(SymTab &symTab) = 0;

private:
    Token _token;
    bool _isOppositeValue;
    int _negSignCount; //for display purposes

};


// An InfixExprNode is useful to represent binary arithmetic operators.
class InfixExprNode: public ExprNode {  // An expression tree node.

public:
    InfixExprNode(Token tk);

    ExprNode *&left();
    ExprNode *&right();
    virtual void print();
    virtual TypeDescriptor * evaluate(SymTab &symTab);


private:
    ExprNode *_left, *_right;

    // Student added helper functions
    TypeDescriptor * stringAddition(StringTypeDescriptor * s1, StringTypeDescriptor * s2);
};

// WholeNumber is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class WholeNumber: public ExprNode {
public:
    WholeNumber(Token token);
    virtual void print();
    virtual TypeDescriptor* evaluate(SymTab &symTab);
};

class DoubleNumber: public ExprNode {
public:
    DoubleNumber(Token token);
    virtual void print();
    virtual TypeDescriptor* evaluate(SymTab &symTab);
};

// Variable is a leaf-node in an expression tree. It corresponds to
// a terminal in the production rules of the grammar that describes the
// syntax of arithmetic expressions.

class Variable: public ExprNode {
public:
    Variable(Token token);
    virtual void print();
    virtual TypeDescriptor* evaluate(SymTab &symTab);
};

class StringTerminal: public ExprNode {
public:
    StringTerminal(Token token);
    virtual void print();
    virtual TypeDescriptor* evaluate(SymTab &symTab);

private:
    bool hasNewLineChar;
};
#endif //EXPRINTER_ARITHEXPR_HPP
