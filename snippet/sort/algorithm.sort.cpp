/**
 * compared with js.array.sort()
 * 
 * C++ sort function uses introsort which is a hybrid algorithm. 
 * Different implementations use different algorithms. 
 * The GNU Standard C++ library, for example, 
 * uses a 3-part hybrid sorting algorithm: 
 * introsort is performed first 
 * (introsort itself being a hybrid of quicksort and heap sort) 
 * followed by an insertion sort on the result.
 * 
 * The new C++11 standard requires that the complexity 
 * of sort to be O(Nlog(N)) in the worst case.
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int asc(int x, int y)
{
    return x < y;
}
int desc(int x, int y)
{
    return x > y;
}

void printVector(const vector<int> &arr)
{
    auto it = arr.begin();
    auto end = arr.end();

    std::cout << "[";
    while (it != end)
    {
        cout << *it << " ";

        it++;
    }
    std::cout << "]" << endl;
    return;
}

class Node
{
  public:
    int v; // value
    int i; // index
    static int cnt;

    Node(int v);
    static void printCnt();
    static void printVector(const vector<Node> &V);
    static int asc(const Node &x, const Node &y);
    static int desc(const Node &x, const Node &y);
};
int Node::cnt = 0;

Node::Node(int v)
{
    this->v = v;
    this->i = Node::cnt;
    Node::cnt++;
}

void Node::printCnt()
{
    cout << "Node.cnt = " << Node::cnt << endl;
    return;
}
void Node::printVector(const vector<Node> &V)
{
    auto it = V.begin();
    auto end = V.end();

    std::cout << "[";
    while (it != end)
    {
        cout << (*it).v << " ";
        it++;
    }
    std::cout << "]" << endl;
    return;
}
int Node::asc(const Node &x, const Node &y)
{
    return x.v - y.v;
}
int Node::desc(const Node &x, const Node &y)
{
    return y.v - x.v;
}

int main()
{

    int arr[] = {11, 77, 66, 33, 22, 55, 44, 88, 99, 0};

    vector<int> ARR = vector<int>(arr, arr + sizeof(arr) / sizeof(int));
    printVector(ARR);

    //range = [begin, end)
    std::sort(ARR.begin(), ARR.end());       // default is ascending
    std::sort(ARR.begin(), ARR.end(), asc);  // self defined ascending
    std::sort(ARR.begin(), ARR.end(), desc); // self defined descending
    printVector(ARR);

    vector<Node> ARR_Node;
    for (auto it = ARR.begin(); it != ARR.end(); it++)
    {
        ARR_Node.push_back(Node(*it));
    }
    Node::printCnt();
    Node::printVector(ARR_Node);

    std::sort(ARR_Node.begin(), ARR_Node.end(), Node::asc);
    Node::printVector(ARR_Node);
    Node::printCnt();
    std::sort(ARR_Node.begin(), ARR_Node.end(), Node::desc);
    Node::printVector(ARR_Node);
    Node::printCnt();

    return 0;
}