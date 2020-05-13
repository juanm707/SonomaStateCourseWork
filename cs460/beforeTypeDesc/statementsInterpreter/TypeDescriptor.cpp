//
// Created by Juan Martinez on 2/29/20.
//

#include "TypeDescriptor.hpp"

IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName, int value) : _name{variableName}, _int_value{value} {}

IntegerTypeDescriptor::IntegerTypeDescriptor(std::string variableName) : _name{variableName} {}

std::string IntegerTypeDescriptor::name() {
    return _name;
}

int IntegerTypeDescriptor::intValue() {
    return _int_value;
}

FloatTypeDescriptor::FloatTypeDescriptor(std::string variableName, float value) : _name{variableName}, _float_value{value} {}

FloatTypeDescriptor::FloatTypeDescriptor(std::string variableName) : _name{variableName} {}

std::string FloatTypeDescriptor::name() {
    return _name;
}

float FloatTypeDescriptor::floatValue() {
    return _float_value;
}

StringTypeDescriptor::StringTypeDescriptor(std::string variableName, std::string actualString) : _name{variableName}, _string_value{actualString} {}

StringTypeDescriptor::StringTypeDescriptor(std::string variableName) : _name{variableName}, _string_value{""} {}

std::string StringTypeDescriptor::name() {
    return _name;
}

std::string StringTypeDescriptor::stringValue() {
    return _string_value;
}
