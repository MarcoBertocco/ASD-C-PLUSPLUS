#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int partition(vector<int> &A, int p, int r) // O(n)
{
    int x = A[r], i = p - 1;

    for (int j = p; j <= r - 1; j++) // O(n)
    {
        if (A[j] <= x)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);

    return i + 1;
}

void quick_sort(vector<int> &A, int p, int r) // O(n^2)
{
    if (p < r)
    {
        int q = partition(A, p, r); // O(n)
        quick_sort(A, p, q - 1);    // T(k)
        quick_sort(A, q + 1, r);    // T(n-1-k)
    }
}
int main()
{
    int arr[] = {33, 13, 14, 22, 31, 52, 18, 2, 1, 3, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // Complessità quick_sort O(n^2)
    quick_sort(vettore, 0, vettore.size() - 1);
    for (int i = 0; i < vettore.size(); i++)
        cout << vettore[i] << " ";
    cout << endl;
    return 0;
}