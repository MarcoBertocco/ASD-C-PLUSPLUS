// Sia T un albero binario di ricerca. Si vogliono stampare le chiavi di T memorizzate in nodi il cui
// sottoalbero radicato nel figlio sinistro contiene un numero pari di chiavi e il sottoalbero radicato nel figlio
// destro contiene un numero dispari di chiavi.
// a. Si rappresenti un albero binario di ricerca la cui visita in pre-order ha come risultato 10, 5, 1, 20, 15, 25.
// Si mostri quali chiavi verrebbero stampate in base alla condizione sopra descritta.
// b. Scrivere una procedura in C efficiente, di nome stampaNodi(u), che data la radice di un albero
// binario di ricerca, stampa le chiavi dei nodi che soddisfano la condizione specificata. Valutarne la
// complessità, indicando eventuali relazioni di ricorrenza.

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

int stampaNodi_rec(Tree u)
{
    if (u != NIL)
    {
        int left = stampaNodi_rec(u->left);
        int right = stampaNodi_rec(u->right);
        if (left % 2 == 0 && right % 2 == 1)
            cout << u->key << " ";
        return 1 + left + right;
    }
    return 0;
}

void stampaNodi(Tree u)
{
    stampaNodi_rec(u);
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
    // Example tree construction

    Tree root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(20);

    root->left->left = new Node(1);
    root->right->left = new Node(15);
    root->right->right = new Node(25);

    print_tree(root);

    cout << "StampaNodi ";
    stampaNodi(root);
    cout << endl;

    return 0;
}