//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include "Statements.hpp"
#include <utility>

// Statement
Statement::Statement() {}

Statement::~Statement() {

}

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

Statements::~Statements() {
    for (auto p : _statements)
    {
        delete p;
        p = nullptr;
    }
    _statements.clear();
}

// AssignmentStatement

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    TypeDescriptor *rhs = rhsExpression()->evaluate(symTab);

    if (rhsExpression()->token().isOppositeValue() || rhsExpression()->isOppositeValue()) {
        //if it should be the opposite value
        if (rhs->isI()) {
            rhs = new IntegerTypeDescriptor("1ignore", dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue() * -1);
        } else if (rhs->isD()) {
            rhs = new DoubleTypeDescriptor("1ignore",
                                           dynamic_cast<DoubleTypeDescriptor *>(rhs)->doubleValue() * -1.0);
        } else if (rhs->isS()) {
            std::cout << "AssignmentStatement::evaluate | should not have - next to a string" << std::endl;
            exit(4);
        }
    }
    //TODO: NOT for doubles????
    if (rhsExpression()->isLogicalOppositeValue()) {
        //if it is a variable or whole number, it was already converted
        if (rhsExpression()->token().isWholeNumber()) {
            //do nothing
        }
        else if (rhsExpression()->token().isName()) {
            if (rhsExpression()->token().isLogicalOperator() || rhsExpression()->token().isKeyword()) {
                rhs = new IntegerTypeDescriptor("bool", !(dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue()));
            }
        }
        else
            rhs = new IntegerTypeDescriptor("bool", !(dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue()));
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

    //if (_rhsExpression->isLogicalOppositeValue() && !_rhsExpression->token().isWholeNumber())
        //std::cout << "not(";
    _rhsExpression->print();
    //if (_rhsExpression->isLogicalOppositeValue()  && !_rhsExpression->token().isWholeNumber())
        //std::cout << ")";
    std::cout << std::endl;
}

AssignmentStatement::~AssignmentStatement() {
    delete _rhsExpression;
    _rhsExpression = nullptr;
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
            finalString += s->token().getString();
        }
        else if (s->token().isName() && !(s->token().isLogicalOperator())) {
            //it is a variable
            TypeDescriptor *v = symTab.getValueFor(s->token().getName());
            // TODO: Not keyword only for int?
            if (v->isD()) {
                //std::cout << dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue();
                if (s->token().isOppositeValue())
                    finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue() * -1);
                else
                    finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue());
            }
            else if (v->isI()) {
                //std::cout << dynamic_cast<IntegerTypeDescriptor *>(v)->intValue();
                if (s->token().isOppositeValue()) {
                    if (s->isLogicalOppositeValue())
                        finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(v)->intValue() * -1));
                    else
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(v)->intValue() * -1);
                }
                else {
                    if (s->isLogicalOppositeValue())
                        finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(v)->intValue()));
                    else
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(v)->intValue());
                }
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
                if (s->isOppositeValue()) {
                    if (s->isLogicalOppositeValue())
                        finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue() * -1));
                    else
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue() * -1);
                }
                else {
                    if(s->isLogicalOppositeValue())
                        finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue()));
                    else
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue());
                }
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
        else if (s->token().isLogicalOperator()) {
            TypeDescriptor *e = s->evaluate(symTab);
            if (e->isI()) {
                if (s->isOppositeValue()) {
                    if (s->isLogicalOppositeValue())
                        finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue() * -1));
                    else
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue() * -1);
                } else {
                    if (s->isLogicalOppositeValue())
                        finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue()));
                    else
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue());
                }
            }
            else {
                std::cout << "PrintStatement::evaluate - Logical operator should be used with bool (int) values." << std::endl;
                exit(2);
            }

        }
        else if (s->token().isWholeNumber()) {
            if (s->token().isOppositeValue() || s->isOppositeValue()) {
                if (s->isLogicalOppositeValue())
                    finalString += std::to_string(!(s->token().getWholeNumber() * -1));
                else
                    finalString += std::to_string(s->token().getWholeNumber() * -1);
            }
            else {
                if (s->isLogicalOppositeValue())
                    finalString += std::to_string(!(s->token().getWholeNumber()));
                else
                    finalString += std::to_string(s->token().getWholeNumber());
            }
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
    bool paran = false;
    std::cout << "print ";
    // print vector
    for (auto s: _rhsStatements) {
        s->print();
        if (s != _rhsStatements.back())
            std::cout << ", ";
        else {}
    }
    std::cout << std::endl;
}

PrintStatement::~PrintStatement() {
    delete _rhsExpression;
    _rhsExpression = nullptr;
    for (auto p : _rhsStatements)
    {
        delete p;
        p = nullptr;
    }
    _rhsStatements.clear();
}

//For Statement
ForStatement::ForStatement() : _assignStmt{nullptr}, _relExpr{nullptr},
        _updateAssignStmt{nullptr}, _bodyStatements{nullptr}, init{false}, _rangeInstance{nullptr} {}

ForStatement::ForStatement(Range *rangeInstance, Statements *bodyStatements, std::string ID) : _assignStmt{nullptr},
                                                                                _relExpr{nullptr},
                                                                               _updateAssignStmt{nullptr},
                                                                               _bodyStatements{bodyStatements},
                                                                               init{false},
                                                                               _rangeInstance{rangeInstance},
                                                                               idName{ID} { }

void ForStatement::evaluate(SymTab &symTab) {
    _rangeInstance->setValues(symTab); // set all the values we need
    while( _rangeInstance->condition() ) {
        //in the symbol table, set i to rangeInstance->next(), using in interger type descriptor.
        //the values that get assigned to i through this loop are 0, 1, 2, 3, and 4, successively.
        //execute the statements in sttmts.

        symTab.setValueFor(idName, new IntegerTypeDescriptor(idName, _rangeInstance->next()));
        _bodyStatements->evaluate(symTab);
    }
}

void ForStatement::print() {

    int numValues = _rangeInstance->numValues();
    std::cout << "for " << idName << " in range(";
    if (numValues == 1)
        _rangeInstance->getRangeExpr()->print();
    else if (numValues == 2) {
        _rangeInstance->getInitExpr()->print();
        std::cout << ", ";
        _rangeInstance->getRangeExpr()->print();
    }
    else if (numValues == 3) {
        _rangeInstance->getInitExpr()->print();
        std::cout << ", ";
        _rangeInstance->getRangeExpr()->print();
        std::cout << ", ";
        _rangeInstance->getStepExpr()->print();
    }
    else {
        std::cout << "Expected 1,2, or 3 values for range. Instead got: " << numValues << " values\n";
        exit(3);
    }

    std::cout << "):\n";
    _bodyStatements->print(); // TAB?
    //std::cout << "}\n";

}

ForStatement::~ForStatement() {
    delete _rangeInstance;
    _rangeInstance = nullptr;
    delete _bodyStatements;
    _bodyStatements = nullptr;
}

IfStatement::IfStatement(std::vector<std::pair<ExprNode *, Statements *> > testSuites,
        std::vector< std::string > labels) : _testSuites{testSuites}, _labels{labels} {}

void IfStatement::evaluate(SymTab &symTab) {
    // Loop through the pairs, find the first one that is true, execute its statements, and return.
    for(auto & _testSuite : _testSuites) {
        TypeDescriptor * it = std::get<0>(_testSuite)->evaluate(symTab);
        if(dynamic_cast<IntegerTypeDescriptor *>(it)->intValue()) {
            std::get<1>(_testSuite)->evaluate(symTab);
            return;
        }
    }
}

void IfStatement::print() {
    for (int i  = 0; i < _testSuites.size(); i++) {
        if (_labels[i] == "else")
            std::cout << "else";
        else {
            std::cout << _labels[i] << " ";
            std::get<0>(_testSuites[i])->print();
        }
        std::cout << ":";
        std::cout << std::endl;
        std::cout << "    ";
        std::get<1>(_testSuites[i])->print();
    }
}

IfStatement::~IfStatement() {
    for (auto p : _testSuites)
    {
     delete p.first;
     p.first = nullptr;
     delete p.second;
     p.second = nullptr;
    }
    _testSuites.clear();
}


