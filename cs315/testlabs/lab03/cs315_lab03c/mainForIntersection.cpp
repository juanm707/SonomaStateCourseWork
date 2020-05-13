#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"
#include<vector>
#include<stdlib.h>

int main( int argc, char *argv[] ) {
    std::cout << "Testing intersection begins.\n";
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing intersection ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();
    BinSearchTree *tree2 = new BinSearchTree();
    BinSearchTree *tree3 = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing intersection ends (fails).\n";
        return 1;
    }

    int v;
    std::vector< int > tree3v;
    while( infile >> v ) {
        if( ! tree->find( v ) ) {
            tree->insert( v );
            tree2->insert( v );
            if( random() % 3 == 0 ) {
                tree3->insert( v );
                tree3v.push_back( v );
            }
        }
    }

    int size = tree->size();

    infile.close();

    BinSearchTree *un = tree->intersectWith( tree2 );
    if( un->size() != size )
        std::cout << "Size mismatch in intersection: should have gotten " << size << " instead got " << un->size() << std::endl;
    
    infile.open( argv[1] );
    while( infile >> v ) {
        if( ! un->find( v ) )
            std::cout << "Unable to find " << v << " in the intersection tree.\n";        
    }

    BinSearchTree *un2 = tree->intersectWith( tree3 );
    std::cout << un2->size() << std::endl;
    if( un2->size() != tree3->size() )
        std::cout << "Size mismatch in intersection: should have gotten " << tree3->size() << " instead got " << un2->size() << std::endl;

    for( std::vector<int>::iterator iter = tree3v.begin(); iter != tree3v.end(); ++iter )
        if( ! un2->find( *iter ) )
            std::cout << "Unable to find " << *iter << " in the intersection tree.\n";
    
    std::cout << "Testing intersection ends.\n";

    return 0;			    
}
