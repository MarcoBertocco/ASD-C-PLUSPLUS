#include "../Rappresentations/bst.hpp"
using namespace std;

bool check(BST t)
{
    Tree iter, succ;
    bool ok = true;
    iter = t.root;
    if (iter == NIL)
    {
        return true;
    }
    iter = t.tree_minimum(iter);
    while (iter != NIL && ok)
    {
        succ = t.tree_successor(iter);
        if (succ != NIL && succ->key == iter->key + 2)
            ok = false;
        else
            iter = succ;
    }
    return ok;
}

int main()
{
    int arr[] = {11, 15, 18, 21, 35};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);
    tree.tree_display();

    cout << "L'albero è k+1 k+2?: " << (check(tree) ? "YES" : "NO") << endl;
}