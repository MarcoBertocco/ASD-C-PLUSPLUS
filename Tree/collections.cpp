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
    // Helper function for inserting a Node
    Node<E> *insert_aux(Node<E> *current, E value, Node<E> *parent)
    {
        if (current == nullptr)
        {
            return new Node<E>(value, parent);
        }

        if (value < current->info)
        {
            current->left = insert_aux(current->left, value, current);
        }
        else
        {
            current->right = insert_aux(current->right, value, current);
        }
        return current;
    }

    // Helper function to find the minimum Node in a subtree
    Node<E> *findMin(Node<E> *current)
    {
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    // Helper function for deletion
    Node<E> *remove_aux(Node<E> *current, E value)
    {
        if (current == nullptr)
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
            if (current->left == nullptr)
            {
                Node<E> *temp = current->right;
                if (temp)
                    temp->parent = current->parent; // Fix parent pointer
                delete current;
                return temp;
            }
            else if (current->right == nullptr)
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
        if (current == nullptr)
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
        if (current == nullptr || current->info == value)
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

    void insert(E value)
    {
        root = insert_aux(root, value, nullptr);
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
        return (found != nullptr) ? found->parent : nullptr;
    }

    Cell<Node<E> *> *son(E value)
    {
        Node<E> *found = find_node(root, value);
        if (!found)
            return nullptr;

        Cell<Node<E> *> *l = nullptr;
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

    // Insert elements
    cout << "Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Display elements (In-order Traversal)
    cout << "In-order Traversal: ";
    tree.display();

    // Display tree structure
    cout << "\nTree Structure:\n";
    tree.displayTree();

    // Remove a Node (leaf, Node with one child, and Node with two children)
    cout << "\nRemoving 20 (leaf Node)...\n";
    tree.remove(20);
    tree.display();
    tree.displayTree();

    cout << "\nRemoving 30 (Node with one child)...\n";
    tree.remove(30);
    tree.display();
    tree.displayTree();

    cout << "\nRemoving 50 (Node with two children)...\n";
    tree.remove(50);
    tree.display();
    tree.displayTree();

    // Checking the father function
    cout << "\nChecking parent of node 40:\n";
    Node<int> *parent40 = tree.father(40);
    if (parent40)
        cout << "Parent of 40: " << parent40->info << endl;
    else
        cout << "40 has no parent (root node or not in tree)." << endl;

    // Checking the son function
    cout << "\nChildren of node 70:\n";
    Cell<Node<int> *> *children = tree.son(70);
    if (children)
    {
        cout << "Children of 70: ";
        while (children)
        {
            cout << children->info->info << " ";
            children = children->next;
        }
        cout << endl;
    }
    else
    {
        cout << "70 has no children." << endl;
    }
    return 0;
}