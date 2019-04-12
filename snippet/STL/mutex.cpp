#include <iostream>
#include <thread>
#include <string>
#include <mutex>

using namespace std;

mutex mtx;

int line(char x)
{
    mtx.lock();
    for (int i = 0; i < 32; i++)
    {
        cout << x;
    }
    cout << endl;
    mtx.unlock();
    return 0;
}

int main()
{

    thread A(line, '#');
    thread B(line, '*');

    // cout << "A.ID=" << A.get_id() << endl;
    // cout << "B.ID=" << B.get_id() << endl;

    A.join();
    B.join();

    return 0;
}