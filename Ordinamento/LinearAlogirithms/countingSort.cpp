#include <iostream>
#include <vector>

using namespace std;

void stampaVettore(const vector<int> &vettore)
{
    for (int num : vettore)
    {
        cout << num << " ";
    }
    cout << endl;
}

void counting_sort(vector<int> A, vector<int> &B, int n, int k)
{
    vector<int> C(k, 0); // vettore occorrenze

    for (int j = 0; j < n; j++)
        C[A[j]]++;

    for (int i = 0; i < k; i++)
        C[i] = C[i] + C[i - 1];

    for (int j = n - 1; j >= 0; j--) // ordinazione degli elementi
    {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }
}

int main()
{
    vector<int> vettore = {2, 5, 2, 8, 4, 6, 4, 7, 9, 7, 5, 2};

    cout << "Vettore originale: ";
    stampaVettore(vettore);

    vector<int> vettore_ordinato(vettore.size(), 0);

    // n = size
    // k = max_value of array + 1
    // Complessità counting_sort O(n)
    counting_sort(vettore, vettore_ordinato, vettore.size(), 10);

    cout << "Vettore ordinato: ";
    stampaVettore(vettore_ordinato);

    return 0;
}