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

void sort_by_color_merge(vector<ColoredNumber> &A, int left, int mid, int right)
{
    vector<ColoredNumber> temp;
    int i = left, j = mid + 1;

    while (i <= mid && A[i].bw == WHITE)
        temp.push_back(A[i++]);
    while (j <= right && A[j].bw == WHITE)
        temp.push_back(A[j++]);

    while (i <= mid)
        temp.push_back(A[i++]);
    while (j <= right)
        temp.push_back(A[j++]);

    for (int k = 0; k < temp.size(); k++)
        A[left + k] = temp[k];
}

void sort_by_color_merge_sort(vector<ColoredNumber> &A, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    sort_by_color_merge_sort(A, left, mid);
    sort_by_color_merge_sort(A, mid + 1, right);
    sort_by_color_merge(A, left, mid, right);
}

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

    sort_by_color_merge_sort(vettore, 0, vettore.size() - 1);

    cout << "[ ";
    for (const auto &num : vettore)
    {
        cout << num.k << (num.bw == WHITE ? "W " : "B ");
    }
    cout << "]" << endl;
    return 0;
}