cmake_minimum_required(VERSION 3.12)
project(ExprInter)

set(CMAKE_CXX_STANDARD 14)

add_executable(ExprInter main.cpp Token.cpp Token.hpp Tokenizer.cpp Tokenizer.hpp Parser.hpp Parser.cpp ArithExpr.cpp ArithExpr.hpp SymTab.cpp SymTab.hpp Statements.cpp Statements.hpp)