#include <iostream>
using namespace std;
#define NIL nullptr
struct Node
{
    int key;
    Node *left;
    Node *right;
    Node *parent;
    Node(int k, Node *p, Node *sx = NIL, Node *dx = NIL) : key(k), parent(p), left(sx), right(dx) {}
};
typedef Node *Tree;

int count_central(Tree r)
{
    int num_leaves;
    return count_central_aux(r, 0, num_leaves);
}

int count_central_aux(Tree n, int sum, int &num_l)
{
    int central_nodes, left_nodes, left_leaves_num, right_nodes, right_leaves_num;

    if (n == NIL)
    {
        num_l = 0;
        return 0;
    }

    // leaf case cause i have dto count leaves
    if (n->left == NIL && n->right == NIL)
    {
        num_l = 1;
        central_nodes = 0;
    }
    else
    {
        left_nodes = count_central_aux(n->left, sum + n->key, left_leaves_num);
        right_nodes = count_central_aux(n->right, sum + n->key, right_leaves_num);

        num_l = left_leaves_num + right_leaves_num;
        central_nodes = left_nodes + right_nodes;
    }

    if (num_l == sum + n->key)
    {
        return central_nodes + 1;
    }
    return central_nodes;
}