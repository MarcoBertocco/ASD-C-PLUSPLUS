#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <list>
#include <cmath>

using namespace std;
#define NIL nullptr

template <class E>
struct Node
{
    E info;

    Node() : info() {}

    Node(const E &info_) : info(info_) {}

    ~Node() {}
};

template <class E>
class Tree
{
private:
    Node<E> *P;      // Array of nodes (positional array)
    size_t size = 0; // Number of nodes in the tree
    size_t capacity; // Capacity of the tree (array size)
    size_t K;        // The grade of the tree (maximum number of children per node)

    void resize(bool increase = true)
    {
        size_t newCapacity = increase ? (capacity == 0 ? 2 : capacity * 2) : (size > 0 ? size : 1);

        Node<E> *newNodes = new Node<E>[newCapacity];
        for (size_t i = 0; i < size; i++)
        {
            newNodes[i] = P[i];
        }
        delete[] P;
        P = newNodes;
        capacity = newCapacity;
    }

    void displayRecursive(int v, int depth)
    {
        if (v >= size || v < 0)
        {
            return; // base case: invalid index
        }
        for (int i = 0; i < depth; i++)
            cout << "  ";
        cout << P[v].info << endl;

        int firstChildIndex = v * K + 1;
        for (int i = 0; i < K; ++i)
        {
            int childIndex = firstChildIndex + i;
            if (childIndex < size)
                displayRecursive(childIndex, depth + 1);
        }
    }

public:
    // Constructor
    Tree(int k_) : P(NIL), size(0), capacity(0), K(k_) {}

    ~Tree()
    {
        delete[] P;
    }

    Node<E> *father(int v)
    {
        if (v <= 0 || v >= size)
            return NIL;
        return &P[static_cast<int>(floor((v - 1) / K))];
    }

    list<int> son(int v)
    {
        list<int> l;
        int firstChild = v * K + 1;
        if (firstChild >= size)
        {
            return l;
        }
        else
        {
            for (int i = 0; i <= K - 1; i++)
                l.push_back(firstChild + i);
            return l;
        }
    }

    void insert(const E &content)
    {
        if (size == capacity)
            resize();
        P[size] = Node<E>(content);
        size++;
    }

    void remove(int v)
    {
        if (v < 0 || v >= size)
            return;

        for (int i = v; i < size - 1; i++)
        {
            P[i] = P[i + 1];
        }

        size--;
    }

    void displayTree()
    {
        for (size_t i = 0; i < size; i++)
        {
            if (father(i) == NIL) // root node
            {
                displayRecursive(i, 0);
            }
        }
    }
};

Tree<string> global_tree(3);

void menu_pretty_print()
{
    system("clear");
    cout << "Menu: " << endl;
    cout << "a) Insert a Node " << endl;
    cout << "b) Delete a Node " << endl;
    cout << "c) Print the Tree (list format) " << endl;
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
    string info;
    cout << "Insert the Info Value: ";
    cin >> info;

    global_tree.insert(info);
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
    string inputs = "abcq";
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
    int k = 3; // Example: 3-ary tree
    Tree<string> tree(k);

    // Insert some nodes into the tree
    tree.insert("A"); // Root
    tree.insert("B");
    tree.insert("C");
    tree.insert("D");
    tree.insert("E");
    tree.insert("F");
    tree.insert("G");
    tree.insert("H");
    tree.insert("I");
    tree.insert("L");
    tree.insert("M");
    tree.insert("N");
    tree.insert("O");

    cout << "Tree structure (hierarchical format):\n";
    tree.displayTree(); // This will call the recursive function to display the tree.

    // Test father and son relationships
    cout << "\nParent of node 3 (D): ";
    Node<string> *parent = tree.father(3);
    if (parent)
    {
        cout << parent->info << endl;
    }
    else
    {
        cout << "No parent found!" << endl;
    }

    cout << "\nChildren of node 1 (B): ";
    list<int> children = tree.son(1);
    for (int child : children)
    {
        cout << child << " ";
    }
    cout << endl;

    // Try a delete operation
    cout << "\nRemoving node 6 (G)...\n";
    tree.remove(6);     // Remove the node at index 6
    tree.displayTree(); // Show the tree again after removal
    // menu();
    return 0;
}