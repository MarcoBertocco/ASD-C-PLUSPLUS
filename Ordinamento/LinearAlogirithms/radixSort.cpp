#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define ASCENDING_ORDER
// #define DESCENDING_ORDER

void stampaVettore(const vector<int> &vettore)
{
    for (int num : vettore)
    {
        cout << num << " ";
    }
    cout << endl;
}

int cifra(int x, int n, int i)
{
    return (x / (int)pow(n, i)) % n;
}

void counting_sort(vector<int> &A, int k, int i)
{
    int n = A.size();
    vector<int> B(n, 0); // vettore
    vector<int> C(k, 0); // vettore occorrenze

    for (int j = 0; j < n; j++)
        C[cifra(A[j], k, i)]++;

#ifdef ASCENDING_ORDER // somme prefisse
    for (int j = 1; j < k; j++)
        C[j] += C[j - 1];
#endif

#ifdef DESCENDING_ORDER // somme postfisse
    for (int j = k - 1; j >= 0; j--)
        C[j] += C[j + 1];
#endif

    for (int j = n - 1; j >= 0; j--) // ordinazione degli elementi
    {
        int d = cifra(A[j], k, i);
        B[C[d] - 1] = A[j];
        C[d]--;
    }

    // copy vector B in A
    A = B;
}

void radix_sort(vector<int> &A, int d, int k)
{
    for (int i = 0; i < d; i++)
        counting_sort(A, k, i);
}

int main()
{
    vector<int> vettore = {326, 453, 608, 835, 751, 435, 704, 690};

    cout << "Vettore originale: ";
    stampaVettore(vettore);

    int d = log10(100) + 1; // number of digits
    int k = 10;             // base 10

    // Complessità radix sort O(n)
    radix_sort(vettore, d, k);

    cout << "Vettore ordinato: ";
    stampaVettore(vettore);

    return 0;
}