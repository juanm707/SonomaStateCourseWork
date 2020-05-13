//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include "Statements.hpp"

// Statement
Statement::Statement() {}

// Statements

Statements::Statements() {}
void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    for (auto s: _statements)
        s->print();
}

void Statements::evaluate(SymTab &symTab) {
    for (auto s: _statements)
        s->evaluate(symTab);
}

// AssignmentStatement

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    int rhs = rhsExpression()->evaluate(symTab);
    symTab.setValueFor(lhsVariable(), rhs);
}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}

void AssignmentStatement::print() {
    std::cout << _lhsVariable << " = ";
    _rhsExpression->print();
    std::cout << std::endl;
}

// Print Statement
PrintStatement::PrintStatement() : _rhsExpression{nullptr} {}

PrintStatement::PrintStatement(ExprNode *rhsExpr):
    _rhsExpression(rhsExpr) {}

ExprNode *&PrintStatement::rhs() {
    return _rhsExpression;
}

void PrintStatement::evaluate(SymTab &symTab) {
    int printValue = rhs()->evaluate(symTab);
    std::cout << printValue << std:: endl;

}

void PrintStatement::print() {
    std::cout << "print ";
    _rhsExpression->print();
    std::cout << std::endl;
}

//For Statement
ForStatement::ForStatement() : _assignStmt{nullptr}, _relExpr{nullptr},
        _updateAssignStmt{nullptr}, _bodyStatements{nullptr}, init{false} {}

ForStatement::ForStatement(AssignmentStatement *assignStmt, ExprNode *relExpr, AssignmentStatement *updateAssignStmt,
                           Statements *bodyStatements) :
                           _assignStmt{assignStmt}, _relExpr{relExpr},
                           _updateAssignStmt{updateAssignStmt}, _bodyStatements{bodyStatements} {
    init = false;
}

AssignmentStatement *&ForStatement::assignStmt() {
    return _assignStmt;
}

ExprNode *&ForStatement::relExpr() {
    return _relExpr;
}

AssignmentStatement *&ForStatement::updateAssignStmt() {
    return _updateAssignStmt;
}

Statements *&ForStatement::bodyStatements() {
    return _bodyStatements;
}

void ForStatement::evaluate(SymTab &symTab) {
    if (init) {
        if (_relExpr->evaluate(symTab)) { // check condition
            _bodyStatements->evaluate(symTab); // execute the body if true
            _updateAssignStmt->evaluate(symTab); // update the variable
            evaluate(symTab);
        }
        else {
            init = false;
            return;
        }
    }
    else {
        _assignStmt->evaluate(symTab); // set variable = x
        init = true;
        evaluate(symTab);
    }
}

void ForStatement::print() {
    std::cout << "for ( ";
    std::string assignStmtLHS = _assignStmt->lhsVariable();
    std::cout << assignStmtLHS;
    std::cout << " = ";
    _assignStmt->rhsExpression()->print();
    std::cout << "; ";
    _relExpr->print();
    std::cout << "; ";
    std::string updateAssignStmtLHS = _updateAssignStmt->lhsVariable();
    std::cout << updateAssignStmtLHS;
    std::cout << " = ";
    _updateAssignStmt->rhsExpression()->print();
    std::cout << " ) {\n";
    _bodyStatements->print(); // TAB?
    std::cout << "}\n";
}

