// Esame del 12/09/2022
// Sia T un albero generale i cui nodi hanno campi: key, left-child, right-sib.
// Scrivere una funzione efficiente in C o C++ che calcoli il numero di foglie di T e analizzarne la complessità.
// Specificare quale linguaggio è stato utilizzato.

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

int leafCount_rec(PNodeG u)
{
    if (u != nullptr)
    {
        int left = leafCount_rec(u->left_child);
        int right = leafCount_rec(u->right_sib);
        return (u->left_child == nullptr) + left + right;
    }
    return 0;
}

int leafCount(PNodeG root)
{
    return leafCount_rec(root);
}

void leafCount1_rec(PNodeG u, int &count)
{
    if (u != nullptr)
    {
        leafCount1_rec(u->left_child, count);
        if (u->left_child == nullptr)
            count++;
        leafCount1_rec(u->right_sib, count);
    }
}

int leafCount1(PNodeG r)
{
    int count = 0;
    leafCount1_rec(r, count);
    return count;
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
    // Giorgia Tree
    PNodeG root = new Node(6);
    root->left_child = new Node(3);
    root->left_child->left_child = new Node(2);
    root->left_child->left_child->right_sib = new Node(1);
    root->left_child->right_sib = new Node(4);
    root->left_child->right_sib->right_sib = new Node(5);
    root->left_child->right_sib->right_sib->left_child = new Node(1);

    // Mine
    PNodeG root1 = new Node(10);
    root1->left_child = new Node(3);
    root1->left_child->left_child = new Node(1);
    root1->left_child->left_child->right_sib = new Node(6);
    root1->left_child->right_sib = new Node(5);
    root1->left_child->right_sib->left_child = new Node(2);
    root1->left_child->right_sib->right_sib = new Node(7);
    root1->left_child->right_sib->right_sib->left_child = new Node(2);
    root1->left_child->right_sib->right_sib->left_child->right_sib = new Node(1);

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    print_tree(root);

    cout << "Numero foglie: \n"
         << leafCount(root) << endl;

    cout << "Numero foglie: \n"
         << leafCount1(root) << endl;

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    print_tree(root1);

    cout << "Numero foglie: \n"
         << leafCount(root1) << endl;

    cout << "Numero foglie: \n"
         << leafCount1(root1) << endl;
    return 0;
}