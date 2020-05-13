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

AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr}, index{nullptr}, isArray{false} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr}, index{nullptr}, isArray{false} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, std::vector<ExprNode *> arrayTestList):
        _lhsVariable{lhsVar}, arrayElements{arrayTestList}, _rhsExpression{nullptr}, index{nullptr}, isArray{true} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr, ExprNode *i):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr}, index{i}, isArray{true} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    if (isArray) {
        if (index == nullptr) {
            // if its null, it means we are not subscripting, just assigning an array to variable
            std::vector<TypeDescriptor *> newArrayElems;
            for ( auto e : arrayElements) {
                if (e->token().getName() != "__end__") {
                    TypeDescriptor *elem = e->evaluate(symTab);
                    newArrayElems.push_back(elem);
                }
            }
            // TODO: Check for same type!
            symTab.setValueFor(lhsVariable(), new ArrayTypeDescriptor(newArrayElems));
        }
        else {
            // index is not null so we are subscripting -> a[i] = ...
            ArrayTypeDescriptor * array = dynamic_cast<ArrayTypeDescriptor *>(symTab.getValueFor(lhsVariable()));
            if (!array->isA()) {
                std::cout << "AssignmentStatement::evaluate - expected an array..." << std::endl;
                exit(3);
            }
            TypeDescriptor *newValue = rhsExpression()->evaluate(symTab);
            // TODO: Check for same type!
            array->updateValue(dynamic_cast<IntegerTypeDescriptor *>(index->evaluate(symTab))->intValue(), newValue);
        }
    }
    else {
        if (rhsExpression()->isFunctionCall()) { // TODO: if time fix not and -
            CallStatement * funcToCall = new CallStatement(rhsExpression()->token().getName(),
                    dynamic_cast<FunctionCall *>(rhsExpression())->getArgs());

            funcToCall->setReturn();
            funcToCall->evaluate(symTab);
            TypeDescriptor * retVal = symTab.getValueFor("1_RETURN");
            if (rhsExpression()->token().isOppositeValue() || rhsExpression()->isOppositeValue()) {
                //if it should be the opposite value
                if (retVal->isI()) {
                    retVal = new IntegerTypeDescriptor("1_RETURN",
                                                    dynamic_cast<IntegerTypeDescriptor *>(retVal)->intValue() * -1);
                } else if (retVal->isD()) {
                    retVal = new DoubleTypeDescriptor("1_RETURN",
                                                   dynamic_cast<DoubleTypeDescriptor *>(retVal)->doubleValue() * -1.0);
                } else if (retVal->isS()) {
                    std::cout << "AssignmentStatement::evaluate | should not have - next to a string" << std::endl;
                    exit(4);
                }
            }

            if (rhsExpression()->isLogicalOppositeValue()) {
                //if it should be the logical opposite value
                if (retVal->isI()) {
                    retVal = new IntegerTypeDescriptor("1_RETURN",
                                                       !dynamic_cast<IntegerTypeDescriptor *>(retVal)->intValue());
                }
                else {
                    std::cout << "Nots only applicable to integers/bools." << std::endl;
                    exit(2);
                }
            }
            symTab.setValueFor(lhsVariable(), retVal);
        }
        else {
            TypeDescriptor *rhs = rhsExpression()->evaluate(symTab);
            if (rhsExpression()->token().isOppositeValue() || rhsExpression()->isOppositeValue()) {
                //if it should be the opposite value
                if (rhs->isI()) {
                    rhs = new IntegerTypeDescriptor("1ignore",
                                                    dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue() * -1);
                } else if (rhs->isD()) {
                    rhs = new DoubleTypeDescriptor("1ignore",
                                                   dynamic_cast<DoubleTypeDescriptor *>(rhs)->doubleValue() * -1.0);
                } else if (rhs->isS()) {
                    std::cout << "AssignmentStatement::evaluate | should not have - next to a string" << std::endl;
                    exit(4);
                }
            }

            if (rhsExpression()->isLogicalOppositeValue()) {
                //if it is a variable or whole number, it was already converted
                if (rhsExpression()->token().isWholeNumber()) {
                    //do nothing
                } else if (rhsExpression()->token().isName()) {
                    if (rhsExpression()->token().isLogicalOperator() || rhsExpression()->token().isKeyword()) {
                        rhs = new IntegerTypeDescriptor("bool",
                                                        !(dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue()));
                    }
                } else
                    rhs = new IntegerTypeDescriptor("bool", !(dynamic_cast<IntegerTypeDescriptor *>(rhs)->intValue()));
            }

            symTab.setValueFor(lhsVariable(), rhs);
        }
    }
}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}

void AssignmentStatement::print() {
    if (index != nullptr) {
        std::cout << _lhsVariable << '[';
        index->print();
        std::cout << "] = ";
    }
    else
        std::cout << _lhsVariable << " = ";
    if (isArray && (index == nullptr)) {
        std::cout << '[';
        for ( auto e : arrayElements) {
            if (e->token().getName() != "__end__") {
                e->print();
                if (e != arrayElements.back())
                    std::cout << ", ";
            }
        }
        std::cout << ']';
    }
    else {
        _rhsExpression->print();
    }
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
            else if (v->isA()) {
                // if its variable array

                if (dynamic_cast<Variable *>(s)->isIndex()) {
                    IntegerTypeDescriptor * index = dynamic_cast<IntegerTypeDescriptor *>(dynamic_cast<Variable *>(s)->getIndex()->evaluate(symTab));
                    TypeDescriptor * ithElem = dynamic_cast<ArrayTypeDescriptor *>(v)->getValueAtIndex(index->intValue());
                    if (ithElem->isS()) {
                        finalString += dynamic_cast<StringTypeDescriptor *>(ithElem)->stringValue();
                    }
                    else if (ithElem->isD()) {
                        finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(ithElem)->doubleValue());
                    }
                    else if (ithElem->isI()) {
                        finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(ithElem)->intValue());
                    }
                    else {
                        std::cout << "PrintStatement::evaluate - Unknown type\n";
                        exit(2);
                    }
                }
                else {
                    // Print the whole array
                    finalString += dynamic_cast<ArrayTypeDescriptor *>(v)->arrayPrintString();
                }

            }
            else if (v->isF()) {
                CallStatement * funcToCall = new CallStatement(s->token().getName(), dynamic_cast<FunctionCall *>(s)->getArgs());
                funcToCall->setReturn();
                funcToCall->evaluate(symTab);
                TypeDescriptor * retVal = symTab.getValueFor("1_RETURN");
                if (retVal->isA()) {
                    if (s->isOppositeValue() || s->isLogicalOppositeValue()) {
                        std::cout << "Logical not and - are only for integers and non string types." << std::endl;
                        exit(2);
                    }
                    finalString += dynamic_cast<ArrayTypeDescriptor *>(retVal)->arrayPrintString();
                }
                else if (retVal->isS()) {
                    if (s->isOppositeValue() || s->isLogicalOppositeValue()) {
                        std::cout << "Logical not and - are only for integers and non string types." << std::endl;
                        exit(2);
                    }
                    finalString += dynamic_cast<StringTypeDescriptor *>(retVal)->stringValue();
                }
                else if (retVal->isD()) {
                    if (s->isLogicalOppositeValue()) {
                        std::cout << "Logical not and - are only for integers and non string types." << std::endl;
                        exit(2);
                    }
                    if (s->isOppositeValue()) {
                        finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(retVal)->doubleValue() * -1.0);
                    }
                    else
                        finalString += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(retVal)->doubleValue());
                }
                else if (retVal->isI()) {
                    if (s->isOppositeValue()) {
                        if (s->isLogicalOppositeValue()) {
                            finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(retVal)->intValue()*-1));
                        }
                        else
                            finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(retVal)->intValue()*-1);
                    }
                    else {
                        if (s->isLogicalOppositeValue()) {
                            finalString += std::to_string(!(dynamic_cast<IntegerTypeDescriptor *>(retVal)->intValue()));
                        }
                        else
                            finalString += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(retVal)->intValue());
                    }
                }
                else {
                    std::cout << "PrintStatement::evaluate, return type cannot be function." << std::endl;
                    exit(3);
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


ArrayOperationStatement::ArrayOperationStatement() : op{""}, var{""}, _test{nullptr} {

}

ArrayOperationStatement::~ArrayOperationStatement() {

}

ArrayOperationStatement::ArrayOperationStatement(std::string operation, std::string variable, ExprNode *test)
                                                : op{operation}, var{variable}, _test{test} {}

void ArrayOperationStatement::print() {
    std::cout << var << '.' << op << '(';
    if (_test != nullptr)
        _test->print();
    std::cout << ')' << std::endl;
}

void ArrayOperationStatement::evaluate(SymTab &symTab) {
    if (op == "push" || op == "append") {
        if (_test != nullptr) {
            ArrayTypeDescriptor * arr = dynamic_cast<ArrayTypeDescriptor *>(symTab.getValueFor(var));
            TypeDescriptor *newElem = _test->evaluate(symTab);
            arr->push(newElem);
        }
        else {
            std::cout << "Cannot push/append a null test." << std::endl;
            exit(3);
        }
    }
    else if (op == "pop") {
        ArrayTypeDescriptor * arr = dynamic_cast<ArrayTypeDescriptor *>(symTab.getValueFor(var));
        arr->pop();
    }
    else {
        std::cout << "Unknown operation for arrays: " << op << std::endl;
        exit(2);
    }
}

CallStatement::CallStatement() : id{""} {}

CallStatement::~CallStatement() {

}

CallStatement::CallStatement(std::string identifier, std::vector<ExprNode *> args)
                            : id{identifier}, arguments{args}, _return{false} {}

void CallStatement::evaluate(SymTab &parentSymTab) {
    // TODO: check that params size and arg size match
    SymTab newSymTab;
    newSymTab = parentSymTab.copyValues();

    TypeDescriptor *f = parentSymTab.getValueFor(id);
    FunctionTypeDescriptor * functionToBeCalled = dynamic_cast<FunctionTypeDescriptor *>(f);

    std::vector<std::string> params = functionToBeCalled->getParams();
    for (int i = 0; i < params.size(); i++) {
        std::string paramName = params[i];
        ExprNode *argForParam = arguments[i];
        TypeDescriptor *v = argForParam->evaluate(parentSymTab);

        if (v->isI()) {
            // make copy of value
            IntegerTypeDescriptor *val = new IntegerTypeDescriptor(paramName, dynamic_cast<IntegerTypeDescriptor *>(v)->intValue());
            newSymTab.setValueFor(paramName, val);
        }
        else if (v->isD()) {
            // make copy of value
            DoubleTypeDescriptor *val = new DoubleTypeDescriptor(paramName, dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue());
            newSymTab.setValueFor(paramName, val);
        }
        else if (v->isS()) {
            // make copy of value
            StringTypeDescriptor *val = new StringTypeDescriptor(paramName, dynamic_cast<StringTypeDescriptor *>(v)->stringValue());
            newSymTab.setValueFor(paramName, val);
        }
        else if (v->isA()) {
            // if array, pass by reference
            newSymTab.setValueFor(paramName, dynamic_cast<ArrayTypeDescriptor *>(v));
        }

    }
    // Check for return statement, should be the last one
    std::vector<Statement *> stmts = functionToBeCalled->getStatements()->getStatements();
    if (stmts.back()->isReturn()) {
        functionToBeCalled->getStatements()->evaluate(newSymTab);
        parentSymTab.setValueFor("1_RETURN", newSymTab.getValueFor("1_RETURN"));
    }
    else {
        functionToBeCalled->getStatements()->evaluate(newSymTab);
    }
}

void CallStatement::print() {
    std::cout << id << "(";
    for (auto e: arguments) {
        e->print();
        if (e != arguments.back())
            std::cout << ", ";
    }
    std::cout << ')' << std::endl;
}

TypeDescriptor *CallStatement::eval(SymTab &symTab) {
    return nullptr;
}

FunctionStatement::FunctionStatement() : _bodyStatements{nullptr}, id{""} {

}

FunctionStatement::~FunctionStatement() {

}

FunctionStatement::FunctionStatement(std::string identifier, Statements *stmts, std::vector<std::string> ids)
                                     : id{identifier}, _bodyStatements{stmts}, parameterList{ids} {}

void FunctionStatement::evaluate(SymTab &symTab) {
    FunctionTypeDescriptor *func = new FunctionTypeDescriptor(id, _bodyStatements, parameterList);
    symTab.setValueFor(id, func);
}

void FunctionStatement::print() {
    std::cout << "def " << id << '(';
    if (parameterList.empty())
        std::cout << "):" << std::endl;
    else {
        for (auto e : parameterList) {
            if (e != parameterList.back()) {
                std::cout << e << ", ";
            } else std::cout << e;
        }
        std::cout << "):" << std::endl;
    }
    _bodyStatements->print();
    std::cout << "END FUNCTION: " << id << " :STATEMENTS" << std::endl;
}

ReturnStatement::ReturnStatement() : returnValue{nullptr} {

}

ReturnStatement::~ReturnStatement() {

}

ReturnStatement::ReturnStatement(ExprNode *expr) : returnValue{expr} {}

void ReturnStatement::evaluate(SymTab &symTab) {
    if (returnValue) {
        TypeDescriptor *v = returnValue->evaluate(symTab);
        if (v->isI()) {
            // make copy of value
            IntegerTypeDescriptor *val = new IntegerTypeDescriptor("1_RETURN",
                                                                   dynamic_cast<IntegerTypeDescriptor *>(v)->intValue());
            symTab.setValueFor("1_RETURN", val);
        } else if (v->isD()) {
            // make copy of value
            DoubleTypeDescriptor *val = new DoubleTypeDescriptor("1_RETURN",
                                                                 dynamic_cast<DoubleTypeDescriptor *>(v)->doubleValue());
            symTab.setValueFor("1_RETURN", val);
        } else if (v->isS()) {
            // make copy of value
            StringTypeDescriptor *val = new StringTypeDescriptor("1_RETURN",
                                                                 dynamic_cast<StringTypeDescriptor *>(v)->stringValue());
            symTab.setValueFor("1_RETURN", val);
        } else if (v->isA()) {
            // if array, pass by reference
            symTab.setValueFor("1_RETURN", dynamic_cast<ArrayTypeDescriptor *>(v));
        }
    }
}

void ReturnStatement::print() {
    std::cout << "return ";
    if (returnValue != nullptr)
        returnValue->print();
    std::cout << std::endl;
}

bool ReturnStatement::isReturn() {
    if (returnValue == nullptr)
        return false;
    else
        return true;
}
