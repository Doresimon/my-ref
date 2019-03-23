/**
 * deque(Double End Queue)
 * 
 * http://www.cplusplus.com/reference/deque/deque/
 * 
 * deque (usually pronounced like "deck") 
 * is an irregular acronym of double-ended queue. 
 * Double-ended queues are sequence containers 
 * with dynamic sizes that can be expanded or 
 * contracted on both ends (either its front or its back).
 * 
 * !!!
 * But, unlike vectors, deques are not guaranteed to 
 * store all its elements in contiguous storage locations: 
 * accessing elements in a deque by offsetting a pointer 
 * to another element causes undefined behavior.
 * 
 * Member functions
 * (constructor)    * Construct deque container (public member function )
 * (destructor)     * Deque destructor (public member function )
 * operator=        * Assign content (public member function )
 * 
 * Iterators:
 * begin    * Return iterator to beginning (public member function )
 * end      * Return iterator to end (public member function )
 * rbegin   * Return reverse iterator to reverse beginning (public member function )
 * rend     * Return reverse iterator to reverse end (public member function )
 * cbegin   * Return const_iterator to beginning (public member function )
 * cend     * Return const_iterator to end (public member function )
 * crbegin  * Return const_reverse_iterator to reverse beginning (public member function )
 * crend    * Return const_reverse_iterator to reverse end (public member function )
 * 
 * Capacity:
 * size             * Return size (public member function )
 * max_size         * Return maximum size (public member function )
 * resize           * Change size (public member function )
 * empty            * Test whether container is empty (public member function )
 * shrink_to_fit    * Shrink to fit (public member function )
 * 
 * Element access:
 * operator[]   * Access element (public member function )
 * at           * Access element (public member function )
 * front        * Access first element (public member function )
 * back         * Access last element (public member function )
 * 
 * Modifiers:
 * assign       * Assign container content (public member function )
 * push_back    * Add element at the end (public member function )
 * push_front   * Insert element at beginning (public member function )
 * pop_back     * Delete last element (public member function )
 * pop_front    * Delete first element (public member function )
 * insert       * Insert elements (public member function )
 * erase        * Erase elements (public member function )
 * swap         * Swap content (public member function )
 * clear        * Clear content (public member function )
 * emplace      * Construct and insert element (public member function )
 * emplace_front    * Construct and insert element at beginning (public member function )
 * emplace_back     * Construct and insert element at the end (public member function )
 * 
 * 
 */

#include <iostream>
#include <deque>

using namespace std;

void print(deque<int> deq)
{
    for (auto i = deq.begin(); i < deq.end(); i++)
    {
        cout << *i << ' ';
    }
    cout << endl;
}

int test_deque()
{
    deque<int> deq;

    // push an element at the end/back
    for (int i = 1; i <= 16; i++)
    {
        deq.push_back(i);
    }
    cout << "push_back()" << endl;
    print(deq);

    // pop an element at the end
    // @return void
    deq.pop_back();
    cout << "pop_back()" << endl;
    print(deq);

    // return an iterator(pointer) of first element
    auto i = deq.begin();

    // insert, use iterator
    deq.insert(i, 0);
    // deq.emplace(i, 0);
    cout << "insert(i, 0)" << endl;
    print(deq);

    // *.end()
    // get the last element's next pointer

    cout << "end() to begin()" << endl;
    for (auto i = deq.end() - 1; i >= deq.begin(); i--)
    {
        cout << *i << ' ';
    }
    cout << endl;

    // read an element at position i
    cout << ".[3]\t\t" << deq[3] << endl;
    cout << ".at(4)\t\t" << deq.at(4) << endl;
    // read the first element
    cout << ".front()\t" << deq.front() << endl;
    // read the last element
    cout << ".end()\t\t" << deq.back() << endl;

    // get the size
    cout << ".size()\t\t" << deq.size() << endl;
    // get the max size
    cout << ".max_size()\t" << deq.max_size() << endl;

    // reset the size, from the begin() iterator.
    cout << ".resize(10)\t" << endl;
    deq.resize(10);
    print(deq);

    // check is empty
    cout << ".empty()\t" << deq.empty() << endl;
}

int main()
{
    test_deque();
    return 0;
}