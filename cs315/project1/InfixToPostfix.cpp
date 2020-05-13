////////////////////////////////////
// Author:     Dr. Kooshesh       //
// Student:    Juan Martinez      //
// Term:       Fall 2017          //
// Course:     CS 315             //       
// Assignment: Project 1          //         
// Date:       9/8/17             //         
// Professor:  Dr. Kooshesh       //
// File:       InfixToPostfix.cpp //        
////////////////////////////////////

/*  The majority of the work is done by the class 'convert'.
    This class builds an expression tree using the input infix
    expression.  A post-order traversal of the expression tree 'dumps'
    it into an array in postfix form.  The iterator copies the token
    from this array to user's arrays.

*/

#include "Token.hpp"
#include "InfixToPostfix.hpp"
#include<vector>

// ExprNode functions
ExprNode::ExprNode(Token *tk): _left(nullptr), _right(nullptr), token(tk) {}
ExprNode *&ExprNode::left() { return _left; }
ExprNode *&ExprNode::right() { return _right; } 
Token *ExprNode::getToken() { return token; }


// InfixToPostfix functions


void InfixToPostfix::convert( std::vector<Token *> &tokens, int numTokens, std::vector<Token *> &postfix )
{
    this->tokens = tokens;
    lex = new TokenIterator( tokens, numTokens );
    root = expr();
    Token *token = lex->next();
    if( token == nullptr || ! token->eol() ) {
        std::cout << "Malformed expression. The unexpected token is: ";
        token->print();
        std::cout << std::endl;
        std::cout << "Tokens that were processed are:\n";
        lex->printProcessedTokens();
	std::cout << std::endl;
        exit(1);
    }
    flatten( root, postfix );
    delete lex;
}

void InfixToPostfix::print( ExprNode *root ) 
{
    if( root == nullptr )  
        return;
    print( root->left() );
    print( root->right() );
    root->getToken()->print();
} 
    
ExprNode *InfixToPostfix::expr() 
{
    Token *tok = nullptr;
    ExprNode *left = term();
    while( (tok = lex->next())->isAdditionOperator() || tok->isSubtractionOperator() ) {
        ExprNode *p = new ExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
    }
    lex->put_back();
    return left;
}

ExprNode *InfixToPostfix::term()  
{
    Token *tok = nullptr;
    ExprNode *left = primary();
    while( (tok = lex->next())->isMultiplicationOperator() || tok->isDivisionOperator() || tok->isModuloOperator() ) {
        ExprNode *p = new ExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
    }
    lex->put_back();
    return left;
}
    
ExprNode *InfixToPostfix::primary() 
{
    ExprNode *p;
    Token *tok = lex->next();
    if( tok == nullptr ) {
        std::cout << "Primary -- Missing operand.\n" ;
        lex->printProcessedTokens();
	std::cout << std::endl;
    }
    if( tok->isRomanNumber() || tok->isAVariable() )
        return new ExprNode(tok);
    else if( tok->isOpenParen() ) {
        p = expr();
        if( ! lex->next()->isCloseParen() ) {
            std::cout << "Primary -- Missing a matching close-parenthesis.\n";
            lex->printProcessedTokens();
	    std::cout << std::endl;
            exit(1);
        }
        return p;
    }
    std::cout << "Primary: Misplaced token.\n";
    lex->printProcessedTokens();
    std::cout << std::endl;
    exit(1);

    return nullptr;  // Will not reach this statement!
}
    
void InfixToPostfix::flatten( ExprNode *root, std::vector<Token *> &tokens ) 
{
    if( root == nullptr ) 
        return;
    if( root->left() != nullptr )
        flatten( root->left(), tokens );
    if( root->right() != nullptr )
        flatten( root->right(), tokens );
    tokens.push_back(root->getToken());
}
