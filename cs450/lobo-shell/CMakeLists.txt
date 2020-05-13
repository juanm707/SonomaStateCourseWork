cmake_minimum_required(VERSION 3.16)
project(lobo_shell C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(lobo_shell
        include/constants.h
        include/parsetools.h
        src/parsetools.c
        main.c)
