//
// Created by Juan Martinez on 2/29/20.
//

#include <iostream>
#include <vector>
#include "TypeDescriptor.hpp"


TypeDescriptor::TypeDescriptor(bool integer, bool flo, bool s, bool array, bool func) : isInt{integer}, isDouble{flo}, isString{s},
                                                                             isArray{array}, isFunction{func} {}

TypeDescriptor::~TypeDescriptor() {
    //std::cout << "Destructor called TypeDescriptor\n";
}

// Integer
IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName, int value) : TypeDescriptor(true, false, false, false,
                                                                                                   false), _name{variableName}, _int_value{value} {

}

IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName) : TypeDescriptor(true, false, false, false, false), _name{variableName} {}

std::string IntegerTypeDescriptor::name() {
    return _name;
}

int IntegerTypeDescriptor::intValue() {
    return _int_value;
}

// Double
DoubleTypeDescriptor::DoubleTypeDescriptor(std::string variableName, double value) : TypeDescriptor(false, true, false, false, false), _name{variableName}, _double_value{value} {}

DoubleTypeDescriptor::DoubleTypeDescriptor(std::string variableName) : TypeDescriptor(false, true, false, false, false), _name{variableName} {}

std::string DoubleTypeDescriptor::name() {
    return _name;
}

double DoubleTypeDescriptor::doubleValue() {
    return _double_value;
}

// String
StringTypeDescriptor::StringTypeDescriptor(std::string variableName, std::string actualString) : TypeDescriptor(false, false, true, false, false), _name{variableName}, _string_value{actualString} {}

StringTypeDescriptor::StringTypeDescriptor(std::string variableName) : TypeDescriptor(false, false, true, false, false), _name{variableName}, _string_value{""} {}

std::string StringTypeDescriptor::name() {
    return _name;
}

std::string StringTypeDescriptor::stringValue() {
    return _string_value;
}

// Array
ArrayTypeDescriptor::ArrayTypeDescriptor(std::vector<TypeDescriptor *> arrayElems) : TypeDescriptor(false, false, false, true, false), _arrayElements{arrayElems} {}

void ArrayTypeDescriptor::updateValue(int i, TypeDescriptor *t) {
    inRange(i);
    delete _arrayElements[i];
    _arrayElements[i] = t;
}

void ArrayTypeDescriptor::arrayPrint() {
    std::cout << '[';
    for (auto e : _arrayElements) {
        if (e->isI()) {
            std::cout << dynamic_cast<IntegerTypeDescriptor *>(e)->intValue();
        } else if (e->isD()) {
            std::cout << dynamic_cast<DoubleTypeDescriptor *>(e)->doubleValue();
        } else if (e->isS()) {
            std::cout << '\"' << dynamic_cast<StringTypeDescriptor *>(e)->stringValue() << '\"';
        } else {
            std::cout << "ArrayTypeDescriptor::arrayPrint - invalid type." << std::endl;
            exit(2);
        }
        if (e != _arrayElements.back()) {
            std::cout << ", ";
        }
    }
    std::cout << ']';
}

TypeDescriptor *ArrayTypeDescriptor::getValueAtIndex(int i) {
    inRange(i);
    return _arrayElements[i];
}

void ArrayTypeDescriptor::inRange(int &i) {
    int maxPositiveSize = _arrayElements.size() - 1;
    int minNegativeSize = _arrayElements.size() * -1;

    if (i > maxPositiveSize || i < minNegativeSize) {
        std::cout << "IndexError: list index, " << i << " out of range\n";
        exit(3);
    } else if (i < 0) {
        // python allows reverse indexing that is a[-1] == a[size - 1], and so on
        i = _arrayElements.size() - (i * -1);
        if (i < minNegativeSize) {
            std::cout << "IndexError: list index, " << i << " out of range\n";
            exit(3);
        }
    }
}

void ArrayTypeDescriptor::pop() {
    if (_arrayElements.empty()) {
        std::cout << "IndexError: pop from empty list" << std::endl;
        exit(3);
    }
    _arrayElements.pop_back();
}

void ArrayTypeDescriptor::push(TypeDescriptor *newElem) {
    // TODO: check same type
    _arrayElements.push_back(newElem);
}

int ArrayTypeDescriptor::size() {
    return int(_arrayElements.size());
}

std::string ArrayTypeDescriptor::arrayPrintString() {
    std::string s;
    s += '[';
    for (auto e : _arrayElements) {
        if (e->isI()) {
            s += std::to_string(dynamic_cast<IntegerTypeDescriptor *>(e)->intValue());
        } else if (e->isD()) {
            s += std::to_string(dynamic_cast<DoubleTypeDescriptor *>(e)->doubleValue());
        } else if (e->isS()) {
            s += '\"' + dynamic_cast<StringTypeDescriptor *>(e)->stringValue() + '\"';
        } else {
            std::cout << "ArrayTypeDescriptor::arrayPrint - invalid type." << std::endl;
            exit(2);
        }
        if (e != _arrayElements.back()) {
            s += ", ";
        }
    }
    s += ']';
    return s;
}

FunctionTypeDescriptor::FunctionTypeDescriptor(std::string name, Statements * stmts, std::vector<std::string> params)
                           : TypeDescriptor(false, false, false, false, true),
                           id{name}, _bodyStatements{stmts}, parameterList{params} {}

std::vector<std::string> FunctionTypeDescriptor::getParams() {
    return parameterList;
}

Statements *FunctionTypeDescriptor::getStatements() {
    return _bodyStatements;
}
