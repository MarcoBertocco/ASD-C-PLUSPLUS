#include "../Rappresentations/bst.hpp"
using namespace std;

Tree modify_key(BST t, Tree &x, int key)
{
    int succ = t.tree_successor()->key;   // O(h)
    int pred = t.tree_predecessor()->key; // O(h)
    x->key = key;                         // O(1)
    if (pred < key && key < succ)         // O(1)
    {
        return t.root; // O(1)
    }
    return NIL; // O(1)
}

int main()
{
    int arr[] = {1, 2, 3, 5, 6, 15, 16};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);

    cout << "é ancora BST? " << ((modify_key(tree, tree.root, 4)) ? "YES" : "NO") << endl;
    tree.tree_display();
}