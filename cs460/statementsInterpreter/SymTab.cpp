//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include <iostream>
#include "SymTab.hpp"


void SymTab::setValueFor(std::string vName, TypeDescriptor* typeD) {
    // Define a variable by setting its initial value.
    // std::cout << vName << " <- " << value << std::endl;
    /*std::cout << "SymTab::setValueFor: Setting type desc for " << vName << std::endl;
    if (typeD->isS())
        std::cout << vName << " <- " << dynamic_cast<StringTypeDescriptor* >(typeD)->stringValue() << std::endl;
    else if (typeD->isD())
        std::cout << vName << " <- " << dynamic_cast<DoubleTypeDescriptor* >(typeD)->doubleValue() << std::endl;
    else if (typeD->isI())
        std::cout << vName << " <- " << dynamic_cast<IntegerTypeDescriptor* >(typeD)->intValue() << std::endl;
    */
    symTab[vName] = typeD;
}

bool SymTab::isDefined(std::string vName) {
    return symTab.find(vName) != symTab.end();
}

TypeDescriptor* SymTab::getValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    /*
    // BEGIN - FOR OUTPUT PURPOSES
    TypeDescriptor* v = symTab.find(vName)->second;
    if (v->isS()) {
        std::cout << "SymTab::getValueFor: " << vName << " contains \"" << dynamic_cast<StringTypeDescriptor* >(v)->stringValue()<< '\"' << std::endl;
    }
    else if (v->isD()) {
        std::cout << "SymTab::getValueFor: " << vName << " contains " << dynamic_cast<DoubleTypeDescriptor* >(v)->doubleValue()<< std::endl;
    }
    else if (v->isI()){
        std::cout << "SymTab::getValueFor: " << vName << " contains " << dynamic_cast<IntegerTypeDescriptor* >(v)->intValue()<< std::endl;
    }
    else if (v->isA()){
        std::cout << "Symtab::getValueFor: " << vName << " contains ";
        dynamic_cast<ArrayTypeDescriptor * >(v)->arrayPrint();
        std::cout << std::endl;
    }
    else if (v->isF()) {
        std::cout << "Symtab::getValueFor: " << vName << " contains function" << std::endl;
    }
    else {
        std::cout << "Symtab::getValue for: " << vName << " has unknown type!" << std::endl;
        exit(2);
    }

    // END - FOR OUTPUT PURPOSES
     */
    return symTab.find(vName)->second;
}

void SymTab::print() {
    for(auto [var, value] : symTab ) {
        if (var == "1_RETURN") {}
        else {
            if (value->isS())
                std::cout << var << " = \"" << dynamic_cast<StringTypeDescriptor * >(value)->stringValue() << "\""
                          << std::endl;
            else if (value->isD())
                std::cout << var << " = " << dynamic_cast<DoubleTypeDescriptor * >(value)->doubleValue() << std::endl;
            else if (value->isI())
                std::cout << var << " = " << dynamic_cast<IntegerTypeDescriptor * >(value)->intValue() << std::endl;
            else if (value->isA()) {
                std::cout << var << " = ";
                dynamic_cast<ArrayTypeDescriptor *>(value)->arrayPrint();
                std::cout << std::endl;
            } else if (value->isF()) {
                std::cout << var << " = function" << std::endl;
            } else {
                std::cout << "Unknown type!" << std::endl;
            }
        }
    }
}

SymTab::~SymTab() {

}

SymTab SymTab::copyValues() {
    SymTab copy;
    for (auto[var, value] : symTab) {
        std::string vName = var;
        TypeDescriptor *typeD = value;

        if (typeD->isI()) {
            // make copy of value
            IntegerTypeDescriptor *val = new IntegerTypeDescriptor(vName, dynamic_cast<IntegerTypeDescriptor *>(typeD)->intValue());
            copy.setValueFor(vName, val);
        }
        else if (typeD->isD()) {
            // make copy of value
            DoubleTypeDescriptor *val = new DoubleTypeDescriptor(vName, dynamic_cast<DoubleTypeDescriptor *>(typeD)->doubleValue());
            copy.setValueFor(vName, val);
        }
        else if (typeD->isS()) {
            // make copy of value
            StringTypeDescriptor *val = new StringTypeDescriptor(vName, dynamic_cast<StringTypeDescriptor *>(typeD)->stringValue());
            copy.setValueFor(vName, val);
        }
        else if (typeD->isA()) {
            // if array, pass by reference
            copy.setValueFor(vName, dynamic_cast<ArrayTypeDescriptor *>(typeD));
        }
        else if (typeD->isF()) {
            copy.setValueFor(vName, dynamic_cast<FunctionTypeDescriptor *>(typeD));
        }
        else {
            std::cout << "Unknown TypeDescriptor" << std::endl;
            exit(1);
        }
    }
    return copy;
}

