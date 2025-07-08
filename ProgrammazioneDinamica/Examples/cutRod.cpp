//      |   r0 = 0,             i = 0
// ri = |
//      |   rn = max{pi+rn−i},  1 ≤ i ≤ n

#include <iostream>
#include <vector>
using namespace std;

int top_down_CutRod_rec(vector<int> p, int i, vector<int> r)
{
    if (r[i] < 0)
    {
        int q = -1;
        if (i == 0)
        {
            q = 0;
        }
        else
        {
            q = -1;
            for (int j = 1; j <= i; j++)
            {
                q = max(q, p[j - 1] + top_down_CutRod_rec(p, i - j, r));
            }
        }
        r[i] = q;
    }
    return r[i];
}

int top_down_CutRod(vector<int> p)
{
    int n = p.size();
    vector<int> r(n + 1, -1);
    return top_down_CutRod_rec(p, n, r);
}

int bottom_up_CutRod(const vector<int> &p)
{
    int n = p.size();
    vector<int> r(n + 1, 0);
    r[0] = 0;
    for (int j = 1; j <= n; j++)
    {
        int q = -1;
        for (int i = 1; i <= j; i++)
        {
            q = max(q, p[i - 1] + r[j - i]);
        }
        r[j] = q;
    }
    return r[n];
}

int main()
{
    vector<int> p = {1, 5, 8, 9, 10, 17, 17};
    cout << top_down_CutRod(p) << endl;
    cout << bottom_up_CutRod(p) << endl;
}