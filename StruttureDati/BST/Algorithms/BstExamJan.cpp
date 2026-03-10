#include <iostream>
#include <math.h>
#include "../Rappresentations/bst.hpp"
using namespace std;

int distance(int x, int y)
{
    return abs(x - y);
}

void distanceK_aux(Tree x, bool &res, int d, int k)
{
    if (x != NIL)
    {
        int dL = k, dR = k;
        if (x->left)
            dL = distance(x->key, x->left->key);
        if (x->right)
            dR = distance(x->key, x->right->key);
        if (res)
        {
            if (x->left)
                if (dL < k || distance(dL, d) < k)
                    res = false;
            if (x->right)
                if (dR < k || distance(dR, d) < k)
                    res = false;
        }
        distanceK_aux(x->left, res, dL, k);
        distanceK_aux(x->right, res, dR, k);
    }
}

bool distanceK(BST t, int k)
{
    bool res = true;
    int d = 0;
    distanceK_aux(t.root, res, d, k);
    return res;
}

int main()
{
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    BST tree = build_bst_C(vettore);

    tree.tree_display();
    cout << "Distance K ? " << ((distanceK(tree, 10)) ? "YES" : "NO") << endl;
}