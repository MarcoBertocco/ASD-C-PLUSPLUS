#include <iostream>
#include <string>
#include <stack>
#include "visitTree.hpp"
using namespace std;
#define NIL nullptr

// Deep First Search
void depth_first_search(Tree root)
{
    if (!root)
        return;
    stack<Tree> stack;
    stack.push(root);
    while (!stack.empty())
    {
        Tree n = stack.top(); // extract node n from STACK
        stack.pop();          // n = pop (S)

        if (n != NIL)
        {
            visit(n); // visit node n

            stack.push(n->right); // Push LEFT & RIGHT child
            stack.push(n->left);
        }
    }
}

// Deep First Search RECURSIVE
void depth_first_search_rec(Tree n)
{
    if (n != NIL)
    {
        visit(n);

        depth_first_search_rec(n->left);
        depth_first_search_rec(n->right);
    }
}

// Deep First Search RECURSIVE PREORDER
void depth_first_search_rec_preorder(Tree r)
{
    if (r != NIL)
    {
        visit(r);

        depth_first_search_rec_preorder(r->left);
        depth_first_search_rec_preorder(r->right);
    }
}

// Deep First Search RECURSIVE SIMMETRIC
void depth_first_search_rec_simmetric(Tree r)
{
    if (r != NIL)
    {
        depth_first_search_rec_simmetric(r->left);

        visit(r);

        depth_first_search_rec_simmetric(r->right);
    }
}

// Deep First Search RECURSIVE POSTORDER
void depth_first_search_rec_postorder(Tree r)
{
    if (r != NIL)
    {
        depth_first_search_rec_postorder(r->left);
        depth_first_search_rec_postorder(r->right);

        visit(r);
    }
}