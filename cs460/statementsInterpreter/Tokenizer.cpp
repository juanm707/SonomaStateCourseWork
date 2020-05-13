//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include <string>
#include <algorithm>
#include "Tokenizer.hpp"

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && (isalnum(c) || c == '_')) {
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

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{}, parsingANewLine{true} {
    _identationStack.push_back(0);
    identCountForEachNewLine = 0;
}

Token Tokenizer::getToken() {
    //some integers are ascii value in decimal

    if(ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;

    while( inStream.get(c) && (isspace(c) && !parsingANewLine) && c != '\n' )  // Skip spaces inside of statements, but not ident spaces and not new-line chars.
        ;

    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }

    if (c == '\t') {
        //std::string tabAndLine;
        //std::getline(inStream, tabAndLine);
        std::cout << "Tabs are not allowed. Use spaces." << std::endl;
        exit(2);
        //return getToken();
    }

    if (isspace(c) && parsingANewLine && c != '\n') {
        // Start counting the number of spaces for ident count and
        // use recursion to get next token that is not a space
        identCountForEachNewLine++;
        return getToken();
    }

    if (parsingANewLine && c == '\n') {
        identCountForEachNewLine = 0;
        return getToken();
    }

    if (parsingANewLine && (_identationStack.back() > identCountForEachNewLine)) {
        // Start dedenting one level back, return dedent token, but put the non dedent token back in input stream
        // Case 3

        // Check if the identCount is in stack, if its not then mismatch.
        // We keep returning dedents until we match .back() and identCount.
        if (std::find(_identationStack.begin(), _identationStack.end(), identCountForEachNewLine) != _identationStack.end())
        {
            // keep going
        }
        else {
            std::cout << "IndentationError: unindent does not match any outer indentation level" << std::endl;
            exit(3);
        }
        if (_identationStack.back() != identCountForEachNewLine) {
            _identationStack.pop_back();
        }

        if (inStream.eof()) {
            identCountForEachNewLine = 0;
            Token dedent;
            dedent.setDedent();
            lastToken = dedent;
            return dedent;
        }
        else if (identCountForEachNewLine == _identationStack.back()) {
            //if after one pop back, they are same, put back token,
            //return a dedent.
            inStream.putback(c);
            Token dedent;
            dedent.setDedent();
            lastToken = dedent;
            return dedent;
        }
        else
            inStream.putback(c);

        Token dedent;
        dedent.setDedent();
        return lastToken = dedent;
    }

    Token token;
    if( inStream.eof() ) {
        token.eof() = true;
    }
    else if( c == '\n' ) {  // will not ever be the case unless new-line characters are not supressed.
        token.eol() = true;
        parsingANewLine = true;
    }
    else if (c == '#') {
        // this is a comment
        std::string comment;
        std::getline(inStream, comment);
        token.symbol(c);
        token.eol() = true;
        identCountForEachNewLine = 0;
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
    else if(c == ':')
        token.symbol(c);
    else if( c == '(' || c == ')')
        token.symbol(c);
    else if( c == '{' || c == '}' || c == '[' || c == ']')
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
    else if(isalpha(c) || c == '_') {  // an identifier?
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
    else if( c == ',' || c == '.'){
        token.symbol(c);
    }
    else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    _tokens.push_back(token);

    if (!token.eol() && parsingANewLine) {
        parsingANewLine = false;
        int topIdentValue = _identationStack.back();

        if (topIdentValue == identCountForEachNewLine) {
            // Case 1
            identCountForEachNewLine = 0;
            return lastToken = token;
        }
        else if (topIdentValue < identCountForEachNewLine) {
            // Case 2
            _identationStack.push_back(identCountForEachNewLine);
            //put back token
            ungetToken();
            lastToken = token;
            // return/report IDENT token
            Token ident;
            ident.setIdent();
            identCountForEachNewLine = 0;
            return ident;
        }
    }

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

char Tokenizer::peek() {
    // This function is used when we are about to parse an assignment statement
    // Once we read variable name, just peek to see if the next character in file stream
    //  is a period -> . <- indicating array operation
    char c;
    while( inStream.get(c) && (isspace(c)));
    inStream.putback(c);
    return c;
}
