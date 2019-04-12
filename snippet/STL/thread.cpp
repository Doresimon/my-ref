#include <iostream>
#include <thread>
#include <string>

using namespace std;

int sayHello()
{
    for (int i = 0; i < 1000; i++)
    {
        cout << "hello!" << endl;
    }

    return 0;
}

int sayGoodbye(string name)
{
    for (int i = 0; i < 1000; i++)
    {
        cout << "goodbye, " << name << endl;
    }
    return 0;
}

int main()
{

    string name = "Alice";
    thread A(sayHello);
    thread B(sayGoodbye, name);

    // cout << "A.ID=" << A.get_id() << endl;
    // cout << "B.ID=" << B.get_id() << endl;

    A.join();
    B.join();

    return 0;
}