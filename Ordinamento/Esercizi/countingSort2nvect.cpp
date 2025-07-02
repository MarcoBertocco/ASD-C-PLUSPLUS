#include <iostream>
#include <vector>

using namespace std;

void stampaVettore(const vector<int> &vettore)
{
    for (int num : vettore)
    {
        cout << num << " ";
    }
    cout << endl;
}

void counting_sort2n(vector<int> &v, int n, int k)
{
    for (int i = k; i < n; i++)
    {
        v[v[i - k] + k] += 1;
    }

    for (int i = k + 1; i < n; i++)
    {
        v[i] += v[i - 1];
    }

    for (int i = 0; i < k; i++)
    {
        v[i] = v[i + k];
    }

    for (int i = k; i < n; i++)
    {
        v[i] = 0;
    }

    stampaVettore(v);
}

int main()
{
    vector<int> vettore = {2, 5, 2, 3, 4, 6, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0}; // 2n

    cout << "Vettore originale: ";
    stampaVettore(vettore);

    counting_sort2n(vettore, vettore.size(), vettore.size() / 2);

    cout << "Vettore ordinato: ";
    stampaVettore(vettore);

    return 0;
}