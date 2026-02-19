#include <iostream>
#include <string>
#include <list>
#include "visitTree.hpp"

using namespace std;
#define NIL nullptr

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
        if (n != NIL)
        {
            visit(n); // visit node n
            
            stack.push_front(n->right);
            stack.push_front(n->left); // S = S U {n.sons}
            
        }
    }
}