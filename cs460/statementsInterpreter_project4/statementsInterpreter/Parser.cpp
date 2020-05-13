
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

    // <statement> -> <simple_stmt> | <compound_stmt>
    // <simple_stmt> -> (<print_stmt | assign_stmt>) NEWLINE
    // <compound_stmt> -> <if_stmt> | <for_stmt>

    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName() || tok.eol() || tok.isComment()) { // Student modified this
        if (tok.eol()) {
            tok = tokenizer.getToken();
        }
        else if  (tok.isComment()) {
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
            else if (tok.getName() == "if") {
                tokenizer.ungetToken();
                IfStatement *ifStmt = ifStatement();
                stmts->addStatement(ifStmt);
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

std::vector<ExprNode *> Parser::testlist() {
    // Parsed the following grammar rule
    // <testlist> -> test {',' test}*
    // <test> -> <or_test>

    std::vector<ExprNode *> testList;
    //ExprNode *rhs = rel_term(); // Get the first variable or whole number or string or expr
    ExprNode *test = or_test();
    testList.push_back(test); // add it to the list of expr nodes

    Token comma = tokenizer.getToken();
    while (comma.isComma()) {
        //rhs = rel_term();
        test = or_test();
        testList.push_back(test);
        comma = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return testList;
}

ExprNode *Parser::or_test() {
    // Parses the following grammar rule
    // <or_test> -> <and_test> {'or' <and_test>}*

    ExprNode *left = and_test();
    Token orKeyword = tokenizer.getToken();

    while(orKeyword.isOrOperator()) {
        InfixExprNode *p = new InfixExprNode(orKeyword);
        p->left() = left;
        p->right() = and_test();
        left = p;
        orKeyword = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::and_test() {
    // Parses the following grammar rule
    // <and_test> -> <not_test> {'and' <not_test>}*

    ExprNode *left = not_test();
    Token andKeyword = tokenizer.getToken();

    while(andKeyword.isAndOperator()) {
        InfixExprNode *p = new InfixExprNode(andKeyword);
        p->left() = left;
        p->right() = not_test();
        left = p;
        andKeyword = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::not_test() {
    // Parses the following grammar rules
    // <not_test> -> 'not' <not_test> | <comparison>

    int notCount = 0;
    Token tok = tokenizer.getToken();
    while(tok.isNotOperator()) {
        notCount++;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    ExprNode *comparison = rel_term();
    comparison->setNotCount(notCount);

    if (notCount % 2 == 1) {
        // if not count is even, then the nots cancel out so comparison is same
        // if not count is odd, then it should be the opposite, not(comparison)
        comparison->setLogicalOppositeValue();
    }
    return comparison;
}

PrintStatement *Parser::printStatement() {
    // Parsed the following grammar rule
    // <print-statement> -> print [ testlist ]

    std::vector<ExprNode *> printStatements;
    printStatements = testlist();

    Token newline = tokenizer.getToken();
    if (!newline.eol() && !newline.isComment())
       die("Parser::printStatement", "Expected a new line token, instead got", newline);
    return new PrintStatement(printStatements);
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
    ExprNode *rightHandSideExpr = or_test();

    // Commented out so we do not need to end with semicolons
    /*Token tok = tokenizer.getToken();
    if (!tok.isSemiColon())
        die("Parser::assignStatement", "Expected a semicolon, instead got", tok);
    */

    Token newline = tokenizer.getToken();
    if (!newline.eol() && !newline.isComment())
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
    // <primary> -> { - } <primary>
    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z][_a-zA-Z0-9]+
    // <primary> -> (<expr>)
    // <primary> -> STRING+

    int negativeSignCount = 0;
    Token tok = tokenizer.getToken();
    while(tok.isSubtractionOperator()) {
        negativeSignCount++;
        tok = tokenizer.getToken();
    }
    tok.setNegSignCount(negativeSignCount);

    if (tok.isWholeNumber() ) {
        if (negativeSignCount % 2 == 1) {
            // if negative sign count is odd new value should be opposite of original
            tok.setWholeNumber(tok.getWholeNumber()*-1);
        }
        // if count is even then the value is unchanged aka it stays original
        return new WholeNumber(tok);
    }
    else if (tok.isDoubleNumber() ) {
        if (negativeSignCount % 2 == 1) {
            // if negative sign count is odd new value should be opposite of original
            tok.setDoubleNumber(tok.getDoubleNumber()*-1);
        }
        // if count is even then the value is unchanged aka it stays original
        return new DoubleNumber(tok);
    }
    else if( tok.isName() ) {
        if (negativeSignCount % 2 == 1) {
            // if negative sign count is odd new value should be opposite of original
            tok.setOppositeValue();
        }
        // if count is even then the value is unchanged aka it stays original
        return new Variable(tok);
    }
    else if( tok.isString())
        return new StringTerminal(tok);
    else if( tok.eol()) {
        // if it is end of line, then it was just a simple print statement ex: print
        // this just prints a new line
        tokenizer.ungetToken();
        Token newLineString = Token();
        newLineString.setString("\n");
        return new StringTerminal(newLineString);
    }
    else if (tok.isOpenParen()) {
        ExprNode *p = or_test();
        if (negativeSignCount % 2 == 1) {
            if (p->isOppositeValue()) //if p is -(p), then now it is -(-(p))
                p->unSetOppositeValue();
            else {
                p->setOppositeValue();
                p->setNegSignCount(negativeSignCount);
            }
        }
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}

ExprNode *Parser::rel_term() {
    // This function parses the grammar rules:
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
    // <for-statement> -> for ID in range(<testlist>): suite

    Token forKeyword = tokenizer.getToken();
    if (!forKeyword.isKeyword())
        die("Parser::forStatement", "Expected a for keyword token, instead got", forKeyword);

    /*Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::forStatement", "Expected an open parantheses token, instead got", openParantheses);
    */

    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::forStatement", "Expected a name token, instead got", varName);

    Token inKeyword = tokenizer.getToken();
    if (inKeyword.getName() != "in")
        die("Parser::forStatement", "Expected an \"in\" token, instead got", varName);

    Token rangeKeyword = tokenizer.getToken();
    if (rangeKeyword.getName() != "range")
        die("Parser::forStatement", "Expected a \"range\" token, instead got", varName);

    Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::forStatement", "Expected an open parantheses token, instead got", openParantheses);

    // 3 cases for range!
    // --------------------------
    // 1. range(e)
    // 2. range(start, end, step)
    // 3. range(start, end)

    std::vector<ExprNode *> rangeParameters = testlist(); //TODO put range instance in evaluate?
    Range *rangeInstce  = nullptr;
    if (rangeParameters.size() == 1)
        rangeInstce = new Range(rangeParameters[0]);
    else if (rangeParameters.size() == 2)
        rangeInstce = new Range(rangeParameters[0], rangeParameters[1]);
    else if (rangeParameters.size() == 3)
        rangeInstce = new Range(rangeParameters[0], rangeParameters[1],
                rangeParameters[2]);
    else {
        std::cout << "Expected 1,2, or 3 values for range. Instead got: " << rangeParameters.size() << " values\n";
        exit(3);
    }

    Token closeParantheses = tokenizer.getToken();
    if (!closeParantheses.isCloseParen())
        die("Parser::forStatement", "Expected a closed parantheses token, instead got", closeParantheses);

    Token colon = tokenizer.getToken();
    if (!colon.isColon())
        die("Parser::forStatement", "Expected a colon token, instead got", colon);

    //Statements *stmts = statements();
    Statements *stmts = suite();

    return new ForStatement(rangeInstce, stmts, varName.getName());
}

IfStatement *Parser::ifStatement() {
    // This function parses the grammar rules:
    // <if-statement> -> 'if' test ':' suite {'elif' test ':' suite}* ['else' ':' suite]
    std::vector< std::pair<ExprNode *, Statements *> > ifStmtTestSuite;
    std::pair<ExprNode *, Statements *> testSuitePair;
    std::vector< std::string> labels;

    Token ifKeyword = tokenizer.getToken();
    if(ifKeyword.getName() != "if")
        die("Parser::ifStatement", "Expected an if keyword token, instead got", ifKeyword);

    labels.emplace_back("if");

    ExprNode *test = or_test();

    Token colon = tokenizer.getToken();
    if(!colon.isColon())
        die("Parser::ifStatement", "Expected a colon token, instead got", colon);

    Statements *stmts = suite();

    testSuitePair = std::make_pair(test, stmts);
    ifStmtTestSuite.push_back(testSuitePair); // Added first if -> stmts to vector

    Token elif = tokenizer.getToken(); // potentially an elif
    while (elif.getName() == "elif") {
        labels.emplace_back("elif");
        test = or_test();
        colon = tokenizer.getToken();
        if(!colon.isColon())
            die("Parser::ifStatement", "Expected a colon token, instead got", colon);
        stmts = suite();
        testSuitePair = std::make_pair(test, stmts);
        ifStmtTestSuite.push_back(testSuitePair);
        elif = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    Token elseKeyword = tokenizer.getToken();
    if (elseKeyword.getName() == "else") {
        labels.emplace_back("else");
        colon = tokenizer.getToken();
        if(!colon.isColon())
            die("Parser::ifStatement", "Expected a colon token, instead got", colon);
        Token alwaysTrue;
        alwaysTrue.setWholeNumber(1);
        WholeNumber * wh = new WholeNumber(alwaysTrue);
        test = wh;
        stmts = suite();
        testSuitePair = std::make_pair(test, stmts);
        ifStmtTestSuite.push_back(testSuitePair);
    }
    else
        tokenizer.ungetToken(); //if it was an else, just move on but if it wasnt then ungetToken to re-get statement token.
    return new IfStatement(ifStmtTestSuite, labels);
}

Statements *Parser::suite() {
    Token newLine = tokenizer.getToken();
    if (!newLine.eol())
        die("Parser::suite", "Expected a newline token, instead got", newLine);
    while (newLine.eol()) {
        newLine = tokenizer.getToken();
    }

    Token ident = newLine; // At this point, newLine should be an ident token.
    if (!ident.isIdent())
        die("Parser::suite", "Expected an ident token, instead got", ident);

    Statements * stmts = statements();

    Token dedent = tokenizer.getToken();
    if (!dedent.isDedent())
        die("Parser::suite", "Expected a dedent token, instead got", dedent);

    return stmts;
}
