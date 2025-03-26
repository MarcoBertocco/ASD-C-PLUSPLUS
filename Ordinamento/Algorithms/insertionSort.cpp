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

void insertion_sort_rec_aux(vector<int> &A, int dim)
{
    if (dim <= 0)
        return;

    insertion_sort_rec_aux(A, dim - 1);

    int last = A[dim];
    int j = dim - 1;

    while (j >= 0 && A[j] > last)
    {
        A[j + 1] = A[j];
        j--;
    }
    A[j + 1] = last;
}

void insertion_sort_rec_aux1(vector<int> &A, int dim, int tmp)
{
    if (dim == 0)
        return;

    insertion_sort_rec_aux1(A, dim - 1, A[dim - 1]);

    int j = dim - 1;
    while (j >= 0 && A[j] > tmp)
    {
        A[j + 1] = A[j];
        j--;
    }
    A[j + 1] = tmp;
}

void insertion_sort_rec(vector<int> &A)
{
    // insertion_sort_rec_aux1(A, A.size() - 1, A[A.size() - 1]);
    insertion_sort_rec_aux(A, A.size() - 1);
}

int main()
{
    int arr[] = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // Complessità di Insertion:O(n^2)
    // insertion_sort(vettore);

    insertion_sort_rec(vettore);

    for (int i = 0; i < vettore.size(); i++)
        cout << vettore.at(i) << " ";
    cout << endl;
    return 1;
}