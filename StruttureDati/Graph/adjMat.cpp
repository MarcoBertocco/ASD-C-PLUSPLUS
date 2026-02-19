#include <iostream>
#include <vector>
using namespace std;

class AdjacentMatrix {
private:
    vector<vector<int>> matrix;
    int size;

public:
    // Constructor with number of nodes
    AdjacentMatrix(int n) {
        size = n;
        matrix.resize(size, vector<int>(size, 0)); // Initialize with 0s
    }

    // Insert an edge from 'node' to 'attachedNode'
    void insert(int node, int attachedNode) {
        if (node >= 0 && node < size && attachedNode >= 0 && attachedNode < size)
            matrix[node][attachedNode] = 1;
    }

    // Display the adjacency matrix
    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int numNodes = 3;
    AdjacentMatrix graph(numNodes);

    graph.insert(0, 1);
    graph.insert(0, 2);
    graph.insert(1, 2);
    graph.insert(2, 0);
    graph.insert(2, 1);

    graph.display();

    return 0;
}
