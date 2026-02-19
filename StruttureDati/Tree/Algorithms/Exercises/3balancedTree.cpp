#include <iostream>
using namespace std;
#define NIL nullptr
struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int k, Node *sx = NIL, Node *dx = NIL) : key(k), left(sx), right(dx) {}
};
typedef Node *Tree;

void three_balanced_aux(Tree n, int &min, int &max)
{
    int min_sx, max_sx, min_dx, max_dx;
    if (n == NIL)
    {
        min = -1;
        max = -1;
    }
    else
    {
        three_balanced_aux(n->left, min_sx, max_sx);
        three_balanced_aux(n->right, min_dx, max_dx);

        min = ((min_sx <= min_dx) ? min_sx : min_dx) + 1;
        max = ((max_sx > max_dx) ? max_sx : max_dx) + 1;
    }
}

bool three_balanced(Tree r)
{
    int min, max;
    three_balanced_aux(r, min, max);
    return (max - min <= 3);
}

int main()
{
    // Example tree construction
    Tree root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->left->right = new Node(5);

    // Count nodes with equal white and black descendants
    int result = three_balanced(root);
    cout << "Is the Tree Three Balanced: " << ((result) ? "Yes" : "No") << endl;

    return 0;
}