// Sia T un albero binario i cui nodi x hanno i campi left, right, key. L’albero si dice k − limitato, per un
// certo valore k, se per ogni nodo x la somma delle chiavi lungo ciascun cammino da x ad una foglia è
// minore o uguale a k.
// Scrivere una funzione efficiente in C k−limitato(u,k) che dato in input la radice u di un albero T e un
// valore k verifica se T è k − limitato e ritorna 1 se T è k − limitato, 0 altrimenti.
// Valutarne la complessità, indicando eventuali relazioni di ricorrenza.

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

void klimited_aux(PNodeG v, int &somma, bool &res, int k)
{
    if (v == nullptr)
    {
        somma = 0;
    }
    else
    {
        int sumr, suml;
        klimited_aux(v->left, suml, res, k);
        klimited_aux(v->right, sumr, res, k);
        if (res)
        {
            if (suml + v->key > k || sumr + v->key > k)
                res = false;
            somma = ((suml > sumr) ? suml : sumr) + v->key;
        }
    }
}

bool klimited(PNodeG r, int k)
{
    bool res = true;
    int somma;
    klimited_aux(r, somma, res, k);
    return res;
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

    print_tree(root);

    PNodeG root1 = new Node(-2);
    root1->left = new Node(2);
    root1->right = new Node(2);

    root1->left->left = new Node(1);
    root1->left->right = new Node(0);

    root1->right->right = new Node(2);

    print_tree(root1);

    cout << "Is kLimit ? " << ((klimited(root, 8)) ? "yes" : "no") << endl;
    cout << "Is kLimit ? " << ((klimited(root1, 2)) ? "yes" : "no") << endl;
}