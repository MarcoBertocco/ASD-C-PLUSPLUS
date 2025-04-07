#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;
#define NIL nullptr
int global_m = 0;
struct Node
{
    int key;
    Node *next;
    Node *prev;
    Node(int _k = 0, Node *p = NIL, Node *n = NIL) : key(_k), prev(p), next(n) {}
};
typedef Node *Nodes;

int h(int key)
{
    return key % global_m;
}

void chained_hash_insert(vector<Nodes> &T, Nodes x)
{
    int index = h(x->key);
    x->next = T[index];

    if (T[index] != NIL)
    {
        T[index]->prev = x;
    }
    T[index] = x;
}
Nodes chained_hash_search(vector<Nodes> T, int k)
{
    Nodes p = T[h(k)];
    while (p != NIL && p->key != k)
    {
        p = p->next;
    }
    return p;
}

void chained_hash_delete(vector<Nodes> &T, Nodes x)
{
    int index = h(x->key);

    if (x->prev != NIL)
    {
        x->prev->next = x->next;
    }
    else
    {
        T[index] = x->next;
    }

    if (x->next != NIL)
    {
        x->next->prev = x->prev;
    }

    delete x;
}

// Funzione per verificare se un numero è primo
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

// Funzione per trovare il primo più vicino e minore di k
int closestPrime(int k)
{
    for (int i = k - 1; i >= 2; i--)
    {
        if (isPrime(i))
        {
            return i;
        }
    }
    return -1; // Nessun primo trovato (es. se k <= 2)
}

int main()
{
    int Universe = 150, collisions = 4;
    global_m = closestPrime(floor(Universe / collisions));
    cout<<global_m<<endl;
    if (global_m == -1)
        global_m = 2;
    vector<Nodes> T(global_m, NIL);

    Nodes n1 = new Node(15);
    Nodes n2 = new Node(25);
    Nodes n3 = new Node(35);
    Nodes n4 = new Node(45);
    Nodes n5 = new Node(55);
    Nodes n6 = new Node(65);
    Nodes n7 = new Node(75);
    Nodes n8 = new Node(85);
    Nodes n9 = new Node(95);
    Nodes n10 = new Node(105);

    chained_hash_insert(T, n1);
    chained_hash_insert(T, n2);
    chained_hash_insert(T, n3);
    chained_hash_insert(T, n4);
    chained_hash_insert(T, n5);
    chained_hash_insert(T, n6);
    chained_hash_insert(T, n7);
    chained_hash_insert(T, n8);
    chained_hash_insert(T, n9);
    chained_hash_insert(T, n10);

    Nodes found = chained_hash_search(T, 25);
    if (found)
        cout << "Found: " << found->key << endl;

    chained_hash_delete(T, n2);
    found = chained_hash_search(T, 25);
    if (!found)
        cout << "Node 25 deleted successfully." << endl;

    return 0;
}
