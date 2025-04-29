#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include "RedBlackTree.h"

/*   Sources I used: 

https://www2.cs.sfu.ca/CourseCentral/307/abulatov/lectures/13.pdf

Zybook 7.12

Zybook 8.12 to 8.15

https://www.geeksforgeeks.org/postorder-traversal-of-binary-tree/

For source three, which is the geeksforgeeks one, I mainly used just this algorithm:

If root is NULL then return
Recursively traverse the left subtree.
Recursively traverse the right subtree.
Process the root node (e.g., print its value).

*/

using namespace std;

RedBlackTree::RedBlackTree() : root(nullptr), numItems(0){   // empty constructor
}

RedBlackTree::RedBlackTree(int newData) : numItems(1){   // constructor with one node
    root=new RBTNode;
    root->data=newData;
    root->color=COLOR_BLACK;
}

RedBlackTree::RedBlackTree(const RedBlackTree& rbt){
    root=CopyOf(rbt.root);   //  copy root and numItems
    numItems=rbt.numItems;
}

RedBlackTree::~RedBlackTree(){  // destructor
    del(root);
}

void RedBlackTree::del(RBTNode* node){
    if (node!=nullptr){
        del(node->left);  // recur across left subtrees
        del(node->right);   // recur across right subtrees
        delete node;   // deallocate each node
    }
}

void RedBlackTree::Insert(int newData){
    RBTNode *node=new RBTNode;  // create new RBTNode and assign value
    node->data=newData;
    BasicInsert(node);   //  //follow the binary search tree to add the node as the leaf node
    if(node->parent!=nullptr && node->parent->color==COLOR_RED){
        InsertFixUp(node);  
    }
    numItems++;  // number of nodes increases by 1
}

void RedBlackTree::BasicInsert(RBTNode *NewNode){
    RBTNode *y=nullptr;
    RBTNode *x=root;
    while (x!=nullptr){
        y=x;
        if (NewNode->data<x->data){  // if our node's value is lesser, go to left child until you reach a leaf
            x=x->left;
        }
        else{
            x=x->right;   // if our node's value is more, go to right child until you reach a leaf
        }
    }
    NewNode->parent=y;
    if (y==nullptr){
        root=NewNode;     // if no parent, our node is the root
    }
    else if (NewNode->data<y->data){     // if our node's value is lesser, our new node is the left child leaf
        y->left=NewNode;
    }
    else{   // if our node's value is more, our new node is the right child leaf
        y->right=NewNode;
    }
    NewNode->left=nullptr;            
    NewNode->right=nullptr;
    NewNode->color=COLOR_RED;
    root->color=COLOR_BLACK;   // making sure that the root STAYS BLACK
}

void RedBlackTree::InsertFixUp(RBTNode *node){
    //Find uncle, parent and grand parent of the node
    RBTNode *parent = node->parent;
    RBTNode *uncle = GetUncle(node);
    RBTNode *grand_parent = parent->parent;
    if (uncle==nullptr||uncle->color == COLOR_BLACK){ 
        // Case 2, uncle is BLACK. nullptr also counts as black
        // This happens in every case
        if (grand_parent!=nullptr){  // make grandparent red for now
            grand_parent->color=COLOR_RED;
        }
        if (IsLeftChild(node) && IsLeftChild(parent)){ 
            // Left Left
            // single right rotation
            RightRotate(grand_parent);  // do right rotation on grandparent and make parent's color black
            parent->color = COLOR_BLACK;
        } 
        else if (IsRightChild(node) && IsRightChild(parent)){
            // Right Right
            // single left rotation
            LeftRotate(grand_parent);  // do left rotation on grandparent and make parent's color black
            parent->color = COLOR_BLACK;
        } 
        else if (IsLeftChild(node) && IsRightChild(parent)){ 
            // Left Right
            // right left rotation
            RightRotate(parent);  // do right rotation on parent and left rotation on parent
            LeftRotate(grand_parent);
            node->color = COLOR_BLACK;  //  make current node black
            parent->color = COLOR_RED;   //  make parent's color red 
        } 
        else if (IsRightChild(node) && IsLeftChild(parent)){ 
            // Right Left
            // left right rotation
            LeftRotate(parent);
            RightRotate(grand_parent);
            node->color = COLOR_BLACK;  //  make current node black
            parent->color = COLOR_RED;   //  make parent's color red 
        } 
        else { 
            //output error message and throw an exception
            throw invalid_argument("Impossible state");
        }
    } 
    else if (uncle != nullptr && uncle->color == COLOR_RED){  
        // Case 6, uncle is RED
        // could use recoloring
        parent->color = COLOR_BLACK;  // make parent and uncle black
        uncle->color=COLOR_BLACK;
        if (grand_parent!=nullptr){
            if (grand_parent!=root){   
                grand_parent->color=COLOR_RED;   // make grandparent red
                if (grand_parent->parent!=nullptr){     // 
                    if (grand_parent->parent->color==COLOR_RED){
                        InsertFixUp(grand_parent);  //  recur up the tree
                    }
                }
            }
        }
    }
    root->color=COLOR_BLACK;  // making sure that the root STAYS BLACK
}
 
void RedBlackTree::LeftRotate(RBTNode *x){
    RBTNode *y=x->right; // y is x's right child
    x->right=y->left;  //x's right child is y's left child
    if (y->left!=nullptr){  
        y->left->parent=x;   //  update parent of left subtree of y to x
    }
    if (x->parent==nullptr){  // if x was a root, update root to y
        root=y;    
    }
    else if(x==x->parent->left){ //  if there was a left subtree
        x->parent->left=y;  //   update it as y
    }
    else{
        x->parent->right=y;   //  if there was a right subtree, update it as y 
    }
    y->left=x;   //  finish rotation, x become's y's left child, making y its parent
    x->parent=y;
}

void RedBlackTree::RightRotate(RBTNode *x){
    RBTNode *y=x->left;  // y is x's left child
    x->left=y->right;   //x's left child is y's right child
    if (y->right != nullptr){
        y->right->parent=x;   //  update parent of right subtree of y to x
    }
    if (x->parent==nullptr){  // if x was a root, update root to y
        root=y;
    }
    else if(x==x->parent->right){  //  if there was a right subtree
        x->parent->right=y;   //   update it as y
    }
    else{
        x->parent->left=y;  //  if there was a left subtree, update it as y 
    }
    y->right=x;   //  finish rotation, x become's y's right child, making y its parent
    x->parent=y;
}


bool RedBlackTree::Contains(int data) const {
    return (Get(data)!=nullptr);  // if we didn't get a node equal to our value, it doesn't exist
}

RBTNode *RedBlackTree::Get(int data) const{
    RBTNode* x=root;  // start at root
    while (x!=nullptr){
        if (data==x->data){   // if data matches our node's value, return node
            return x;
        } 
        else if (data<x->data){  // if data is less than our node's value, go to left child
            x=x->left;
        } 
        else{
            x=x->right;   // if data is more than our node's value, go to right child
        }
    }
    return nullptr;  // otherwise node doesn't exist
}

RBTNode* RedBlackTree::GetUncle(RBTNode *node){
    if (node->parent==nullptr||node->parent->parent==nullptr){ // if no parent or grandparent
        return nullptr; // there's no uncle 
    }
    RBTNode *parent=node->parent;  
    RBTNode *grand_parent=parent->parent;
    if (parent==grand_parent->left){  // if parent is left child, uncle is right child and vice versa
        return grand_parent->right;
    }
    else {
        return grand_parent->left;
    }
}


int RedBlackTree::GetMin() const{
    if (root==nullptr){  // no node, no minimum
        throw invalid_argument("No minimum exists");
    }
    RBTNode* x=root;
    while (x->left!=nullptr){  // keep going down left to get minimum
        x=x->left;
    }
    return x->data;  // return lowest value
}

int RedBlackTree::GetMax() const{
    if (root==nullptr){  // no node, no maximum
        throw invalid_argument("No maximum exists");
    }
    RBTNode* x=root;
    while (x->right!=nullptr){  // keep going down right to get maximum
        x=x->right;
    }
    return x->data;  // return highest value
}

bool RedBlackTree::IsLeftChild(RBTNode *node) const{
    return (node->parent!=nullptr && node==node->parent->left);  // parent and parent's left child has to exist
}

bool RedBlackTree::IsRightChild(RBTNode *node) const{
    return (node->parent!=nullptr && node==node->parent->right);   // parent and parent's right child has to exist
}

/*Recursively traverse the left subtree.
Process the root node
Recursively traverse the right subtree.
*/

string RedBlackTree::ToInfixString(const RBTNode *n) {
    if (n==nullptr){
        return "";
    }
    return ToInfixString(n->left)+GetNodeString(n)+ToInfixString(n->right);  
}

/*
Process the root node
Recursively traverse the left subtree.
Recursively traverse the right subtree.
*/

string RedBlackTree::ToPrefixString(const RBTNode *n) {
    if (n==nullptr){
        return "";
    }
    return GetNodeString(n)+ToPrefixString(n->left)+ToPrefixString(n->right);  
}

/*Recursively traverse the left subtree.
Recursively traverse the right subtree.
Process the root node*/


string RedBlackTree::ToPostfixString(const RBTNode *n) {
    if (n==nullptr){
        return "";
    }
    return ToPostfixString(n->left)+ToPostfixString(n->right)+GetNodeString(n);  
}

string RedBlackTree::GetNodeString(const RBTNode *n) {
    if (n==nullptr){
        return "";
    }
    else{
        return " "+GetColorString(n)+to_string(n->data)+" ";
    }
}

string RedBlackTree::GetColorString(const RBTNode *n){
    if (n==nullptr){
        return "";
    }
    if (n->color==COLOR_RED){
        return "R";
    }
    if (n->color==COLOR_BLACK){
        return "B";
    }
}

RBTNode *RedBlackTree::CopyOf(const RBTNode *node) {
    if (node==nullptr){  // copying nothing
        return nullptr;
    }
    RBTNode* n = new RBTNode();
    n->data=node->data;
    n->color=node->color;
    n->left=CopyOf(node->left);  // recursive call to copy each left node
    if (n->left!=nullptr){    // and if it exists, add it to the copy tree
        n->left->parent=n;
    }
    n->right=CopyOf(node->right);
    if (n->right!=nullptr){  // recursive call to copy each right node
        n->right->parent=n;   // and if it exists, add it to the copy tree
    }
    return n;
}

