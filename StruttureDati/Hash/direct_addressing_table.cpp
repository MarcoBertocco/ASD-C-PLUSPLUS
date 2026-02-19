#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
#define NIL nullptr

struct Node
{
    int key;
    Node(int _k) : key(_k) {}
    Node() : key(0) {}
};
typedef Node *Nodes;

Nodes direct_address_search(vector<Nodes> &T, int k)
{
    return T[k];
}

void direct_address_insert(vector<Nodes> &T, Nodes x)
{
    T[x->key] = x;
}

void direct_address_delete(vector<Nodes> &T, Nodes x)
{
    T[x->key] = NIL;
}

int main()
{
    int U = 10; // Universe size
    int w = U;  // w = |U|

    // Create table of size w, initially all nullptr
    vector<Node *> T(w, NIL);

    // Insert
    cout<<"Inserting x"<<endl;
    Node *x = new Node(3);
    direct_address_insert(T, x);

    cout<<"Inserting y"<<endl;
    Node *y = new Node(2);
    direct_address_insert(T, y);

    // Search
    cout << "Found 2? " << ((direct_address_search(T, 2)) ? "YES" : "NO") << endl;

    // Delete
    cout<<"Deleting x"<<endl;
    direct_address_delete(T, x);
    cout<<"Deleting t"<<endl;
    direct_address_delete(T, y);
    // Clean up (only for inserted node)
    delete x;

    return 0;
}