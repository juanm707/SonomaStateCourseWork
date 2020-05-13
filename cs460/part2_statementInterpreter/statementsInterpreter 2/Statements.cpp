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
    TypeDescriptor *rhs = rhsExpression()->evaluate(symTab);
    if (rhsExpression()->token().isName()) {
        //if variable
        if (rhsExpression()->token().isOppositeValue() || rhsExpression()->isOppositeValue()) {
            //if it should be the opposite value of the variable aka -variable
            rhs = rhsExpression()->evaluate(symTab);
            if (rhs->isI()) {
                rhs = new IntegerTypeDescriptor("1ignore", dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue() * -1);
            } else if (rhs->isD()) {
                rhs = new DoubleTypeDescriptor("1ignore",
                                               dynamic_cast<DoubleTypeDescriptor *>(rhs)->doubleValue() * -1);
            } else if (rhs->isS()) {
                std::cout << "AssignmentStatement::evaluate | should not have - next to a string" << std::endl;
                exit(4);
            }
        }
    }
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
    if (rhsExpression()->isOppositeValue()) {
        rhsExpression()->printNegativeSigns();
    }
    _rhsExpression->print();
    std::cout << std::endl;
}

// Print Statement
PrintStatement::PrintStatement() : _rhsExpression{nullptr} {}

PrintStatement::PrintStatement(std::vector<ExprNode *> rhsExprs):
    _rhsStatements(rhsExprs), _rhsExpression{nullptr} {}

ExprNode *&PrintStatement::rhs() {
    return _rhsExpression;
}

void PrintStatement::evaluate(SymTab &symTab) {
    std::string finalString = "";
    for (auto s: _rhsStatements) {
        if (s->token().isString()) {
            //it is a string terminal
            //std::cout << s->token().getString();
            finalString += s->token().getString();
        }
        else if (s->token().isName()) {
            //it is a variable
            TypeDescriptor *v = symTab.getValueFor(s->token().getName());
            if (v->isD()) {
                //std::cout << dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue();
                if (s->token().isOppositeValue())
                    finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue() * -1);
                else
                    finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue());
            }
            else if (v->isI()) {
                //std::cout << dynamic_cast<IntegerTypeDescriptor *>(v)->intValue();
                if (s->token().isOppositeValue())
                    finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(v)->intValue() * -1);
                else
                    finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(v)->intValue());
            }
            else if (v->isS()) {
                if (dynamic_cast<StringTypeDescriptor *>(v)->stringValue() == "\n") {
                    //std::cout << std::endl;
                    finalString += "\n";
                }
                else {
                    //std::cout << dynamic_cast<StringTypeDescriptor *>(v)->stringValue();
                    finalString += dynamic_cast<StringTypeDescriptor *>(v)->stringValue();
                }
            }
        }

        else if (s->token().isArithmeticOperator() || s->token().isRelationalOperator()) {
            // it is expression example a + b, 1 + 2, 1 > a
            TypeDescriptor *e = s->evaluate(symTab);
            if (e->isD()) {
                //std::cout << dynamic_cast<DoubleTypeDescriptor *>(e)->doubleValue();
                if(s->isOppositeValue())
                    finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(e)->doubleValue() * -1);
                else
                    finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(e)->doubleValue());
            }
            else if (e->isI()) {
                //std::cout << dynamic_cast<IntegerTypeDescriptor *>(e)->intValue();
                if (s->isOppositeValue())
                    finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue() * -1);
                else
                    finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue());
            }
            else if (e->isS()) {
                if (dynamic_cast<StringTypeDescriptor *>(e)->stringValue() == "\n") {
                    //std::cout << std::endl;
                    finalString += "\n";
                }
                else {
                    //std::cout << dynamic_cast<StringTypeDescriptor *>(e)->stringValue();
                    finalString += dynamic_cast<StringTypeDescriptor *>(e)->stringValue();
                }
            }
        }
        else if (s->token().isWholeNumber()) {
            if (s->token().isOppositeValue() || s->isOppositeValue())
                finalString += std::to_string(s->token().getWholeNumber() * -1);
            else
                finalString += std::to_string(s->token().getWholeNumber());
        }
        else if (s->token().isDoubleNumber()) {
            if (s->token().isOppositeValue() || s->isOppositeValue())
                finalString += std::to_string(s->token().getDoubleNumber() * -1);
            else
                finalString += std::to_string(s->token().getDoubleNumber());
        }
        finalString += " ";
    }

    std::cout << finalString << std::endl;
}

void PrintStatement::print() {
    std::cout << "print ";
    // print vector
    for (auto s: _rhsStatements) {
        s->print();
        if (s != _rhsStatements.back())
            std::cout << ", ";
        else {}
    }
    //_rhsExpression->print();
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
        if (dynamic_cast<IntegerTypeDescriptor *>(_relExpr->evaluate(symTab))->intValue() == 1) { // check condition
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

