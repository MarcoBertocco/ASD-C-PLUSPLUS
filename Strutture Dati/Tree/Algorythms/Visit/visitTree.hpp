#ifndef VISITTREE_H
#define VISITTREE_H

#include <string>

struct Node
{
    std::string info;
    Node *left;
    Node *right;
    Node(std::string i) : info(i), left(nullptr), right(nullptr) {}
};

typedef Node *Tree;

void visit(Tree node);
void generic_visit(Tree root);
void breadth_first_search(Tree root);
void depth_first_search(Tree root);
void depth_first_search_rec(Tree n);
void depth_first_search_rec_preorder(Tree n);
void depth_first_search_rec_simmetric(Tree n);
void depth_first_search_rec_postorder(Tree n);
#endif