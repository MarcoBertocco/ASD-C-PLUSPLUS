#include <iostream>
#include <vector>
#include <cmath>
#define NIL nullptr

using namespace std;
void stampaVettore(const vector<int> &vettore)
{
    for (int num : vettore)
    {
        cout << num << " ";
    }
    cout << endl;
}

int father(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return i * 2 + 1;
}

int right(int i)
{
    return i * 2 + 2;
}

void max_heapify(vector<int> &A, int heap_size, int i)
{
    int massimo = i;
    int l = left(i);
    int r = right(i);

    if (l < heap_size && A[l] > A[massimo])
    {
        massimo = l;
    }
    if (r < heap_size && A[r] > A[massimo])
    {
        massimo = r;
    }
    stampaVettore(A);
    if (i != massimo)
    {
        swap(A[i], A[massimo]);
        max_heapify(A, heap_size, massimo);
    }
}

void build_max_heap(vector<int> &A)
{
    int heap_size = A.size();
    for (int i = heap_size / 2 - 1; i >= 0; i--)
    {
        cout << "++++++++HEAPIFY+(" << i << ")+++" << endl;
        max_heapify(A, heap_size, i);
        cout << "+++++++++++++++++++++++" << endl;
    }
}

void heap_sort(vector<int> &A)
{
    int heap_size = A.size();
    cout << "---------BUILD---------" << endl;
    build_max_heap(A);
    cout << "-----------------------" << endl;
    cout << "" << endl;
    for (int i = heap_size - 1; i > 0; i--)
    {
        swap(A[i], A[0]);
        heap_size--;
        cout << "-----------------------" << endl;
        stampaVettore(A);
        cout << "-----------------------" << endl;

        cout << "++++++++HEAPIFY+(" << i << ")+++" << endl;
        max_heapify(A, heap_size, 0);
        cout << "+++++++++++++++++++++++" << endl;
    }
}

int main()
{
    vector<int> vettore = {16, 4, 10, 24, 7, 9, 3, 2, 8, 1};

    cout << "Vettore originale: ";
    stampaVettore(vettore);

    heap_sort(vettore);

    cout << "Vettore ordinato: ";
    stampaVettore(vettore);

    return 0;
}