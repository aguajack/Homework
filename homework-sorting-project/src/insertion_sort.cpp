#include "sorting.h"

#include <vector>

using namespace std;

bool isSorted(const vector<int>& arr)
{
    for (int i = 1; i < static_cast<int>(arr.size()); i++)
    {
        if (arr[i - 1] > arr[i])
        {
            return false;
        }
    }

    return true;
}

void insertionSort(vector<int>& arr)
{
    int n = static_cast<int>(arr.size());

    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
