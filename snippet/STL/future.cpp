// future example
#include <iostream> // std::cout
#include <future>   // std::async, std::future
#include <chrono>   // std::chrono::milliseconds

// a non-optimized way of checking for prime numbers:
bool is_prime(int x)
{

    int half = x / 2 + 1;

    for (int i = 2; i < half; ++i)
        if (x % i == 0)
            return false;
    return true;
}

int countPrime(int bound)
{
    int cnt = 0;

    for (size_t i = 2; i < bound; i++)
    {
        if (is_prime(i))
            cnt++;
    }

    return cnt;
}

int main()
{
    // call function asynchronously:

    int bound = 500000;

    std::future<int> fut = std::async(countPrime, bound);

    // do something while waiting for function to set future:
    std::cout << "checking, please wait";
    std::chrono::milliseconds span(1000);
    while (fut.wait_for(span) == std::future_status::timeout)
        std::cout << '.' << std::flush;

    int x = fut.get(); // retrieve return value

    std::cout << "\n";
    std::cout << "count of primes less than " << bound << " is " << x << "\n";

    return 0;
}