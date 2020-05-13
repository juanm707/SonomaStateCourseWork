#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing kthSmallest begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing kthSmallest ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing kthSmallest ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
      if( ! tree->find( v ) ) 
            tree->insert( v );
    }

    infile.close();

    int prev = tree->kthSmallest( 1 );
    int size = tree->size();
    for( int i = 2; i <= size; i++ ) {
        int  cur = tree->kthSmallest( i );
        if( cur < prev ) {
            std::cout << "The values in the tree are out of order.\n";
            return 1;			    
        } else std::cout << cur << std::endl;
        prev = cur;			    
    }
    
    
    std::cout << "Testing kthSmallest ends.\n";

    return 0;			    
}
