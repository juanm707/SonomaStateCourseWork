//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include<iostream>
#include "ArithExpr.hpp"
#include "TypeDescriptor.hpp"
#include "Statements.hpp"

// ExprNode
ExprNode::ExprNode(Token token): _token{token}, _isOppositeValue{false}, _logicalOpposite{false} {}

Token ExprNode::token() { return _token; }

void ExprNode::printNegativeSigns() const {
    //for display purposes
    for (int i = 0; i < _negSignCount; i++)
        std::cout << '-';
}

ExprNode::~ExprNode() {

}

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }

TypeDescriptor* InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    TypeDescriptor* lValue = left()->evaluate(symTab);
    TypeDescriptor* rValue = right()->evaluate(symTab);

    bool bothStrings = false;
    bool intAndDouble = false;
    bool bothInt = false;
    bool bothDouble = false;
    bool l = false;
    bool r = false;

    if (lValue->isS() && rValue->isS()) {
        // both are strings
        bothStrings = true;
    }

    else if (lValue->isI() && rValue->isI()) {
        // both are integers
        bothInt = true;
        // do int stuff
    }

    else if (lValue->isD() && rValue->isD()) {
        // both are doubles
        bothDouble = true;
        // do double stuff
    }

    else {
        // one of them is int and one is double
        // the double one, l or r is set to true if double
        intAndDouble = true;
        if (lValue->isD())
            l = true;
        else
            r = true;
    }

    // START - FOR OUTPUT PURPOSES
//    std::string root;
//    if (token().is2PartChar())
//        root = token().str_symbol();
//    else if (token().isAndOperator())
//        root = "and";
//    else if (token().isOrOperator())
//        root = "or";
//    else
//        root = token().symbol();
//
//    if (bothInt) {
//        int a = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue();
//        int b = dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
//        if (isLogicalOppositeValue())
//            std::cout << "InfixExprNode::evaluate: not(" << a << " " << root << " " << b << ")" << std::endl;
//        else
//            std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
//    }
//    else if (bothDouble) {
//        double a = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue();
//        double b = dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
//        std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
//    }
//    else if (intAndDouble) {
//        if (l) {
//            double a = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue();
//            int b = dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
//            std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
//        }
//        else if (r) {
//            int a = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue();
//            double b = dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
//            std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
//        }
//    }
    //std::cout << "InfixExprNode::evaluate: " << lValue << " " << root << " " << rValue << std::endl; //prints out addresses
    // END - FOR OUTPUT PURPOSES

    int newIntValue;
    if( token().isAdditionOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() + dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
        }
        else if (bothStrings) {
            // if token is + operator, string concatenation
            return stringAddition(dynamic_cast<StringTypeDescriptor* >(lValue), dynamic_cast<StringTypeDescriptor* >(rValue));
        }
        else if (bothDouble) {
            double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() + dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            return new DoubleTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() + dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                return new DoubleTypeDescriptor("", newValue);
            }
            else if (r) {
                double newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() + dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                return new DoubleTypeDescriptor("", newValue);
            }
        }
    }
    else if(token().isSubtractionOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() - dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothDouble) {
            double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() - dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            return new DoubleTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() - dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                return new DoubleTypeDescriptor("", newValue);
            }
            else if (r) {
                double newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() - dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                return new DoubleTypeDescriptor("", newValue);
            }
        }
    }
    else if(token().isMultiplicationOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() * dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothDouble) {
            double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() * dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            return new DoubleTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() * dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                return new DoubleTypeDescriptor("", newValue);
            }
            else if (r) {
                double newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() * dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                return new DoubleTypeDescriptor("", newValue);
            }
        }
    }
    else if(token().isDivisionOperator() && !bothInt) {
        if (bothDouble) {
            double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() / dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            return new DoubleTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                double newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() / dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                return new DoubleTypeDescriptor("", newValue);
            }
            else if (r) {
                double newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() / dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                return new DoubleTypeDescriptor("", newValue);
            }
        }
        // division by zero?
    }
    else if((token().isIntegerDivisionOperator() || token().isDivisionOperator()) && bothInt) {
        // Integer division for integers obviously...
        newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() / dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
        //return new IntegerTypeDescriptor("", newValue);
    }
    else if(token().isModuloOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() % dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else {
            std::cout << "Both operands for modulus operation % must be Integer Type\n";
            exit(3);
        }

    }

    // Relational / Comparison operators for double or float type should not be used. Nor mixed as in int and double/float.
    else if(token().isEqualEqualOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() == dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothStrings) {
            return new IntegerTypeDescriptor("", dynamic_cast<StringTypeDescriptor* >(lValue)->stringValue() == dynamic_cast<StringTypeDescriptor* >(rValue)->stringValue());
        }
        else if (bothDouble) {
            //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() == dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() == dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
            else if (r) {
                //int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() == dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
        }
        else {
            std::cout << "For == operator, operands should be both int or string, not double/float\n";
            exit(1);
        }
    }
    else if(token().isNotEqualOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() != dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothStrings) {
            return new IntegerTypeDescriptor("", dynamic_cast<StringTypeDescriptor* >(lValue)->stringValue() != dynamic_cast<StringTypeDescriptor* >(rValue)->stringValue());
        }
        else if (bothDouble) {
            //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() != dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() != dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
            else if (r) {
                //int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() != dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
        }
        else {
            std::cout << "For != or <> operator, operands should be both int or string, not double/float\n";
            exit(1);
        }
    }
    else if(token().isGreaterThanOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() > dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothStrings) {
            return new IntegerTypeDescriptor("", dynamic_cast<StringTypeDescriptor* >(lValue)->stringValue() > dynamic_cast<StringTypeDescriptor* >(rValue)->stringValue());
        }
        else if (bothDouble) {
            //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() > dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() > dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
            else if (r) {
                //int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() > dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
        }
        else {
            std::cout << "For > operator, operands should be both int or string, not double/float\n";
            exit(1);
        }
    }
    else if(token().isGreaterThanOrEqualOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() >= dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothStrings) {
            return new IntegerTypeDescriptor("", dynamic_cast<StringTypeDescriptor* >(lValue)->stringValue() >= dynamic_cast<StringTypeDescriptor* >(rValue)->stringValue());
        }
        else if (bothDouble) {
            //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() >= dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() >= dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
            else if (r) {
                //int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() >= dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
        }
        else {
            std::cout << "For >= operator, operands should be both int or string, not double/float\n";
            exit(1);
        }
    }
    else if(token().isLessThanOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() < dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothStrings) {
            return new IntegerTypeDescriptor("", dynamic_cast<StringTypeDescriptor* >(lValue)->stringValue() < dynamic_cast<StringTypeDescriptor* >(rValue)->stringValue());
        }
        else if (bothDouble) {
            //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() < dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() < dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
            else if (r) {
                //int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() < dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
        }
        else {
            std::cout << "For < operator, operands should be both int or string, not double/float\n";
            exit(1);
        }
    }
    else if(token().isLessThanOrEqualOperator()) {
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() <= dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (bothStrings) {
            return new IntegerTypeDescriptor("", dynamic_cast<StringTypeDescriptor* >(lValue)->stringValue() <= dynamic_cast<StringTypeDescriptor* >(rValue)->stringValue());
        }
        else if (bothDouble) {
            //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() <= dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else if (intAndDouble) {
            if (l) {
                //int newValue = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue() <= dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
            else if (r) {
                //int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() <= dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
                //return new IntegerTypeDescriptor("", newValue);
            }
        }
        else {
            std::cout << "For <= operator, operands should be both int or string, not double/float\n";
            exit(1);
        }
    }
    // Logical Operators
    else if (token().isOrOperator()) {
        // for right now just worry about regular int/bool case
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() || dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else {
            std::cout << "InfixExprNode::evaluate: or operator - left and right must be integers!\n" << std::endl;
            exit(3);
        }
    }
    else if (token().isAndOperator()) {
        // for right now just worry about regular int/bool case
        if (bothInt) {
            newIntValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() && dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            //return new IntegerTypeDescriptor("", newValue);
        }
        else {
            std::cout << "InfixExprNode::evaluate: and operator - left and right must be integers!\n" << std::endl;
            exit(3);
        }
    }
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
    if (isLogicalOppositeValue()) {
        newIntValue = !newIntValue;
        unSetLogicalOppositeValue();
    }

    return new IntegerTypeDescriptor("", newIntValue);
}

void InfixExprNode::print() {
    if (isLogicalOppositeValue())
        std::cout << "not(";
    if (isOppositeValue())
        std::cout << "-(";
    _left->print();
    token().print();
    _right->print();
    if (isOppositeValue())
        std::cout << ")";
    if (isLogicalOppositeValue())
        std::cout << ")";
}

TypeDescriptor * InfixExprNode::stringAddition(StringTypeDescriptor * s1, StringTypeDescriptor * s2) {
    //std::cout << "InfixExprNode::evaluate: " << s1->stringValue() << " " << token().symbol() << " " << s2->stringValue() << std::endl;
    return new StringTypeDescriptor("", s1->stringValue() + s2->stringValue());
}

InfixExprNode::~InfixExprNode() {
    delete _left;
    _left = nullptr;
    delete _right;
    _right = nullptr;
}

// WholeNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    if (isLogicalOppositeValue())
        std::cout << "not(";
    if (isOppositeValue() || token().isOppositeValue())
        std::cout << '-';
    token().print();
    if (isLogicalOppositeValue())
        std::cout << ")";
}

TypeDescriptor * WholeNumber::evaluate(SymTab &symTab) {
    if (isLogicalOppositeValue()) {
        //std::cout << "WholeNumber::evaluate: returning " << !(token().getWholeNumber()) << std::endl;
        return new IntegerTypeDescriptor("", !(token().getWholeNumber()));
    }
    //std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
    return new IntegerTypeDescriptor("1IGNORE_INT", token().getWholeNumber());
}

// DoubleNumber
DoubleNumber::DoubleNumber(Token token): ExprNode{token} {}

void DoubleNumber::print() {
    if (isOppositeValue() || token().isOppositeValue())
        std::cout << '-';
    token().print();
}


TypeDescriptor * DoubleNumber::evaluate(SymTab &symTab) {
    //std::cout << "DoubleNumber::evaluate: returning " << token().getDoubleNumber() << std::endl;
    return new DoubleTypeDescriptor("1IGNORE_FLOAT", token().getDoubleNumber());
}

// Variable

Variable::Variable(Token token): ExprNode{token}, index{nullptr} {}

Variable::Variable(Token token, ExprNode *i): ExprNode{token}, index{i} {}

void Variable::print() {
    if (isLogicalOppositeValue())
        std::cout << "not(";
    token().print();
    if (index != nullptr) {
        std::cout << '[';
        index->print();
        std::cout << ']';
    }
    if (isLogicalOppositeValue())
        std::cout << ")";
}

TypeDescriptor* Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }

    if (isLogicalOppositeValue()) {
        if (index == nullptr)
            return new IntegerTypeDescriptor("", !(dynamic_cast<IntegerTypeDescriptor *>(symTab.getValueFor(token().getName()))->intValue()));
        else {
            ArrayTypeDescriptor * a = dynamic_cast<ArrayTypeDescriptor *>(symTab.getValueFor(token().getName()));
            TypeDescriptor * t = a->getValueAtIndex(index->token().getWholeNumber());
            return new IntegerTypeDescriptor("", !(dynamic_cast<IntegerTypeDescriptor *>(index->evaluate(symTab))->intValue()));
        }

    }
    if (index == nullptr) {
        return symTab.getValueFor(token().getName());
    } else {
        ArrayTypeDescriptor * a = dynamic_cast<ArrayTypeDescriptor *>(symTab.getValueFor(token().getName()));
        TypeDescriptor * t = a->getValueAtIndex(dynamic_cast<IntegerTypeDescriptor *>(index->evaluate(symTab))->intValue());
        return t;
    }
}
bool Variable::isIndex() {
    return index != nullptr;
}

ExprNode * Variable::getIndex() {
    return index;
}

// StringTerminal


StringTerminal::StringTerminal(Token token) : ExprNode(token), hasNewLineChar{false} {}

void StringTerminal::print() {
    if (token().getString() == "\n") {}
    else {
        std::cout << '"';
        token().print();
        std::cout << '"';
    }
}

TypeDescriptor * StringTerminal::evaluate(SymTab &symTab) {
    //std::cout << "StringTerminal::evaluate: returning \"" << token().getString() << '\"' << std::endl;
    return new StringTypeDescriptor("1IGNORE_STRING", token().getString());
}


ArrayLen::ArrayLen(Token token) : ExprNode(token){}

void ArrayLen::print() {
    if (isLogicalOppositeValue())
        std::cout << "not(";
    if (isOppositeValue() || token().isOppositeValue())
        std::cout << '-';
    std::cout << "len(" << token().getName() << ')';
    if (isLogicalOppositeValue())
        std::cout << ")";
}

TypeDescriptor *ArrayLen::evaluate(SymTab &symTab) {
    ArrayTypeDescriptor * arr = dynamic_cast<ArrayTypeDescriptor *>(symTab.getValueFor(token().getName()));
    int len = arr->size();

    if (isOppositeValue() || token().isOppositeValue())
        len = len * -1;
    if (isLogicalOppositeValue())
        len = !len;

    //std::cout << "ArrayLen::evaluate: returning " << len << std::endl;
    return new IntegerTypeDescriptor(token().getName(), len);
}

FunctionCall::FunctionCall(Token token, std::vector<ExprNode *> args) : ExprNode(token), arguments{args} {

}

TypeDescriptor *FunctionCall::evaluate(SymTab &parentSymTab) {
    // TODO: check that params size and arg size match
    SymTab newSymTab;
    newSymTab = parentSymTab.copyValues();

    FunctionTypeDescriptor *functionToBeCalled = dynamic_cast<FunctionTypeDescriptor *>(parentSymTab.getValueFor(token().getName()));
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
    // Check for return statement, should be the last one, and get return value
    std::vector<Statement *> stmts = functionToBeCalled->getStatements()->getStatements();
    if (stmts.back()->isReturn()) {
        functionToBeCalled->getStatements()->evaluate(newSymTab);
        TypeDescriptor * returnVal = newSymTab.getValueFor("1_RETURN");
        if (returnVal->isI()) {
            // make copy of value
            IntegerTypeDescriptor *val = new IntegerTypeDescriptor("", dynamic_cast<IntegerTypeDescriptor *>(returnVal)->intValue());
            return val;
        }
        else if (returnVal->isD()) {
            // make copy of value
            DoubleTypeDescriptor *val = new DoubleTypeDescriptor("", dynamic_cast<DoubleTypeDescriptor *>(returnVal)->doubleValue());
            return val;
        }
        else if (returnVal->isS()) {
            // make copy of value
            StringTypeDescriptor *val = new StringTypeDescriptor("", dynamic_cast<StringTypeDescriptor *>(returnVal)->stringValue());
            return val;
        }
        else if (returnVal->isA()) {
            // if array, return by reference
            return returnVal;
        }
    }
    else {
        std::cout << "There should be a return statement!" << std::endl;
        exit(2);
    }
    return nullptr;
}

void FunctionCall::print() {
    if (isLogicalOppositeValue()) {
        std::cout << "not(";
    }
    if (isOppositeValue()) {
        std::cout << '-';
    }
    std::cout << token().getName();
    std::cout << '(';
    for (auto a: arguments) {
        if (a)
            a->print();
        if (a != arguments.back())
            std::cout << ", ";
        else {}
    }
    std::cout << ')';
    if (isLogicalOppositeValue()) {
        std::cout << ")";
    }
}
