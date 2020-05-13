////////////////////////////////////////
// Author:     Dr. Kooshesh           //
// Student:    Juan Martinez          //
// Term:       Fall 2017              //
// Course:     CS 315                 //
// Assignment: Lab 01                 //
// Date:       9/11/17                //
// Professor:  Dr. Kooshesh           //
// File:       lab01b_printBits_2.cpp //
////////////////////////////////////////

#include<iostream>
#include "lab01b_printBits_2.hpp"

// Two different implementation of the same function.

void dumpBits0(bit_t v, int digitsPrinted)
{
    if( v == 0 ) {
        int leadingZerosToPrint = sizeof(bit_t) * 8 - digitsPrinted;
        for( int i = 0; i < leadingZerosToPrint; i++ ) 
            std::cout << 0;
        if( digitsPrinted == 0 )
            std::cout << std::endl;
        return;
    }
    dumpBits0(v / 2, digitsPrinted + 1);
    std::cout << ( v % 2 ? 1 : 0 );
    if( digitsPrinted == 0 )
        std::cout << std::endl;
}

void dumpBits(bit_t v)
{
    bit_t pos = 1;
    for( pos <<= sizeof(bit_t) * 8 - 1; pos; pos >>= 1 ) {
        std::cout << (v & pos ? 1 : 0);
    }
    std::cout << std::endl;
}
