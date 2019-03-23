/**
 * array (wrapper of c-style array)
 * 
 * 1. Array classes knows its own size, 
 * whereas C-style arrays lack this property. 
 * So when passing to functions, we don’t 
 * need to pass size of Array as a separate parameter.
 * 
 * 2. With C-style array there is more risk 
 * of array being decayed into a pointer. 
 * Array classes don’t decay into pointers
 * 
 * 3. Array classes are generally more efficient, 
 * light-weight and reliable than C-style arrays.
 * 
 * Member Functions
 * .at()        - read an element
 * .get()       - read an element
 * operator[]   - read an element
 * .front()     - first element
 * .back()      - last element
 * 
 * .size()
 * .max_size()  - equal to .size()
 * 
 * .swap()      - swap two array's content
 * .empty()     - return if array is empty(size == 0)
 * .fill()      - fill the whole array with a value
 * 
 * Tips:
 * - if array is uninitialized, the values is undetermined, not zero(0).
 * 
 */

#include <iostream>
#include <array>

using namespace std;

void print(array<int, 16> arr)
{
    for (auto &e : arr)
    {
        cout << e << ' ';
    }

    cout << endl;
}

void test_array()
{
    array<int, 16> arr;

    print(arr);
    cout << ".empty() = " << arr.empty() << endl;

    arr.fill(0);
    print(arr);

    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = i;
    }
    print(arr);

    arr.fill(6);
    print(arr);

    cout << ".empty() = " << arr.empty() << endl;
}

int main()
{
    test_array();
    return 0;
}