#include "../Rappresentations/bst.hpp"
using namespace std;

void buildVect(Tree n, vector<int> &simm) // Theta(n)
{
    if (n != nullptr)
    {
        buildVect(n->left, simm);
        simm.push_back(n->key);
        buildVect(n->right, simm);
    }
}

int maxOcc(BST tree) // Theta(n)
{
    vector<int> simm;
    buildVect(tree.root, simm); // Theta(n)

    int maxOcc = 1, maxKey = simm[0], Occ = 1;

    for (int i = 1; i < simm.size(); i++) // Theta(n-1)
    {
        if (simm[i - 1] != simm[i])
        {
            if (maxOcc < Occ)
            {
                maxOcc = Occ;
                maxKey = simm[i - 1];
            }
            Occ = 1;
        }
        else
        {
            Occ++;
        }
    }

    return maxKey;
}
int main()
{
    int arr[] = {1, 2, 2, 7, 7, 8, 55, 55, 55, 60};
    vector<int> vettore(arr, arr + sizeof(arr) / sizeof(arr[0]));
    BST tree = build_bst(vettore);

    tree.tree_display();
}