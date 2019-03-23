/**
 * forward_list (Singly Linked List)
 * 
 * Introduced from C++11, forward list 
 * are useful than other containers 
 * in insertion, removal and moving 
 * operations (like sort) and allows 
 * time constant insertion and removal of elements.
 * 
 * It differs from list by the fact that 
 * forward list keeps track of location 
 * of only next element while list keeps 
 * track to both next and previous elements, 
 * thus increasing the storage space required 
 * to store each element. 
 * 
 * Forward List is preferred over list 
 * when only forward traversal is required 
 * (same as singly linked list is preferred 
 * over doubly linked list) as we can save space. 
 * Some example cases are, chaining in hashing, 
 * adjacency list representation of graph, etc.
 * 
 */

#include <iostream>
#include <forward_list>

using namespace std;

void print(forward_list<int> fl)
{
    for (auto &e : fl)
    {
        cout << e << ' ';
    }

    cout << endl;
}

void test_forward_list()
{
    forward_list<int> fl;

    for (int i = 0; i < 16; i++)
    {
        fl.push_front(i); // only push front
    }
    print(fl);

    fl.emplace_front(66);
    print(fl);

    fl.assign(6, 5);
    print(fl);
    fl.assign({1, 2, 3, 4, 5, 6, 7, 8});
    print(fl);

    fl.remove(2);
    print(fl);
    // Removing according to condition.
    fl.remove_if([](int x) { return x % 2 == 0; });
    print(fl);
}

int main()
{
    test_forward_list();
    return 0;
}