//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include <algorithm>
#include "Token.hpp"

Token::Token(): _name{""}, _stringValue{""}, _eof{false}, _eol{false}, _symbol{'\0'}, _isWholeNumber{false}, _isDoubleNumber{false},
                                _isString{false}, _twoPartChar(false), _oppositeValue{false}, _isIdent{false},
                                _isDedent{false} {}

void Token::print() const {
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if( isOpenBracket() ) std::cout << '[' ;
    else if( isCloseBracket() ) std::cout << ']' ;
    else if( isAssignmentOperator() )  std::cout << " = " ;
    else if( isSemiColon() )  std::cout << ";" ;
    else if( isColon() ) std::cout << ":" ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isIntegerDivisionOperator() ) std::cout << " // ";
    else if( isOrOperator() ) std::cout << " or " ;
    else if (isAndOperator() ) std::cout << " and " ;
    else if (isNotOperator() ) std::cout << " not " ;
    else if( isName() ) {
        if (isOppositeValue())
            printNegativeSigns();
        std::cout << getName();
    }
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else if( isDoubleNumber() ) std::cout << getDoubleNumber();
    else if( isString() ) {
        std::string forOutputDisplay = getString();
        for (char i : forOutputDisplay) {
            if (i == '\n')
                std::cout << "\\n";
            else
                std::cout << i;
        }
    }
    else if( isComma() ) std::cout << " , " ;
    else if( isEqualEqualOperator() ) std::cout << " == " ;
    else if( isNotEqualOperator() ) std::cout << ' ' << _str_symbol << ' ';
    else if( isGreaterThanOperator() ) std::cout << " > " ;
    else if( isGreaterThanOrEqualOperator() ) std::cout << " >= " ;
    else if( isLessThanOperator() ) std::cout << " < " ;
    else if( isLessThanOrEqualOperator() ) std::cout << " <= " ;
    else std::cout << "Uninitialized token.\n";
}

bool Token::isKeyword() {
    return _name == "print" || _name == "for" || _name == "if" || _name == "or"
    || _name == "and" || _name == "not" || _name == "len" || _name == "def" || _name == "return";
}

void Token::printNegativeSigns() const {
    // for display purposes
    for (int i = 0; i < _negSignCount; i++)
        std::cout << '-';
}
