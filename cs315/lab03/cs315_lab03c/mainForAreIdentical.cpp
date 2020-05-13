#include<iostream>
#include<fstream>
#include<vector>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {

    std::cout << "Testing areIdentical begins.\n";

    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        std::cout << "Testing areIdentical ends.\n";
        return 1;
    }

    BinSearchTree *tree = new BinSearchTree();
    BinSearchTree *tree2 = new BinSearchTree();
    std::vector<int> treeValues;


    std::fstream infile;
    infile.open( argv[1] );

    if( ! infile.is_open() ) {
        std::cout << "Unable to open input-file: " << argv[1] << std::endl;
        std::cout << "Testing areIdentical ends (fails).\n";
        return 1;
    }

    int v;
    while( infile >> v ) {
        if( ! tree->find( v ) )  {
            tree->insert( v );
            tree2->insert( v );

            treeValues.push_back(v);
        }
    }

    if( ! tree->areIdentical( tree2 ) )
        std::cout << "Wrong output for areIdentical I\n";
    int newValue = 0;
    for( int i = 200; ; i++ )
        if( ! tree2->find( i ) ) {
            tree2->insert( i );
            newValue = i;
            break;  // only one new value.
        }

    if( tree->areIdentical( tree2 ) )
        std::cout << "Wrong output for areIdentical II\n";
    if( tree->size() + 1 != tree2->size() )
        std::cout << "areIdentical has modified the structure of one of the trees.\n";

    for( unsigned int i = 0; i < treeValues.size(); i++)  {
        if( ! tree->find(treeValues[i]) || ! tree2->find(treeValues[i]) )
            std::cout << "areIdentical has modified the structure of one of the trees II.\n";
    }
    if( ! tree2->find(newValue) ) 
            std::cout << "areIdentical has modified the structure of one of the trees III.\n";    
    
    std::cout << "Testing areIdentical ends.\n";

    return 0;			    
}
