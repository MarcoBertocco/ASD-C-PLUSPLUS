// Esame del 18/06/2018
// Scrivere una funzione ricorsiva in C range che dato un albero binario di ricerca, due interi k1 e k2 tali che
// k1 ≤ k2 e un vettore v, inserisce in v tutte le chiavi k ordinate in senso crescente contenute nell’albero
// tali che k1 ≤ k ≤ k2 .
// La funzione restituisce la dimensione del vettore v.
// Il prototipo della funzione è: int range(Node u, int k1, int k2, int v []) .
// Analizzare la complessità in tempo della funzione.

#include <iostream>
#include <vector>
#include "../Rappresentations/bst.hpp"
using namespace std;

int range(Tree u, int k1, int k2, vector<int> &v)
{
    if (u != nullptr)
    {
        int left = range(u->left, k1, k2, v);
        int x = 0;
        if (u->key >= k1 && u->key <= k2)
        {
            v.push_back(u->key);
            x++;
        }
        int right = range(u->right, k1, k2, v);
        return left + right + x;
    }

    return 0;
}

int main()
{
    int arr[] = {1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 7, 7, 8, 55, 55, 60};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);

    tree.tree_display();

    vector<int> vector;

    cout << range(tree.root, 2, 7, vector) << endl;

    for (auto x : vector)
    {
        cout << x << " ";
    }
    cout << endl;
}