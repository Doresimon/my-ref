/**
 * queue(FIFO: First-In First-Out)
 * 
 * elements are inserted into one end 
 * of the container and extracted from the other.
 * 
 * Member Functions
 * .empty()
 * .size()
 * .front()
 * .back()
 * .push_back()
 * .pop_front()
 * 
 */

#include <iostream>
#include <queue>

using namespace std;

void print(queue<int> que)
{
    queue<int> g = que;
    while (!g.empty())
    {
        cout << g.front() << " ";
        g.pop();
    }
    cout << endl;
    return;
}

void test_queue()
{
    queue<int> que;
    cout << "size=" << que.size() << endl;

    for (int i = 0; i < 16; i++)
    {
        que.push(i);
    }
    print(que);
    cout << "size=" << que.size() << endl;

    que.pop();
    print(que);
    cout << "size=" << que.size() << endl;
}

int main()
{
    test_queue();

    return 0;
}