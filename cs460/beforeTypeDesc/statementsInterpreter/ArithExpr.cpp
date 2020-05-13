//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include<iostream>
#include "ArithExpr.hpp"

// ExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

int InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    int lValue = left()->evaluate(symTab);
    int rValue = right()->evaluate(symTab);

    std::string root;
    if (token().is2PartChar())
        root = token().str_symbol();
    else
        root = token().symbol();

    std::cout << "InfixExprNode::evaluate: " << lValue << " " << root << " " << rValue << std::endl;
    if( token().isAdditionOperator() )
        return lValue + rValue;
    else if(token().isSubtractionOperator())
        return lValue - rValue;
    else if(token().isMultiplicationOperator())
        return lValue * rValue;
    else if(token().isDivisionOperator())
        return lValue / rValue; // division by zero?
    else if(token().isIntegerDivisionOperator())
        return lValue / rValue; // Integer Division, might have to change later
    else if(token().isModuloOperator())
        return lValue % rValue;
    else if(token().isEqualEqualOperator())
        return lValue == rValue;
    else if(token().isNotEqualOperator())
        return lValue != rValue;
    else if(token().isGreaterThanOperator())
        return lValue > rValue;
    else if(token().isGreaterThanOrEqualOperator())
        return lValue >= rValue;
    else if(token().isLessThanOperator())
        return lValue < rValue;
    else if(token().isLessThanOrEqualOperator())
        return lValue <= rValue;
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
}

void InfixExprNode::print() {
    _left->print();
    token().print();
    _right->print();
}

// WHoleNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    token().print();
}

int WholeNumber::evaluate(SymTab &symTab) {
    std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
    return token().getWholeNumber();
}

// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}

int Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    std::cout << "Variable::evaluate: returning " << symTab.getValueFor(token().getName()) << std::endl;
    return symTab.getValueFor(token().getName());
}


