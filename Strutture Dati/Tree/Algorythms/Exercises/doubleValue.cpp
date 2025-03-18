#include <iostream>
using namespace std;
#define NIL nullptr
struct Node
{
    int key;
    Node *left_child;
    Node *right_sib;
    Node(int k, Node *sx = NIL, Node *dx = NIL) : key(k), left_child(sx), right_sib(dx) {}
};
typedef Node *Tree;

void transform_double_value(Tree u)
{
    Tree iter;
    if (u != NIL)
    {
        u->key = u->key * 2;
        transform_double_value(u->right_sib);
        iter = u->left_child;
        while (iter != NIL)
        {
            transform_double_value(iter->left_child);
            iter = iter->right_sib;
        }
    }
}

void print_tree(Tree root, int level = 0)
{
    if (root == NIL)
        return;

    // Print indentation based on the tree level
    for (int i = 0; i < level; i++)
        cout << "  ";

    cout << root->key << endl;

    // Recursive call for children
    print_tree(root->left_child, level + 1);

    // Recursive call for siblings
    print_tree(root->right_sib, level);
}

int main()
{
    // Creating the tree structure as per the left-side diagram
    Tree root = new Node(1);

    root->left_child = new Node(5);                                     // First child of root
    root->left_child->right_sib = new Node(0);                          // Child of node 1
    root->left_child->right_sib->left_child = new Node(9);              // Child of node 0
    root->left_child->right_sib->left_child->left_child = new Node(10); // Child of node 8

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    print_tree(root);
    transform_double_value(root);
    cout << "Tree Structure:" << endl;
    print_tree(root);
    return 0;
}