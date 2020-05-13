// Student: Juan Martinez
#include <iostream>
#include <vector>


#include "Token.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"



int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;

    inputStream.open(argv[1], std::ios::in);
    if (!inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(2);
    }

    Tokenizer tokenizer(inputStream);
    Parser parser(tokenizer);
    Statements *statements = parser.statements();
    Token lastToken = tokenizer.getToken();
    if (!lastToken.eof()) {
        std::cout << "Unexpected token in input." << std::endl;
        lastToken.print();
        exit(1);
    }
    SymTab symTab;

    std::cout << "-----------BEGIN PRINT CODE INPUT-----------" << std::endl;
    statements->print();
    std::cout << "-----------END PRINT CODE INPUT-----------" << std::endl;
    std::cout << "-----------BEGIN PROGRAM OUTPUT-----------" << std::endl;
    statements->evaluate(symTab);
    std::cout << "------------END PROGRAM OUTPUT------------" << std::endl;
    std::cout << std::endl << "Symbol table contains the following variables.\n";
    std::cout << "-----------BEGIN SYMBOL TABLE OUTPUT-----------" << std::endl;
    symTab.print();
    std::cout << "-----------END SYMBOL TABLE OUTPUT-----------" << std::endl;

    delete statements;

    return 0;
}
