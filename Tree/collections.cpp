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

    Node<E> *findMin(Node<E> *current)
    {
        while (current && current->left != NIL)
        {
            current = current->left;
        }
        return current;
    }

    Node<E> *remove_aux(Node<E> *current, E value)
    {
        if (current == NIL)
            return current;

        if (value < current->info)
        {
            current->left = remove_aux(current->left, value);
            if (current->left)
                current->left->parent = current;
        }
        else if (value > current->info)
        {
            current->right = remove_aux(current->right, value);
            if (current->right)
                current->right->parent = current;
        }
        else
        {
            if (current->left == NIL)
            {
                Node<E> *temp = current->right;
                if (temp)
                    temp->parent = current->parent;
                delete current;
                return temp;
            }
            else if (current->right == NIL)
            {
                Node<E> *temp = current->left;
                if (temp)
                    temp->parent = current->parent;
                delete current;
                return temp;
            }

            Node<E> *temp = findMin(current->right);
            current->info = temp->info;
            current->right = remove_aux(current->right, temp->info);
            if (current->right)
                current->right->parent = current;
        }
        return current;
    }

    void inorder(Node<E> *current)
    {
        if (current)
        {
            inorder(current->left);
            cout << current->info << " ";
            inorder(current->right);
        }
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
        if (current == NIL || current->info == value)
            return current;
        if (value < current->info)
            return find_node(current->left, value);
        return find_node(current->right, value);
    }

public:
    Tree() : root(NIL) {}

    ~Tree()
    {
        destroy_tree_aux(root);
    }

    void insert(E value, E parentValue, bool isLeft)
    {
        if (root == NIL)
        {
            root = new Node<E>(value, NIL);
            return;
        }

        Node<E> *parent = find_node(root, parentValue);
        if (!parent)
        {
            cout << "Parent node " << parentValue << " not found!\n";
            return;
        }

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
    cout << "c) Print the Tree (list format)\n";
    cout << "d) Print the Tree (hierarchical format)\n";
    cout << "q) Quit\n";
}

void menu_insert_option()
{
    string parent, info, isleft;
    clear_screen();
    cout << "OPTION: Insert a Node\n";
    cout << "Insert the Parent Node Value (-1 for root): ";
    cin >> parent;

    cout << "Insert the 'LEFT' OR 'RIGHT' Value: ";
    cin >> isleft;

    cin.ignore();
    cout << "Insert the Info Value: ";
    getline(cin, info);

    if (isleft.substr(0, 0) == "LEFT")
    {
        global_tree.insert(info, parent, true);
    }
    else
    {
        global_tree.insert(info, parent, false);
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