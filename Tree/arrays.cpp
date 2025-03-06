#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;
#define NIL nullptr
template <class E>
struct cell
{
    E info;
    cell<E> *next;

    cell() : info(), next(NIL) {}

    cell(const E &info_) : info(info_), next(NIL) {}

    ~cell() {}
};

template <class E>
struct Node
{
    E info;
    int parent;

    Node() : info(), parent(-1) {}

    Node(const E &info_, int parent_) : info(info_), parent(parent_) {}

    ~Node() {}
};

template <class E>
class Tree
{
private:
    Node<E> *arrayNodes;
    size_t size;
    size_t capacity;

    void resize(bool increase = true)
    {
        size_t newCapacity = increase ? (capacity == 0 ? 2 : capacity * 2) : (size > 0 ? size : 1);
        Node<E> *newNodes = new Node<E>[newCapacity];

        for (size_t i = 0; i < size; i++)
        {
            newNodes[i] = arrayNodes[i];
        }

        delete[] arrayNodes;
        arrayNodes = newNodes;
        capacity = newCapacity;
    }

    void removeSubtree(int v)
    {
        for (int i = 0; i < size; i++)
        {
            if (arrayNodes[i].parent == v)
            {
                removeSubtree(i);
            }
        }

        for (int i = v; i < size - 1; i++)
        {
            arrayNodes[i] = arrayNodes[i + 1];
        }
        size--;
    }

    void displayRecursive(int v, int depth)
    {
        for (int i = 0; i < depth; i++)
            cout << "  "; // Indentation for hierarchy
        cout << arrayNodes[v].info << endl;

        for (int i = 0; i < size; i++)
        {
            if (arrayNodes[i].parent == v)
            {
                displayRecursive(i, depth + 1);
            }
        }
    }

public:
    // Constructor
    Tree() : arrayNodes(NIL), size(0), capacity(0) {}

    // Destructor
    ~Tree()
    {
        delete[] arrayNodes;
    }

    Node<E> *father(int v)
    {
        if (arrayNodes[v].parent == -1)
            return NIL;
        else
            return &arrayNodes[v].parent;
    }

    cell<int> *son(int v)
    {
        cell<int> *l = NIL;
        for (int i = 0; i < size; i++)
        {
            if (arrayNodes[i].parent == v)
            {
                cell<int> *p = new cell<int>(i);
                p->next = l;
                l = p;
            }
        }
        return l;
    }

    void insert(const E &content, int parentIndex)
    {
        if (size == capacity)
            resize();

        arrayNodes[size] = Node<E>(content, parentIndex);
        size++;
    }

    void remove(int v)
    {
        if (v < 0 || v >= size)
            return;
        removeSubtree(v);
    }

    void display()
    {
        for (size_t i = 0; i < size; i++)
        {
            cout << "Node " << i << ": Info = " << arrayNodes[i].info << ", Parent = " << arrayNodes[i].parent << endl;
        }
    }

    void displayTree()
    {
        for (int i = 0; i < size; i++)
        {
            if (arrayNodes[i].parent == -1)
            {
                displayRecursive(i, 0);
            }
        }
    }
};

Tree<string> global_tree;

void menu_pretty_print()
{
    system("clear");
    cout << "Menu: " << endl;
    cout << "a) Insert a Node " << endl;
    cout << "b) Delete a Node " << endl;
    cout << "c) Print the Tree (list format) " << endl;
    cout << "d) Print the Tree (hierarchical format HORRIZONTAL)" << endl;
    cout << "q) Quit" << endl;
}
bool validate_input(string s)
{
    int i = 0;
    while (i < s.length())
    {
        if (s.at(i) < '0' || s.at(i) > '9')
            if (s.at(i) != '-' || i != 0)
                return false;
        i++;
    }
    return true;
}
void menu_insert_input()
{
    int parent = 0;
    string info;
    string input;
    do
    {
        system("clear");
        cout << "OPTION: Insert a Node" << endl;
        cout << "Insert the Node Value: ";
        cin >> input; // Read input as a string
    } while (!validate_input(input));

    parent = stoi(input);
    cin.ignore();

    cout << "Insert the Info Value: ";
    getline(cin, info);

    global_tree.insert(info, parent);
}
void menu_insert_option()
{
    menu_insert_input();
}
void menu_delete_input()
{
    int NodeIndex = 0;
    string input = "";
    do
    {
        system("clear");
        cout << "OPTION: Delete a Node" << endl;
        cout << "Insert the Node Value: ";
        cin >> input;
    } while (!validate_input(input));

    NodeIndex = stoi(input);

    global_tree.remove(NodeIndex);
}
void menu_delete_option()
{
    menu_delete_input();
}
void menu_print_option()
{
    string x;
    system("clear");
    cout << "OPTION: Print the Tree" << endl;
    cout << "Tree structure (list format):" << endl;
    global_tree.display();
    cin >> x;
}
void menu_pretty_print_option()
{
    string x;
    system("clear");
    cout << "OPTION: Print the Tree" << endl;
    cout << "Tree structure (hierarchical format):" << endl;
    global_tree.displayTree();
    cin >> x;
}
bool menu_selection(char s)
{
    switch (s)
    {
    case 'a':
    {
        system("clear");
        menu_insert_option();
        break;
    }
    case 'b':
    {
        system("clear");
        menu_delete_option();
        break;
    }
    case 'c':
    {
        system("clear");
        menu_print_option();
        break;
    }
    case 'd':
    {
        system("clear");
        menu_pretty_print_option();
        break;
    }
    case 'q':
    {
        return false;
        break;
    }
    }
    return true;
}
char menu_input()
{
    char c = 'e';
    string inputs = "abcdq";
    do
    {
        menu_pretty_print();
        string input = "";
        cout << "Insert an option ";
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
    system("clear");
    return;
}

int main()
{
    /*
    Tree<string> tree;

    // Insert arrayNodes
    tree.insert("A", -1); // Root
    tree.insert("B", 0);
    tree.insert("C", 0);
    tree.insert("D", 0);
    tree.insert("E", 1);
    tree.insert("F", 1);
    tree.insert("G", 3);
    tree.insert("H", 6);
    tree.insert("I", 6);

    cout << "Tree structure (list format):" << endl;
    tree.display();
    cout << endl;

    cout << "Tree structure (hierarchical format):" << endl;
    tree.displayTree();
    cout << endl;

    cout << "Removing Node 3 (D)..." << endl;
    tree.remove(3);
    tree.displayTree();
    */

    menu();
    return 0;
}