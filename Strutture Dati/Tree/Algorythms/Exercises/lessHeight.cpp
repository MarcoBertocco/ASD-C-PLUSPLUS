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
typedef Node *Tree;

int less_height_aux(Tree n, int h)
{
    if (n != NIL)
    {
        int count_dx, count_sx;
        count_sx = less_height_aux(n->left, h + 1);
        count_dx = less_height_aux(n->right, h + 1);

        return ((n->key <= h) ? 1 : 0) + count_dx + count_sx;
    }
    return 0;
}

int less_height(Tree r)
{
    int h = 0;
    return less_height_aux(r, h);
}

void print_tree(Tree root, int level = 0)
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
    Tree root = new Node(3);
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