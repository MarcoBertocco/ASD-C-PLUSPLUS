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
void inOrderTraversal(Tree root){
    if(root!=NIL){
        inOrderTraversal(root->left);
        cout << root->key <<" ";
        inOrderTraversal(root->right);
       
    }
}
Tree insertNode(Tree root, int key, Node *parent = NIL)
{
    if (root == NIL)
        return new Node(key, parent);

    if (key < root->key)
        root->left = insertNode(root->left, key, root);
    else
        root->right = insertNode(root->right, key, root);

    return root;
}
int main()
{
    Tree root = NIL;
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 70);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 60);
    insertNode(root, 80);

    cout << "In-Order Traversal: ";
    inOrderTraversal(root);
    cout << endl;

    return 0;
}