/**
 * list (Doubly Linked List)
 * 
 * Lists are sequence containers that allow non-contiguous memory allocation. 
 * As compared to vector, list has slow traversal, 
 * but once a position has been found, insertion and deletion are quick.
 * 
 * 
 */

#include <iostream>
#include <list>

using namespace std;

void print(list<int> l)
{
    list<int>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    {
        cout << '\t' << *it;
    }
    cout << endl;
}

void test_list()
{
    list<int> l;

    for (int i = 0; i < 16; i++)
    {
        l.push_back(i);
    }
    print(l);
}

int main()
{
    test_list();
    return 0;
}