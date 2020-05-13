//
// Created by Ali A. Kooshesh on 1/30/19.
//

#ifndef EXPRINTER_TOKENIZER_HPP
#define EXPRINTER_TOKENIZER_HPP


#include <fstream>
#include <vector>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::ifstream &inStream);
    Token getToken();
    void ungetToken();
    void printProcessedTokens();
    char peek();


private:
    Token lastToken;
    bool ungottenToken;
    std::ifstream &inStream;
    std::vector<Token> _tokens; 

    std::string readName();
    int readInteger();
    std::string readNumber();
    std::string readString();

    std::vector<int> _identationStack;
    bool parsingANewLine;
    int identCountForEachNewLine;
};

#endif //EXPRINTER_TOKENIZER_HPP
