/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 3 Part C
*/

#include <iostream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

int main( int argc, char *argv[] ) {
    // create a tree and then print the values of its nodes
    // from the smallest to the largest.

    BinSearchTree *tree = new BinSearchTree();
    BinSearchTree *other = new BinSearchTree();

    int v;
    while( std::cin >> v ) {
        tree->insert( v );
    }

    other->insert(40);
    other->insert(30);
    other->insert(60);
    other->insert(25);
    other->insert(35);
    other->insert(52);
    other->insert(65);
    other->insert(43);
    other->insert(55);
    other->insert(41);
    other->insert(45);
    other->insert(57);
    other->insert(56);
    other->insert(58);

    std::cout << "There are " << tree->size() << " values in tree\n";
    std::cout << "There are " << other->size() << " values in other tree\n";

    /*if (tree->find(3))
        std::cout << "Recursion find\n";

    if (tree->iterFind(3))
        std::cout << "Iterative find\n";*/

    //std::cout << "Leaf nodes of tree are:\n";
    //tree->leafNodes();

    std::cout << "Values in tree in-order travesal:\n";
    tree->inorderDump();
    std::cout << "Values in other tree in-order travesal:\n";
    other->inorderDump();

    std::cout << "Depth of tree is " << tree->maxDepth() << std::endl;
    std::cout << "Depth of other tree is " << other->iterMaxDepth() << std::endl;

    BinSearchTree * differTree = tree->differenceOf(other);
    std::cout << "There are " << differTree->size() << " values in differTree\n";
    std::cout << "Values in differTree in-order traversal:\n";
    differTree->inorderDump();

    if (tree->hasRootToLeafSum(322))
        std::cout << "TRUE! 322 sum found\n";
    else
        std::cout << "322 sum not found\n";
    if (tree->areIdentical(other))
        std::cout << "Structurally identical\n";
    else
        std::cout << "Structurally different\n";

    //std::cout << "Removing 10\n";
    //differTree->remove(10);
    //std::cout << "Now has:\n";
    //differTree->inorderDump();

    std::cout << "Values in tree level-order travesal:\n";
    tree->levelOrderDump();

    std::cout << "Values in level 3 other tree: " << std::endl;
    other->iterValuesAtLevel(3);
    std::cout << '\n';
    std::cout << "Values in level 3 other tree using recursion: " << std::endl;
    other->valuesAtLevel(3);
    std::cout << '\n';

    for (int i = 0; i < other->size() + 1; i++) {
        std::cout << "The " << i+1 << " smallest value in other is: " << other->kthSmallest(i+1) << std::endl;
    }
    /*

    std::cout << "Is 4 a leaf?\n";
    if (tree->isVLeaf(4))
        std::cout << "Yes 4 is leaf\n";
    else
        std::cout << "4 is not leaf\n";

    std::cout << "Does 2 have one child?\n";
    if (tree->hasOneChild(2))
        std::cout << "Yeah 2 has one child\n";
    else
        std::cout << "No 2 has no child or two children\n";*/

    std::cout << "\nremoving 58 from tree ...\n";
    if (tree->remove(58))
        std::cout << "deleted!\n";
    else
        std::cout << "Not deleted\n";
    std::cout << "Values in tree level order travesal\n";
    for (int i = 0; i < tree->maxDepth(); i++) {
        std::cout << "Values in level " << i + 1 << " in tree: ";
        tree->iterValuesAtLevel(i+1);
        std::cout << std::endl;
    }

    return 0;
}
