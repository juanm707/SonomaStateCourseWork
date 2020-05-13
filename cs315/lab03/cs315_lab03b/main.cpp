/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 3 Part B
*/

#include <iostream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {
    // create a tree and then print the values of its nodes
    // from the smallest to the largest.

    BinSearchTree *tree = new BinSearchTree();

    int v;
    while( std::cin >> v ) {
        tree->insert( v );
    }
    /*    tree->insert(50);
    tree->insert(25);
    tree->insert(75);
    tree->insert(190);
    tree->insert(43);
    tree->insert(210);
    tree->insert(10);
    tree->insert(60);
    tree->insert(49);
    tree->insert(21);
    tree->insert(47);
    tree->insert(1);
    tree->insert(0);
    tree->insert(100);
    tree->insert(23);
    tree->insert(66);
    tree->insert(3);
    tree->insert(390);
    tree->insert(400);
    tree->insert(401);
    tree->insert(2);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->insert(7);*/
    

    /*tree->insert(9);
    tree->insert(2);
    tree->insert(1);
    tree->insert(4);
    tree->insert(3);
    tree->insert(6);
    tree->insert(7);
    tree->insert(8);
    tree->insert(5);
    tree->insert(10);
    /*    tree->insert(11);
    tree->insert(12);
    tree->insert(13);
    tree->insert(14);
    tree->insert(15);
    tree->insert(16);
    tree->insert(17);
    tree->insert(18);
    tree->insert(19);
    tree->insert(20);*/

    //std::cout << "There are " << tree->size() << " values in tree\n";

    /*if (tree->find(3))
        std::cout << "Recursion find\n";

    if (tree->iterFind(4))
    std::cout << "Iterative find\n";*/

    tree->inorderDump();

    std::cout << "Depth of tree is " << tree->maxDepth() << std::endl;

    return 0;
}
