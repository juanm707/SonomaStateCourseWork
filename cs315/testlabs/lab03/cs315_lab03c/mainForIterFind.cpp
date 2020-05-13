#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing iterFind begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing iterFind ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing iterFind ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
      if( ! tree->find( v ) ) 
            tree->insert( v );
    }

    infile.close();
    infile.open( argv[1] );

    while( infile >> v ) {
        if( ! tree->iterFind( v ) )  {
          std::cout << "Unable to find " << v << std::endl;
          return 1;
        }
    }
    
    infile.close();
    infile.open( argv[1] );

    while( infile >> v ) {
        if( tree->iterFind( v+1 ) )  
          std::cout << "Found " << v+1 << std::endl;
    }
    
    std::cout << "Testing iterFind ends.\n";

    return 0;			    
}
