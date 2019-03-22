# C++

## tips

### 引用

引用变量是一个别名，也就是说，它是某个已存在变量的另一个名字。一旦把引用初始化为某个变量，就可以使用该引用名称或变量名称来指向变量。

### C++ 引用 vs 指针

引用很容易与指针混淆，它们之间有三个主要的不同：

- 不存在空引用。引用必须连接到一块合法的内存。
- 一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
- 引用必须在创建时被初始化。指针可以在任何时间被初始化。

引用通常用于函数参数列表和函数返回值。

C++之所以增加引用类型， 主要是把它作为函数参数，以扩充函数传递数据的功能。

C++ 函数传参：

1. 将变量名作为实参和形参。这时传给形参的是变量的值，传递是单向的。如果在执行函数期间形参的值发生变化，并不传回给实参。因为在调用函数时，形参和实参不是同一个存储单元。// 同 c

2. 传递变量的指针。形参是指针变量，实参是一个变量的地址，调用函数时，形参(指针变量)指向实参变量单元。这种通过形参指针可以改变实参的值。// 同 c

3. C++提供了 传递变量的引用。形参是引用变量，和实参是一个变量，调用函数时，形参(引用变量)指向实参变量单元。这种通过形参引用可以改变实参的值

## `STL`(Standrad Template Library)

- Algorithms
  - Sorting
  - Searching
  - Important STL Algorithms
  - Useful Array algorithms
  - Partition Operations
- Containers
  - Sequence Containers
    - `vector`
    - `list`
    - `deque`
    - `arrays`
    - `forward_list`
  - Container Adaptors
    - `queue`
    - `priority_queue`
    - `stack`
  - Associative Containers
    - `set`
    - `multiset`
    - `map`
    - `multimap`
  - Unordered Associative Containers
    - `unordered_set`
    - `unordered_multiset`
    - `unordered_map`
    - `unordered_multimap`
- Functions
  - Functors
- Iterators
  - Iterators

### vector

Vectors are same as **dynamic arrays** with the ability to **resize itself automatically** when an element is inserted or deleted, with their storage being handled automatically by the container.

Vector elements are **placed in contiguous storage** so that they can be accessed and traversed using iterators.

**Inserting at the end** takes differential time, as sometimes there may be a need of extending the array. **Removing** the last element takes only **constant time** because no resizing happens. **Inserting and erasing at the beginning or in the middle** is **linear in time**.

[http://www.cplusplus.com/reference/vector/vector/](http://www.cplusplus.com/reference/vector/vector/)
