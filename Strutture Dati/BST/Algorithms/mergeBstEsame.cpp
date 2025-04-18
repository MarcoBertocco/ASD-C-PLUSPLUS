#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
vector<int> mergeBST(const vector<int> &t1, const vector<int> &t2, int val)
{
    int heapsize = t1.size();
    vector<int> t(heapsize * 2 + 1);

    int h = log2(heapsize + 1);

    t[0] = val;

    int x = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < pow(2, i); j++)
        {
            // cout << i << " " << j << " " << x + pow(2, i) << " " << x + pow(2, i) * 2 << endl;
            cout << "Ciao" << endl;
            t[x + pow(2, i)] = t1[x];
            t[x + pow(2, i + 1)] = t2[x];
            x++;
        }
    }
    return t;
}

int main()
{
    int arr1[] = {100, 90, 111, 82, 91, 104, 120};
    vector<int> t1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));

    int arr2[] = {200, 178, 230, 160, 180, 227, 239};
    vector<int> t2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));

    vector<int> t = mergeBST(t1, t2, 150);
    cout << "[";
    for (int i = 0; i < t.size() - 1; i++)
    {
        cout << t[i] << " ";
    }
    cout << t[t.size() - 1] << "]" << endl;
}