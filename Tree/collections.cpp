#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;
#define NIL nullptr
template <class E>
struct Cell
{
    E info;
    Cell<E> *next;

    Cell() : info(), next(NIL) {}

    Cell(const E &info_) : info(info_), next(NIL) {}

    ~Cell() {}
};

template <class E>
struct Node
{
    E info;
    Node<E> *parent;
    Node<E> *left;
    Node<E> *right;

    Node() : info(), parent(NIL), left(NIL), right(NIL) {}

    Node(const E &info_, Node<E> *parent_ = NIL) : info(info_), parent(parent_), left(NIL), right(NIL) {}

    ~Node() {}
};

template <class E>
class Tree
{
private:
    Node<E> *root;

    // Helper function to find the minimum Node in a subtree
    Node<E> *findMin(Node<E> *current)
    {
        while (current && current->left != NIL)
        {
            current = current->left;
        }
        return current;
    }

    // Helper function for deletion
    Node<E> *remove_aux(Node<E> *current, E value)
    {
        if (current == NIL)
            return current;

        if (value < current->info)
        {
            current->left = remove_aux(current->left, value);
            if (current->left)
                current->left->parent = current; // Fix parent pointer
        }
        else if (value > current->info)
        {
            current->right = remove_aux(current->right, value);
            if (current->right)
                current->right->parent = current; // Fix parent pointer
        }
        else
        {
            if (current->left == NIL)
            {
                Node<E> *temp = current->right;
                if (temp)
                    temp->parent = current->parent; // Fix parent pointer
                delete current;
                return temp;
            }
            else if (current->right == NIL)
            {
                Node<E> *temp = current->left;
                if (temp)
                    temp->parent = current->parent; // Fix parent pointer
                delete current;
                return temp;
            }

            Node<E> *temp = findMin(current->right);
            current->info = temp->info;
            current->right = remove_aux(current->right, temp->info);
            if (current->right)
                current->right->parent = current; // Fix parent pointer
        }
        return current;
    }

    // Helper function for in-order traversal
    void inorder(Node<E> *current)
    {
        if (current)
        {
            inorder(current->left);
            cout << current->info << " ";
            inorder(current->right);
        }
    }

    // Helper function to display the tree structure
    void display_tree_aux(Node<E> *current, int space)
    {
        if (current == NIL)
            return;

        space += 5;
        display_tree_aux(current->right, space);

        cout << endl;
        for (int i = 5; i < space; i++)
            cout << " ";
        cout << current->info << "\n";

        display_tree_aux(current->left, space);
    }

    void destroy_tree_aux(Node<E> *current)
    {
        if (current)
        {
            if (current->left != NIL)
            {
                destroy_tree_aux(current->left);
            }
            if (current->right != NIL)
            {
                destroy_tree_aux(current->right);
            }
            delete current;
        }
    }

    Node<E> *find_node(Node<E> *current, E value)
    {
        if (current == NIL || current->info == value)
            return current;
        if (value < current->info)
            return find_node(current->left, value);
        return find_node(current->right, value);
    }

public:
    // Constructor
    Tree() : root(NIL) {}

    ~Tree()
    {
        destroy_tree_aux(root);
    }

    void insert(E value, E parentValue, bool isLeft)
    {
        // If the tree is empty, make this node the root
        if (root == NIL)
        {
            root = new Node<E>(value, NIL);
            return;
        }

        // Find the parent node
        Node<E> *parent = find_node(root, parentValue);
        if (!parent)
        {
            cout << "Parent node " << parentValue << " not found!\n";
            return;
        }

        // Check if the position is already occupied
        if (isLeft && parent->left != NIL)
        {
            cout << "Error: Parent " << parentValue << " already has a left child!\n";
            return;
        }
        if (!isLeft && parent->right != NIL)
        {
            cout << "Error: Parent " << parentValue << " already has a right child!\n";
            return;
        }

        // Create and attach the new node
        Node<E> *newNode = new Node<E>(value, parent);
        if (isLeft)
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    void remove(E value)
    {
        root = remove_aux(root, value);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }

    void displayTree()
    {
        display_tree_aux(root, 0);
    }

    Node<E> *father(E value)
    {
        Node<E> *found = find_node(root, value);
        return (found != NIL) ? found->parent : NIL;
    }

    Cell<Node<E> *> *son(E value)
    {
        Node<E> *found = find_node(root, value);
        if (!found)
            return NIL;

        Cell<Node<E> *> *l = NIL;
        if (found->left)
        {
            Cell<Node<E> *> *temp = new Cell<Node<E> *>(found->left);
            temp->next = l;
            l = temp;
        }
        if (found->right)
        {
            Cell<Node<E> *> *temp = new Cell<Node<E> *>(found->right);
            temp->next = l;
            l = temp;
        }
        return l;
    }
};

int main()
{
    Tree<int> tree;

    // Insert root node
    cout << "Inserting root: 50\n";
    tree.insert(50, -1, true); // Root node

    // Manually inserting nodes with specified parents
    cout << "Inserting 30 as left child of 50\n";
    tree.insert(30, 50, true);

    cout << "Inserting 70 as right child of 50\n";
    tree.insert(70, 50, false);

    cout << "Inserting 20 as left child of 30\n";
    tree.insert(20, 30, true);

    cout << "Inserting 40 as right child of 30\n";
    tree.insert(40, 30, false);

    cout << "Inserting 60 as left child of 70\n";
    tree.insert(60, 70, true);

    cout << "Inserting 80 as right child of 70\n";
    tree.insert(80, 70, false);

    // Display tree structure
    cout << "\nCurrent Tree Structure:\n";
    tree.displayTree();

    // Remove nodes
    cout << "\nRemoving 20 (leaf node)...\n";
    tree.remove(20);
    tree.displayTree();

    cout << "\nRemoving 30 (node with one child)...\n";
    tree.remove(30);
    tree.displayTree();

    cout << "\nRemoving 50 (node with two children)...\n";
    tree.remove(50);
    tree.displayTree();

    // Checking the parent function
    int target = 40;
    cout << "\nChecking parent of node " << target << ":\n";
    Node<int> *parent = tree.father(target);
    if (parent)
        cout << "Parent of " << target << ": " << parent->info << endl;
    else
        cout << target << " has no parent (root node or not in tree)." << endl;

    // Checking the son function
    int parentNode = 70;
    cout << "\nChildren of node " << parentNode << ":\n";
    Cell<Node<int> *> *children = tree.son(parentNode);
    if (children)
    {
        cout << "Children of " << parentNode << ": ";
        while (children)
        {
            cout << children->info->info << " ";
            children = children->next;
        }
        cout << endl;
    }
    else
    {
        cout << parentNode << " has no children." << endl;
    }

    return 0;
}
