#include <iostream>
#include <string>
#include <queue>
#include "visitTree.hpp"
using namespace std;
#define NIL nullptr

// Breadth First Search
void breadth_first_search(Tree root)
{
    if (!root)
        return;
    queue<Tree> queue;
    queue.push(root); // enqueue root
    while (!queue.empty())
    {
        Tree n = queue.front(); // extract node n from QUEUE
        queue.pop();            // dequeue n

        if (n != NIL)
        {
            visit(n);            // visit node n
            queue.push(n->left); // enqueue LEFT & RIGHT child
            queue.push(n->right);
        }
    }
}