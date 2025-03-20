#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;
#define NIL nullptr

template <class E>
struct record
{
    E info;
    int key;

    record() : info(), key(0) {}

    record(const E &info_, int key_) : info(info_), key(key_) {}

    ~record() {}
};

template <typename E>
using dict = record<E>*;

template <class E>
class Dictionary
{
private:
    dict<E> records;
    size_t size;
    size_t capacity;

    void resize(bool increase = true)
    {
        size_t newCapacity = increase ? (capacity == 0 ? 2 : capacity * 2) : (size > 0 ? size : 1);
        dict<E>newRecords = new record<E>[newCapacity]; // Use `new` instead of `malloc`

        for (size_t i = 0; i < size; i++)
        {
            newRecords[i] = records[i]; // Copy objects properly
        }

        delete[] records; // Free old memory
        records = newRecords;
        capacity = newCapacity;
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
    Dictionary() : records(NIL), size(0), capacity(0) {}

    // Destructor
    ~Dictionary()
    {
        delete[] records;
    }

    void insert(E info, int key)
    {
        if (size == capacity)
        {
            resize(true);
        }

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
            for (size_t j = size; j > i; --j)
            {
                records[j] = records[j - 1];
            }

            records[i] = record<E>(info, key);
            ++size;
        }
    }

    E search(int key)
    {
        int i = search_index(key, 0, size - 1);
        return (i == -1) ? NIL : records[i]->info;
    }

    void display() const
    {
        if (size == 0)
        {
            cout << "Dictionary is empty.\n";
            return;
        }

        for (size_t i = 0; i < size; ++i)
        {
            cout << "Record " << i + 1 << ": Info = " << records[i].info << ", Key = " << records[i].key << endl;
        }
    }

    void remove(int key)
    {
        int i = search_index(key, 0, size - 1);
        for (int j = i; j < size - 1; j++)
            records[j] = records[j + 1];
        --size;

        if (size < capacity / 2)
            resize(false);
    }
};

Dictionary<string> global_dict;

void menu_pretty_print()
{
    system("clear");
    cout << "Menu: " << endl;
    cout << "a) Insert a Record " << endl;
    cout << "b) Delete a Record " << endl;
    cout << "c) Find a Record " << endl;
    cout << "d) Print the Dictionary " << endl;
    cout << "q) Quit" << endl;
}
/*
Enum {integerNumber, longDoubleNumber, doubleNumber, floatNumber, character}

template E;
bool validate_input(string s, enum x){
    return s is convertable to x
    where convertable is to read the string and see if it could be converted
}
*/
bool validate_input(string s)
{
    int i = 0;
    while (i < s.length())
    {
        if (s.at(i) < '0' || s.at(i) > '9')
            return false;
        i++;
    }

    return true;
}
void menu_insert_input()
{
    int key = 0;
    string info;
    string input;
    do
    {
        system("clear");
        cout << "OPTION: Insert a Record" << endl;
        cout << "Insert the Key Value: ";
        cin >> input; // Read input as a string
    } while (!validate_input(input));

    key = stoi(input);
    cin.ignore();

    cout << "Insert the Info Value: ";
    getline(cin, info);

    global_dict.insert(info, key);
}
void menu_insert_option()
{
    menu_insert_input();
}
void menu_delete_input()
{
    int key = 0;
    string input = "";
    do
    {
        system("clear");
        cout << "OPTION: Delete a Record" << endl;
        cout << "Insert the Key Value: ";
        cin >> input;
    } while (!validate_input(input));

    key = stoi(input);

    global_dict.remove(key);
}
void menu_delete_option()
{
    menu_delete_input();
}
string menu_find_input()
{
    int key = 0;
    string input = "";
    do
    {
        system("clear");
        cout << "OPTION: Find a Record" << endl;
        cout << "Insert the Key Value: ";
        cin >> input;
    } while (!validate_input(input));

    key = stoi(input);

    return global_dict.search(key);
}
void menu_find_option()
{
    string info = menu_find_input();
    cout << "Info" << info << endl;
    string x;
    cin >> x;
}
void menu_print_option()
{
    string x;
    system("clear");
    cout << "OPTION: Print the Dictionary" << endl;
    global_dict.display();
    cin >> x;
}
bool menu_selection(char s)
{
    switch (s)
    {
    case 'a':
    {
        system("clear");
        menu_insert_option();
        break;
    }
    case 'b':
    {
        system("clear");
        menu_delete_option();
        break;
    }
    case 'c':
    {
        system("clear");
        menu_find_option();
        break;
    }
    case 'd':
    {
        system("clear");
        menu_print_option();
        break;
    }
    case 'q':
    {
        return false;
        break;
    }
    }
    return true;
}
char menu_input()
{
    char c = 'e';
    string inputs = "abcdq";
    do
    {
        menu_pretty_print();
        string input = "";
        cout << "Insert an option ";
        cin >> input;
        c = input[0];
    } while (inputs.find(c) == string::npos);
    return c;
}
void menu()
{
    bool quit = true;
    do
    {
        quit = menu_selection(menu_input());
    } while (quit);
    system("clear");
    return;
}

int main()
{
    /*
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
    */

    menu();
    return 0;
}
