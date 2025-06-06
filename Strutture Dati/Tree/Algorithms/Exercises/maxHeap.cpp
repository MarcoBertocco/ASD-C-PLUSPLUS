#include <iostream>
#include <vector>
using namespace std;

void max_heapify(vector<int> &A, int heap_size, int i) // T(n) = O(h) = O(log n) whr h is Height Heap
{
    int massimo = i;
    int l = i * 2 + 1;
    int r = i * 2 + 2;

    if (l < heap_size && A[l] > A[massimo])
    {
        massimo = l;
    }
    if (r < heap_size && A[r] > A[massimo])
    {
        massimo = r;
    }
    if (i != massimo)
    {
        swap(A[i], A[massimo]);             // O(1)
        max_heapify(A, heap_size, massimo); // ?
    }
}

void extractMax(vector<int> &h)
{
    if (h.size() == 0)
        return;

    swap(h[0], h[h.size() - 1]);
    h.pop_back();

    max_heapify(h, h.size(), 0);
}

vector<int> intersezione(vector<int> h1, vector<int> h2)
{
    vector<int> res;

    while (!h1.empty() && !h2.empty())
    {
        cout << h1[0] << " " << h2[0] << endl;
        if (h1[0] == h2[0])
        {
            res.push_back(h1[0]);
            extractMax(h1);
            extractMax(h2);
        }
        else if (h1[0] > h2[0])
        {
            extractMax(h1);
        }
        else
        {
            extractMax(h2);
        }
    }

    return res;
}
void stampaVettore(const vector<int> &vettore)
{
    for (int num : vettore)
    {
        cout << num << " ";
    }
    cout << endl;
}
int main()
{
    vector<int> heap1 = {100, 7, 25, 1, 4, 5};
    vector<int> heap2 = {101, 100, 50, 25, 5, 50, 25, 7, 1};

    cout << "Heap 1: ";
    stampaVettore(heap1);
    cout << "Heap 2: ";
    stampaVettore(heap2);

    vector<int> heap3 = intersezione(heap1, heap2);

    cout << "Intersezione: ";
    stampaVettore(heap3);
    return 0;
}