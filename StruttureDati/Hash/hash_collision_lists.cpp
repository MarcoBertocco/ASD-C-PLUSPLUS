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
        if (i % 2 != 0)
        {
            if (isPrime(i))
                return i;
        }
    }
    return -1; // Nessun primo trovato (es. se k <= 2)
}

int main()
{
    vector<int> x = {12, 23, 35, 47, 61, 73, 85, 92, 101, 13, 21, 32, 45, 67, 79, 87, 95, 104, 11, 24, 33, 46, 63, 74, 86, 97, 106, 17, 26, 31, 44, 62, 75, 82, 91, 103};

    int keyUniverse = x.size(), collisions = 3;
    global_m = closestPrime(floor(keyUniverse / collisions));
    cout << global_m << endl;
    if (global_m == -1)
        global_m = 2;
    vector<Nodes> T(global_m, NIL);

    for (int i = 0; i < x.size(); i++)
    {
        chained_hash_insert(T, new Node(x[i]));
    }

    Nodes found = chained_hash_search(T, x[1]);
    if (found)
        cout << "Found: " << found->key << endl;

    chained_hash_delete(T, new Node(x[1]));
    found = chained_hash_search(T, x[1]);
    if (!found)
        cout << "Node 25 deleted successfully." << endl;

    return 0;
}
