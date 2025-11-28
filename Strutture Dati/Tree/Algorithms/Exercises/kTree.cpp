#include <iostream>
using namespace std;

// Esame del 05/09/2017
// Sia T un albero generale i cui nodi hanno campi: key, left − child e right − sib.
// Progettare un algoritmo efficiente che dato T e un intero k ≥ 2 stabilisca se T è un albero k − ario completo,
// e analizzarne la complessità.
// Deve essere fornita una funzione C e si deve dichiarare il tipo Node utilizzato per rappresentare l’albero generale.

struct Node
{
    Node *left_child;
    Node *right_sib;
    int key;

    Node(int _k, Node *_lc = nullptr, Node *_rs = nullptr) : key(_k), left_child(_lc), right_sib(_rs) {}
    ~Node();
};
typedef Node *PNodeG;

int kArio_rec(PNodeG n, int k, int &res)
{
    if (n != nullptr)
    {
        int rS = kArio_rec(n->right_sib, k, res);
        int lC = kArio_rec(n->left_child, k, res);
        rS++;
        cout << rS <<" "<< lC << endl;
        if (n->left_child != nullptr)
        {
            if (lC != k)
            {
                res = -1;
            }
        }
        return rS;
    }
    return 0;
}

bool kArio(PNodeG root, int k)
{
    int res = 1;
    kArio_rec(root, k, res);
    return (res == 1) ? true : false;
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
    int k = 3;

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

    cout << "isKario k = 3? " << ((kArio(root, 3)) ? "Yes" : "No") << endl;

    // Print the tree structure
    cout << "Tree Structure:" << endl;
    print_tree(root1);

    cout << "isKario k = 3? " << ((kArio(root1, 3)) ? "Yes" : "No") << endl;

    return 0;
}