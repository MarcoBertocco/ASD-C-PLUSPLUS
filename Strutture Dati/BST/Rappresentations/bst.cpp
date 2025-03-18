#include <cmath>
#include "bst.hpp"
#define NIL nullptr

Tree BST::tree_searc_aux(Tree x, int k)
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

Tree BST::tree_maximum_aux(Tree x)
{
    if (x->right != NIL)
        return tree_maximum_aux(x->right);
    return x;
}

Tree BST::tree_minimum_aux(Tree x)
{
    if (x->left != NIL)
        return tree_minimum_aux(x->left);
    return x;
}

Tree BST::tree_successor_aux(Tree x)
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

Tree BST::tree_predecessor_aux(Tree x)
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

void BST::tree_insert_aux(Tree &root, Tree z)
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

void BST::transplant_aux(Tree &r, Tree n, Tree v)
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
void BST::tree_delete_aux(Tree &r, Tree z)
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

void BST::tree_display_aux(Tree &r, int h)
{
    if (r == NIL)
        return;

    h += 5;
    tree_display_aux(r->right, h);

    std::cout << std::endl;
    for (int i = 5; i < h; i++)
        std::cout << " ";
    std::cout << r->key << "\n";

    tree_display_aux(r->left, h);
}

BST::BST() : root(NIL) {}

Tree BST::tree_search(int k)
{
    return tree_searc_aux(root, k);
}

Tree BST::tree_maximum(Tree n)
{
    if (n)
        return tree_maximum_aux(n);
    else
        return tree_maximum_aux(root);
}

Tree BST::tree_minimum(Tree n)
{
    if (n)
        return tree_minimum_aux(n);
    else
        return tree_minimum_aux(root);
}

Tree BST::tree_successor(Tree n)
{
    if (n)
        return tree_successor_aux(n);
    else
        return tree_successor_aux(root);
}

Tree BST::tree_predecessor(Tree n)
{
    if (n)
        return tree_predecessor_aux(n);
    else
        return tree_predecessor_aux(root);
}

void BST::tree_insert(int z)
{
    Tree nodo = new Node(z);
    tree_insert_aux(root, nodo);
}

void BST::transplant(Tree n, Tree v)
{
    transplant_aux(root, n, v);
}

void BST::tree_delete(Tree z)
{
    tree_delete_aux(root, z);
}

void BST::tree_display()
{
    tree_display_aux(root, 0);
}

Tree build_bst_aux(std::vector<int> A, int inf, int sup, Tree parent)
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

BST build_bst(std::vector<int> A)
{
    BST t = BST();
    t.root = build_bst_aux(A, 0, A.size() - 1, NIL);
    return t;
}