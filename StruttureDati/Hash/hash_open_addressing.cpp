#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;
#define NIL nullptr
#define DELETED -6

struct Node
{
    int key;
    Node *next;
    Node *prev;
    Node(int _k = 0, Node *p = NIL, Node *n = NIL) : key(_k), prev(p), next(n) {}
};