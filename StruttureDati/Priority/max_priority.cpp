#include "max_priority.hpp"

void MaxPriorityQueue::heapIncreaseKey(size_t i, int key)
{
    if (i >= heap.size())
        throw std::out_of_range("Index out of range");
    if (key < heap[i])
        throw std::invalid_argument("New key is smaller than current key");

    heap[i] = key;
    while (i > 0 && heap[parent(i)] < heap[i])
    {
        std::swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void MaxPriorityQueue::heapInsert(int key)
{
    heap.push_back(-INFINITY);
    heapIncreaseKey(heap.size() - 1, key);
}

int MaxPriorityQueue::heapExtract()
{
    if (heap.empty())
        throw std::runtime_error("Heap underflow");
    int max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty())
        maxHeapify(0);
    return max;
}

void MaxPriorityQueue::maxHeapify(size_t i)
{
    size_t l = left(i), r = right(i);
    size_t largest = i;

    if (l < heap.size() && heap[l] > heap[largest])
        largest = l;
    if (r < heap.size() && heap[r] > heap[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(heap[i], heap[largest]);
        maxHeapify(largest);
    }
}

std::string MaxPriorityQueue::toString() const
{
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < heap.size(); ++i)
    {
        oss << heap[i];
        if (i < heap.size() - 1)
            oss << ", ";
    }
    oss << "]";
    return oss.str();
}