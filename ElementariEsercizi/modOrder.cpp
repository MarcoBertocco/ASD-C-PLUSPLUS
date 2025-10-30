// Esame del 10/01/2023
// Dato un vettore A di n numeri naturali, scrivere una procedura efficiente che ordini A in modo tale che
// nel vettore risultante, dati i e j con
// 1≤i≤j≤n
// vale
// mod(A[i], 3) ≤ mod(A[j], 3)
// dove mod(x, 3) è il resto della divisione di x per 3.
// a. Dire se la soluzione proposta è in loco e se è stabile.
// b. Valutare e giustificare la complessità della procedura proposta.

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int mod3(int x)
{
    return x % 3;
}
void orderMod3(vector<int> &vet, int n)
{
    vector<int> C(3, 0);
    vector<int> output(n);
    for (int i = 0; i < n; i++)
    {
        C[mod3(vet[i])]++;
    }

    for (int i = 1; i < 3; i++)
    {
        C[i] += C[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int d = mod3(vet[i]);
        C[d]--;
        output[C[d]] = vet[i];
    }
    vet = output;
}
int main()
{
    
    vector<int> vettore = {1, 5, 8, 9, 4, 6, 3, 6, 6, 3, 2, 7};
    int n = vettore.size();
    orderMod3(vettore, n);

    for (auto v : vettore)
    {
        cout << v << " ";
    }
    cout << endl;
}