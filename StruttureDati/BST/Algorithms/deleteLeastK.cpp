#include "../Rappresentations/bst.hpp"
using namespace std;

void deleteMinorKey(BST t, Tree x, int key)
{
    if (x != NIL)
    {
        if (x->key <= key)
        {
            deleteMinorKey(t, x->left, key);
            
            if (x->key < key)
            {
                deleteMinorKey(t, x->right, key);
                cout<<"x.key: "<<x->key<<" key: "<<key<<endl;
                t.tree_delete(x);
            }
        }
    }
}

int main()
{
    int arr[] = {1, 2, 3, 5, 6, 15, 16};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);
    tree.tree_display();
    cout << "MinorKey" << endl;
    deleteMinorKey(tree, tree.root, 15);
    tree.tree_display();
}