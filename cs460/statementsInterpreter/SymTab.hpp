//
// Created by Ali A. Kooshesh on 2/5/19.
//

#ifndef EXPRINTER_SYMTAB_HPP
#define EXPRINTER_SYMTAB_HPP

#include <string>
#include <map>
#include "TypeDescriptor.hpp"

// This is a flat and integer-based symbol table. It allows for variables to be
// initialized, determines if a give variable has been defined or not, and if
// a variable has been defined, it returns its value.

class SymTab {
public:
    void setValueFor(std::string vName, TypeDescriptor* typeD);
    bool isDefined(std::string vName);
    TypeDescriptor* getValueFor(std::string vName);
    void print();
    SymTab copyValues();
    ~SymTab();

private:
    std::map<std::string, TypeDescriptor *> symTab;
};

#endif //EXPRINTER_SYMTAB_HPP
