#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <list>
using namespace std;
#define NIL nullptr

template <class E>
struct Node
{
    E info;
    Node<E> *parent;
    Node<E> *left_child;
    Node<E> *right_sib;

    Node() : info(), parent(NIL), left_child(NIL), right_sib(NIL) {}

    Node(const E &info_, Node<E> *parent_ = NIL) : info(info_), parent(parent_), left_child(NIL), right_sib(NIL) {}

    ~Node() {}
};

template <class E>
class Tree
{
private:
    Node<E> *root;

    Node<E> *find(Node<E> *v, const E &info)
    {
        if (v == nullptr)
            return nullptr;
        if (v->info == info)
            return v;

        // Traverse the left child and its right siblings
        Node<E> *child = v->left_child;
        while (child != nullptr)
        {
            Node<E> *res = find(child, info);
            if (res != nullptr)
                return res;
            child = child->right_sib;
        }
        return nullptr;
    }

    Node<E> *remove_aux(Node<E> *current, const E &value)
    {
        if (current == nullptr)
            return nullptr;

        // Use the find function to locate the node to be deleted
        Node<E> *nodeToDelete = find(current, value);

        if (nodeToDelete == nullptr)
            return current; // Node not found, return the current tree

        // Get the parent of the node to delete
        Node<E> *parent = nodeToDelete->parent;

        // Promote the children of the node to delete
        Node<E> *child = nodeToDelete->left_child;
        if (child != nullptr)
        {
            // Attach the children to the parent
            if (parent == nullptr)
            {
                // If the node to delete is the root, make the first child the new root
                current = child;
                current->parent = nullptr;
            }
            else
            {
                // Attach the children to the parent's children list
                child->parent = parent;
                if (parent->left_child == nodeToDelete)
                {
                    parent->left_child = child;
                }
                else
                {
                    Node<E> *prevSibling = parent->left_child;
                    while (prevSibling->right_sib != nodeToDelete)
                        prevSibling = prevSibling->right_sib;
                    prevSibling->right_sib = child;
                }
            }

            // Attach the remaining siblings of the node to delete to the last child
            Node<E> *lastChild = child;
            while (lastChild->right_sib != nullptr)
                lastChild = lastChild->right_sib;
            lastChild->right_sib = nodeToDelete->right_sib;
        }
        else
        {
            // If the node to delete has no children, just remove it from the parent's children list
            if (parent != nullptr)
            {
                if (parent->left_child == nodeToDelete)
                {
                    parent->left_child = nodeToDelete->right_sib;
                }
                else
                {
                    Node<E> *prevSibling = parent->left_child;
                    while (prevSibling->right_sib != nodeToDelete)
                        prevSibling = prevSibling->right_sib;
                    prevSibling->right_sib = nodeToDelete->right_sib;
                }
            }
            else
            {
                // If the node to delete is the root and has no children, the tree becomes empty
                current = nullptr;
            }
        }

        // Delete the node itself
        delete nodeToDelete;
        return current;
    }

public:
    Tree() : root(NIL) {}

    void insert(const E &info, const E &parent_info)
    {
        if (parent_info == "-1")
        {
            if (root == nullptr)
            {
                root = new Node<E>(info);
            }
            return;
        }

        Node<E> *parent = find(root, parent_info);
        if (!parent)
            return;

        Node<E> *newNode = new Node<E>(info, parent);
        if (parent->left_child == nullptr)
        {
            parent->left_child = newNode;
        }
        else
        {
            Node<E> *sibling = parent->left_child;
            while (sibling->right_sib != nullptr)
                sibling = sibling->right_sib;
            sibling->right_sib = newNode;
        }
    }

    void remove(E info)
    {
        root = remove_aux(root, info);
    }

    void display_aux(Node<E> *node, int depth = 0)
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < depth; i++)
            cout << "  ";
        cout << node->info << endl;

        Node<E> *child = node->left_child;
        while (child != nullptr)
        {
            display_aux(child, depth + 1);
            child = child->right_sib;
        }
    }

    void display()
    {
        display_aux(root);
    }

    Node<E> *father(E value)
    {
        Node<E> *found = find(root, value);
        return (found != NIL) ? found->parent : NIL;
    }

    list<Node<E> *> son(E value)
    {
        Node<E> *found = find(root, value);
        list<Node<E> *> children;

        if (found)
        {
            Node<E> *child = found->left_child;
            while (child != nullptr)
            {
                children.push_back(child);
                child = child->right_sib;
            }
        }

        return children;
    }
};

Tree<string> global_tree;

void clear_screen()
{
    cout << "\033[2J\033[H"; // ANSI escape code for clearing screen
}

void menu_pretty_print()
{
    clear_screen();
    cout << "Menu:\n";
    cout << "a) Insert a Node\n";
    cout << "b) Delete a Node\n";
    cout << "c) Print the Tree (hierarchical format)\n";
    cout << "q) Quit\n";
}

void menu_insert_option()
{
    string parent, info;
    clear_screen();
    cout << "OPTION: Insert a Node\n";
    cout << "Insert the Parent Node Value (-1 for root): ";
    cin >> parent;
    cin.ignore();
    cout << "Insert the Info Value: ";
    getline(cin, info);
    global_tree.insert(info, parent);
}

void menu_delete_option()
{
    string node;
    clear_screen();
    cout << "OPTION: Delete a Node\n";
    cout << "Insert the Node Value: ";
    cin >> node;
    global_tree.remove(node);
}

void menu_print_option()
{
    clear_screen();
    cout << "OPTION: Print the Tree\n";
    cout << "Tree structure (hierarchical format):\n";
    global_tree.display();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

bool menu_selection(char s)
{
    switch (s)
    {
    case 'a':
        menu_insert_option();
        break;
    case 'b':
        menu_delete_option();
        break;
    case 'c':
        menu_print_option();
        break;
    case 'q':
        return false;
    }
    return true;
}

char menu_input()
{
    char c;
    string inputs = "abcdq";
    do
    {
        menu_pretty_print();
        string input;
        cout << "Insert an option: ";
        cin >> input;
        c = input[0];
    } while (inputs.find(c) == string::npos);
    return c;
}

void menu()
{
    bool quit = true;
    do
    {
        quit = menu_selection(menu_input());
    } while (quit);
    clear_screen();
}

int main()
{
    menu();
    return 0;
}
