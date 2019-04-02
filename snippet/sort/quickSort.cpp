

int partition(int *arr, int left, int right);
int quickSort(int *arr, int left, int right);

int quickSort(int *arr, int left, int right)
{
    if (right > left)
    {
        int mid = partition(arr, left, right);

        quickSort(arr, left, mid - 1);
        quickSort(arr, mid + 1, right);
    }
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
            }
        }
        else
        {
            if (arr[j] < x)
            {
                arr[i] = arr[j];
                i++;
            }
        }
    }

    arr[i] = x;

    return 0;
}
