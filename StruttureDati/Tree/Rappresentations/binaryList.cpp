#include <iostream>
#include <list>
using namespace std;
#define NIL nullptr

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

    Node<E> *remove_aux(Node<E> *current, E value)
    {
        if (current == NIL)
            return NIL;

        list<Node<E> *> queue;
        queue.push_back(current);

        while (!queue.empty())
        {
            Node<E> *u = queue.front();
            queue.pop_front();

            if (u->info == value)
            {
                if (u->parent != NIL)
                {
                    if (u->parent->left == u)
                        u->parent->left = NIL;
                    else if (u->parent->right == u)
                        u->parent->right = NIL;
                }
                else
                    current = NIL;

                if (u->left != NIL)
                {
                    u->left->parent = NIL;
                    queue.push_back(u->left);
                }
                if (u->right != NIL)
                {
                    u->right->parent = NIL;
                    queue.push_back(u->right);
                }

                delete u;
                continue; // Skip pushing u's children again
            }
            else
            {
                if (u->left != NIL)
                    queue.push_back(u->left);
                if (u->right != NIL)
                    queue.push_back(u->right);
            }
        }

        return current;
    }

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
        if (current == NIL)
            return NIL;

        list<Node<E> *> queue;
        queue.push_back(current);

        while (!queue.empty())
        {
            Node<E> *node = queue.front();
            queue.pop_front();

            if (node->info == value)
                return node;

            if (node->left != NIL)
                queue.push_back(node->left);
            if (node->right != NIL)
                queue.push_back(node->right);
        }

        return NIL;
    }

public:
    Tree() : root(NIL) {}

    ~Tree()
    {
        destroy_tree_aux(root);
    }

    void insert(E value, E parentValue = NIL, bool isLeft = false)
    {
        if (root == NIL)
        {
            root = new Node<E>(value, NIL);
            return;
        }

        if (parentValue)
        {
            Node<E> *parent = find_node(root, parentValue);
            if (!parent || isLeft && parent->left != NIL || !isLeft && parent->right != NIL)
            {
                cout << "Error: Parent " << parentValue << " not found or already has R/L child!\n";
                return;
            }

            Node<E> *newNode = new Node<E>(value, parent);
            if (isLeft)
                parent->left = newNode;
            else
                parent->right = newNode;
        }
    }

    void remove(E value)
    {
        root = remove_aux(root, value);
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

    list<Node<E> *> son(E value)
    {
        Node<E> *found = find_node(root, value);
        list<Node<E> *> children;
        if (found)
        {
            if (found->left)
                children.push_back(found->left);
            if (found->right)
                children.push_back(found->right);
        }
        return children;
    }
};

/*int main()
{
    Tree<int> tree;

    cout << "Inserting root: 50\n";
    tree.insert(50, -1, true);

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

    cout << "\nCurrent Tree Structure:\n";
    tree.displayTree();

    cout << "\nRemoving 20 (leaf node)...\n";
    tree.remove(20);
    tree.displayTree();

    cout << "\nRemoving 30 (node with one child)...\n";
    tree.remove(30);
    tree.displayTree();

    cout << "\nRemoving 50 (node with two children)...\n";
    tree.remove(50);
    tree.displayTree();

    int target = 40;
    cout << "\nChecking parent of node " << target << ":\n";
    Node<int> *parent = tree.father(target);
    if (parent)
        cout << "Parent of " << target << ": " << parent->info << endl;
    else
        cout << target << " has no parent (root node or not in tree)." << endl;

    int parentNode = 70;
    cout << "\nChildren of node " << parentNode << ":\n";
    list<Node<int> *> children = tree.son(parentNode);
    if (!children.empty())
    {
        cout << "Children of " << parentNode << ": ";
        for (Node<int> *child : children)
        {
            cout << child->info << " ";
        }
        cout << endl;
    }
    else
    {
        cout << parentNode << " has no children." << endl;
    }

    return 0;
}*/

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
    string parent, info, isleft;
    clear_screen();
    global_tree.displayTree();
    cout << "OPTION: Insert a Node\n";
    cout << "Insert the Parent Node Value (-1 for root): ";
    cin >> parent;

    cout << "Insert the 'L' OR 'R' Value: ";
    cin >> isleft;

    cin.ignore();
    cout << "Insert the Info Value: ";
    getline(cin, info);

    if (isleft.at(0) == 'L')
    {
        global_tree.insert(info, parent, true);
    }
    else
    {
        global_tree.insert(info, parent);
    }
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

void menu_pretty_print_option()
{
    clear_screen();
    cout << "OPTION: Print the Tree\n";
    cout << "Tree structure (hierarchical format):\n";
    global_tree.displayTree();
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
    string inputs = "abcq";
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