#include <iostream>
using namespace std;

enum Color
{
    WHITE,
    BLACK
};

struct Node
{
    Color color;
    Node *left;
    Node *right;

    Node(Color c) : color(c), left(nullptr), right(nullptr) {}
};

pair<int, int> countDescendants(Node *node, int &count)
{
    if (!node)
    {
        return {0, 0};
    }

    auto left = countDescendants(node->left, count);
    auto right = countDescendants(node->right, count);

    int whiteDescendants = left.first + right.first + (node->color == WHITE ? 1 : 0);
    int blackDescendants = left.second + right.second + (node->color == BLACK ? 1 : 0);

    if (whiteDescendants == blackDescendants)
    {
        count++;
    }
    return {whiteDescendants, blackDescendants};
}

int countNodesWithEqualDescendants(Node *root)
{
    int count = 0;
    pair<int, int> colorsCounts = countDescendants(root, count);
    cout << colorsCounts.first << " " << colorsCounts.second << endl;
    return count;
}

int main()
{
    // Example tree construction
    Node *root = new Node(WHITE);
    root->left = new Node(BLACK);
    root->right = new Node(WHITE);
    root->left->left = new Node(WHITE);
    root->left->right = new Node(BLACK);
    root->right->left = new Node(BLACK);
    root->right->right = new Node(WHITE);

    // Count nodes with equal white and black descendants
    int result = countNodesWithEqualDescendants(root);
    cout << "Number of nodes with equal white and black descendants: " << result << endl;

    return 0;
}