// Sia T un albero binario i cui nodi x hanno i campi left, right, key. L’albero si dice k − limitato, per un
// certo valore k, se per ogni nodo x la somma delle chiavi lungo ciascun cammino da x ad una foglia è
// minore o uguale a k.
// Scrivere una funzione efficiente in C k−limitato(u,k) che dato in input la radice u di un albero T e un
// valore k verifica se T è k − limitato e ritorna 1 se T è k − limitato, 0 altrimenti.
//  Valutarne la complessità, indicando eventuali relazioni di ricorrenza.

#include <iostream>
using namespace std;

struct Node
{
    Node *left;
    Node *right;
    int key;

    Node(int _k, Node *_l = nullptr, Node *_r = nullptr) : key(_k), left(_l), right(_r) {}
};
typedef Node *PNodeG;

int kLimitTree_rec(PNodeG u, int k, int &res)
{
    if (u != nullptr && res != -1)
    {
        int left = kLimitTree_rec(u->left, k, res);
        int right = kLimitTree_rec(u->right, k, res);

        if (left > k || right > k)
        {
            res = -1;
        }
        return left + right + u->key;
    }
    return 0;
}

bool kLimitTree(PNodeG root, int k)
{
    int res = 1;
    kLimitTree_rec(root, k, res);
    return (res == 1);
}

void print_tree(PNodeG root, int level = 0)
{
    if (root == nullptr) // Use nullptr instead of NIL
        return;

    // Print indentation based on the tree level
    for (int i = 0; i < level; i++)
        cout << "  ";

    cout << root->key << endl;

    // Recursive call for left child (increase level for indentation)
    print_tree(root->left, level + 1);

    // Recursive call for right child (same level)
    print_tree(root->right, level + 1);
}

int main()
{
    PNodeG root = new Node(3);
    root->left = new Node(3);
    root->right = new Node(2);

    root->left->left = new Node(1);
    root->left->right = new Node(2);

    root->right->left = new Node(2);
    root->right->right = new Node(1);

    root->right->right->right = new Node(20);

    print_tree(root);

    cout << kLimitTree(root, 22) << endl;
}