/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 3 Part C
*/

// Forward declaration of TreeNode class below.
// Since BinSearchTree uses TreeNode pointers rather
// than objects, we can get away with this in the .hpp.
// You should include "TreeNode.hpp" in the BinSearchTree.cpp

#include <queue>

class TreeNode;

class BinSearchTree {
public:

    //part b functions
    void insert( int v );
    bool find( int v );
    bool iterFind( int v );
    int size();
    void inorderDump();
    int maxDepth();

    //part c functions
    void levelOrderDump();
    bool remove ( int v );
    int kthSmallest (int k ); 
    void valuesAtLevel ( int k ); 
    void iterValuesAtLevel ( int k ); 
    int iterMaxDepth(); 
    bool hasRootToLeafSum ( int sum ); 
    bool areIdentical ( BinSearchTree *bst);
    BinSearchTree *intersectWith( BinSearchTree *bst ); 
    BinSearchTree *unionWith( BinSearchTree *bst ); 
    BinSearchTree *differenceOf( BinSearchTree *bst );

private:

    //part b helper functions
    TreeNode *local_insert( TreeNode *, int );
    bool local_find ( TreeNode *, int);
    int local_size ( TreeNode *);
    void local_inorderDump ( TreeNode *);
    int local_maxDepth ( TreeNode *);

    //part c helper functions
    int local_kthSmallest ( TreeNode * root, int k);
    void levelKValues ( std::queue<TreeNode *> & treeq, int k );
    bool isVLeaf(int v);
    bool hasOneChild ( int v );
    bool isLeaf (TreeNode * root, int v);
    bool onlyChild ( TreeNode * root, int v);
    int inorderSuccessor( TreeNode * root);
    bool local_remove (TreeNode * root, int v);
    bool hasLeafSum ( TreeNode * root, int sum);
    bool identical ( TreeNode * root, TreeNode * bstR);
    BinSearchTree *intersection ( BinSearchTree * interTree, TreeNode * root);
    BinSearchTree *union_ ( BinSearchTree * unionTree, TreeNode * root);
    BinSearchTree *differ ( BinSearchTree * difTree, TreeNode * root);

    TreeNode *root;
};
