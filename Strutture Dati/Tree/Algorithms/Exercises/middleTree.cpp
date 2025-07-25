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
        int leftSub = 0, rightSibs = 0;
        if (u->right_sib != nullptr || u->left_child != nullptr)
        {
            leftSub = intermedi_rec(u->left_child, somma + u->key, nMedi);
            rightSibs = intermedi_rec(u->right_sib, somma, nMedi);
        }
        cout << "(" << u->key << ") SUM: " << somma << " L: " << leftSub << " Rs: " << rightSibs << endl;
        if (leftSub + u->key == somma)
            nMedi++;
        return u->key + rightSibs + leftSub;
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

    cout << "Numero nodi intermedi: \n"
         << intermedi(root) << endl;

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    print_tree(root1);

    cout << "Numero nodi intermedi: \n"
         << intermedi(root1) << endl;
    return 0;
}