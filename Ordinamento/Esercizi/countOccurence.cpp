#include <iostream>
#include <vector>

using namespace std;

int countOccurences(vector<int> v, int p, int r, int k)
{
    if (p < r)
    {
        cout << "p:" << p << " r:" << r << " vp:" << v[p] << " vr:" << v[r] << endl;
        if (k > v[p] || v[r] > k)
            return 0;
        else
        {
            if (v[p] == k && v[r] == k)
            {
                return r - p;
            }
            else
            {
                int q = (p + r) / 2;
                return (v[q] == k) + countOccurences(v, p, q, k) + countOccurences(v, q + 1, r, k);
            }
        }
    }
    return 0;
}

int main()
{
    vector<int> v = {100,100,100,100,100,100,100,100,100,100,100};

    cout << "Count Occ " << countOccurences(v, 0, v.size() - 1, 100) << endl;
}