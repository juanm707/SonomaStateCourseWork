
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
    Parser(Tokenizer &tokenizer) : tokenizer{tokenizer}, parsingFunction{0} {}

    Statements *statements();
    AssignmentStatement *assignStatement();
    PrintStatement *printStatement();
    ForStatement *forStatement();
    IfStatement *ifStatement();
    ArrayOperationStatement *array_ops();
    CallStatement *callStatement();
    CallStatement *call();
    FunctionStatement *functionStatement();
    ReturnStatement *returnStatement();

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
    ArrayLen *array_len();
    std::vector<std::string> parameter_list();
    std::string id();

private:
    Tokenizer &tokenizer;
    void die(std::string where, std::string message, Token &token);
    int parsingFunction;
};

#endif

