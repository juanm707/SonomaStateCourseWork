/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 3 Part B
*/

#include <iostream>
#include "TreeNode.hpp"
#include "BinSearchTree.hpp"

TreeNode * BinSearchTree::local_insert( TreeNode *root, int v ) {
    if( root == nullptr )
        return new TreeNode( v );
    if( root->value() < v )
        root->rightSubtree( local_insert( root->rightSubtree(), v ) );
    else
        root->leftSubtree( local_insert( root->leftSubtree(), v ) );
    return root;
}

void BinSearchTree::insert(int v) {
    if( ! find(v) )
        root = local_insert( root, v );
}

bool BinSearchTree::local_find(TreeNode *root, int v) {
    if (root == nullptr)
        return false;

    if (root->value() == v)
        return true;

    return local_find(root->rightSubtree(), v) || local_find(root->leftSubtree(), v);
}

bool BinSearchTree::find(int v) {

    return local_find(root, v);

}

bool BinSearchTree::iterFind(int v) {
    TreeNode * copy = root;
    if (copy == nullptr)
      return false;

 while ( copy != nullptr ) {
   if(copy->value() == v) 
     return true;

   if ( v > copy->value())
     copy = copy->rightSubtree();
   else 
     copy = copy->leftSubtree();
 }
 return false;
}


int BinSearchTree::local_size(TreeNode * root) {
    if (root == nullptr)
        return 0;
    return 1 + local_size(root->leftSubtree()) + local_size(root->rightSubtree());
}

int BinSearchTree::size () {

    return local_size(root);
}

void BinSearchTree::inorderDump() {
    if (root == nullptr) {
        std::cout << "Empty..." << std::endl;
	return;
    }

    local_inorderDump(root);
}

void BinSearchTree::local_inorderDump(TreeNode * root) {
  if( root == nullptr )
    return;

  local_inorderDump(root->leftSubtree());
  std::cout << root->value() << std::endl;
  local_inorderDump(root->rightSubtree());

}

int BinSearchTree::local_maxDepth(TreeNode * root) {
      if (root == nullptr)
	return 0;

      int left = local_maxDepth(root->leftSubtree()) + 1;
      int right = local_maxDepth(root->rightSubtree()) + 1;
      if (left >= right)
	return left;
      return right;
}


int BinSearchTree::maxDepth() {
  return local_maxDepth(root);
}
    
