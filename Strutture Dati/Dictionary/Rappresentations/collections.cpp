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
    record<E> *prev;
    record<E> *next;

    record() : info(), key(0), prev(NIL), next(NIL) {}

    record(const E &info_, int key_) : info(info_), key(key_), prev(NIL), next(NIL) {}

    ~record() {}
};
template <class E>
class Dictionary
{
private:
    record<E> *head;

public:
    // Constructor
    Dictionary() : head(NIL) {}

    // Destructor
    ~Dictionary()
    {
        record<E> *current = head;
        while (current != NIL)
        {
            record<E> *temp = current;
            current = current->next;
            delete temp; // Free memory
        }
        head = NIL;
    }

    void insert(E info, int key)
    {
        record<E> *p = new record<E>(info, key); // Create new node
        p->next = head;
        if (head != NIL)
            head->prev = p;
        p->prev = NIL;
        head = p;
    }

    E search(int key) const
    {
        record<E> *x = head;
        while (x != NIL && x->key != key)
            x = x->next;
        return x->info;
    }

    void remove(int k)
    {
        record<E> *x = head;
        while (x != NIL)
        {
            if (x->key == k)
            {
                if (x->next != NIL)
                    x->next->prev = x->prev;
                if (x->prev != NIL)
                    x->prev->next = x->next;
                else
                    head = x->next;

                record<E> *temp = x;
                x = x->next;
                delete temp;
            }
            else
                x = x->next;
        }
    }

    void display() const
    {
        if (head == NIL) {
            cout << "Dictionary is empty" << endl;
            return;
        }

        record<E>* current = head;
        cout << "Dictionary Records" << endl;
        cout << "KEY\tINFO" << endl;
        while (current != NIL) {
            cout << current->key << "\t" << current->info << endl;
            current = current->next;
        }
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

    global_dict.insert(info,key);
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
    cout << "Info"<< info << endl;
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
    /*Dictionary<string> dict;
    dict.insert("Alice", 1);
    dict.insert("Bob", 2);
    dict.insert("Charlie", 3);

    dict.display();

    cout<< dict.search(3)<<endl;
    cout<< dict.search(1)<<endl;

    dict.remove(3);
    dict.display();

    cout << "Deleting dictionary..." << endl;
    */
    menu();
    return 0;
}