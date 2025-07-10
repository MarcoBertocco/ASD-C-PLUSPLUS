// 4. Esame del 17/05/2016
// Scrivere l’algoritmo Radix-Sort con le eventuali procedure ausiliarie e discuterne la complessità.
// Illustrare l’esecuzione di Radix-Sort con la seguente lista di parole inglesi:
// COW, DOG, SEA, RUG, ROW, MOB, BOX, TAB, BAR, EAR, TAR, DIG, BIG, TEA, NOW, FOX
// Non è necessaria alcuna codifica delle lettere in numeri e alla fine le parole devono essere ordinate in
// senso crescente rispetto all’ordinamento lessicografico.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void countingSort(vector<string> &A, int n, int k, int i)
{
    vector<int> c(k, 0); // A = 65, B = 66 ..
    vector<string> B(n);

    for (int j = 0; j < n; j++)
        c[A[j][i] - 'A'] += 1;

    for (int j = 1; j < k; j++)
    {
        c[j] += c[j - 1];
    }
   
    for (int j = n - 1; j >= 0; j--)
    {
        int d = A[j][i] - 'A';
        B[c[d] - 1] = A[j];
        c[d]--;
    }
    A = B;
}
void radixSort(vector<string> &A, int n, int d, int k)
{
    for (int i = d - 1; i >= 0; i--)
    {
        countingSort(A, n, k, i);
    }
}

int main()
{
    vector<string> vettore = {"COW", "DOG", "SEA", "RUG", "ROW", "MOB", "BOX", "TAB", "BAR", "EAR", "TAR", "DIG", "BIG", "TEA", "NOW", "FOX"};
    int k = 26, d = 3, n = vettore.size();

    radixSort(vettore, n, d, k);

    for (const auto &word : vettore)
    {
        cout << word << endl;
    }
}