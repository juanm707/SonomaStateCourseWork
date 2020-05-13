//
// Created by Ali A. Kooshesh on 1/30/19.
//

#ifndef EXPRINTER_TOKEN_HPP
#define EXPRINTER_TOKEN_HPP

#include<string>

class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    void symbol(char c) { _symbol = c; }
    char symbol() { return _symbol; }

    bool &is2PartChar() { return _twoPartChar; }

    void str_symbol(std::string s) { _str_symbol = s; }
    std::string str_symbol() { return _str_symbol; }

    bool isKeyword();
    bool isOpenCurly() const { return _symbol == '{'; }
    bool isCloseCurly() const { return _symbol == '}'; }

    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isIntegerDivisionOperator() const{return _str_symbol == "//"; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator() || isIntegerDivisionOperator();
    }

    bool isEqualEqualOperator() const { return _str_symbol == "=="; }
    bool isNotEqualOperator() const { return _str_symbol == "!=" || _str_symbol == "<>"; }
    bool isGreaterThanOperator() const { return _symbol == '>'; }
    bool isGreaterThanOrEqualOperator() const { return _str_symbol == ">="; }
    bool isLessThanOperator() const { return _symbol == '<'; }
    bool isLessThanOrEqualOperator() const { return _str_symbol == "<="; }
    bool isRelationalOperator() const {
        return isEqualEqualOperator() ||
        isNotEqualOperator() ||
        isGreaterThanOperator() ||
        isGreaterThanOrEqualOperator() ||
        isLessThanOperator() ||
        isLessThanOrEqualOperator();
    }

    bool isName() const                   { return _name.length() > 0; }
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }

    void print() const;

private:
    std::string _name;
    bool _eof, _eol;
    bool _isWholeNumber;
    char _symbol;
    int _wholeNumber;
    bool _twoPartChar;

    std::string _str_symbol; // For relational operators
};

#endif //EXPRINTER_TOKEN_HPP
