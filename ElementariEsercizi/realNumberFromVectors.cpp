// Dato un numero reale x e due vettori v1 e v2 con le relative dimensioni, scrivere una funzione efficiente
// cerca che restituisce 1 se esistono x1 in v1 e x2 in v2 per cui x = x1 /x2 , 0 altrimenti.
// Nel caso in cui la funzione restituisca 1, anche i valori x1 e x2
// che soddisfano la condizione devono essere ritornati all’utente.
// Analizzare la complessità in tempo della funzione.
// Si devono scrivere eventuali procedure e/o funzioni ausiliarie.

#include <vector>
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

#define Near_infinite 2147483647
const double EPSILON = 1e-6;

void merge(vector<double> &A, int p, int q, int r) // O(n)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<double> L(n1 + 1), R(n2 + 1);

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
void merge_sort(vector<double> &A, int p, int r) // 2T(n/2) + O(n) -> O(nlog(n))
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r); // O(n)
    }
}

bool divisionReal(double real, vector<double> v1, vector<double> v2, double &x1, double &x2) // T(n, m) = O(nlog(n)) + O(mlog(m)) + O(n * m) -> O(n * m)
{
    // merge_sort(v1, 0, v1.size() - 1); // O(nlog(n))
    // merge_sort(v2, 0, v2.size() - 1); // O(mlog(m))

    cout << "v1 = { ";
    for (auto y1 : v1)
        cout << y1 << " ";
    cout << "}" << endl;

    cout << "v2 = { ";
    for (auto y2 : v2)
        cout << y2 << " ";
    cout << "}" << endl;

    for (double a : v1)
    {
        if (a >= real)
        {
            for (double b : v2)
            {
                if (fabs(b) > EPSILON)
                { // Evita divisione per zero
                    if (fabs(a / b - real) < EPSILON)
                    {
                        x1 = a;
                        x2 = b;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    double real = 3.5f;
    vector<double> v1 = {1.0, 4.2, 5.0, 7.0, 9.1, 11.0, 13.5, 15.2, 18.8, 20.0};
    vector<double> v2 = {1.0, 1.5, 2.0, 2.5, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

    double x1 = -1.0f, x2 = -1.0f;

    if (divisionReal(real, v1, v2, x1, x2))
        cout << "Trovato: " << real << " = " << x1 << " / " << x2 << endl;
    else
        cout << "Impossibile trovare x1 e x2 per " << real << endl;
}