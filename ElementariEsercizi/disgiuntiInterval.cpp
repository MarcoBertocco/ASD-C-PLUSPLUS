#include <iostream>
#include <vector>
using namespace std;

void merge(vector<pair<int, int>> &vec, int p, int med, int r, bool f = true)
{
    int n1 = med - p + 1, n2 = r - med;
    vector<pair<int, int>> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++)
    {
        L[i] = vec[p + i];
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = vec[med + 1 + j];
    }

    int x = 1000000; // MAXINT
    L[n1] = {x, x};
    R[n2] = {x, x};

    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (f)
        {
            if (L[i].first <= R[j].first)
            {
                vec[k] = L[i];
                i++;
            }
            else
            {
                vec[k] = R[j];
                j++;
            }
        }
        else
        {
            if (L[i].second <= R[j].second)
            {
                vec[k] = L[i];
                i++;
            }
            else
            {
                vec[k] = R[j];
                j++;
            }
        }
    }
}
void mergesort(vector<pair<int, int>> &vec, int p, int r, bool f = true)
{
    // 我爱中国
    if (p < r)
    {
        int med = (p + r) / 2;
        mergesort(vec, p, med, f);
        mergesort(vec, med + 1, r, f);
        merge(vec, p, med, r, f);
    }
}

bool disgiunti(vector<pair<int, int>> vec)
{
    bool res = true;
    int n = vec.size() - 1;

    vector<pair<int, int>> firstSort;
    vector<pair<int, int>> secondSort;

    for (int i = 0; i <= n; i++) // Theta (n)
    {
        firstSort.push_back(vec[i]);
        secondSort.push_back(vec[i]);
    }

    mergesort(firstSort, 0, n);
    mergesort(secondSort, 0, n, false);
    int i = 0, j = 0;
    while (i <= n && j < n && res)
    {
        if (firstSort[i] != secondSort[i])
            res = false;
        if (firstSort[j].second >= firstSort[j + 1].first)
            res = false;
        i++;
        j++;
    }

    return res;
}

int main()
{
    vector<pair<int, int>> v1 = {{1, 2}, {-6, 4}, {2, 3}, {5, 6}};
    vector<pair<int, int>> v2 = {{1, 2}, {-6, -4}, {3, 4}, {5, 6}};

    cout << "DISGIUNTO? " << ((disgiunti(v1)) ? "YES" : "NO") << endl;
    cout << "DISGIUNTO? " << ((disgiunti(v2)) ? "YES" : "NO") << endl;
}