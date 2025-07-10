// Si deve organizzare una gara di programmazione. Ogni programmatore ha un punteggio che esprime la
// sua abilità (più alto è il punteggio migliore è il programmatore). Ogni programmatore è abbinato a un
// altro programmatore e la differenza fra i loro punteggi è detta “scarto”. Scrivere un algoritmo efficiente
// int scarto( int n, int punteggi []) che dati n programmatori, con n pari, e i loro punteggi, restituisce il minimo
// scarto totale (somma degli scarti delle varie coppie) che si può ottenere pianificando in modo ottimale le
// coppie nella gara. Calcolare e giustificare la complessità dell’algoritmo proposto. Si devono scrivere le
// eventuali procedure/funzioni ausiliarie utilizzate.

#include <iostream>
#include <vector>
using namespace std;

#define Near_infinite 2147483647
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

int scarto(int n, vector<int> punteggi)
{
    merge_sort(punteggi, 0, n - 1); // O(nlog(n))
    int cont = 0;
    for (auto x : punteggi)
    {
        cout << x << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i += 2) // O(n)
    {
        cont += (punteggi[i + 1] - punteggi[i]);
    }
    return cont;
}

int main()
{
    vector<int> punteggi = {53, 62, 36, 48, 26, 84, 69, 43, 21, 46};
    cout << scarto(punteggi.size(), punteggi) << endl;
}