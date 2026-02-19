#include <iostream>
#include <vector>
using namespace std;

class IncidenceMatrix {
private:
    vector<vector<int>> matrix;  // [vertices][edges]
    int numVertices;
    int edgeCount;
    bool isDirected;

public:
    // Constructor
    IncidenceMatrix(int vertices, bool directed = true) {
        numVertices = vertices;
        edgeCount = 0;
        isDirected = directed;
    }

    // Insert edge between node and attachedNode
    void insert(int node, int attachedNode) {
        // Add a new column (new edge)
        for (auto& row : matrix) {
            row.push_back(0);
        }

        // If first edge, initialize matrix rows
        if (matrix.empty()) {
            matrix.resize(numVertices, vector<int>(1, 0));
        }

        if (isDirected) {
            matrix[node][edgeCount] = -1;           // from node
            matrix[attachedNode][edgeCount] = 1;    // to attachedNode
        } else {
            matrix[node][edgeCount] = 1;
            matrix[attachedNode][edgeCount] = 1;
        }

        edgeCount++;
    }

    // Display the incidence matrix
    void display() {
        cout << (isDirected ? "Directed" : "Undirected") << " Incidence Matrix:\n";
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < edgeCount; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int numVertices = 3;

    cout << "=== Directed Graph ===" << endl;
    IncidenceMatrix directedGraph(numVertices, true);
    directedGraph.insert(0, 1);
    directedGraph.insert(0, 2);
    directedGraph.insert(1, 2);
    directedGraph.insert(2, 0);
    directedGraph.insert(2, 1);
    directedGraph.display();

    cout << "\n=== Undirected Graph ===" << endl;
    IncidenceMatrix undirectedGraph(numVertices, false);
    undirectedGraph.insert(0, 1);
    undirectedGraph.insert(0, 2);
    undirectedGraph.insert(1, 2);
    undirectedGraph.insert(2, 0);
    undirectedGraph.insert(2, 1);
    undirectedGraph.display();

    return 0;
}
