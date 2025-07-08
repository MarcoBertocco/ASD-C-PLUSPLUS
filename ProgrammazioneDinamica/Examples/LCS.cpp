//          | 0                                 se i = 0 o j = 0
//          |
// c[i, j] =| c[i − 1, j − 1] + 1               se i, j > 0 e xi = yj
//          |
//          | max {c[i − 1, j], c[i, j − 1]}    se i, j > 0 e xi ̸= yj

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int top_down_LCS_rec(string &X, string &Y, vector<vector<int>> &c, int i, int j)
{
    if (c[i][j] == -1)
    {
        if (i == 0 || j == 0)
            c[i][j] = 0;
        else
        {
            if (X[i] == Y[j])
                c[i][j] = top_down_LCS_rec(X, Y, c, i - 1, j - 1) + 1;
            else
                c[i][j] = max(top_down_LCS_rec(X, Y, c, i - 1, j), top_down_LCS_rec(X, Y, c, i, j - 1));
        }
    }
    return c[i][j];
}

int top_down_LCS(string X, string Y)
{
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> c(m + 1, vector<int>(n + 1, -1));
    return top_down_LCS_rec(X, Y, c, m, n);
}

int bottom_up_LCS(string X, string Y)
{
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
                c[i][j] = c[i - 1][j - 1] + 1;
            else
            {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }
    return c[m - 1][n - 1];
}

int main()
{
    string X = "ACTACCTG";
    string Y = "ATCACCTC";

    cout << top_down_LCS(X, Y) << endl;
    cout << bottom_up_LCS(X, Y) << endl;
}