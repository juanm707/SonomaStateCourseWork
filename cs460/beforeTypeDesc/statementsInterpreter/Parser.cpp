
#include<vector>
#include<iostream>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"

// Parser functions

void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    // This function is called when we KNOW that we are about to parse
    // a series of assignment statements.

    // This function parses the grammar rules:

    // <statement> -> <statement> {<statement>}
    // <statement> -> <for-statement> | <assign-statement> | <print-statement>
    // <statement> -> Epsilon


    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName() || tok.eol()) { // Student modified this
        if (tok.eol()) {
            tok = tokenizer.getToken();
        }
        else if (tok.isKeyword()) {

            if (tok.getName() == "print") {
                PrintStatement *printStmt = printStatement();
                stmts->addStatement(printStmt);
                tok = tokenizer.getToken();
            }
            else if (tok.getName() == "for") {
                tokenizer.ungetToken();
                ForStatement *forStmt = forStatement();
                stmts->addStatement(forStmt);
                tok = tokenizer.getToken();
            }
        }
        else {
            tokenizer.ungetToken();
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
            tok = tokenizer.getToken();
        }
    }
    tokenizer.ungetToken();
    return stmts;
}

PrintStatement *Parser::printStatement() {
    // Parsed the following grammar rule
    // <print-statement> -> print <id>

   ExprNode *rhs = primary(); // Get the variable or whole number

   Token newline = tokenizer.getToken();
   if (!newline.eol())
       die("Parser::printStatement", "Expected a new line token, instead got", newline);

   return new PrintStatement(rhs);
}

AssignmentStatement *Parser::assignStatement() {
    // Parses the following grammar rule
    // 
    // <assign-statement> -> <id> = <expr>
    // <assign-statement> -> <id> = <rel-expr> ???

    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);

    // ExprNode *rightHandSideExpr = expr();
    ExprNode *rightHandSideExpr = rel_term();

    // Commented out so we do not need to end with semicolons
    /*Token tok = tokenizer.getToken();
    if (!tok.isSemiColon())
        die("Parser::assignStatement", "Expected a semicolon, instead got", tok);
    */

    Token newline = tokenizer.getToken();
    if (!newline.eol())
        die("Parser::assignStatement", "Expected a new line token, instead got", newline);

    return new AssignmentStatement(varName.getName(), rightHandSideExpr);
}

ExprNode *Parser::expr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.

    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode *Parser::term() {
    // This function parses the grammar rules:

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | % | //
    // "//" = integer divison

    // However, the implementation makes the <mult-op> left associate.

    ExprNode *left = primary();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator() || tok.isIntegerDivisionOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::primary() {
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z][_a-zA-Z0-9]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();

    if (tok.isWholeNumber() )
        return new WholeNumber(tok);
    else if( tok.isName() )
        return new Variable(tok);
    else if (tok.isOpenParen()) {
        ExprNode *p = expr();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}


/*ExprNode *Parser::rel_expr() {
    // This function parses the grammar rules:
    // <rel-expr> -> <rel-term> {(==, !=) <rel-term>}

    ExprNode *left = rel_term();
    Token tok = tokenizer.getToken();

    while (tok.isEqualEqualOperator() || tok.isNotEqualOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = rel_term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
*/

ExprNode *Parser::rel_term() {
    // This function parses the grammar rules:
    // <rel-term> -> <rel-primary> {(>, >=, <, <=) <rel-primary>} No longer valid.... From part 1 of project
    //
    // comparison: arith_expr {comp_op arith_expr}*
    // comp_op: '<'|'>'|'=='|'>='|'<='|'<>'|'!='

    ExprNode *left = expr();
    Token tok = tokenizer.getToken();

    while (tok.isGreaterThanOperator() || tok.isGreaterThanOrEqualOperator() || tok.isLessThanOperator()
    || tok.isLessThanOrEqualOperator() || tok.isEqualEqualOperator() || tok.isNotEqualOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = expr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

/*ExprNode *Parser::rel_primary() {
    // This function parses the grammar rules:
    // <rel-primary> -> <arith-expr>
    return expr();
}*/

ForStatement *Parser::forStatement() {
    // This function parses the grammar rules:
    // <for-statement> -> for ( <assign-statement> ; <rel-expr> ; <assign-statement> ) { <statements> }

    Token forKeyword = tokenizer.getToken();
    if (!forKeyword.isKeyword())
        die("Parser::forStatement", "Expected a for keyword token, instead got", forKeyword);

    Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::forStatement", "Expected an open parantheses token, instead got", openParantheses);

    AssignmentStatement *assignStmt = assignStatement();

    Token semiColon = tokenizer.getToken();
    if (!semiColon.isSemiColon())
        die("Parser::forStatement", "Expected a semi-colon token, instead got", semiColon);

    ExprNode *relExpr = rel_term();

    semiColon = tokenizer.getToken();
    if (!semiColon.isSemiColon())
        die("Parser::forStatement", "Expected a semi-colon token, instead got", semiColon);

    //get rid of any "blanks", if any, before the assignment statement begins
    Token throwaway = tokenizer.getToken();
    if (throwaway.isName())
        tokenizer.ungetToken();
    else {} // do nothing

    AssignmentStatement *updateAssignStmt = assignStatement();

    Token closeParantheses = tokenizer.getToken();
    if (!closeParantheses.isCloseParen())
        die("Parser::forStatement", "Expected a closed parantheses token, instead got", closeParantheses);

    Token openCurlyBracket = tokenizer.getToken();
    if (!openCurlyBracket.isOpenCurly())
        die("Parser::forStatement", "Expected an opened curly token, instead got", openCurlyBracket);

    Statements *stmts = statements();

    Token closeCurlyBracket = tokenizer.getToken();
    if (!closeCurlyBracket.isCloseCurly())
        die("Parser::forStatement", "Expected an close curly token, instead got", closeCurlyBracket);

    return new ForStatement(assignStmt, relExpr, updateAssignStmt, stmts);
}
