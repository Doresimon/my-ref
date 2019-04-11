#include <iostream>
#include <map>

using namespace std;

class Balance
{
  private:
    /* data */
    map<string, int> mm;

  public:
    Balance(/* args */);
    ~Balance();
    int setAccount(string name, int value);
    int eraseAccount(string name);
    int getBalance(string name);
    int getBalances();
};

Balance::Balance(/* args */)
{
}

Balance::~Balance()
{
}

int Balance::setAccount(string name, int value)
{

    auto it = this->mm.find(name);
    if (it == this->mm.end())
        this->mm.insert(pair<string, int>(name, value));
    else
        this->mm.at(name) = value;

    return 0;
}
int Balance::eraseAccount(string name)
{

    auto it = this->mm.find(name);
    if (it != this->mm.end())
        this->mm.erase(name);

    return 0;
}

int Balance::getBalance(string name)
{
    // find if a key is existed.
    auto it = this->mm.find(name);
    if (it != this->mm.end())
        return this->mm.at(name);

    return -1;
}
int Balance::getBalances()
{
    // find if a key is existed.
    map<string, int>::iterator it;
    for (it = this->mm.begin(); it != this->mm.end(); it++)
    {
        cout << it->first << " = " << it->second << endl;
    }

    return -1;
}

int main()
{
    Balance B = Balance();
    B.setAccount("alice", 10);
    B.setAccount("bob", 100);
    B.setAccount("bob", 66);

    B.getBalances();

    cout << B.getBalance("alice") << endl;
    cout << B.getBalance("coco") << endl;
    cout << B.getBalance("bob") << endl;
    B.eraseAccount("bob");
    cout << B.getBalance("bob") << endl;

    return 0;
}
