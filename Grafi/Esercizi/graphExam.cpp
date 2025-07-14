#include <iostream>
#include <vector>
using namespace std;
//Fuck this exam

bool MyFunction(vector<int> S, int i, vector<vector<int>> A)
{
    for (auto j : S)
    {
        if (A[i][j] > 0)
            return false;
    }
    return true;
}

vector<int> MyAlgorithm(vector<vector<int>> A)
{
    int n = A.size();
    vector<int> S;
    for (int i = 0; i < 5; i++)
    {
        if (MyFunction(S, i, A))
            S.push_back(i);
    }
    return S;
}

int main()
{
    vector<vector<int>> adiacentMat = {{0, 0, 0, 0, 0, 1},
                                       {0, 0, 0, 1, 1, 1},
                                       {0, 0, 0, 0, 1, 1},
                                       {0, 0, 1, 0, 0, 1},
                                       {0, 1, 1, 0, 0, 0},
                                       {1, 1, 1, 1, 0, 0}};

    cout << "\t1\t2\t3\t4\t5\t6" << endl;
    int c = 1;
    for (auto x : adiacentMat)
    {
        cout << c++;
        for (auto y : x)
        {
            cout << "\t" << y;
        }
        cout << endl;
    }
    vector<int> S = MyAlgorithm(adiacentMat);

    cout << " S = { ";
    for (auto j : S)
    {
        cout << j + 1 << " ";
    }
    cout << "}" << endl;
}