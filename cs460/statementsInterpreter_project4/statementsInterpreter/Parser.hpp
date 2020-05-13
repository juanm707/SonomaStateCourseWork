
#ifndef __PARSER_HPP
#define __PARSER_HPP

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "SymTab.hpp"
#include "ArithExpr.hpp"
#include "Statements.hpp"

#include<vector>
#include<iostream>
#include<map>


class Parser {
public:
    Parser(Tokenizer &tokenizer) : tokenizer{tokenizer} {}

    Statements *statements();
    AssignmentStatement *assignStatement();
    PrintStatement *printStatement();
    ForStatement *forStatement();
    IfStatement *ifStatement();

    ExprNode *rel_expr();
    ExprNode *rel_term();
    ExprNode *rel_primary();

    ExprNode *expr();
    ExprNode *term();
    ExprNode *primary();

    ExprNode *or_test();
    ExprNode *and_test();
    ExprNode *not_test();

    std::vector<ExprNode *> testlist();
    Statements *suite();

private:
    Tokenizer &tokenizer;
    void die(std::string where, std::string message, Token &token);
};

#endif

