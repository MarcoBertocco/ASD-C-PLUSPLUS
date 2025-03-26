#include <iostream>
using namespace std;
#define NIL nullptr
struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int k, Node *sx = NIL, Node *dx = NIL) : key(k), left(sx), right(dx) {}
};
typedef Node *PNode;

int less_height_aux(PNode n, int &count)
{ // RADU IS THE BEST
    if (n != NIL)
    {
        int h_sx = less_height_aux(n->left, count), h_dx = less_height_aux(n->right, count);
        int h = max(h_dx, h_sx);

        if (n->key <= h)
            count++;
        return h + 1;
    }
    return 0;
}

int less_height(PNode r)
{
    int count = 0;
    less_height_aux(r, count);
    return count;
}

void print_tree(PNode root, int level = 0)
{
    if (root == nullptr) // Use nullptr instead of NIL
        return;

    // Print indentation based on the tree level
    for (int i = 0; i < level; i++)
        std::cout << "  ";

    std::cout << root->key << std::endl;

    // Recursive call for left child (increase level for indentation)
    print_tree(root->left, level + 1);

    // Recursive call for right child (same level)
    print_tree(root->right, level + 1);
}

int main()
{
    PNode root = new Node(3);
    root->left = new Node(2);
    root->right = new Node(4);
    root->left->left = new Node(1);
    root->right->left = new Node(9);
    root->right->right = new Node(2);
    root->left->left->left = new Node(3);
    root->left->left->right = new Node(2);
    root->right->right->right = new Node(1);
    root->right->right->right->right = new Node(0);

    print_tree(root);

    cout << "Less Height Counter = " << less_height(root) << endl;
}