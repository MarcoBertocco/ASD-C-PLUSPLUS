// Scrivere un algoritmo per individuare, all’interno di una stringa x1 ...xn la lunghezza massima di una
// sottostringa (di caratteri consecutivi) palindroma. Ad esempio, nella stringa colonna la sottostringa
// palindroma di lunghezza massima è olo, dunque la lunghezza massima è 3. Più precisamente:
// a) dare una caratterizzazione ricorsiva della lunghezza massima lung[ i , j ] di una sottostringa palin-
// droma di xi ...xj ;
// b) tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo top-down che
// determina la lunghezza massima;
// c) valutare e giustificare la complessità dell’algoritmo
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int top_down_LPS_rec(string &s, vector<vector<int>> &c, int i, int j)
{
    if (i > j)
        return 0;
    if (i == j)
        return 1;

    if (c[i][j] != -1)
        return c[i][j];
    if (s[i] == s[j])
    {
        int len_inside = j - i - 1;
        int rec = top_down_LPS_rec(s, c, i + 1, j - 1);
        if (rec == len_inside)
            return c[i][j] = 2 + rec;
    }
    return c[i][j] = max(top_down_LPS_rec(s, c, i + 1, j), top_down_LPS_rec(s, c, i, j - 1));
}

int bottom_up_LPS(string s)
{
    int n = s.size();
    if (n == 0)
        return 0;

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int max_len = 1;

    for (int i = 0; i < n; i++)
        dp[i][i] = true;
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == s[i + 1])
        {
            dp[i][i + 1] = true;
            max_len = 2;
        }
    }
    for (int len = 3; len <= n; len++)
    {
        for (int i = 0; i <= n - len; i++)
        {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1])
            {
                dp[i][j] = true;
                max_len = len;
            }
        }
    }

    return max_len;
}
int top_down_LPS(string s)
{
    int n = s.size();
    vector<vector<int>> c(n, vector<int>(n, -1));
    return top_down_LPS_rec(s, c, 0, n - 1);
}
int main()
{

    cout << top_down_LPS("coocking") << endl;
    cout << top_down_LPS("NYAHAHAHAHA") << endl;

    cout << bottom_up_LPS("coocking") << endl;
    cout << bottom_up_LPS("NYAHAHAHAHA") << endl;
}