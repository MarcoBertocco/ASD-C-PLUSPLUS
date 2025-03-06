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
    Node<E> *remove_aux(Node<E> *current, E value)
    {
        if (current == NIL)
            return current;

        // If the current node is the one to be deleted
        if (current->info == value)
        {
            // If the node has no left child, return its right sibling
            if (current->left_child == NIL)
            {
                Node<E> *temp = current->right_sib;
                if (temp)
                    temp->parent = current->parent; // Fix the parent pointer of the sibling
                delete current;
                return temp;
            }
            // If the node has no right sibling, return its left child
            else if (current->right_sib == NIL)
            {
                Node<E> *temp = current->left_child;
                if (temp)
                    temp->parent = current->parent; // Fix the parent pointer of the child
                delete current;
                return temp;
            }

            // If the node has both children and right sibling
            Node<E> *temp = current->left_child;
            while (temp->right_sib != NIL)
            {
                temp = temp->right_sib;
            }

            // Connect the children with the right sibling chain of the node's parent
            temp->right_sib = current->right_sib;
            if (temp->right_sib)
                temp->right_sib->parent = current->parent;

            Node<E> *next = current->left_child; // The new root of the subtree
            delete current;
            return next;
        }

        // If the current node isn't the one to delete, search both the left child and right sibling
        Node<E> *new_left_child = remove_aux(current->left_child, value);
        if (new_left_child != NIL)
        {
            current->left_child = new_left_child;
            if (new_left_child)
                new_left_child->parent = current;
        }

        current->right_sib = remove_aux(current->right_sib, value);
        if (current->right_sib)
            current->right_sib->parent = current;

        return current;
    }

public:
    Tree() : root(NIL) {}

    Node<E> *find(Node<E> *v, const E &info)
    {
        if (v == NIL)
            return NIL;
        if (v->info == info)
            return v;

        Node<E> *res = find(v->left_child, info);
        if (res != NIL)
            return res;
        return find(v->right_sib, info);
    }

    void insert(const E &info, const E &parent_info)
    {
        if (parent_info == "-1")
        {
            if (root == NIL)
            {
                root = new Node<E>(info);
            }
            return;
        }

        Node<E> *parent = find(root, parent_info);
        if (!parent)
            return;

        Node<E> *newNode = new Node<E>(info, parent);
        if (parent->left_child == NIL)
        {
            parent->left_child = newNode;
        }
        else
        {
            Node<E> *sibling = parent->left_child;
            while (sibling->right_sib != NIL)
            {
                sibling = sibling->right_sib;
            }
            sibling->right_sib = newNode;
        }
    }

    void remove(E info)
    {
        root = remove_aux(root, info);
    }

    void display(Node<E> *node, int depth = 0)
    {
        if (node == NIL)
            return;

        for (int i = 0; i < depth; i++)
            cout << "  ";
        cout << node->info << endl;

        display(node->left_child, depth + 1);
        display(node->right_sib, depth);
    }

    void display()
    {
        display(root);
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
    cout << "c) Print the Tree (list format)\n";
    cout << "d) Print the Tree (hierarchical format)\n";
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
    cout << "Tree structure (list format):\n";
    global_tree.display();
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void menu_pretty_print_option()
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
    case 'd':
        menu_pretty_print_option();
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
