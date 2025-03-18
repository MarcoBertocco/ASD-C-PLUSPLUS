#include <iostream>
#include <vector>
using namespace std;

void insertion_sort(vector<int> &A)
{
    for (int j = 1; j < A.size(); j++)
    {
        int k = A[j], i = j - 1;
        while (i >= 0 && k < A[i])
        {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = k;
    }
}
/*
Worst case O(n^2)
Better with small vectors
*/

int main()
{
    int arr[] = {33, 13, 14, 22, 31, 52, 18, 2, 1, 3, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    insertion_sort(vettore);
    for (int i = 0; i < vettore.size(); i++)
        cout << vettore.at(i) << " ";
    cout << endl;
    return 1;
}