#include<iostream>
#include<fstream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"
#include<vector>
#include<stdlib.h>

int main( int argc, char *argv[] ) {
    std::cout << "Testing difference begins.\n";
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing difference ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();
    BinSearchTree *tree2 = new BinSearchTree();
    BinSearchTree *tree3 = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing difference ends (fails).\n";
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

    std::cout << "Elements in tree3v " << tree3v.size() << std::endl;

    BinSearchTree *un = tree->differenceOf( tree2 );
    if( un->size() != 0 )
        std::cout << "Size mismatch in difference: should have gotten " << 0 << " instead got " << un->size() << std::endl;

    BinSearchTree *un2 = tree3->differenceOf( tree );
    std::cout << "Elements in un2 " << un2->size() << std::endl;
    if( un2->size() != size - (int) tree3v.size() )
        std::cout << "Size mismatch in difference: should have gotten " << size - tree3v.size() << " instead got " << un2->size() << std::endl;

    for( std::vector<int>::iterator iter = tree3v.begin(); iter != tree3v.end(); ++iter )
        if( un2->find( *iter ) )
            std::cout << "Shouldn't have been able to find " << *iter << " in the difference tree.\n";
    
    std::cout << "Testing difference ends.\n";

    return 0;			    
}
