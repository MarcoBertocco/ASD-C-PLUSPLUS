#ifndef MAXPP_HPP
#define MAXPP_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <sstream>

#define NIL nullptr

using namespace std;
class MaxPriorityQueue
{
public:
    MaxPriorityQueue() = default;

    int heapSize() const { return heap.size(); }
    int heapMaximum() const
    {
        if (heap.empty())
            throw std::runtime_error("Heap is empty");
        return heap[0];
    }

    void heapInsert(int key);
    int heapExtract();
    void heapIncreaseKey(size_t i, int key);
    std::string toString() const;

private:
    std::vector<int> heap;

    void maxHeapify(size_t i);
    size_t parent(size_t i) const { return (i - 1) / 2; }
    size_t left(size_t i) const { return 2 * i + 1; }
    size_t right(size_t i) const { return 2 * i + 2; }
};
#endif