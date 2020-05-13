//
// Created by Juan Martinez on 2/29/20.
//

#include <iostream>
#include "TypeDescriptor.hpp"


TypeDescriptor::TypeDescriptor(bool integer, bool flo, bool s) : isInt{integer}, isDouble{flo}, isString{s} {}

TypeDescriptor::~TypeDescriptor() {
    //std::cout << "Destructor called TypeDescriptor\n";
}

// Integer
IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName, int value) : TypeDescriptor(true, false, false), _name{variableName}, _int_value{value} {

}

IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName) : TypeDescriptor(true, false, false), _name{variableName} {}

std::string IntegerTypeDescriptor::name() {
    return _name;
}

int IntegerTypeDescriptor::intValue() {
    return _int_value;
}

// Double
DoubleTypeDescriptor::DoubleTypeDescriptor(std::string variableName, double value) : TypeDescriptor(false, true, false), _name{variableName}, _double_value{value} {}

DoubleTypeDescriptor::DoubleTypeDescriptor(std::string variableName) : TypeDescriptor(false, true, false), _name{variableName} {}

std::string DoubleTypeDescriptor::name() {
    return _name;
}

double DoubleTypeDescriptor::doubleValue() {
    return _double_value;
}

// String
StringTypeDescriptor::StringTypeDescriptor(std::string variableName, std::string actualString) : TypeDescriptor(false, false, true), _name{variableName}, _string_value{actualString} {}

StringTypeDescriptor::StringTypeDescriptor(std::string variableName) : TypeDescriptor(false, false, true), _name{variableName}, _string_value{""} {}

std::string StringTypeDescriptor::name() {
    return _name;
}

std::string StringTypeDescriptor::stringValue() {
    return _string_value;
}
