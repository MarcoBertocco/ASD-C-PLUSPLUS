#include <iostream>
#include <list>
#include <vector>
#include <cmath>
using namespace std;
#define NIL nullptr

struct Node
{
    int key;
    Node *parent;
    Node *left;
    Node *right;

    Node() : key(), parent(NIL), left(NIL), right(NIL) {}

    Node(int key_, Node *parent_ = NIL) : key(key_), parent(parent_), left(NIL), right(NIL) {}

    ~Node() {}
};
typedef Node *Tree;

class BST
{
private:
    Tree tree_searc_aux(Tree x, int k)
    {
        if (x == NIL || x->key == k)
        {
            return x;
        }
        else
        {
            if (x->key > k)
                return tree_searc_aux(x->left, k);
            else //<=
                return tree_searc_aux(x->right, k);
        }
    }

    Tree tree_maximum_aux(Tree x)
    {
        if (x != NIL)
            return tree_maximum_aux(x->right);
        return x;
    }

    Tree tree_minimum_aux(Tree x)
    {
        if (x != NIL)
            return tree_minimum_aux(x->left);
        return x;
    }

    Tree tree_successor_aux(Tree x)
    {
        if (x->right != NIL)
            return tree_minimum(x->right);

        else
        {
            Tree y = x->parent;
            while (y != NIL && x == y->right)
            {
                x = y;
                y = y->parent;
            }
            return y;
        }
    }

    Tree tree_predecessor_aux(Tree x)
    {
        if (x->left != NIL)
            return tree_minimum(x->left);

        else
        {
            Tree y = x->parent;
            while (y != NIL && x == y->left)
            {
                x = y;
                y = y->parent;
            }
            return y;
        }
    }

    void tree_insert_aux(Tree root, Tree z)
    {
        Tree y = NIL;
        Tree x = root;

        while (x != NIL)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == NIL)
            root = z;
        else
        {
            if (z->key < y->key)
                y->left = z;
            else
                y->right = z;
        }
    }

    void transplant_aux(Tree &r, Tree n, Tree v)
    {
        if (n->parent == NIL)
        {
            r = v;
        }
        else
        {
            if (n == n->parent->left)
                n->parent->left = v;
            else
                n->parent->right = v;
        }

        if (v != NIL)
        {
            v->parent = n->parent;
        }
    }
    void tree_delete_aux(Tree &r, Tree z)
    {
        if (z->left == NIL)
            transplant(z, z->right);
        else
        {
            if (z->right == NIL)
                transplant(z, z->left);
            else
            {
                Tree y = tree_minimum(z->right);
                if (y->parent != z)
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    z->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
            }
        }
    }

public:
    Tree root;
    BST() : root(NIL) {}

    Tree tree_search(int k)
    {
        return tree_searc_aux(root, k);
    }

    Tree tree_maximum(Tree n = NIL)
    {
        if (n)
            return tree_maximum_aux(n);
        else
            return tree_maximum_aux(root);
    }

    Tree tree_minimum(Tree n = NIL)
    {
        if (n)
            return tree_minimum_aux(n);
        else
            return tree_minimum_aux(root);
    }

    Tree tree_successor(Tree n = NIL)
    {
        if (n)
            return tree_successor_aux(n);
        else
            return tree_successor_aux(root);
    }

    Tree tree_predecessor(Tree n = NIL)
    {
        if (n)
            return tree_predecessor_aux(n);
        else
            return tree_predecessor_aux(root);
    }

    void tree_insert(int z)
    {
        Tree nodo = new Node(z);
        tree_insert_aux(root, nodo);
    }

    void transplant(Tree n, Tree v)
    {
        transplant_aux(root, n, v);
    }

    void tree_delete(Tree z)
    {
        tree_delete_aux(root, z);
    }
};

Tree build_bst_aux(vector<int> A, int inf, int sup, Tree parent)
{
    if (inf > sup)
        return NIL;
    else
    {
        int med = floor((inf + sup) / 2);
        Tree n = new Node(A[med]);
        n->parent = parent;
        n->left = build_bst_aux(A, inf, med - 1, n);
        n->right = build_bst_aux(A, med + 1, sup, n);
        return n;
    }
}

BST build_bst(vector<int> A)
{
    BST t = BST();
    t.root = build_bst_aux(A, 1, A.size(), NIL);
    return t;
}

int main()
{
    int arr[] = {1, 3, 5, 7, 9}; // Array di interi
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    BST albero = build_bst(vettore);

    // visita(albero.root);

    Tree n1 = albero.tree_search(5);

    Tree succ = albero.tree_successor(n1);

    cout << "Il successore del nodo con Key = " << n1->key << " e': " << succ->key << endl;

    Tree prec = albero.tree_predecessor(n1);

    cout << "Il predecessore del nodo con Key = " << n1->key << " e': " << prec->key << endl;

    Tree max = albero.tree_maximum(n1);

    cout << "Il valore massimo dell'albero e': " << max->key << endl;

    Tree min = albero.tree_maximum(n1);

    cout << "Il valore minimo dell'albero e': " << min->key << endl;

    return 0;
}