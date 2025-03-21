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
    int arr[] = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // Complessità di Insertion:O(n^2)
    insertion_sort(vettore);
    for (int i = 0; i < vettore.size(); i++)
        cout << vettore.at(i) << " ";
    cout << endl;
    return 1;
}