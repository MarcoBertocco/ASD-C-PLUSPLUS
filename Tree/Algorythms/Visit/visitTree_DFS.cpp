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

// Deep First Search
void deep_first_search(Tree root)
{
    if (!root)
        return;
    list<Tree> stack;
    stack.push_front(root);
    while (!stack.empty())
    {
        Tree n = stack.front(); // extract node n from STACK
        stack.pop_front();      // n = pop (S)

        if (n != NIL)
        {
            visit(n); // visit node n

            stack.push_front(n->left); // Push LEFT & RIGHT child
            stack.push_front(n->right);
        }
    }
}

// Deep First Search RECURSIVE
void deep_first_search_rec(Tree n)
{
    if (n != NIL)
    {
        visit(n);

        deep_first_search_rec(n->left);
        deep_first_search_rec(n->right);
    }
}

// Deep First Search RECURSIVE PREORDER
void deep_first_search_rec_preorder(Tree r)
{
    if (r != nullptr)
    {
        visit(r);

        deep_first_search_rec_preorder(r->left);
        deep_first_search_rec_preorder(r->right);
    }
}

// Deep First Search RECURSIVE SIMMETRIC
void deep_first_search_rec_simmetric(Tree r)
{
    if (r != nullptr)
    {
        deep_first_search_rec_simmetric(r->left);

        visit(r);

        deep_first_search_rec_simmetric(r->right);
    }
}

// Deep First Search RECURSIVE POSTORDER
void deep_first_search_rec_postorder(Tree r)
{
    if (r != nullptr)
    {
        deep_first_search_rec_postorder(r->left);
        deep_first_search_rec_postorder(r->right);

        visit(r);
    }
}