#include <iostream>
#include <iomanip>
using namespace std;
#define NIL nullptr
struct Node
{
    int key;
    bool fruitful;
    Node *left;
    Node *center;
    Node *right;
    Node(int k, Node *sx = NIL, Node *cx = NIL, Node *dx = NIL) : key(k), fruitful(false), left(sx), center(cx), right(dx) {}
};
typedef Node *PTNode;

int set_fruitful_aux(PTNode n, int k)
{
    if (n)
    {
        int left_s = set_fruitful_aux(n->left, k);
        int center_s = set_fruitful_aux(n->center, k);
        int right_s = set_fruitful_aux(n->right, k);

        if (left_s + center_s + right_s > k)
        {
            n->fruitful = true;
        }

        return left_s + center_s + right_s + n->key;
    }
    return 0;
}

void set_fruitful(PTNode r, int k)
{
    set_fruitful_aux(r, k);
}

void prettyPrintTree(PTNode root, int indent = 0)
{
    if (root)
    {
        if (root->right)
        {
            prettyPrintTree(root->right, indent + 4);
        }

        if (indent)
        {
            cout << setw(indent) << ' ';
        }

        cout << root->key << (root->fruitful ? "*" : "") << "\n";

        if (root->center)
        {
            prettyPrintTree(root->center, indent + 4);
        }

        if (root->left)
        {
            prettyPrintTree(root->left, indent + 4);
        }
    }
}

int main()
{
    PTNode root = new Node(1);
    root->left = new Node(2);
    root->center = new Node(3);
    root->right = new Node(4);

    root->left->left = new Node(5);
    root->left->center = new Node(6);
    root->left->right = new Node(7);

    root->center->center = new Node(8);

    root->right->left = new Node(9);
    root->right->right = new Node(10);

    root->left->left->left = new Node(11);
    root->center->center->center = new Node(12);

    root->right->right->center = new Node(13);
    root->right->right->right = new Node(14);

    cout << "Original Tree:\n";
    prettyPrintTree(root);

    int k = 12;
    set_fruitful(root, k);

    cout << "\nTree after setting fruitful nodes (k = " << k << "):\n";
    prettyPrintTree(root);

    return 0;
}