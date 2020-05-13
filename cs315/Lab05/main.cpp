/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 5
*/

#include <iostream>
#include "InvertedList.hpp"
#include <fstream>

int main() {

    std::fstream inputFile;
    inputFile.open("./valuesToInsert.txt");

    InvertedList * invList = new InvertedList();

    //Insert into list
    int input;
    while (inputFile >> input) {
        invList->insert(input);
    }

    std::fstream checkThis;
    checkThis.open("./memberValues.txt");

    // Count the members if actually in list
    int check;
    int count = 0;
    while( checkThis >> check) {
        if(invList->lookup(check))
            count++;
    }


    std::fstream nonMem;
    nonMem.open("./nonMemberValues.txt");

    // Count non-members and if not in list count it
    int non;
    int nonCheck = 0;
    while (nonMem >> non)
        if (!invList->lookup(non))
            nonCheck++;

    std::cout << "Member Count: " << count << std::endl;
    std::cout << "Non-Member Count: " << nonCheck << std::endl;

    /*InvertedList * check = new InvertedList();
    check->insert(5);
    check->insert(4);
    check->insert(2);
    check->insert(1);

    std::cout << "Printing...\n";
    check->print();

    check->remove(1);
    std::cout << "Printing...\n";
    check->print();

    check->remove(4);
    std::cout << "Printing...\n";
    check->print();

    check->insert(3);
    std::cout << "Printing...\n";
    check->print();

    check->insert(4);
    std::cout << "Printing...\n";
    check->print();

    check->remove(4);
    std::cout << "Printing...\n";
    check->print();

    check->remove(5);
    std::cout << "Printing...\n";
    check->print();

    check->remove(3);
    std::cout << "Printing...\n";
    check->print();

    check->remove(2);
    std::cout << "Printing...\n";
    check->print();

    check->insert(0);
    std::cout << "Printing...\n";
    check->print();

    check->insert(4999);
    std::cout << "Printing...\n";
    check->print();

    check->insert(5000);
    std::cout << "Printing...\n";
    check->print();*/
    return 0;
}
