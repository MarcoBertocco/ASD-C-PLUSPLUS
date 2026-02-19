#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int info;
    Node* next;
};

typedef Node* PNode;

class AdjacentList {
private:
    vector<PNode> list;
    int size;

public:
    // Constructor with number of nodes
    AdjacentList(int n) {
        size = n;
        list.resize(n, nullptr);
    }

    // Insert an edge from 'node' to 'attachedNode'
    void insert(int node, int attachedNode) {
        PNode newNode = new Node{attachedNode, list[node]};
        list[node] = newNode;
    }

    // Display adjacency list
    void display() {
        for (int i = 0; i < size; ++i) {
            cout << i << ": ";
            PNode temp = list[i];
            while (temp != nullptr) {
                cout << temp->info << " -> ";
                temp = temp->next;
            }
            cout << "nullptr" << endl;
        }
    }

    // Destructor to free memory
    ~AdjacentList() {
        for (int i = 0; i < size; ++i) {
            PNode current = list[i];
            while (current != nullptr) {
                PNode next = current->next;
                delete current;
                current = next;
            }
        }
    }
};

int main() {
    int numNodes = 3;
    AdjacentList graph(numNodes);

    graph.insert(0, 1);
    graph.insert(0, 2);
    graph.insert(1, 2);
    graph.insert(2, 0);
    graph.insert(2, 1);

    graph.display();

    return 0;
}