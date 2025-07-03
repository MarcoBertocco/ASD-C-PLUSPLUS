// Scrivere una funzione efficiente in C o in C++ blackHeight(u) che dato in input la radice u di un albero
// binario, i cui nodi x hanno, oltre ai campi key, left e right, un campo col che può essere B (per “black”)
// oppure R (per “red”), verifica se per ogni nodo, il cammino da quel nodo a qualsiasi foglia contiene
// lo stesso numero di nodi neri (altezza nera del nodo x). In caso negativo, restituisce −1, altrimenti
// restituisce l’altezza nera della radice.
// Valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza.
// Scrivere il tipo del nodo dell’albero in C o in C++ a seconda del linguaggio scelto.
#include <iostream>
#define MAXINT 13295864
#define NIL nullptr
using namespace std;
enum col
{
    B,
    R
};

struct Node
{
    int key;
    Node *left;
    Node *right;
    col c;

    Node(int k, col _c = R, Node *sx = NIL, Node *dx = NIL) : key(k), c(_c), left(sx), right(dx) {}
};
typedef Node *PnodeG;

int blackH_rec(PnodeG u, int &maxh, int h)
{
    if (u != nullptr)
    {
        int l_b = blackH_rec(u->left, maxh, h + 1);
        int r_b = blackH_rec(u->right, maxh, h + 1);

        if (l_b != r_b)
        {
            maxh = MAXINT;
        }
        maxh = ((h > maxh) ? h : maxh);
        return (u->c == B) + l_b + r_b;
    }
    return 0;
}

int blackHeight(PnodeG u)
{
    int maxh = 0, h = 0;
    blackH_rec(u, maxh, h);
    if (maxh == MAXINT)
        return -1;
    return maxh;
}

void print_tree(PnodeG root, int level = 0)
{
    if (root == nullptr) // Use nullptr instead of NIL
        return;

    // Print indentation based on the tree level
    for (int i = 0; i < level; i++)
        cout << "  ";

    cout << root->key << ((root->c == B) ? "B" : "R") << endl;

    // Recursive call for left child (increase level for indentation)
    print_tree(root->left, level + 1);

    // Recursive call for right child (same level)
    print_tree(root->right, level + 1);
}

int main()
{
    PnodeG root = new Node(5, B);
    root->left = new Node(3, R);
    root->right = new Node(8, R);

    root->left->left = new Node(2, B);
    root->left->right = new Node(4, B);

    root->right->left = new Node(7, B);
    root->right->right = new Node(9, B);

    print_tree(root);

    cout << blackHeight(root) << endl;
}