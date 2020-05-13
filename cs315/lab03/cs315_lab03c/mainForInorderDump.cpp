#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing inorderDump begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing inorderDump ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing inorderDump ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
      if( ! tree->find( v ) ) 
            tree->insert( v );
    }

    tree->inorderDump();    
    std::cout << "Testing inorderDump ends.\n";

    return 0;			    
}
