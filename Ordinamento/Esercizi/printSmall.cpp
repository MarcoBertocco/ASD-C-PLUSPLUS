// Esame del 05/09/2017
// Si consideri un vettore v di n numeri reali distinti e un intero k ∈ {1, ..., n}; l’array non è ordinato.
// a) Scrivere un algoritmo che, dati v, k e n, stampi i k valori più piccoli presenti in v. Il costo
// dell’algoritmo proposto deve essere al più O(kn).
// b) Analizzare la complessità dell’algoritmo.

#include <iostream>
#include <vector>
#define MAX_INT 1000000000
using namespace std;
void printSmall(vector<int> v, int k, int n) {
    for (int i = 0; i < k; i++) {
        int minIndex = -1;
        int minValue = MAX_INT;

        for (int j = 0; j < n; j++) {
            if (v[j] < minValue) {
                minValue = v[j];
                minIndex = j;
            }
        }

        if (minIndex != -1) {
            cout << minValue << " ";
            v[minIndex] = MAX_INT; // Escludi il minimo trovato dalle prossime iterazioni
        }
    }
    cout << endl;
}
int main()
{
    vector<int> vett = {24, 352, 35, 235, 35, 23, 132, 35, 3, 5, 6, 24};
    int k = 4, n = vett.size();
    printSmall(vett, k, n);
}