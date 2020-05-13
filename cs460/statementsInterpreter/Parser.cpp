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
    // <simple_stmt> -> (<print_stmt | assign_stmt> | <array_ops> | <call_stmt> | <return_stmt> ) NEWLINE
    // <compound_stmt> -> <if_stmt> | <for_stmt> | <func_def>
    // <return_stmt> only when dealing with functions

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
            else if (tok.getName() == "def") {
                parsingFunction++;
                tokenizer.ungetToken();
                FunctionStatement * funcStmt = functionStatement();
                parsingFunction--;
                stmts->addStatement(funcStmt);
                tok = tokenizer.getToken();
            }
            else if (tok.getName() == "return"){
                if (parsingFunction) {
                    tokenizer.ungetToken();
                    ReturnStatement *returnStmt = returnStatement();
                    stmts->addStatement(returnStmt);
                    tok = tokenizer.getToken();
                }
                else {
                    std::cout << "Return statements are only allowed when parsing functions." << std::endl;
                    exit(2);
                }
            }
        }
        else {
            // either assignment statement or array operation or function call
            tokenizer.ungetToken(); //unget so we can store variable name
            char p = tokenizer.peek();

            if (p == '.') {
                ArrayOperationStatement *arrayOpStmt = array_ops();
                stmts->addStatement(arrayOpStmt);
                tok = tokenizer.getToken();
            }
            else if (p == '(') {
                //if p is open parentheses, its a fucntion call
                // so far we have ID '('
                CallStatement *callStmt = callStatement();
                stmts->addStatement(callStmt);
                tok = tokenizer.getToken();
            }
            else {
                AssignmentStatement *assignStmt = assignStatement();
                stmts->addStatement(assignStmt);
                tok = tokenizer.getToken();
            }
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
    if (comparison)
        comparison->setNotCount(notCount);

    if (notCount % 2 == 1) {
        // if not count is even, then the nots cancel out so comparison is same
        // if not count is odd, then it should be the opposite, not(comparison)
        if (comparison)
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
    // <assign-statement> -> (<id> | <subscription> ) '=' ( <test> | <array_init> )
    // <subscription> -> <id> '[' <test> ']'
    // <array_init> -> '[' [ <testlist> ] ']'

    Token varName = tokenizer.getToken(); // id
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name/id token, instead got", varName);

    Token assignOp_or_LeftOpenBracket = tokenizer.getToken();

    if (assignOp_or_LeftOpenBracket.isAssignmentOperator()) { // id '='
            Token maybeArrayInit = tokenizer.getToken();
            if (maybeArrayInit.isOpenBracket()) { // if true then this is an array init [ ]
                std::vector<ExprNode *>testList = testlist(); // get the testlist
                Token closeBracket = tokenizer.getToken(); //should be close bracket ]
                if (!closeBracket.isCloseBracket())
                    die("Parser::assignStatement", "Expected a close bracket token, instead got", closeBracket);
                Token newline = tokenizer.getToken();
                if (!newline.eol() && !newline.isComment())
                    die("Parser::assignStatement", "Expected a new line token, instead got", newline);
                return new AssignmentStatement(varName.getName(), testList); // for when id = '[' testlist ']' aka array
            }
            else {
                tokenizer.ungetToken();
                //just a regular test
                ExprNode *rightHandSideExpr = or_test();
                Token newline = tokenizer.getToken();
                if (!newline.eol() && !newline.isComment())
                    die("Parser::assignStatement", "Expected a new line token, instead got", newline);
                return new AssignmentStatement(varName.getName(), rightHandSideExpr); // for when id = test
            }
    }
    else if (assignOp_or_LeftOpenBracket.isOpenBracket()) { // [
        // We are subscripting, 2-D arrays are not supported at the moment
        ExprNode *index = or_test();
        Token closeBracket = tokenizer.getToken(); //should be close bracket ]
        if (!closeBracket.isCloseBracket())
            die("Parser::assignStatement", "Expected a close bracket token, instead got", closeBracket);
        Token assignOp = tokenizer.getToken();
        if (!assignOp.isAssignmentOperator())
            die("Parser::assignStatement", "expected an assignment operator, instead got", assignOp);
        Token regularTest = tokenizer.getToken();
        if (regularTest.isOpenBracket())
            die("Parser::assignStatement", "expected a test, 2-D arrays are not supported at the moment", regularTest);
        tokenizer.ungetToken(); // un-get the token that was gotten in regularTest
        ExprNode *rightHandSideExpr = or_test();

        Token newline = tokenizer.getToken();
        if (!newline.eol() && !newline.isComment())
            die("Parser::assignStatement", "Expected a new line token, instead got", newline);

        return new AssignmentStatement(varName.getName(), rightHandSideExpr, index); // for when id[i] = test
    }
    else
        die("Parser::assignStatement", "Expected an equal sign or open bracket token, instead got", assignOp_or_LeftOpenBracket);
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
    // <primary> -> <array_len>
    // <primary< -> call

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
    else if(tok.isName() && tok.isKeyword() && tok.getName() == "len") {
        tokenizer.ungetToken();
        ArrayLen *arrLen = array_len();
        if (negativeSignCount % 2 == 1) {
            // if negative sign count is odd new value should be opposite of original
            arrLen->setOppositeValue();
        }
        // if count is even then the value is unchanged aka it stays original
        return arrLen;
    }
    else if( tok.isName() ) {
        if (negativeSignCount % 2 == 1) {
            // if negative sign count is odd new value should be opposite of original
            tok.setOppositeValue();
        }
        // if count is even then the value is unchanged aka it stays original
        Token potentialOpenBracketOrOpenParan = tokenizer.getToken();
        if (potentialOpenBracketOrOpenParan.isOpenBracket()) {
            ExprNode *index = or_test();
            Token hasToBeCloseBracket = tokenizer.getToken();
            if (!hasToBeCloseBracket.isCloseBracket())
                die("Parser::primary", "Expected a close bracket, instead got", hasToBeCloseBracket);
            return new Variable(tok, index);
        }
        else if(potentialOpenBracketOrOpenParan.isOpenParen()) {
            // function call
            std::vector<ExprNode *> arguments = testlist();
            Token closeParantheses = tokenizer.getToken();
            if (!closeParantheses.isCloseParen())
                die("Parser::primary", "Expected a closed parantheses token, instead got", closeParantheses);

            return new FunctionCall(tok, arguments);
        }
        tokenizer.ungetToken();
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
    else if (tok.isCloseParen()) {
        tokenizer.ungetToken();
        return nullptr;
    }
    else if (tok.isCloseBracket()) {
        tokenizer.ungetToken();
        Token endArray = Token();
        endArray.setName("__end__");
        return new Variable(endArray);
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
    // <suite> -> NEWLINE IDENT stmt+ DEDENT

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

ArrayOperationStatement *Parser::array_ops() {
    // <array_ops> -> ID '.' ( 'append' | 'push' | 'pop' ) '(' <test> ')'

    Token varName = tokenizer.getToken();
    if (!varName.isName())
        die("Parser::array_ops", "Expected a name/id token, instead got", varName);

    Token dot = tokenizer.getToken();
    if (dot.symbol() != '.')
        die("Parser::array_ops", "Expected a dot/period ( . ), instead got", dot);

    Token operation = tokenizer.getToken();
    if (operation.getName() != "append" && operation.getName() != "pop" && operation.getName() != "push")
        die("Parser::array_ops", "Expected valid array operation ( append | pop | push ), instead got", operation);

    Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::array_ops", "Expected an open parantheses token, instead got", openParantheses);

    ExprNode * test = nullptr; // are we going to need a test?
    if (operation.getName() == "pop") {}
    else
        test = or_test();

    Token closeParantheses = tokenizer.getToken();
    if (!closeParantheses.isCloseParen())
        die("Parser::array_ops", "Expected a closed parantheses token, instead got", closeParantheses);

    Token newline = tokenizer.getToken();
    if (!newline.eol() && !newline.isComment())
        die("Parser::array_ops", "Expected a new line token, instead got", newline);

    return new ArrayOperationStatement(operation.getName(), varName.getName(), test);
}

ArrayLen *Parser::array_len() {
    // <array_len> -> 'len' '(' ID ')'

    Token lenKeyword = tokenizer.getToken();
    if (!(lenKeyword.isKeyword()) && lenKeyword.getName() != "len")
        die("Parser::array_len", "Expected 'len' keyword, instead got", lenKeyword);

    Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::array_len", "Expected an open parantheses token, instead got", openParantheses);

    Token variable = tokenizer.getToken();
    if (!variable.isName())
        die("Parser:array_len", "Expected a variable, instead got", variable);

    Token closeParantheses = tokenizer.getToken();
    if (!closeParantheses.isCloseParen())
        die("Parser::array_len", "Expected a closed parantheses token, instead got", closeParantheses);

    return new ArrayLen(variable);
}

CallStatement *Parser::call() {
    // <call> -> ID '(' { <testlist> } ')'

    Token functionName = tokenizer.getToken();
    if (!functionName.isName())
        die("Parser::callStatement", "Expected a function name/id token, instead got", functionName);

    Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::array_len", "Expected an open parantheses token, instead got", openParantheses);

    std::vector<ExprNode *> arguments; // are we going to need a testlist?
    Token eitherClosedParanOrTestList = tokenizer.getToken();

    if (eitherClosedParanOrTestList.isCloseParen()) {
        return new CallStatement(functionName.getName(), arguments);
    }
    else {
        tokenizer.ungetToken();
        arguments = testlist();

        Token closeParantheses = tokenizer.getToken();
        if (!closeParantheses.isCloseParen())
            die("Parser::call", "Expected a closed parantheses token, instead got", closeParantheses);

        return new CallStatement(functionName.getName(), arguments);
    }
}

CallStatement *Parser::callStatement() {
    // <call_stmt> -> <call>
    CallStatement *callStmt = call();

    Token newline = tokenizer.getToken();
    if (!newline.eol() && !newline.isComment())
        die("Parser::callStatement", "Expected a new line token, instead got", newline);

    return callStmt;
}

std::vector<std::string> Parser::parameter_list() {
    // <parameter_list> -> ID {, ID}*
    std::vector<std::string> parameterList;
    ExprNode *id = primary();
    while (id->token().isName()) {
        parameterList.push_back(id->token().getName());
        Token comma = tokenizer.getToken();
        if (!comma.isComma() && !comma.isCloseParen())
            die("Parser::parameter_list", "Expected a comma token or closed parantheses token, instead got", comma);
        if (comma.isCloseParen())
            break;
        id = primary();
    }
    tokenizer.ungetToken();
    return parameterList;
}

FunctionStatement *Parser::functionStatement() {
    // <func_def> -> 'def' ID '(' [<parameter_list>] ')' ':' suite

    Token defKeyword = tokenizer.getToken();
    if (defKeyword.getName() != "def")
        die("Parser::functionStatement", "Expected 'def' keyword token, instead got", defKeyword);

    //std::string id = primary()->token().getName();
    std::string _id = id();

    Token openParantheses = tokenizer.getToken();
    if (!openParantheses.isOpenParen())
        die("Parser::functionStatement", "Expected an open parantheses token, instead got", openParantheses);

    std::vector<std::string> parameterList;
    Token potentialClosedParantheses = tokenizer.getToken();

    if (potentialClosedParantheses.isCloseParen()) {
        // no parameter list
        Token colon = tokenizer.getToken();
        if (!colon.isColon())
            die("Parser::functionStatement", "Expected a colon token, instead got", colon);

        Statements *stmts = suite();

        return new FunctionStatement(_id, stmts, parameterList);
    }
    else {
        tokenizer.ungetToken();
        parameterList = parameter_list();

        Token closeParantheses = tokenizer.getToken();
        if (!closeParantheses.isCloseParen())
            die("Parser::functionStatement", "Expected a closed parantheses token, instead got", closeParantheses);

        Token colon = tokenizer.getToken();
        if (!colon.isColon())
            die("Parser::functionStatement", "Expected a colon token, instead got", colon);

        Statements *stmts = suite();

        return new FunctionStatement(_id, stmts, parameterList);
    }
}

ReturnStatement *Parser::returnStatement() {
    // <return_stmt> -> 'return' [test]
    Token returnKeyword = tokenizer.getToken();
    if (returnKeyword.getName() != "return")
        die("Parser::returnStatement", "Expected a 'return' keyword token, instead got", returnKeyword);

    ExprNode *returnValue = nullptr;
    Token maybeNewLine = tokenizer.getToken();
    if (maybeNewLine.eol()) {
        // if it was a new line token, then it was just an empty returns statement
    }
    else {
        // otherwise, we have an expr
        tokenizer.ungetToken();
        returnValue = or_test();
    }
    return new ReturnStatement(returnValue);
}

std::string Parser::id() {
    Token name = tokenizer.getToken();
    if (!name.isName())
        die("Parser::id", "Expected a name token, instead got", name);
    return name.getName();
}


