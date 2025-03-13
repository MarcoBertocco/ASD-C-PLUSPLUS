#include <iostream>
#include <string>
#include <list>
using namespace std;
#define NIL nullptr

// Structure for a binary tree node
struct Node
{
    string info;
    Node *left;
    Node *right;

    Node(string i) : info(i), left(nullptr), right(nullptr) {}
};
typedef Node *Tree;

// VISIT NODE
void visit(Tree node)
{
    std::cout << node->info << " ";
}

// Visit a Tree Generic
void generic_visit(Tree root)
{
    if (!root)
        return;
    list<Tree> stack;
    stack.push_front(root);
    while (!stack.empty())
    {
        Tree n = stack.front(); // extract node n from STACK
        stack.pop_front();

        visit(n); // visit node n

        stack.push_front(n->left); // S = S U {n.sons}
        stack.push_front(n->right);
    }
}

void generic_visit(Tree root)
{
    if (!root)
        return;
    list<Tree> stack;
    stack.push_front(root);
    while (!stack.empty())
    {
        Tree n = stack.front(); // extract node n from
        stack.pop_front();

        visit(n); // visit node n

        stack.push_front(n->left); // S = S U {n.sons}
        stack.push_front(n->right);
    }
}