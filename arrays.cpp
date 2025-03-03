#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

template <class E>
struct record
{
    E info;
    int key;

    record(E info_, int key_) : info(info_), key(key_) {}

    ~record() {}
};

template <class E>
class Dictionary
{
private:
    record<E> *records;
    size_t size;
    size_t capacity;

    void resize(int cap = true)
    {
        if (cap)
        {
            size_t newCapacity = capacity == 0 ? 2 : capacity * 2;
            record<E> *newRecords = (record<E> *)malloc(newCapacity * sizeof(record<E>)); // Allocate memory for new array

            for (size_t i = 0; i < size; i++)
            {
                new (&newRecords[i]) record<E>(records[i].info, records[i].key);
            }
            free(records);
            records = newRecords;
            capacity = newCapacity;
        }
        else
        {
            
            if (size == 0)
            {
                free(records);
                records = nullptr;
                capacity = 0;
                return;
            }

            record<E> *newRecords = (record<E> *)malloc(size * sizeof(record<E>)); // Allocate smaller array

            for (size_t i = 0; i < size; ++i)
            {
                new (&newRecords[i]) record<E>(records[i].info, records[i].key); // Copy records to the new array
            }

            free(records);
            records = newRecords;
            capacity = size;
        }
    }

    int search_index(int key, int p, int r)
    {
        if (r < p)
            return -1; // Key not found, return -1

        int med = (p + r) / 2; // Find the middle index
        if (records[med].key == key)
            return med; // If the key matches, return the index
        else if (records[med].key > key)
            return search_index(key, p, med - 1); // Search in the left half
        else
            return search_index(key, med + 1, r); // Search in the right half
    }

public:
    // Constructor
    Dictionary() : records(nullptr), size(0), capacity(0) {}

    // Destructor
    ~Dictionary()
    {
        for (size_t i = 0; i < size; i++)
        {
            records[i].~record<E>();
        }
        free(records);
    }

    // Insert a new record into the dictionary
    void insert(int key, const E &info)
    {
        size_t i = 0;
        while (i < size && records[i].key < key)
        {
            i++;
        }
        if (i < size && records[i].key == key)
        {
            records[i].info = info;
        }
        else
        {
            resize();
            for (size_t j = size; j > i; --j)
            {
                records[j] = records[j - 1];
            }

            records[i] = record<E>(info, key);
            ++size;
        }
    }

    // Search for a record by its key
    record<E> *search(int key)
    {
        int i = search_index(key, 0, size - 1);
        if (i == -1)
            return nullptr;

        else
            return &records[i];
    }

    // Display all records in the dictionary
    void display() const
    {
        for (size_t i = 0; i < size; ++i)
        {
            cout << "Record " << i + 1 << ": Info = " << records[i].info << ", Key = " << records[i].key << endl;
        }
    }

    // Remove a record by its key
    void remove(int key)
    {
        int i = search_index(key, 0, size - 1);
        for (int j = i; j < size - 1; j++)
            records[j] = records[j + 1];
        resize(false);
        --size;
    }
};

int main()
{
    Dictionary<string> dict;

    // Insert some records into the dictionary
    dict.insert(1, "Hello");
    dict.insert(2, "World");
    dict.insert(3, "C++");

    // Display all records
    cout << "Dictionary records:" << endl;
    dict.display();

    // Search for a record with key 2
    record<string> *found = dict.search(2);
    if (found)
    {
        cout << "Found: Info = " << found->info << ", Key = " << found->key << endl;
    }
    else
    {
        cout << "Not found!" << endl;
    }

    // Remove a record
    dict.remove(2);
    cout << "After removal:" << endl;
    dict.display();
    dict.remove(1);
    cout << "After removal:" << endl;
    dict.display();
    dict.remove(3);
    cout << "After removal:" << endl;
    dict.display();
    return 0;
}
