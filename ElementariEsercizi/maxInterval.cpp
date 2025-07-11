// Scrivere un algoritmo efficiente maxIntervallo(v, n) che, dato un vettore v di n intervalli (con n > 0),
// verifica se esiste un intervallo in v che contiene tutti gli altri intervalli. Tutti gli intervalli sono NON
// vuoti.
// Analizzare la complessità dell’algoritmo giustificando opportunamente la risposta.
// Si devono scrivere eventuali procedure e/o funzioni ausiliarie.
// Esempio:
// Sia v = ⟨(−2, 11), (−5, −4), (−1, 7), (10, 15)⟩: maxIntervallo(v,4) = false
// Sia v = ⟨(−2, 11), (−11, 15), (7, 10)⟩: maxIntervallo(v,3) = true
#include <vector>
#include <iostream>
using namespace std;

bool maxIntervallo(vector<pair<int, int>> v, int n) // O(n)
{
    int index = 0;
    for (int i = 1; i < n; i++) // O(n-1)
    {
        if (v[i].first <= v[index].first && v[i].second >= v[index].second)
        {
            index = i;
        }
    }

    int container_start = v[index].first;
    int container_end = v[index].second;

    // Check if it contains all other intervals
    for (int i = 0; i < n; i++) // O(n)
    {
        if (v[i].first < container_start || v[i].second > container_end)
            return false;
    }
    cout << "Interval that contains all: [" << container_start << ", " << container_end << "] (";
    return true;
}

bool maxIntervallo1(vector<pair<int, int>> v, int n) // O(n)
{
    int min = v[0].first, max = v[0].second;
    for (int i = 1; i < n; i++) // O(n-1)
    {
        if (min >= v[i].first && max <= v[i].second)
        {
            min = v[i].first;
            max = v[i].second;
        }
    }

    for (int i = 0; i < n; i++) // O(n)
    {
        if (v[i].first < min || v[i].second > max)
            return false;
    }
    cout << "Interval that contains all: [" << min << ", " << max << "] (";
    return true;
}
int main()
{
    vector<pair<int, int>> v1 = {{-2, 11}, {-5, -4}, {-1, 7}, {10, 15}};
    vector<pair<int, int>> v2 = {{-11, 15}, {-2, 11}, {7, 10}};

    cout << "C'è l'intervallo? " << ((maxIntervallo(v1, v1.size())) ? " " : "(no)") << endl;
    cout << "C'è l'intervallo? " << ((maxIntervallo(v2, v2.size())) ? "si) " : "(no)") << endl;

    cout << "C'è l'intervallo? " << ((maxIntervallo1(v1, v1.size())) ? " " : "(no)") << endl;
    cout << "C'è l'intervallo? " << ((maxIntervallo1(v2, v2.size())) ? "si) " : "(no)") << endl;
}