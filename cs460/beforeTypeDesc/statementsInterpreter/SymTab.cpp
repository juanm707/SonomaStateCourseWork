//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include <iostream>
#include "SymTab.hpp"


void SymTab::setValueFor(std::string vName, int value) {
    // Define a variable by setting its initial value.
    std::cout << vName << " <- " << value << std::endl;
    symTab[vName] = value;
}

bool SymTab::isDefined(std::string vName) {
    return symTab.find(vName) != symTab.end();
}

int SymTab::getValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    std::cout << "SymTab::getValueFor: " << vName << " contains " << symTab.find(vName)->second << std::endl;
    return symTab.find(vName)->second;
}

void SymTab::print() {
    for(auto [var, value] : symTab )
        std::cout << var << " = " << value << std::endl;
}

