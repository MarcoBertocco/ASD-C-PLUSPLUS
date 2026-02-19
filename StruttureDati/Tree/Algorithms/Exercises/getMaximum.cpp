#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
void maxHeapify(vector<int> &A, int i, int heapsize) // T(n) = O(h) = O(log n) whr h is Height Heap
{
    int max = i;
    int l = i * 2 + 1, r = i * 2 + 2;

    if (A[max] < A[l] && l < heapsize)
        max = l;
    else if (A[max] < A[r] && r < heapsize)
        max = r;
    if (i != max)
    {
        swap(A[i], A[max]);
        maxHeapify(A, max, heapsize); // ?
    }
}

void buildMaxHeap(vector<int> &A) // O(n)
{
    int heapsize = A.size();
    for (int i = floor(heapsize / 2); i >= 0; i--) // O(n/2)
        maxHeapify(A, i, heapsize);                // O(log n)
}

int main()
{
    vector<int> array = {3, 23, 1, 42, 52, 3, 62, 100, 24};
    buildMaxHeap(array); // O(n)

    cout << "Maximum " << array[0] << endl; // O(1)
}