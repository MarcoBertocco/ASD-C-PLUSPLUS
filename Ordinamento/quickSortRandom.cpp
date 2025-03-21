#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding rand()
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

int partition_rand(vector<int> &A, int p, int r) // O(n)
{
    int i = p + rand() % (r - p + 1); // O(1) -> Random pivot selection
    swap(A[i], A[r]);                 // O(1)
    return partition(A, p, r);        // O(n)
}

void quick_sort_rand(vector<int> &A, int p, int r) // Expected: O(n log(n)), Worst-case: O(n^2) (rare)
{
    if (p < r)
    {
        int q = partition_rand(A, p, r); // O(n)
        quick_sort_rand(A, p, q - 1);    // T(k)   -> T(n/2) on average
        quick_sort_rand(A, q + 1, r);    // T(n-1-k) -> T(n/2) on average
    }
}
int main()
{
    int arr[] = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));

    // Complessità quick_sort_rand: Expected O(n log(n)), Worst O(n^2) (rare)
    quick_sort_rand(vettore, 0, vettore.size() - 1);
    for (int i = 0; i < vettore.size(); i++)
        cout << vettore[i] << " ";
    cout << endl;
    return 0;
}