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

// Breadth First Search
void breadth_first_search(Tree root)
{
    if (!root)
        return;
    list<Tree> queue;
    queue.push_front(root); // enqueue root
    while (!queue.empty())
    {
        Tree n = queue.front(); // extract node n from QUEUE
        queue.pop_back();       // dequeue n

        if (n != NIL)
        {
            visit(n); // visit node n

            queue.push_front(n->left); // enqueue LEFT & RIGHT child
            queue.push_front(n->right);
        }
    }
}