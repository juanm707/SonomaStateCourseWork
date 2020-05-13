#ifndef EXPRINTER_RANGE_HPP
#define EXPRINTER_RANGE_HPP


#include "ArithExpr.hpp"

class Range {
public:
    Range(ExprNode  *_rangeValue); // set initValue to zero 0 and stepValue to 1
    Range(ExprNode *_initValue, ExprNode *_rangeValue); // set step value to 1
    Range(ExprNode *_initValue, ExprNode *_rangeValue, ExprNode *_stepValue); // set all to appropriate value
    ~Range();

    void setValues(SymTab &symTab);

    ExprNode  *getInitExpr();
    ExprNode  *getStepExpr();
    ExprNode  *getRangeExpr();

    int getInitValue();
    int getStepValue();
    int getRangeValue();

    bool condition(); // iterate?
    int next(); // the value to be assigned to the loop counter
    int numValues();

private:
    int initValue, stepValue, rangeValue, numberOfValues;
    ExprNode *initV, *stepV, *rangeV;
    bool firstTime;
};


#endif //EXPRINTER_RANGE_HPP
