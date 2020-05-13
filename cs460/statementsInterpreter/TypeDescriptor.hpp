//
// Created by Juan Martinez on 2/29/20.
//

#ifndef EXPRINTER_TYPEDESCRIPTOR_H
#define EXPRINTER_TYPEDESCRIPTOR_H

#include <string>
#include <vector>

class Statements;
class SymTab;

class TypeDescriptor {
public:
    virtual ~TypeDescriptor();
    bool isI() { return isInt; }
    bool isD() { return isDouble; }
    bool isS() { return isString; }
    bool isA() { return isArray; }
    bool isF() { return isFunction; }

protected:
    TypeDescriptor(bool integer, bool flo, bool s, bool array, bool func);

private:
    bool isInt;
    bool isDouble;
    bool isString;
    bool isArray;
    bool isFunction;
};

class IntegerTypeDescriptor: public TypeDescriptor {
public:
    IntegerTypeDescriptor(std::string variableName, int value);
    IntegerTypeDescriptor(std::string variableName);
    std::string name(); // returns the name of the integer variable
    int intValue(); // return its integer value
    void setName(std::string s) {_name = s;}
private:
    std::string _name;
    int _int_value;
};

class DoubleTypeDescriptor: public TypeDescriptor {
public:
    DoubleTypeDescriptor(std::string variableName, double value);
    DoubleTypeDescriptor(std::string variableName);
    std::string name();
    double doubleValue();
    void setName(std::string s) {_name = s;}

private:
    std::string _name;
    double _double_value;
};

class StringTypeDescriptor: public TypeDescriptor {
public:
    StringTypeDescriptor(std::string variableName, std::string actualString);
    StringTypeDescriptor(std::string variableName);
    std::string name();
    std::string stringValue();
    void setName(std::string s) {_name = s;}

private:
    std::string _name;
    std::string _string_value;
};

class ArrayTypeDescriptor: public TypeDescriptor {
public:
    ArrayTypeDescriptor(std::vector<TypeDescriptor *> arrayElems);
    void updateValue(int i, TypeDescriptor * t);
    TypeDescriptor * getValueAtIndex(int i);
    void arrayPrint();
    std::string arrayPrintString();
    void pop();
    void push(TypeDescriptor * newElem);
    int size();

private:
    std::vector<TypeDescriptor *> _arrayElements;
    void inRange(int &i);
};

class FunctionTypeDescriptor: public TypeDescriptor {
public:
    FunctionTypeDescriptor(std::string name, Statements * stmts, std::vector<std::string> params);
    std::vector<std::string> getParams();
    Statements *getStatements();

private:
    std::string id;
    Statements *_bodyStatements;
    std::vector<std::string> parameterList;

};


#endif //EXPRINTER_TYPEDESCRIPTOR_H
