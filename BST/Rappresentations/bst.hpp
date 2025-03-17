#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <vector>

#define NIL nullptr

struct Node
{
    int key;
    Node *parent;
    Node *left;
    Node *right;

    Node() : key(), parent(NIL), left(NIL), right(NIL) {}

    Node(int key_, Node *parent_ = NIL) : key(key_), parent(parent_), left(NIL), right(NIL) {}

    ~Node() {}
};

typedef Node *Tree;

class BST
{
private:
    Tree tree_searc_aux(Tree x, int k);
    Tree tree_maximum_aux(Tree x);
    Tree tree_minimum_aux(Tree x);
    Tree tree_successor_aux(Tree x);
    Tree tree_predecessor_aux(Tree x);
    void tree_insert_aux(Tree root, Tree z);
    void transplant_aux(Tree &r, Tree n, Tree v);
    void tree_delete_aux(Tree &r, Tree z);

public:
    Tree root;
    BST();
    Tree tree_search(int k);
    Tree tree_maximum(Tree n = NIL);
    Tree tree_minimum(Tree n = NIL);
    Tree tree_successor(Tree n = NIL);
    Tree tree_predecessor(Tree n = NIL);
    void tree_insert(int z);
    void transplant(Tree n, Tree v);
    void tree_delete(Tree z);
};

Tree build_bst_aux(std::vector<int> A, int inf, int sup, Tree parent);
BST build_bst(std::vector<int> A);

#endif // BST_HPP
