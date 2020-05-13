cmake_minimum_required(VERSION 3.8)
project(assembly)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Instruction.h)
add_executable(main ${SOURCE_FILES})