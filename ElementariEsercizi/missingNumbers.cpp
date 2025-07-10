// Sia A un array di lunghezza n*k con k ≥ 2, privo di ripetizioni e
// contenente interi nell’intervallo [n^2 + 1, n^2 + n*k + k].
// Si consideri il problema di determinare i k numeri interi appartenenti
// all’intervallo [n^2 + 1, n^2 + n*k + k] che non compaiono in A.
// Scrivere una procedura efficiente che, dati A, n e k,
// stampi i k interi mancanti in ordine crescente.
// Calcolare e giustificare la complessità dell’algoritmo.

#include <iostream>
#include <vector>
using namespace std;
#define Near_infinite 2147483647

#include <algorithm>
#include <random>

void merge(vector<int> &punteggi, int p, int q, int r) // O(n)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) // O(n1)
        L[i] = punteggi[p + i];
    for (int j = 0; j < n2; j++) // O(n2)
        R[j] = punteggi[q + j + 1];

    L[n1] = Near_infinite;
    R[n2] = Near_infinite;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) // O(n)
    {
        if (L[i] <= R[j])
        {
            punteggi[k] = L[i];
            i++;
        }
        else
        {
            punteggi[k] = R[j];
            j++;
        }
    }
}

void merge_sort(vector<int> &punteggi, int p, int r) // 2T(n/2) + O(n) -> O(nlog(n))
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(punteggi, p, q);
        merge_sort(punteggi, q + 1, r);
        merge(punteggi, p, q, r); // O(n)
    }
}

void missingNumbers(vector<int> A, int n)
{
    merge_sort(A, 0, n); // O(nlog(n))

    cout << "A = { ";
    for (int x : A)
        cout << x << " ";
    cout << "}" << endl;

    cout << "missing numbers: ";
    for (int i = 0; i < n - 1; i++) // O(n)
    {
        if (A[i] + 1 != A[i + 1])
        {
            cout << A[i] + 1 << " ";
        }
    }
    cout << endl;
}

int main()
{
    int n = 5, k = 2;
    int total = n * k;
    int min_val = n * n + 1;
    int max_val = n * n + n * k + k;

    // 1. Generate full interval [n^2 + 1, n^2 + nk + k]
    vector<int> full_range;
    for (int i = min_val; i <= max_val; ++i)
    {
        full_range.push_back(i);
    }

    // 2. Shuffle the interval
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister RNG
    shuffle(full_range.begin(), full_range.end(), gen);

    vector<int> A(full_range.begin(), full_range.begin() + total);

    cout << "A = { ";
    for (int x : A)
        cout << x << " ";
    cout << "}" << endl;

    missingNumbers(A, total);
}