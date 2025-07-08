// Esame del 14/06/2021
// I numeri di Fibonacci sono deFiniti dalla seguente ricorrenza:
// F0 = 0
// F1 = 1
// Fi = Fi − 1 + Fi − 2 per i ≥ 2
// Scrivere un algoritmo di programmazione dinamica con tempo O(n) per calcolare n-esimo numero di
// Fibonacci. Quale schema è stato utilizzato (top-down o bottom-up)? GiustiFicare il calcolo della comp-
// lessità.

#include <iostream>
#include <vector>
using namespace std;
int fib_top_down(vector<int> &F, int n)
{
    if (F[n] != -1)
        return F[n]; // già calcolato
    if (n == 0)
        return F[n] = 0;
    if (n == 1)
        return F[n] = 1;

    F[n] = fib_top_down(F, n - 1) + fib_top_down(F, n - 2);
    return F[n];
}

int fib_bottom_up(int n)
{
    if (n == 0)
        return 0;
    vector<int> F(n + 1); // da F[0] a F[n]
    F[0] = 0;
    F[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        F[i] = F[i - 1] + F[i - 2];
    }
    return F[n];
}

int main()
{
    cout << "fibonacci 10 " << fib_bottom_up(10) << endl;
    cout << "fibonacci 40 " << fib_bottom_up(40) << endl;

    vector<int> fib1(11, -1);
    cout << "fibonacci 10 " << fib_top_down(fib1, 10) << endl;

    vector<int> fib2(41, -1);
    cout << "fibonacci 40 " << fib_top_down(fib2, 40) << endl;
}