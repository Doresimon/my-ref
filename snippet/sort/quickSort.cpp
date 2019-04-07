#include <iostream>

using namespace std;

int partition(int *arr, int left, int right);
int quickSort(int *arr, int left, int right);

int main()
{
    int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    quickSort(arr, 0, 9);

    std::cout << "[";
    for (auto var : arr)
    {
        std::cout << var << ", ";
    }
    std::cout << "]" << endl;

    return 0;
}

int partition(int *arr, int left, int right)
{
    int i = left;
    int j = right;

    int x = arr[i]; // choose arr[i]

    bool asc = false;

    while (i != j)
    {
        if (asc)
        {
            if (arr[i] > x)
            {
                arr[j] = arr[i];
                j--;
                asc = false;
            }
            else
            {
                i++;
            }
        }
        else
        {
            if (arr[j] < x)
            {
                arr[i] = arr[j];
                i++;
                asc = true;
            }
            else
            {
                j--;
            }
        }
    }

    arr[i] = x; // put x back

    return i;
}

int quickSort(int *arr, int left, int right)
{
    if (right > left)
    {
        int mid = partition(arr, left, right);

        quickSort(arr, left, mid - 1);
        quickSort(arr, mid + 1, right);
    }

    return 0;
}