// Realizzare una funzione efficiente triplo che, dato un array A di n interi, verifica se esiste una coppia di
// indici i, j tali che A[j] = 3 A[i]. Restituisce 1 e i corrispondenti indici se la coppia esiste, 0 altrimenti.
// Analizzare la complessità e scrivere le eventuali funzioni/procedure ausiliarie utilizzate.

#include <vector>
#include <iostream>
#include <string>
using namespace std;

#define Near_infinite 2147483647

void merge(vector<pair<int, int>> &A, int p, int q, int r) // O(n)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<pair<int, int>> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) // O(n1)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++) // O(n2)
        R[j] = A[q + j + 1];

    L[n1] = {Near_infinite, -1};
    R[n2] = {Near_infinite, -1};

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
void merge_sort(vector<pair<int, int>> &A, int p, int r) // 2T(n/2) + O(n) -> O(nlog(n))
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r); // O(n)
    }
}

int binary_search(const vector<pair<int, int>> &v, int p, int r, int x)
{
    if (p > r)
        return -1;
    int mid = (p + r) / 2;
    if (v[mid].first == x)
        return mid;
    else if (v[mid].first < x)
        return binary_search(v, mid + 1, r, x);
    else
        return binary_search(v, p, mid - 1, x);
}

bool triplo(const vector<int> &A, pair<int, int> &c)
{
    int n = A.size();
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++)
        v.push_back({A[i], i});

    merge_sort(v, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        int triple = 3 * v[i].first;
        int idx = binary_search(v, 0, n - 1, triple);
        if (idx != -1 && v[i].second != v[idx].second)
        {
            c = {v[i].second, v[idx].second};
            return true;
        }
    }

    return false;
}

int main()
{
    pair<int, int> couple = {-1, -1};
    vector<int> v1 = {24, 26, 23, 13, 55, 33, 4};
    vector<int> v2 = {72, 42, 64, 12, 23, 35, 46, 4};

    if (triplo(v1, couple))
        cout << v1[couple.first] << "," << v1[couple.second] << endl;
    else
        cout << "NotFound" << endl;

    couple = {-1, -1};
    if (triplo(v2, couple))
        cout << v2[couple.first] << "," << v2[couple.second] << endl;
    else
        cout << "NotFound" << endl;
}
