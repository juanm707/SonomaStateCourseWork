/*
  Author: Juan Martinez
  Course: CS 315
  Assignment: Lab 3 Part C
*/

#include <iostream>
#include <queue>
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

    while ( copy != nullptr) {
        if (copy->value() == v)
            return true;
        if ( v > copy->value())
            copy = copy->rightSubtree();
        else if (v < copy->value())
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
    local_inorderDump(root);
}

void BinSearchTree::local_inorderDump(TreeNode * root) {

    if (root == nullptr) {
        return;
    }
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

//PART C FUNCTIONS
void BinSearchTree::levelOrderDump() {

    if (root == nullptr)
        return;

    std::queue<TreeNode *> treeq;
    treeq.push(root);

    while (!treeq.empty()) {

        TreeNode * temp = treeq.front();
        treeq.pop();
        std::cout << temp->value() << std::endl;
        if (temp->leftSubtree() != nullptr)
            treeq.push(temp->leftSubtree());
        if (temp->rightSubtree() != nullptr)
            treeq.push(temp->rightSubtree());
    }
}

// Helpers for remove

bool BinSearchTree::isLeaf(TreeNode *root, int v) {

    if (root == nullptr)
        return false;

    if (!find(v))
        return false;

    if (root->value() == v && root->leftSubtree() == nullptr && root->rightSubtree() == nullptr)
        return true;

    return isLeaf(root->leftSubtree(),v) || isLeaf(root->rightSubtree(),v);

}

bool BinSearchTree::isVLeaf(int v) {

    return isLeaf(root,v);
}

bool BinSearchTree::onlyChild ( TreeNode * root, int v) {

    if (root == nullptr)
        return false;
    if (!find(v))
        return false;
    if (root->value() == v && (root->leftSubtree() == nullptr || root->rightSubtree() == nullptr))
        return true;
    return onlyChild(root->leftSubtree(),v) || onlyChild(root->rightSubtree(), v);
}

bool BinSearchTree::hasOneChild ( int v ) {

    return onlyChild(root, v);
}

int BinSearchTree::inorderSuccessor (TreeNode * root) {

    TreeNode * successor = root->rightSubtree();
    while (successor->leftSubtree() != nullptr) {
        successor = successor->leftSubtree();
    }
    return successor->value();
}

bool BinSearchTree::local_remove (TreeNode * root, int v) {

    if (root == nullptr)
        return false;

    if (!find(v))
        return false;

    if (isVLeaf(v)) { // if value to be removed has no children

        TreeNode *copy = root;

        while (copy != nullptr) {

            if (copy->leftSubtree() != nullptr && copy->leftSubtree()->value() == v) {
                delete copy->leftSubtree();
                copy->leftSubtree(nullptr);
                return true;
            } else if (copy->rightSubtree() != nullptr && copy->rightSubtree()->value() == v) {
                delete copy->rightSubtree();
                copy->rightSubtree(nullptr);
                return true;
            }
            if (v >= copy->value())
                copy = copy->rightSubtree();
            else if (v < copy->value())
                copy = copy->leftSubtree();
        }
        return false;
    }

    if (hasOneChild(v)) { //if value to be removed has one child

        TreeNode *parent = root;
        TreeNode *child = root;

        while (child != nullptr) {

            if (child->value() == v) {
                if (v < parent->value()) {
                    if (child->leftSubtree() != nullptr) {
                        parent->leftSubtree(child->leftSubtree());
                        delete child;
                        child = nullptr;
                        return true;
                    } else {
                        parent->leftSubtree(child->rightSubtree());
                        delete child;
                        child = nullptr;
                        return true;
                    }
                }
                else if (v > parent->value()) {
                    if (child->leftSubtree() != nullptr) {
                        parent->rightSubtree(child->leftSubtree());
                        delete child;
                        child = nullptr;
                        return true;
                    } else {
                        parent->rightSubtree(child->rightSubtree());
                        delete child;
                        child = nullptr;
                        return true;
                    }
                }
                else {
                    if (child->leftSubtree() != nullptr) {
                        root = child->leftSubtree();
                        delete child;
                        child = nullptr;
                        return true;
                    } else {
                        root = child->rightSubtree();
                        delete child;
                        child = nullptr;
                        return true;
                    }
                }
            }

            if (v > child->value()) {
                parent = child;
                child = parent->rightSubtree();
            } else if (v < child->value()) {
                parent = child;
                child = child->leftSubtree();
            }
        }
        return false;
    }

    else { //has 2 children

        TreeNode * copy = root;

        while ( copy != nullptr) {
            if (copy->value() == v) {
                int replace = inorderSuccessor(copy);
                local_remove(copy,replace);
                copy->value() = replace;
                return true;
            }
            if ( v > copy->value())
                copy = copy->rightSubtree();
            else if (v < copy->value())
                copy = copy->leftSubtree();
        }
        return false;
    }

}

bool BinSearchTree::remove ( int v ) {

  if (root == nullptr)
    return false;

    if (root->value() == v) {

        if (isVLeaf(v)) {
            root = nullptr;
            return true;
        }
        if (hasOneChild(v)) {
            if (root->leftSubtree() != nullptr) {
                root = root->leftSubtree();
                return true;
            }
            else {
                root = root->rightSubtree();
                return true;
            }
        }
    }

    return local_remove(root,v);
}

int BinSearchTree::local_kthSmallest ( TreeNode * root, int k) {

    int leftS = local_size(root->leftSubtree());   //doesnt count root
    if (k < leftS + 1)
        return local_kthSmallest(root->leftSubtree(), k);
    else if (k > leftS + 1)
        return local_kthSmallest(root->rightSubtree(), k - (leftS + 1));
    return root->value();
}

int BinSearchTree::kthSmallest (int k ) {
    if (size() >= k && k > 0) {
        return local_kthSmallest(root,k);
    }
    return 0;
}

void BinSearchTree::levelKValues ( std::queue<TreeNode *> & treeq, int k ) {

    if (k == 1) {
        unsigned long tqSize = treeq.size();
        for (int i = 0; unsigned(i) < tqSize; i++) {
            TreeNode *temp = treeq.front();
            std::cout << temp->value() << std::endl;
            treeq.pop();
        }
        return;
    }
    unsigned long tqSize = treeq.size();
    for (int i = 0; unsigned(i) < tqSize; i++) {
        TreeNode *temp = treeq.front();
        treeq.pop();
        if (temp->leftSubtree() != nullptr)
            treeq.push(temp->leftSubtree());
        if (temp->rightSubtree() != nullptr)
            treeq.push(temp->rightSubtree());
    }
    levelKValues(treeq, k - 1);
}

void BinSearchTree::valuesAtLevel ( int k ) {
    if (root == nullptr || k <= 0  || k > maxDepth())
        return;
    std::queue< TreeNode * > treeq;
    treeq.push(root);
    levelKValues(treeq,k);
}

void BinSearchTree::iterValuesAtLevel ( int k ) {

    if (root == nullptr)
        return;
    if (k <= 0 || k > maxDepth())
        return;

    int count = 1;

    std::queue<TreeNode *> treeq;
    treeq.push(root);

    while (!treeq.empty() && count != k) {

        unsigned long tqSize = treeq.size();

        for (int i = 0; unsigned(i) < tqSize; i++) {
            TreeNode * temp = treeq.front();
            treeq.pop();
            if (temp->leftSubtree() != nullptr)
                treeq.push(temp->leftSubtree());
            if (temp->rightSubtree() != nullptr)
                treeq.push(temp->rightSubtree());
        }
        count++;
    }
    unsigned long tqSize = treeq.size();
    for (int i = 0; unsigned(i) < tqSize; i++) {
        TreeNode * temp = treeq.front();
        std::cout << temp->value() << std::endl;
        treeq.pop();
    }
}

int BinSearchTree::iterMaxDepth() {

    if (root == nullptr)
        return 0;

    int count = 1;

    std::queue<TreeNode *> treeq;
    treeq.push(root);

    while (!treeq.empty()) {
        count++;
        for (int i = 0; unsigned(i) < treeq.size(); i++) {
            TreeNode *temp = treeq.front();
            treeq.pop();

            if (temp->leftSubtree() != nullptr)
                treeq.push(temp->leftSubtree());
            if (temp->rightSubtree() != nullptr)
                treeq.push(temp->rightSubtree());
        }
    }
    return count;
}

bool BinSearchTree::hasLeafSum ( TreeNode * root, int sum) {
    if (root == nullptr)
        return false;
    if (sum == root->value() && root->leftSubtree() == nullptr && root->rightSubtree() == nullptr)
        return true;
    if (sum != root->value() && root->leftSubtree() == nullptr && root->rightSubtree() == nullptr)
        return false;
    return hasLeafSum(root->leftSubtree(), sum - root->value()) || hasLeafSum(root->rightSubtree(), sum - root->value());
}

bool BinSearchTree::hasRootToLeafSum ( int sum ) {

    return hasLeafSum(root,sum);

}
bool BinSearchTree::identical ( TreeNode * root, TreeNode * bstR ) {

    if (root == nullptr && bstR == nullptr)
        return true;
    if (root != nullptr && bstR != nullptr)
        return identical(root->leftSubtree(), bstR->leftSubtree()) && identical(root->rightSubtree(), bstR->rightSubtree());
    return false;
}
bool BinSearchTree::areIdentical ( BinSearchTree *bst ) {
    return identical(root, bst->root);
}

BinSearchTree * BinSearchTree::intersection (BinSearchTree * interTree, TreeNode * root) { // look at this in debug

    if (root == nullptr)
        return interTree;

    if (find(root->value()))
        interTree->insert(root->value());

    intersection(interTree,root->leftSubtree());
    intersection(interTree,root->rightSubtree());
    return interTree;
}

BinSearchTree * BinSearchTree::intersectWith( BinSearchTree *bst ) {

    BinSearchTree * inter = new BinSearchTree();
    return intersection(inter, bst->root);
}

BinSearchTree * BinSearchTree::union_ ( BinSearchTree * unionTree, TreeNode * root) {

    if (root == nullptr)
        return unionTree;
    unionTree->insert(root->value());
    union_(unionTree,root->leftSubtree());
    union_(unionTree,root->rightSubtree());
    return unionTree;
}
BinSearchTree * BinSearchTree::unionWith( BinSearchTree *bst ) {

    BinSearchTree * unionTree = new BinSearchTree();
    union_(unionTree, root);
    union_(unionTree, bst->root);
    return unionTree;
}

BinSearchTree * BinSearchTree::differ ( BinSearchTree * difTree, TreeNode * root) {

    if (root == nullptr)
        return difTree;
    if (!find(root->value())) {
        difTree->insert(root->value());
        differ(difTree,root->leftSubtree());
        differ(difTree,root->rightSubtree());
        return difTree;
    }
    differ(difTree,root->leftSubtree());
    differ(difTree,root->rightSubtree());
    return difTree;
}

BinSearchTree * BinSearchTree::differenceOf( BinSearchTree *bst ) {
//The difference of two sets,
// written A - B is the set of all elements of A
// that are not elements of B
// What is returned is T(bst) - T(callee),

    BinSearchTree * difTree = new BinSearchTree();
    return differ(difTree, bst->root);
}

