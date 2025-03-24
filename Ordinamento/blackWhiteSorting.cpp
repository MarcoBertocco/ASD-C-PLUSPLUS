#include <iostream>
#include <vector>
using namespace std;

enum Color
{
    WHITE,
    BLACK
};

struct ColoredNumber
{
    int k;
    Color bw;

    ColoredNumber(int _k) : k(_k), bw(WHITE) {}
    ColoredNumber(int _k, Color _color) : k(_k), bw(_color) {}
};

void sortbyColor(vector<ColoredNumber> &A)
{
    int j = 0;
    for (int i = 0; i < A.size(); i++)
    {
        if (j == i && A[j].bw == WHITE)
        {
            j++;
        }
        else
        {
            if (j < i && A[i].bw == WHITE)
            {
                // ColoredNumber tmp = A[i];
                //  shift a dx gli elementi
                // inserisco in A[j] A[i]
                for (int x = i; x > j; x--)
                {
                    swap(A[x], A[x - 1]);
                }
                j++;
            }
        }
    }
}

int main()
{
    vector<ColoredNumber> vettore = {
        {1, BLACK}, {2, WHITE}, {3, BLACK}, {4, BLACK}, {5, WHITE}, {6, BLACK}, {7, WHITE}, {8, WHITE}, {9, BLACK}};

    cout << "[ ";
    for (const auto &num : vettore)
    {
        cout << num.k << (num.bw == WHITE ? "W " : "B ");
    }
    cout << "]" << endl;

    sortbyColor(vettore);

        cout << "[ ";
    for (const auto &num : vettore)
    {
        cout << num.k << (num.bw == WHITE ? "W " : "B ");
    }
    cout << "]" << endl;
    return 0;
}