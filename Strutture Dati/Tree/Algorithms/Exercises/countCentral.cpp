#include <iostream>
using namespace std;
#define NIL nullptr
/*
Un nodo di un albero binario è detto centrale se il numero di foglie del sottoalbero di cui è radice è pari
alla somma delle chiavi dei nodi appartementi al percorso dalla radice al nodo stesso.
a. Scrivere una funzione efficiente in C che restituisca il numero di nodi centrali.
b. Discutere la complessità della soluzione trovata.
c. Se vogliamo modificare la funzione in modo che restituisca l’insieme dei nodi centrali che tipo
di struttura dati si può utilizzare per rappresentare l’insieme?
 */

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node *parent;
    Node(int k, Node *p, Node *sx = NIL, Node *dx = NIL) : key(k), parent(p), left(sx), right(dx) {}
};
typedef Node *Tree;

int count_central_aux(Tree n, int sum, int &central_nodes)
{
    if (n != NIL)
    {
        int left = count_central_aux(n->left, sum + n->key, central_nodes);
        int right = count_central_aux(n->right, sum + n->key, central_nodes);
        int tot_f = left + right;
        if (tot_f == sum + n->key)
        {
            cout << left + right << " " << sum << " " << n->key << endl;
            central_nodes++;
        }
        return tot_f + (n->left == NIL && n->right == NIL);
    }
    return 0;
}

int count_central(Tree r)
{
    int central_nodes = 0;
    count_central_aux(r, 0, central_nodes);
    return central_nodes;
}

int main()
{
    // Example tree construction
    Tree root = new Node(0, NIL);
    root->left = new Node(2, root);
    root->right = new Node(3, root);
    root->left->left = new Node(1, root->left);
    root->left->right = new Node(-1, root->left);

    // Count nodes with equal white and black descendants
    int result = count_central(root);
    cout << "Number of Central Nodes: " << result << endl;

    return 0;
}