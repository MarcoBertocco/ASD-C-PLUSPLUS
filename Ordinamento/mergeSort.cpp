#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define Near_infinite 2147483647

void merge(vector<int> &A, int p, int q, int r) // O(n)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1 + 1), R(n2 + 1);

    // Copy subarrays
    for (int i = 0; i < n1; i++) // O(n1)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++) // O(n2)
        R[j] = A[q + 1 + j];

    // Sentinel values
    L[n1] = Near_infinite;
    R[n2] = Near_infinite;

    int i = 0, j = 0;
    // Merge the two subarrays back into A
    for (int k = p; k <= r; k++) // O(n)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}

void merge_sort(vector<int> &A, int p, int r) // 2T(n/2) + O(n) -> O(nlog(n))
{
    if (p < r)
    {
        int med = (p + r) / 2;
        merge_sort(A, p, med);
        merge_sort(A, med + 1, r);
        merge(A, p, med, r); // O(n)
    }
}

int main()
{
    int arr[] = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // Complessità di MergeSort: O(nlog(n))
    merge_sort(vettore, 0, vettore.size() - 1);
    for (int i = 0; i < vettore.size(); i++)
        cout << vettore[i] << " ";
    cout << endl;
    return 0;
}