#include <iostream>

using namespace std;

int f(int &x, int c)
{
    c = c - 1;
    if (c == 0)
        return 1;
    x = x + 1;
    return f(x, c) * x;
}

int swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
    return 0;
}

int increase(int &x)
{
    x++;
    return x;
}

int main()
{
    int p = 5;
    // cout << f(p, p) << endl;
    cout << increase(p) * p << endl; // notice the p will increase first, then  multiplied.
}