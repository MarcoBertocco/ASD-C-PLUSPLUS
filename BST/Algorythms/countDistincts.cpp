#include "Rappresentations/bst.hpp"

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