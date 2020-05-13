/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 3 Part B
*/

// Forward declaration of TreeNode class below.
// Since BinSearchTree uses TreeNode pointers rather
// than objects, we can get away with this in the .hpp.
// You should include "TreeNode.hpp" in the BinSearchTree.cpp

class TreeNode;

class BinSearchTree {
public:
    void insert( int v );
    bool find( int v );
    bool iterFind( int v );
    int size();
    void inorderDump();
    int maxDepth();

private:
    TreeNode *local_insert( TreeNode *, int );
    bool local_find ( TreeNode *, int);
    int local_size ( TreeNode *);
    void local_inorderDump ( TreeNode *);
    int local_maxDepth ( TreeNode *);
    TreeNode *root;
};
