#include <iostream>
#include <vector>
using namespace std;

void insertion_sort(vector<int> &A) // O(n^2)
{
    for (int j = 1; j < A.size(); j++) // n volte
    {
        int k = A[j], i = j - 1;
        while (i >= 0 && k < A[i]) // n volte
        {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = k;
    }
}

int main()
{
    int arr[] = {33, 13, 14, 22, 31, 52, 18, 2, 1, 3, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // Complessità di Insertion:O(n^2)
    insertion_sort(vettore);
    for (int i = 0; i < vettore.size(); i++)
        cout << vettore.at(i) << " ";
    cout << endl;
    return 1;
}