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

int count_central(Tree r)
{
    int num_leaves;
    return count_central_aux(r, 0, num_leaves);
}

int main()
{
    // Example tree construction
    Tree root = new Node(0, NIL);
    root->left = new Node(2, root);
    root->right = new Node(3, root);
    root->left->left = new Node(1, root->left);
    root->left->right = new Node(-1, root->left);

    // Count nodes with equal white and black descendants
    int result = count_central(root);
    cout << "Number of Central Nodes: " << result << endl;

    return 0;
}