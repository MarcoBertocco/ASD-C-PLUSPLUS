#include "../Rappresentations/bst.hpp"
using namespace std;

int count_distincts(BST t)
{
    Tree iter;
    int num_dist = 0, count = 1, val;

    if (t.root == NIL)
        return 0;
    iter = t.tree_minimum();
    val = iter->key;

    iter = t.tree_successor(iter);

    while (iter != NIL)
    {
        if (iter == NIL)
            break;

        if (iter->key == val)
            count++;
        else
        {
            if (count == 1)
                num_dist++;
            count = 1;
            val = iter->key;
        }
        iter = t.tree_successor(iter);
    }

    if (count == 1)
    {
        num_dist++;
    }
    return num_dist;
}

int main()
{
    int arr[] = {1, 2, 2, 7, 7, 8, 55, 55, 60};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);
    cout << "Numero distinti: " << count_distincts(tree) << endl;
}