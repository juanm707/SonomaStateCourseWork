//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include <string>
#include "Tokenizer.hpp"

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}

int Tokenizer::readInteger() {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    int intValue = 0;
    char c;
    while( inStream.get(c) && isdigit(c) ) {
        intValue = intValue * 10 + c - '0';
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return intValue;
}

std::string Tokenizer::readNumber() {
    std::string name;
    int decimalCount = 0;
    char c;
    while( inStream.get(c) && (isdigit(c) || c == '.')) {
        if (decimalCount == 2) {
            std::cout << "Found 2 decimals when only one is expected in a double number; Tokenizer::readNumber()\n";
            exit(2);
        }
        if (c == '.')
            decimalCount++;
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}

std::string Tokenizer::readString() {
    std::string s;
    char end; // should end at double or single quote
    inStream.get(end);

    char c;
    while( inStream.get(c) && c != end) {
        if (c == '\\') {
            char next_c = inStream.peek();
            if (next_c == 'n') { //potentially others?
                inStream.get(c);
                s += '\n';
            }
            else if (next_c == 't') {
                inStream.get(c);
                s += '\t';
            }
            else {
                s += c;
                inStream.get(c);
                s += c;
            }
        }
        else
            s += c;
    }
    return s;
}

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{} {}

Token Tokenizer::getToken() {

    if(ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;

    /* */
    while( inStream.get(c) && isspace(c) && c != '\n' )  // Skip spaces but not new-line chars.
        ;

    /*
    while( inStream.get(c) && isspace(c) )  // Skip spaces including the new-line chars.
        ;
    */

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }

    //    std::cout << "c = " << c << std::endl;

    Token token;
    if( inStream.eof()) {
        token.eof() = true;
    }
    else if( c == '\n' ) {  // will not ever be the case unless new-line characters are not supressed.
        token.eol() = true;
    }
    else if (c == '#') {
        // this is a comment
        std::string comment;
        std::getline(inStream, comment);
        token.symbol(c);
        token.eol() = true;
    }
    else if( isdigit(c) ) { // an integer or double?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
        // create string containing the full number
        // example "2" or "23.5"
        std::string number = readNumber();
        // determine if it has .
        // if it does then double point
        // else it is regular integer
        if (number.find('.') != std::string::npos) {
            //std::cout << "Found double point number: " << number << std::endl;
            token.setDoubleNumber(std::stof(number));
        }
        else {
            //token.setWholeNumber( readInteger() );
            token.setWholeNumber(std::stoi(number));
        }

    }
    // whole numbers refer to ascii decimal values for some characters
    else if( c == '=' ) {
        std::string temp = "="; // might be equal equal ==
        int next_c = inStream.peek();
        if (next_c == 61) {
            inStream.get(c);
            token.str_symbol(temp += "=");
            token.is2PartChar() = true;
        }
        else // if next_c is 32 it is a space so c is just = equal aka assignment sign
            token.symbol(c);
    }
    else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        if (c == '/') {
            int next_c = inStream.peek();
            if (next_c == 47) { //if theres another / for a //
                inStream.get(c);
                token.str_symbol("//");
                token.is2PartChar() = true;
            }
            else
                token.symbol(c);
        }
        else
            token.symbol(c);
    }
    else if( c == ';' )
        token.symbol(c);
    else if( c == '(' || c == ')')
        token.symbol(c);
    else if( c == '{' || c == '}')
        token.symbol(c);
    else if( c == '!') {// assuming next is =     might have to change later!
        inStream.get(c);
        token.str_symbol("!=");
        token.is2PartChar() = true;
    }
    else if( c == '>') {
        int next_c = inStream.peek();
        if (next_c == 61) {
            inStream.get(c);
            token.str_symbol(">=");
            token.is2PartChar() = true;
        }
        else // if next_c is 32 it is a space so c is just > greater than
            token.symbol(c);
    }
    else if( c == '<') {
        int next_c = inStream.peek();
        if (next_c == 61) {
            inStream.get(c);
            token.str_symbol("<=");
            token.is2PartChar() = true;
        }
        else if (next_c == 62) { //  62 is > meaning this is <> operator which is not equal operator
            inStream.get(c);
            token.str_symbol("<>");
            token.is2PartChar() = true;
        }
        else // if next_c is 32 it is a space so c is just < less than
            token.symbol(c);
    }
    else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        token.setName( readName() );
    }
    else if( c == '"') {
        //std::cout << "double quotes" << std::endl;
        inStream.putback(c);
        token.setString(readString());
    }
    else if( c == '\'') {
        //std::cout << "single quotes" << std::endl;
        inStream.putback(c);
        token.setString(readString());
    }
    else if( c == ','){
        token.symbol(c);
    }
    else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    _tokens.push_back(token);
    return lastToken = token;
}

void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        std::cout << std::endl;
    }
}

// Student added
int Tokenizer::getLineCount() {
    int count = 0;
    for (auto t : _tokens) {
        if (t.eol())  // what do we count? Every line in input file or statements -> ;????
            count++;
    }
    return count;
}
