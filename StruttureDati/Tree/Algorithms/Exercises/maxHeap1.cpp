#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct Cell
{
    int key;
    Cell *left;
    Cell *right;
    Cell *parent;

    Cell(int k, Cell *p = nullptr, Cell *l = nullptr, Cell *r = nullptr) : key(k), parent(p), left(l), right(r) {};
};
typedef Cell *PNode;

void maxheapifyPNode(PNode i)
{
    PNode max = i;
    PNode l = i->left;
    PNode r = i->right;
    if (l != nullptr && l->key > max->key)
        max = l;
    if (r != nullptr && r->key > max->key)
        max = r;

    if (i != max)
    {
        int c = i->key;
        i->key = max->key;
        max->key = c;
        maxheapifyPNode(max);
    }
}

void maxheapify(vector<int> &A, int i, int heapsize)
{
    int max = i;
    int l = i * 2 + 1;
    int r = i * 2 + 2;

    if (l < heapsize && A[l] > A[max])
        max = l;
    if (r < heapsize && A[r] > A[max])
        max = r;

    if (i != max)
    {
        swap(A[i], A[max]);
        maxheapify(A, max, heapsize);
    }
}

void buildmaxHeap(vector<int> &x)
{
    int heapsize = x.size();
    for (int i = (heapsize / 2); i >= 0; i--)
    {
        maxheapify(x, i, heapsize);
    }
}

PNode buildTreeAux(vector<int> v, int i, PNode parent)
{
    if (i < v.size())
    {
        PNode n = new Cell(v[i]);
        n->parent = parent;
        n->left = buildTreeAux(v, i * 2 + 1, n);
        n->right = buildTreeAux(v, i * 2 + 2, n);
        return n;
    }
    else
        return nullptr;
}

PNode buildTree(vector<int> x)
{
    return buildTreeAux(x, 0, nullptr);
}

vector<int> buildVector(PNode x)
{
    vector<int> xv;

    queue<PNode> q;
    q.push(x);

    while (!q.empty())
    {
        PNode node = q.front();
        q.pop();

        xv.push_back(node->key);

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    return xv;
}

void print_tree(PNode root, int level = 0)
{
    if (root == nullptr)
        return;

    for (int i = 0; i < level; i++)
        std::cout << "  ";

    std::cout << root->key << std::endl;
    print_tree(root->left, level + 1);
    print_tree(root->right, level + 1);
}

PNode unionMaxHeapN(PNode x, PNode y) // unionMaxHeapN T(n)= Theta(n)+Theta(n)+Theta(n) = 3Theta(n) = Theta(n)
{
    vector<int> x1 = buildVector(x), y1 = buildVector(y); // S(n)= Theta(hsX+hsY)=Theta(n/2+n/2)=Theta(n)
    vector<int> z;

    for (auto i : x1)
    { // T(n)= Theta(hsX) = Theta(n/2)
        z.push_back(i);
    }
    for (auto i : y1)
    { // T(n)= Theta(hsY) = Theta(n/2)
        z.push_back(i);
    }
    // build vector z T(n)=Theta(hsX)+Theta(hsY) = Theta(n/2 + n/2) = Theta(n)

    buildmaxHeap(z);     // buildMaxHeap z T(n)=Theta(n)
    return buildTree(z); // buildTree z T(n)=Theta(n)
}

PNode unionMaxHeapLogN(PNode x, PNode y)
{
    PNode temp = x;
    while (temp->right != nullptr)
    {
        temp = temp->right;
    }
    temp->parent->right = nullptr;
    temp->right = x;
    temp->left = y;

    maxheapifyPNode(temp);
    return temp;
}

int main()
{
    vector<int> x = {1, 2, 2, 8, 7, 44, 1};
    vector<int> y = {3, 23, 8, 7, 14, 2, 1};
    buildmaxHeap(x);
    buildmaxHeap(y);

    PNode xp = buildTree(x);
    PNode yp = buildTree(y);
    cout << "\n-------X Tree-------" << endl;
    print_tree(xp);

    cout << "\n-------Y Tree-------" << endl;
    print_tree(yp);

    // UNION n=32, size=O(n), time=O(n);
    cout << "\n------- UNION N Z Tree -------" << endl;
    PNode zp = unionMaxHeapN(xp, yp);
    print_tree(zp);

    // UNION n=32, size=O(1), time=O(logn);
    cout << "\n----- UNION LOG(N) Z Tree ----" << endl;
    PNode zp1 = unionMaxHeapLogN(xp, yp);
    print_tree(zp1);
}