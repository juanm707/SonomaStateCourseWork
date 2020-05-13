//
// Created by Juan Martinez on 2/29/20.
//

#ifndef EXPRINTER_TYPEDESCRIPTOR_H
#define EXPRINTER_TYPEDESCRIPTOR_H

#include <string>

class TypeDescriptor {

};

class IntegerTypeDescriptor: public TypeDescriptor {
public:
    IntegerTypeDescriptor(std::string variableName, int value);
    IntegerTypeDescriptor(std::string variableName);
    std::string name(); // returns the name of the integer variable
    int intValue(); // return its integer value
private:
    std::string _name;
    int _int_value;
};

class FloatTypeDescriptor: public TypeDescriptor {
public:
    FloatTypeDescriptor(std::string variableName, float value);
    FloatTypeDescriptor(std::string variableName);
    std::string name();
    float floatValue();

private:
    std::string _name;
    float _float_value;
};

class StringTypeDescriptor: public TypeDescriptor {
public:
    StringTypeDescriptor(std::string variableName, std::string actualString);
    StringTypeDescriptor(std::string variableName);
    std::string name();
    std::string stringValue();

private:
    std::string _name;
    std::string _string_value;
};
















#endif //EXPRINTER_TYPEDESCRIPTOR_H
