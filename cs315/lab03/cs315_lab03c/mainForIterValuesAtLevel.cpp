#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing iterValuesAtLevel begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing iterValuesAtLevel ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing iterValuesAtLevel ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
      if( ! tree->find( v ) ) 
            tree->insert( v );
    }

    infile.close();

    int maxDepth = tree->maxDepth();
    for( int i = 1; i <= maxDepth; i++ )
        tree->iterValuesAtLevel( i ); 
    
    std::cout << "Testing iterValuesAtLevel ends.\n";

    return 0;			    
}
