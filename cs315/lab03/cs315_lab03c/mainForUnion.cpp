#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing union begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing union ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();
    BinSearchTree *tree2 = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing union ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
        if( ! tree->find( v ) ) {
            tree->insert( v );
            tree2->insert( v );
        }
    }

    int size = tree->size();

    infile.close();

    BinSearchTree *un = tree->unionWith( tree2 );
    if( un->size() != size )
        std::cout << "Size mismatch in union: should have gotten " << size << " instead got " << un->size() << std::endl;
    
    infile.open( argv[1] );
    while( infile >> v ) {
        if( ! un->find( v ) )
            std::cout << "Unable to find " << v << " in the union tree.\n";        
    }
    
    std::cout << "Testing union ends.\n";

    return 0;			    
}
