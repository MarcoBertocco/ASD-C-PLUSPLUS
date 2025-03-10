#include <iostream>
using namespace std;

// Define the color of a node
enum Color { WHITE, BLACK };

// Structure for a binary tree node
struct Node {
    Color color;
    Node *left;
    Node *right;

    Node(Color c) : color(c), left(nullptr), right(nullptr) {}
};

// Helper function to count nodes with equal white and black descendants
pair<int, int> countDescendants(Node *node, int &count) {
    if (!node) {
        return {0, 0}; // Base case: no node, so no descendants
    }

    // Recursively compute the number of white and black descendants for the left and right subtrees
    auto left = countDescendants(node->left, count);
    auto right = countDescendants(node->right, count);

    // Total white descendants = white descendants from left + white descendants from right + (if current node is white)
    int whiteDescendants = left.first + right.first + (node->color == WHITE ? 1 : 0);

    // Total black descendants = black descendants from left + black descendants from right + (if current node is black)
    int blackDescendants = left.second + right.second + (node->color == BLACK ? 1 : 0);

    // If white descendants == black descendants, increment the count
    if (whiteDescendants == blackDescendants) {
        count++;
    }

    // Return the total white and black descendants for the current node
    return {whiteDescendants, blackDescendants};
}

// Main function to count nodes with equal white and black descendants
int countNodesWithEqualDescendants(Node *root) {
    int count = 0;
    countDescendants(root, count);
    return count;
}

int main() {
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