//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include <iostream>
#include "SymTab.hpp"


void SymTab::setValueFor(std::string vName, TypeDescriptor* typeD) {
    // Define a variable by setting its initial value.
    // std::cout << vName << " <- " << value << std::endl;
    std::cout << "SymTab::setValueFor: Setting type desc for " << vName << std::endl;
    if (typeD->isS())
        std::cout << vName << " <- " << dynamic_cast<StringTypeDescriptor* >(typeD)->stringValue() << std::endl;
    else if (typeD->isD())
        std::cout << vName << " <- " << dynamic_cast<DoubleTypeDescriptor* >(typeD)->doubleValue() << std::endl;
    else if (typeD->isI())
        std::cout << vName << " <- " << dynamic_cast<IntegerTypeDescriptor* >(typeD)->intValue() << std::endl;

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

    // BEGIN - FOR OUTPUT PURPOSES
    TypeDescriptor* v = symTab.find(vName)->second;
    if (v->isS()) {
        std::cout << "SymTab::getValueFor: " << vName << " contains " << dynamic_cast<StringTypeDescriptor* >(v)->stringValue()<< std::endl;
    }
    else if (v->isD()) {
        std::cout << "SymTab::getValueFor: " << vName << " contains " << dynamic_cast<DoubleTypeDescriptor* >(v)->doubleValue()<< std::endl;
    }
    else {
        std::cout << "SymTab::getValueFor: " << vName << " contains " << dynamic_cast<IntegerTypeDescriptor* >(v)->intValue()<< std::endl;
    }

    // END - FOR OUTPUT PURPOSES
    return symTab.find(vName)->second;
}

void SymTab::print() {
    for(auto [var, value] : symTab ) {
        if (value->isS())
            std::cout << var << " = \"" << dynamic_cast<StringTypeDescriptor* >(value)->stringValue() << "\"" << std::endl;
        else if (value->isD())
            std::cout << var << " = " << dynamic_cast<DoubleTypeDescriptor* >(value)->doubleValue() << std::endl;
        else if (value->isI())
            std::cout << var << " = " << dynamic_cast<IntegerTypeDescriptor* >(value)->intValue() << std::endl;
    }
}

SymTab::~SymTab() {
    // std::cout << "SymTab Destructor called...\n";
    for(auto [var, value] : symTab )
        delete value;
}

