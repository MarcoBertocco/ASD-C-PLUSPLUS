// Sia A un array di n numeri interi. Si consideri il problema di decidere se esistono 3 posizioni distinte
// x, y, z in A tali che A[x] + A[y] + A[z] = 0.
// Scrivere un algoritmo di complessità O(n^2 ) per risolvere il problema.
// (Suggerimento: si ordini A, poi si utilizzino 3 contatori i, j, k: i assume tutti i valori da 1 a n^2; poi per
// ogni valore di i, j viene inizializzato a i + 1, e k ad n ...).
// Dimostrare che la complessità della soluzione proposta sia O(n^2 ).

#include <iostream>
#include <vector>
using namespace std;

#define Near_infinite 2147483647
void merge(vector<int> &A, int p, int q, int r) // O(n)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) // O(n1)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++) // O(n2)
        R[j] = A[q + j + 1];

    L[n1] = Near_infinite;
    R[n2] = Near_infinite;

    int i = 0, j = 0;
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
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r); // O(n)
    }
}

// solution
bool threePos(vector<int> A, int n)
{
    merge_sort(A, 0, n - 1);

    bool end = false;
    for (int i = 0; i < n - 2; ++i)
    {
        int j = i + 1;
        int k = n - 1;

        while (j < k && !end)
        {
            int sum = A[i] + A[j] + A[k];
            if (sum == 0)
                end = true;
            else if (sum < 0)
                k--;
            else
                j++;
        }
    }

    return end;
}
int main()
{
    vector<int> A = {-7, -5, -3, -1, 0, 1, 4, 6};
    cout << "Esiste? " << ((threePos(A, A.size())) ? "YES" : "NO") << endl;
}
