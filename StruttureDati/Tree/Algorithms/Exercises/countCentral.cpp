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
        int tot_f = left + right + (n->left == NIL && n->right == NIL);
        if (tot_f == sum + n->key)
        {
            cout << tot_f << " " << sum + n->key << " " << n->key << endl;
            central_nodes++;
        }
        return tot_f;
    }
    return 0;
}

int count_central(Tree r)
{
    int central_nodes = 0;
    count_central_aux(r, 0, central_nodes);
    return central_nodes;
}

int node_central_aux(Tree u, int &cc, int sum)
{
    if (u != NIL)
    {
        int tot = sum + u->key;
        int left = node_central_aux(u->left, cc, tot);
        int right = node_central_aux(u->right, cc, tot);

        int leaves = (!u->left && !u->right) + left + right;

        if (leaves == tot)
            cc++;
        return leaves;
    }
    return 0;
}

int node_central(Tree r)
{
    int central_nodes = 0;
    node_central_aux(r, central_nodes, 0);
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
    int result1 = node_central(root);
    cout << "Number of Central Nodes: " << result1 << endl;
    return 0;
}