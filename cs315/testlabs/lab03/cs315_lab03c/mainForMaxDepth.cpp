#include<iostream>
#include<fstream>
#include <vector>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing maxDepth begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing maxDepth ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();

    std::fstream infile( argv[1] );
    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing maxDepth ends (fails).\n";
        return 1;
    }

    int v;
    std::vector<int> treeValues;    
    while( infile >> v ) {
      if( ! tree->find( v ) ) 
            tree->insert( v );
            treeValues.push_back(v);
    }

    infile.close();

    std::cout << "Max depth = " << tree->maxDepth() << std::endl;

    for( unsigned int i = 0; i < treeValues.size(); i++)  {
        if( ! tree->find(treeValues[i]) )
            std::cout << "maxDepth has modified the structure of one of the trees.\n";
    }
    
    
    std::cout << "Testing maxDepth ends.\n";

    return 0;			    
}
