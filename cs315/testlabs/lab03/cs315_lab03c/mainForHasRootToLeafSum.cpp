#include<iostream>
#include<fstream>
#include<vector>

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

    std::fstream infile;
    infile.open( argv[1] );
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

    int values[] = {13109008, 9172813, 14102902, 11145790, 13119734, 13120156, 11147134, 15125392, 17101206, 16116167, 13154198, 11177215, 14146197, 15135825, 16130941, 17121388, 14152885, 12178006, 13169753, 18133532, 17146514, 15170940, 14178295, 15172808};

    for( int i = 0; i < 24; i++ ) {
        if( ! tree->hasRootToLeafSum(values[i]) ) {
            std::cout << "hasRootToLeafSum failed for " << values[i] << std::endl;
        }
        
    }
    
    std::cout << "Testing hasRootToLeafSum ends.\n";

    return 0;			    
}
