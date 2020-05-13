#include <iostream>
#include "Range.hpp"

Range::Range(ExprNode *_rangeValue) : initV{nullptr}, stepV{nullptr}, rangeV{_rangeValue}, numberOfValues{1}, firstTime{true} {

}

Range::Range(ExprNode *_initValue, ExprNode *_rangeValue) : initV{_initValue}, stepV{nullptr}, rangeV{_rangeValue},
                                                                numberOfValues{2}, firstTime{true} {

}

Range::Range(ExprNode *_initValue, ExprNode *_rangeValue, ExprNode *_stepValue) : initV{_initValue}, stepV{_stepValue},
                                                                rangeV{_rangeValue}, numberOfValues{3}, firstTime{true} {

}

bool Range::condition() {
    if (stepValue < 0)
        return initValue > rangeValue;
    else if (stepValue > 0)
        return initValue < rangeValue;
    else {
        //if zero
        std::cout << "step arg must not be zero\n";
        exit(2);
    }
}

int Range::next() {
  int oldValue = initValue;
  initValue += stepValue;
  return oldValue;
    
}

int Range::numValues() {
    return numberOfValues;
}

int Range::getInitValue() {
    return initValue;
}

int Range::getStepValue() {
    return stepValue;
}

int Range::getRangeValue() {
    return rangeValue;
}

void Range::setValues(SymTab &symTab) {
    if (numberOfValues == 1) {
        initValue = 0;
        stepValue = 1;
        rangeValue = dynamic_cast<IntegerTypeDescriptor *>(rangeV->evaluate(symTab))->intValue();
    }
    else if (numberOfValues == 2) {
        stepValue = 1;
        initValue = dynamic_cast<IntegerTypeDescriptor *>(initV->evaluate(symTab))->intValue();
        rangeValue = dynamic_cast<IntegerTypeDescriptor *>(rangeV->evaluate(symTab))->intValue();
    }
    else if (numberOfValues == 3) {
        initValue = dynamic_cast<IntegerTypeDescriptor *>(initV->evaluate(symTab))->intValue();
        rangeValue = dynamic_cast<IntegerTypeDescriptor *>(rangeV->evaluate(symTab))->intValue();
        stepValue = dynamic_cast<IntegerTypeDescriptor *>(stepV->evaluate(symTab))->intValue();
    }
    else {
        std::cout << "Whoops, expected 1, 2, or 3 range values, instead got " << numberOfValues << std::endl;
        exit(3);
    }
}

ExprNode *Range::getInitExpr() {
    return initV;
}

ExprNode *Range::getStepExpr() {
    return stepV;
}

ExprNode *Range::getRangeExpr() {
    return rangeV;
}

Range::~Range() {
    delete initV;
    initV = nullptr;
    delete stepV;
    stepV = nullptr;
    delete rangeV;
    rangeV = nullptr;
}

