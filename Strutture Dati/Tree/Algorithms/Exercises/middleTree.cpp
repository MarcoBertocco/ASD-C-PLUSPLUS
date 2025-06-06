#include <iostream>
using namespace std;

struct Node
{
    Node *left_child;
    Node *right_sib;
    int key;
    Node(int k, Node *sx = nullptr, Node *dx = nullptr) : key(k), left_child(sx), right_sib(dx) {}
};
typedef Node *PNodeG;

int intermedi_rec(PNodeG u, int somma, int &nMedi)
{
    if (u != nullptr)
    {
        int x = 0, y = 0;
        if (u->right_sib != nullptr || u->left_child != nullptr)
        {
            x = intermedi_rec(u->left_child, somma + u->key, nMedi);
            y = intermedi_rec(u->right_sib, somma + u->key, nMedi);
        }
        cout << "(" << u->key << ") SUM: " << somma << " L: " << x << " Rs: " << y << endl;
        if (x == somma)
            nMedi++;
        return x + y + u->key;
    }
    return 0;
}

int intermedi(PNodeG u)
{
    int nMedi = 0;
    intermedi_rec(u, 0, nMedi);
    return nMedi;
}

void print_tree(PNodeG root, int level = 0)
{
    if (root == nullptr)
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
    PNodeG root = new Node(2);
    root->left_child = new Node(3);
    root->left_child->left_child = new Node(1);
    root->left_child->left_child->right_sib = new Node(1);
    root->left_child->right_sib = new Node(5);
    root->left_child->right_sib->left_child = new Node(2);
    root->left_child->right_sib->right_sib = new Node(7);
    root->left_child->right_sib->right_sib->left_child = new Node(6);
    root->left_child->right_sib->right_sib->left_child->right_sib = new Node(4);

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    print_tree(root);

    cout << "Numero nodi intermedi: " << intermedi(root) << endl;
    return 0;
}