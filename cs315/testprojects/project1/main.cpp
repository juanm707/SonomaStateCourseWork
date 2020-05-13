////////////////////////////////////
// Author:     Juan Martinez      //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //
// Assignment: Project 1          //
// Date:       9/8/17             //
// Professor:  Dr. Kooshesh       //
// File:       main.cpp           //
////////////////////////////////////

#include <sstream>
#include "Token.hpp"
#include "InfixToPostfix.hpp"
#include "Tokenizer.h"
#include "Number.h"
#include <stack>
#include <map>

using namespace std;

//GLOBAL TO STORE MAP TABLE
char mapletter;
std::map<char, int> symTab;

//Function Prototype
std::vector<Token* > Parser(std::vector <Token* > & infix); //Checks expression and returns tokens in infix form
int Evaluate(std::vector<Token* > & postfixTokens); //Evaluates postfix expression
std::string getExpr(); //Gets user input
void initMap(); //Initialize map

int main() {

    initMap(); //initialize map variables with -1 (UNDEFINED)
    std::cout << "Enter valid expression (CMD-D/CTRL-D to stop): \n";
    std::string expr = getExpr();

    while (expr != "eof") {

        Tokenizer *tok = new Tokenizer(expr);
        std::vector<Token *> tokens = tok->tokenize();
        std::vector<Token *> newTokens = Parser(tokens);

        int answer = Evaluate(newTokens);
        Number ans(answer);
	
	if (answer < 0 || answer > 3999) {
	  std::cout << mapletter << " UNDEFINED" << std::endl;
	  symTab[mapletter] = -1;
	}
	else
	  std::cout << mapletter << " equals " << ans.romanValue() << std::endl;

        delete tok;

        expr = getExpr();
    }

    return 0;
}

std::vector<Token *> Parser(std::vector <Token* > & infix) {

    if (infix[0]->isAVariable()) { //get variable and remove it and store it!
        mapletter = infix[0]->getVariable();
        infix.erase(infix.begin());

        if (infix[0]->isEqualSign()) { //get equal sign and remove it
            infix.erase(infix.begin());

            InfixToPostfix *itop = new InfixToPostfix(); //begin conversion
            std::vector<Token *> postfixTokens;
            int numTokens = infix.size();
            itop->convert(infix, numTokens, postfixTokens);
            delete itop;
            return postfixTokens; //return in post fix form
        } else {
            std::cerr << "MUST HAVE EQUAL SIGN AFTER VARIABLE\n";
            exit(2);
        }
    } else {
        std::cerr << "MUST BEGIN WITH VARIABLE STARTING FROM a UNTIL z\n";
        exit(3);
    }
}

int Evaluate(std::vector<Token* > & postfixTokens) {

    int right = 0; //OPERANDS
    int left = 0;
    std::stack<int> pfStack;

    for (int i = 0; unsigned(i) < postfixTokens.size(); i++) {
        int sum = 0; // for values

        if (postfixTokens[i]->isRomanNumber()) { // if its a roman numeral
            Number roNum(postfixTokens[i]->romanNumber()); //create roman numeral
            if (roNum.isALegalRomanNumber()) { // if legal roman numeral
                pfStack.push(roNum.intValue());
            } else {
                std::cerr << "NOT A LEGAL ROMAN NUMERAL\n";
                exit(6);
            }

        } else if (postfixTokens[i]->isAdditionOperator()) {
            right = pfStack.top();
            pfStack.pop();
            left = pfStack.top();
            pfStack.pop();
            sum = left + right;
            pfStack.push(sum);
        } else if (postfixTokens[i]->isSubtractionOperator()) {
            right = pfStack.top();
            pfStack.pop();
            left = pfStack.top();
            pfStack.pop();
            sum = left - right;
            pfStack.push(sum);
        } else if (postfixTokens[i]->isMultiplicationOperator()) {
            right = pfStack.top();
            pfStack.pop();
            left = pfStack.top();
            pfStack.pop();
            sum = left * right;
            pfStack.push(sum);
        } else if (postfixTokens[i]->isDivisionOperator()) {
            right = pfStack.top();
            pfStack.pop();
            left = pfStack.top();
            pfStack.pop();
            sum = left / right;
            pfStack.push(sum);
        } else if (postfixTokens[i]->isModuloOperator()) {
            right = pfStack.top();
            pfStack.pop();
            left = pfStack.top();
            pfStack.pop();
            sum = left % right;
            pfStack.push(sum);
        } else {

            if (postfixTokens[i]->getVariable() >= 'a' && postfixTokens[i]->getVariable() <= 'z') { // if operand is a map variable, get its value.
	      if (symTab[postfixTokens[i]->getVariable()] == -1) //if we encounter an undefined value in expression, return -1(undefined)
		return -1;
	      pfStack.push(symTab[postfixTokens[i]->getVariable()]); //push valid variable and not undefined
            }
        }
    }
    if (symTab.find(mapletter) == symTab.end()) {
        symTab.insert(std::pair<char, int>(mapletter, pfStack.top())); // if variable not in map, store it with corresponding value
    }
    else {
        symTab[mapletter] = pfStack.top(); //if variable already in map, change value of variable
    }

    return pfStack.top();
}

std::string getExpr() {

    char item;              //store character
    std::cin.get(item);     //get character
    std::string expr = "";  //for return expression
    std::string roman = ""; //for Roman Numerals

    while (item != '\n') {

        if (cin.eof())
            return "eof"; //end of user input

        else if (item == ' ') {
            //do nothing if space
        }
        else if (item >= 'a' && item <= 'z') {
            expr += item;
        }
        else if (item == '=' || item == '\t') {
            expr += item;
        }
        else if (item == 'I' || item == 'V' || item == 'X' || item == 'L' || item == 'C' || item == 'D' ||
                   item == 'M') {
            roman += item;
        }
        else if (item == '+' || item == '-' || item == '*' || item == '/' || item == '%') {
	  expr += roman; //add roman numeral
            roman = ""; //set roman empty string for next roman numeral
            expr += " ";
            expr += item;
        }
        else if (item == '(') {
            expr += item;
        }
        else if (item == ')') {
            expr += roman;
            expr += " ";
            expr += item;
            roman = "";
        }
        else if (item >= '0' && item <= '9') {
            std::cerr << "NO DECIMAL INTEGERS IN EXPRESSION!\n";
            exit(26);
        }
        else {
            std::cerr << "NOT ABLE TO RECOGNIZE ROMAN NUMERAL!\n";
            exit(27);
        }

        expr += " "; //add space after each item
        cin.get(item); //get next item
    }

    expr += roman; // any last roman characters (if any)

    if (expr == "\n" || expr == "") {
        std::cerr << "NO INPUT!\n";
        exit(25);
    }

    return expr;
}

void initMap() {

    symTab['a'] = -1;
    symTab['b'] = -1;
    symTab['c'] = -1;
    symTab['d'] = -1;
    symTab['e'] = -1;
    symTab['f'] = -1;
    symTab['g'] = -1;
    symTab['h'] = -1;
    symTab['i'] = -1;
    symTab['j'] = -1;
    symTab['k'] = -1;
    symTab['l'] = -1;
    symTab['m'] = -1;
    symTab['n'] = -1;
    symTab['o'] = -1;
    symTab['p'] = -1;
    symTab['q'] = -1;
    symTab['r'] = -1;
    symTab['s'] = -1;
    symTab['t'] = -1;
    symTab['u'] = -1;
    symTab['v'] = -1;
    symTab['w'] = -1;
    symTab['x'] = -1;
    symTab['y'] = -1;
    symTab['z'] = -1;
}
