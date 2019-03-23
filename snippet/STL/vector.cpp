/**
 * vector(Dynamic Array)
 * 
 * Iterators
 * Capacity
 * Element access
 * Modifiers
 * 
 * 
 * Vector elements are placed in contiguous storage 
 * so that they can be accessed and traversed using iterators. 
 * 
 * 
 * 
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> v)
{
    for (auto i = v.begin(); i < v.end(); i++)
    {
        cout << *i << ' ';
    }
    cout << endl;
}

int test_vector()
{
    // new empty vector
    vector<int> v_int;

    // push an element at the end
    for (int i = 1; i <= 16; i++)
    {
        v_int.push_back(i);
    }
    cout << "push_back()" << endl;
    print(v_int);

    // pop an element at the end
    // @return void
    v_int.pop_back();
    cout << "pop_back()" << endl;
    print(v_int);

    // return an iterator(pointer) of first element
    auto i = v_int.begin();

    // insert, use iterator
    v_int.insert(i, 0);
    // v_int.emplace(i, 0);
    cout << "insert(i, 0)" << endl;
    print(v_int);

    // *.end()
    // get the last element's next pointer

    cout << "end() to begin()" << endl;
    for (auto i = v_int.end() - 1; i >= v_int.begin(); i--)
    {
        cout << *i << ' ';
    }
    cout << endl;

    // read an element at position i
    cout << ".[3]\t\t" << v_int[3] << endl;
    cout << ".at(4)\t\t" << v_int.at(4) << endl;
    // read the first element
    cout << ".front()\t" << v_int.front() << endl;
    // read the last element
    cout << ".end()\t\t" << v_int.back() << endl;

    // get the size
    cout << ".size()\t\t" << v_int.size() << endl;
    // get the max size
    cout << ".max_size()\t" << v_int.max_size() << endl;
    // get the  capacity(more than size)
    // capacity can enlarged automatically, exp of 2
    // eg: 1, 2, 4, 8, 16 ... 2^n
    cout << ".capacity\t" << v_int.capacity() << endl;

    // reset the size, from the begin() iterator.
    cout << ".resize(10)\t" << endl;
    v_int.resize(10);
    print(v_int);

    // check is empty
    cout << ".empty()\t" << v_int.empty() << endl;
}

int main()
{
    test_vector();
    return 0;
}