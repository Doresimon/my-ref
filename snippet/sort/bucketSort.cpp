#include <iostream>
#include <array>
#include <list>

using namespace std;

class Bucket
{
  public:
    list<float> values;
    void insert(float v);
    void print();
};

void Bucket::insert(float v)
{
    if (values.empty())
    {
        values.push_back(v);
        return;
    }

    auto it = values.begin();
    auto end = values.end();
    while (it != end)
    {
        if (v <= *it)
        {
            values.insert(it, v);
            return;
        }

        it++;
    }

    values.push_back(v);
    return;
}
void Bucket::print()
{
    if (!values.empty())
    {
        auto it = values.begin();
        auto end = values.end();

        while (it != end)
        {
            cout << *it << " ";

            it++;
        }

    }
    cout << endl;
    return;
}
#define N 10

int main()
{
    array<Bucket, N> buckets;

    float arr[N] = {0.3,
                    0.11,
                    0.45,
                    0.12,
                    0.98,
                    0.78,
                    0.66,
                    0.8121321,
                    0.5678,
                    0.00123};

    for (int i = 0; i < N; i++)
    {
        const int key = int(arr[i] * N);
        buckets[key].insert(arr[i]);
    }

    for (int i = 0; i < N; i++)
    {
        buckets[i].print();
    }

    return 0;
}