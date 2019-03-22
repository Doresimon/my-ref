#include <iostream>

/**
 * return x^c mod n
 */
int power_mod(int x, int c, int n)
{
    int b = 0;
    int s = 1;
    int e = x;

    while (true)
    {
        /* code */
        b = c & 0x1;
        if (b == 1)
        {
            s *= e;
            s = s % n;
        }
        e *= e;
        e = e % n;

        c = c >> 1;
        if (c == 0)
        {
            break;
        }
    }

    return s;
}

int main(){
    int ret = power_mod(2, 10, 1023);
    std::cout << ret <<  std::endl;
    return 0;
}