#include "../Rappresentations/bst.hpp"
using namespace std;
void remove_branch(Tree n)
{
    if (n != NIL)
    {
        remove_branch(n->left);
        remove_branch(n->right);
        delete n;
    }
}

void remove_greater_k(BST t, int k)
{
    Tree iter, temp;
    iter = t.root;
    while (iter->key != k)
    {
        if (iter->key > k)
        {
            t.tree_delete(iter->right);
            iter->right = NIL;
            temp = iter;

            t.transplant(iter, iter->left);
            iter = iter->left;
            delete (temp);
        }
        else
            iter = iter->right;
    }
    remove_branch(iter->right);
    iter->right = NIL;
}
int main()
{
    int arr[] = {1, 2, 2, 7, 7, 8, 55, 55, 60};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);

    remove_greater_k(tree, 55);
    tree.tree_display();
}