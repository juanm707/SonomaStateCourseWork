#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing hasRootToLeafSum begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing hasRootToLeafSum ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing hasRootToLeafSum ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
      if( ! tree->find( v ) ) 
            tree->insert( v );
    }

    infile.close();
    int val[] = {17331, 22138, 1896, 3054, 2000};
    int numVal = sizeof( val ) / sizeof( int );
    for( int i = 0; i < numVal; i++ )
        if( ! tree->hasRootToLeafSum( val[i] ) )
        std::cout << "Was not able to find root-to-leaf sum for " << val[i] << std::endl;

    std::cout << "Testing hasRootToLeafSum ends.\n";

    return 0;			    
}
