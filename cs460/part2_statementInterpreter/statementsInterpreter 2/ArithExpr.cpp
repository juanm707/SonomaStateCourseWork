//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include<iostream>
#include "ArithExpr.hpp"
#include "TypeDescriptor.hpp"

// ExprNode
ExprNode::ExprNode(Token token): _token{token}, _isOppositeValue{false} {}

Token ExprNode::token() { return _token; }

void ExprNode::printNegativeSigns() const {
    //for display purposes
    for (int i = 0; i < _negSignCount; i++)
        std::cout << '-';
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
    std::string root;
    if (token().is2PartChar())
        root = token().str_symbol();
    else
        root = token().symbol();

    if (bothInt) {
        int a = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue();
        int b = dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
        std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
    }
    else if (bothDouble) {
        double a = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue();
        double b = dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
        std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
    }
    else if (intAndDouble) {
        if (l) {
            double a = dynamic_cast<DoubleTypeDescriptor* >(lValue)->doubleValue();
            int b = dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
        }
        else if (r) {
            int a = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue();
            double b = dynamic_cast<DoubleTypeDescriptor* >(rValue)->doubleValue();
            std::cout << "InfixExprNode::evaluate: " << a << " " << root << " " << b << std::endl;
        }
    }
    //std::cout << "InfixExprNode::evaluate: " << lValue << " " << root << " " << rValue << std::endl; //prints out addresses
    // END - FOR OUTPUT PURPOSES

    if( token().isAdditionOperator()) {
        if (bothInt) {
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() + dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() - dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() * dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
        int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() / dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
        return new IntegerTypeDescriptor("", newValue);
    }
    else if(token().isModuloOperator()) {
        if (bothInt) {
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() % dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
        }
        else {
            std::cout << "Both operands for modulus operation % must be Integer Type\n";
            exit(3);
        }

    }

    // Relational / Comparison operators for double or float type should not be used. Nor mixed as in int and double/float.
    else if(token().isEqualEqualOperator()) {
        if (bothInt) {
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() == dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() != dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() > dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() >= dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() < dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
            int newValue = dynamic_cast<IntegerTypeDescriptor* >(lValue)->intValue() <= dynamic_cast<IntegerTypeDescriptor* >(rValue)->intValue();
            return new IntegerTypeDescriptor("", newValue);
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
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
}

void InfixExprNode::print() {
    if (isOppositeValue())
        std::cout << "-(";
    _left->print();
    token().print();
    _right->print();
    if (isOppositeValue())
        std::cout << ")";
}

TypeDescriptor * InfixExprNode::stringAddition(StringTypeDescriptor * s1, StringTypeDescriptor * s2) {
    std::cout << "InfixExprNode::evaluate: " << s1->stringValue() << " " << token().symbol() << " " << s2->stringValue() << std::endl;
    return new StringTypeDescriptor("", s1->stringValue() + s2->stringValue());
}

// WholeNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    if (isOppositeValue() || token().isOppositeValue())
        std::cout << '-';
    token().print();
}

TypeDescriptor * WholeNumber::evaluate(SymTab &symTab) {
    std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
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
    std::cout << "DoubleNumber::evaluate: returning " << token().getDoubleNumber() << std::endl;
    return new DoubleTypeDescriptor("1IGNORE_FLOAT", token().getDoubleNumber());
}

// Variable

Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}

TypeDescriptor* Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    //std::cout << "Variable::evaluate: returning " << symTab.getValueFor(token().getName()) << std::endl;
    return symTab.getValueFor(token().getName());
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
    std::cout << "StringTerminal::evaluate: returning " << token().getString() << std::endl;
    return new StringTypeDescriptor("1IGNORE_STRING", token().getString());
}



